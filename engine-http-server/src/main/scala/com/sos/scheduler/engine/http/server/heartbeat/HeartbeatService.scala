package com.sos.scheduler.engine.http.server.heartbeat

import akka.actor.ActorRefFactory
import com.sos.scheduler.engine.common.scalautil.{Logger, ScalaConcurrentHashMap}
import com.sos.scheduler.engine.common.sprayutils.Marshalling.marshalToHttpResponse
import com.sos.scheduler.engine.common.time.ScalaTime._
import com.sos.scheduler.engine.common.time.alarm.AlarmClock
import com.sos.scheduler.engine.http.client.heartbeat.HeartbeatRequestHeaders._
import com.sos.scheduler.engine.http.client.heartbeat.{HeartbeatId, HeartbeatResponseHeaders, HttpHeartbeatTiming}
import com.sos.scheduler.engine.http.server.heartbeat.HeartbeatService._
import java.time.{Duration, Instant}
import java.util.concurrent.atomic.AtomicReference
import javax.inject.Inject
import org.jetbrains.annotations.TestOnly
import scala.collection.immutable
import scala.concurrent._
import spray.http.StatusCodes.{Accepted, BadRequest}
import spray.http._
import spray.httpx.marshalling._
import spray.routing.Directives._
import spray.routing.Route

/**
  * @author Joacim Zschimmer
  */
final class HeartbeatService @Inject() (alarmClock: AlarmClock) {

  private val pendingOperations = new ScalaConcurrentHashMap[HeartbeatId, PendingOperation]()
  private var _pendingOperationsMaximum = 0  // Possibly not really thread-safe

  def startHeartbeat[A](
    onHeartbeat: () ⇒ Unit = () ⇒ {},
    @Deprecated @TestOnly onHeartbeatTimeout: Option[OnHeartbeatTimeout] = None)
    (operation: Option[Duration] ⇒ Future[A])
    (implicit marshaller: Marshaller[A], actorRefFactory: ActorRefFactory): Route =
  {
    import actorRefFactory.dispatcher
    headerValueByName(`X-JobScheduler-Heartbeat-Start`.name) { case `X-JobScheduler-Heartbeat-Start`.Value(timing) ⇒
      requestUri { uri ⇒
        val responseFuture = operation(Some(timing.timeout)) map marshalToHttpResponse
        val pendingOperation = new PendingOperation(uri, responseFuture, onHeartbeat, onHeartbeatTimeout)(actorRefFactory.dispatcher)
        startHeartbeatPeriod(pendingOperation, timing)
      }
    } ~
      onSuccess(operation(None)) { response ⇒ complete(response) }
  }

  def continueHeartbeat(implicit actorRefFactory: ActorRefFactory): Route =
    headerValueByName(`X-JobScheduler-Heartbeat-Continue`.name) { case `X-JobScheduler-Heartbeat-Continue`.Value(heartbeatId, times) ⇒
      requestEntityEmpty {
        pendingOperations.remove(heartbeatId) match {
          case None ⇒ complete(BadRequest, "Unknown heartbeat ID (HTTP request is too late?)")
          case Some(o) ⇒
            o.onHeartbeat()
            startHeartbeatPeriod(o, times)
        }
      } ~
        complete(BadRequest, "Heartbeat with entity?")
    }

  private def startHeartbeatPeriod(pendingOperation: PendingOperation, timing: HttpHeartbeatTiming)(implicit actorRefFactory: ActorRefFactory): Route = {
    import actorRefFactory.dispatcher
    val lastHeartbeatReceivedAt = Instant.now()
    alarmClock.delay(timing.period, name = pendingOperation.uri.toString) {
      val heartbeatId = HeartbeatId.generate()
      pendingOperations.insert(heartbeatId, pendingOperation)
      _pendingOperationsMaximum = _pendingOperationsMaximum max pendingOperations.size
      val oldPromise = pendingOperation.renewPromise()
      val heartbeatResponded = oldPromise trySuccess HttpResponse(Accepted, headers = HeartbeatResponseHeaders.`X-JobScheduler-Heartbeat`(heartbeatId) :: Nil)
      if (heartbeatResponded) {
        for (onHeartbeatTimeout ← pendingOperation.onHeartbeatTimeout) {
          alarmClock.delay(timing.timeout, name = pendingOperation.uri.toString) {
            for (o ← pendingOperations.remove(heartbeatId)) {
              logger.debug(s"No heartbeat after ${timing.period.pretty} for $pendingOperation")
              onHeartbeatTimeout(HeartbeatTimeout(heartbeatId, since = lastHeartbeatReceivedAt, timing, name = pendingOperation.uri.toString))
            }
          }
        }
      } else {
        pendingOperations -= heartbeatId
      }
    }
    onSuccess(pendingOperation.currentFuture) { response ⇒ complete(response) }
  }

  private[heartbeat] def pendingHeartbeatIds: immutable.Set[HeartbeatId] = pendingOperations.keys.toSet

  private[heartbeat] def pendingOperationsMaximum: Int = _pendingOperationsMaximum
}

object HeartbeatService {
  private val logger = Logger(getClass)

  private final class PendingOperation(
    val uri: Uri,
    responseFuture: Future[HttpResponse],
    val onHeartbeat: () ⇒ Unit,
    val onHeartbeatTimeout: Option[OnHeartbeatTimeout])
    (implicit ec: ExecutionContext)
  {
    private val currentPromiseRef = new AtomicReference(Promise[HttpResponse]())

    responseFuture onComplete { responseTry ⇒
      val completed = currentPromiseRef.get.tryComplete(responseTry)
      if (!completed) {  // Race condition: A new heartbeat period has begun. So we complete the new promise.
        currentPromiseRef.get.complete(responseTry)
      }
    }

    def renewPromise(): Promise[HttpResponse] = currentPromiseRef getAndSet Promise()

    def currentFuture = currentPromiseRef.get.future

    override def toString = s"PendingOperation($uri)"
  }

  type OnHeartbeatTimeout = HeartbeatTimeout ⇒ Unit
}
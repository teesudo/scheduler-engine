package com.sos.scheduler.engine.plugins.newwebservice.routes.agent

import akka.actor.ActorRefFactory
import com.sos.scheduler.engine.agent.client.AgentClient
import com.sos.scheduler.engine.client.api.ProcessClassClient
import com.sos.scheduler.engine.common.sprayutils.SprayJsonOrYamlSupport._
import com.sos.scheduler.engine.data.agent.AgentAddress
import com.sos.scheduler.engine.data.common.WebError
import com.sos.scheduler.engine.kernel.DirectSchedulerClient
import com.sos.scheduler.engine.plugins.newwebservice.html.HtmlDirectives._
import com.sos.scheduler.engine.plugins.newwebservice.html.WebServiceContext
import com.sos.scheduler.engine.plugins.newwebservice.routes.agent.AgentRoute._
import scala.concurrent.{ExecutionContext, Future}
import scala.util.{Failure, Success}
import spray.client.pipelining.Get
import spray.http.HttpHeaders.{Accept, `Cache-Control`}
import spray.http.StatusCodes.{BadRequest, Forbidden}
import spray.http.{HttpHeader, HttpRequest, HttpResponse, Uri}
import spray.httpx.UnsuccessfulResponseException
import spray.json.DefaultJsonProtocol._
import spray.routing.Directives._
import spray.routing.Route

/**
  * @author Joacim Zschimmer
  */
trait AgentRoute {
  protected def isKnownAgentUriFuture(uri: AgentAddress): Future[Boolean]
  protected def toAgentClient: AgentAddress ⇒ AgentClient
  protected def client: ProcessClassClient
  protected def webServiceContext: WebServiceContext
  protected implicit def actorRefFactory: ActorRefFactory
  protected implicit def executionContext: ExecutionContext

  final def agentRoute: Route =
    testSlash(webServiceContext) {
      get {
        rawPathPrefix(Slash) {
          pathEnd {
            dontCache {
              complete(client.agentUris map { _ map { _.toSeq.sorted }})
            }
          } ~
          extract(identity) { requestContext ⇒
            // The remainder of the URI is interpreted as the complete URI of an Agent
            val (agentUri, tailUri) = splitIntoAgentUriAndTail(requestContext.unmatchedPath, requestContext.request.uri.query)
            if (!isAllowedTailUri(tailUri))
              complete(Forbidden → WebError(s"Forbidden Agent URI: $tailUri"))
            else
              onSuccess(isKnownAgentUriFuture(agentUri)) {
                case false ⇒ complete(BadRequest → WebError("Unknown Agent"))
                case true ⇒ forwardTo(requestContext.request, toAgentClient(agentUri), tailUri)
              }
          }
        }
      }
    }

  private def forwardTo(request: HttpRequest, agentClient: AgentClient, tailUri: Uri): Route =
    onComplete(agentClient[HttpResponse](request.headers filter { o ⇒ isForwardableHeaderClass(o.getClass) }, Get(tailUri))) {
      case Success(response) ⇒
        complete(response)
      case Failure(e: UnsuccessfulResponseException) ⇒
        complete(BadRequest → ForwardingError(e.response.status.intValue, e.getMessage))
      case Failure(throwable) ⇒
        complete(BadRequest → WebError(throwable.toString))
    }
}

object AgentRoute {
  private val isForwardableHeaderClass = Set[Class[_ <: HttpHeader]](
    classOf[Accept],
    classOf[`Cache-Control`])

  private[agent] def splitIntoAgentUriAndTail(unmatchedPath: Uri.Path, query: Uri.Query): (AgentAddress, Uri) = {
    val agentRequestUri: Uri = Uri(unmatchedPath.toString)
    val Uri(scheme, authority, path, Uri.Query.Empty, None) = agentRequestUri
    val agentUri = AgentAddress.normalized(Uri(scheme, authority).toString)
    val tailUri = Uri(path = path, query = query)
    (agentUri, tailUri)
  }

  private[agent] def isAllowedTailUri(uri: Uri) =
    isAllowedPath(uri.path) && uri.query.isEmpty && uri.fragment.isEmpty

  private def isAllowedPath = Set(Uri.Path("/jobscheduler/agent/api"))
}
package com.sos.scheduler.engine.tests.jira.js993

import com.sos.scheduler.engine.common.system.Bitness._
import com.sos.scheduler.engine.data.folder.JobPath
import com.sos.scheduler.engine.data.job.TaskStartedEvent
import com.sos.scheduler.engine.data.log.ErrorLogEvent
import com.sos.scheduler.engine.eventbus.EventHandler
import com.sos.scheduler.engine.test.configuration.TestConfiguration
import com.sos.scheduler.engine.test.scala.ScalaSchedulerTest
import com.sos.scheduler.engine.test.scala.SchedulerTestImplicits._
import org.junit.runner.RunWith
import org.scalatest.FunSuite
import org.scalatest.Matchers._
import org.scalatest.junit.JUnitRunner

@RunWith(classOf[JUnitRunner])
final class JS993IT extends FunSuite with ScalaSchedulerTest {

  protected override lazy val testConfiguration = TestConfiguration(
    testClass = getClass,
    terminateOnError = bitness != Bits64)

  @volatile private var errorLogged = false

  List("spidermonkey", "javascript") foreach { language =>
    test(s"language=$language should work on 32bit and rejected on 64bit") {
      val jobPath = JobPath(s"/test-$language")
      controller.getEventBus.dispatchEvents()   // Ruft ggf. handle(ErrorLogEvent)
      bitness match {
        case Bits64 =>
          assert(errorLogged, "Error SCHEDULER-482 expected")
          intercept[Exception] { startJob(jobPath) }
        case Bits32 =>
          assert(!errorLogged, "Unexpected error SCHEDULER-482")
          val eventPipe = controller.newEventPipe()
          startJob(jobPath)
          eventPipe.nextWithCondition[TaskStartedEvent] { _.jobPath == jobPath }
      }
    }
  }

  @EventHandler def handle(e: ErrorLogEvent) {
    if (e.getLine contains "SCHEDULER-428") {    // SCHEDULER-428  Error when reading base file ...
      e.getLine should include ("SCHEDULER-482")  // SCHEDULER-482  Language 'javascript' is not supported on 64 bit
      errorLogged = true
    }
  }

  private def startJob(jobPath: JobPath) {
    scheduler executeXml <start_job job={jobPath.string}/>
  }
}
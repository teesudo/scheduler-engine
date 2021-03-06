package com.sos.scheduler.engine.agent.data

import com.sos.scheduler.engine.common.process.Processes.Pid
import com.sos.scheduler.engine.data.job.{JobPath, TaskId}
import java.nio.file.Paths
import org.junit.runner.RunWith
import org.scalatest.FreeSpec
import org.scalatest.junit.JUnitRunner

/**
  * @author Joacim Zschimmer
  */
@RunWith(classOf[JUnitRunner])
final class ProcessKillScriptTest extends FreeSpec {

  "toCommandArguments" in {
    val killScript = ProcessKillScript(Paths.get("KILL-SCRIPT"))
    assert(killScript.toCommandArguments(AgentTaskId(1, 2), None, JobPath("/JOB"), TaskId(123)) ==
      List("KILL-SCRIPT", "-kill-agent-task-id=1-2", "-master-task-id=123", "-job=/JOB"))
    assert(killScript.toCommandArguments(AgentTaskId(1, 2), Some(Pid(777)), JobPath("/JOB"), TaskId(123)) ==
      List("KILL-SCRIPT", "-kill-agent-task-id=1-2", "-pid=777", "-master-task-id=123", "-job=/JOB"))
  }
}

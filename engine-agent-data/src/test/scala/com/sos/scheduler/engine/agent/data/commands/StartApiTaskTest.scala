package com.sos.scheduler.engine.agent.data.commands

import org.junit.runner.RunWith
import org.scalatest.FreeSpec
import org.scalatest.junit.JUnitRunner
import spray.json._

/**
 * @author Joacim Zschimmer
 */
@RunWith(classOf[JUnitRunner])
final class StartApiTaskTest extends FreeSpec {

  "JSON" in {
    val obj = StartApiTask(
      javaOptions = "JAVA-OPTIONS",
      javaClasspath = "JAVA-CLASSPATH")
    val json = """{
      "$TYPE": "StartApiTask",
      "javaOptions": "JAVA-OPTIONS",
      "javaClasspath": "JAVA-CLASSPATH"
    }""".parseJson
    assert((obj: Command).toJson == json)   // Command serializer includes $TYPE
    assert(obj == json.convertTo[Command])
  }
}
package com.sos.scheduler.engine.common.scalautil.xmls

import com.sos.scheduler.engine.common.scalautil.xmls.RichScalaXML.RichElem
import org.junit.runner.RunWith
import org.scalatest.FreeSpec
import org.scalatest.Matchers._
import org.scalatest.junit.JUnitRunner

@RunWith(classOf[JUnitRunner])
class RichScalaXMLTest extends FreeSpec {

  "attributeText" in {
    val e = <a b="B"/>
    e.attributeText("b") should equal ("B")
    e.attributeText("x") should equal ("")
  }
}

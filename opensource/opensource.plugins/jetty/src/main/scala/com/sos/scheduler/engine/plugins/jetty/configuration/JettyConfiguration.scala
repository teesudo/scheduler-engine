package com.sos.scheduler.engine.plugins.jetty.configuration

import JettyConfiguration._
import com.sos.scheduler.engine.common.utils.FreeTcpPortFinder.findRandomFreeTcpPort
import com.sos.scheduler.engine.plugins.jetty.configuration.JettyConfiguration.WebAppContextConfiguration
import java.io.File
import java.net.URL
import org.eclipse.jetty.security.LoginService
import org.eclipse.jetty.server.Handler
import scala.collection.immutable

final case class JettyConfiguration(
  portOption: Option[TcpPortNumber] = None,
  contextPath: String = "",
  webAppContextConfigurationOption: Option[WebAppContextConfiguration] = None,
  jettyXMLURLOption: Option[URL] = None,
  accessLogFileOption: Option[File] = None,
  loginServiceOption: Option[LoginService] = None,
  handlers: immutable.Seq[Handler] = Nil
)

object JettyConfiguration {
  private val testPortRange = 40000 until 50000

  final case class WebAppContextConfiguration(
    resourceBaseURL: URL,
    webXMLFileOption: Option[File] = None)


  trait TcpPortNumber {
    val value: Int
  }

  object TcpPortNumber {
    def apply(o: Int) = new TcpPortNumber {
      lazy val value = o
    }

    def random() = new TcpPortNumber {
      lazy val value = findRandomFreeTcpPort(testPortRange)
    }
  }
}
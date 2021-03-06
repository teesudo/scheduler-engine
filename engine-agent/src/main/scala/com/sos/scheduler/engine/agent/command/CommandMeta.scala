package com.sos.scheduler.engine.agent.command

import com.sos.scheduler.engine.common.auth.User
import com.sos.scheduler.engine.common.soslicense.LicenseKeyBunch
import com.sos.scheduler.engine.data.session.SessionToken
import java.net.InetAddress

/**
 * @author Joacim Zschimmer
 */
final case class CommandMeta(
  user: User = User.Anonymous,
  clientIpOption: Option[InetAddress] = None,
  sessionTokenOption: Option[SessionToken] = None,
  licenseKeyBunch: LicenseKeyBunch = LicenseKeyBunch())

object CommandMeta {
  private val Empty = new CommandMeta

  def apply(): CommandMeta = Empty
}

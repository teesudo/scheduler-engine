package com.sos.scheduler.engine.common.sprayutils.web.auth

import com.sos.scheduler.engine.base.generic.SecretString
import com.sos.scheduler.engine.common.auth.{EncodedPasswordValidator, UserAndPassword}
import com.sos.scheduler.engine.common.configutils.Configs.ConvertibleConfig
import com.sos.scheduler.engine.common.sprayutils.SprayUtils._
import com.sos.scheduler.engine.common.sprayutils.web.auth.GateKeeper._
import com.sos.scheduler.engine.common.time.ScalaTime._
import com.typesafe.config.Config
import java.time.Duration
import scala.concurrent.ExecutionContext
import spray.routing.Directives._
import spray.routing._
import spray.routing.authentication._

/**
  * @author Joacim Zschimmer
  */
final class GateKeeper(configuraton: Configuration, isUnsecuredHttp: Boolean = false)(implicit ec: ExecutionContext) {

  import configuraton.{getIsPublic, httpIsPublic, invalidAuthenticationDelay, isValidUserAndPassword, realm}

  val allows: Directive0 =
    mapInnerRoute { inner ⇒
      if (isUnsecuredHttp && httpIsPublic)
        inner
      else
        handleRejections(failIfCredentialsRejected(invalidAuthenticationDelay)) {
          authenticate(BasicAuth(new SimpleUserPassAuthenticator(isValidUserAndPassword), realm = realm)) { _ ⇒
            inner
          }
        } ~
        passIf(getIsPublic) {  // After authenticate, to return its error
          (get | head) {
            inner
          }
        }
    }
}

object GateKeeper {
  final case class Configuration(
    /** Basic authentication realm */
    realm: String,
    isValidUserAndPassword: UserAndPassword ⇒ Boolean,
    /** To hamper an attack */
    invalidAuthenticationDelay: Duration = 1.s,
    /** HTTP is open (assuming local access only) */
    httpIsPublic: Boolean = false,
    /** HTTP GET is open */
    getIsPublic: Boolean = false)

  object Configuration {
    def fromSubConfig(config: Config) = new Configuration(
      realm = config.getString("realm"),
      isValidUserAndPassword = new EncodedPasswordValidator(config.getConfig("users").optionAs[SecretString]),
      invalidAuthenticationDelay = config.getDuration("invalid-authentication-delay"),
      httpIsPublic = config.getBoolean("http-is-public"),
      getIsPublic = config.getBoolean("get-is-public")
    )
  }
}
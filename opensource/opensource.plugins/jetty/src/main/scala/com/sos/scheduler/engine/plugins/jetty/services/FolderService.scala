package com.sos.scheduler.engine.plugins.jetty.services

import com.sos.scheduler.engine.cplusplus.runtime.CppException
import com.sos.scheduler.engine.data.folder.AbsolutePath
import com.sos.scheduler.engine.kernel.folder.FolderSubsystem
import com.sos.scheduler.engine.plugins.jetty.services.WebServices.noCache
import javax.inject.Inject
import javax.servlet.http.HttpServletRequest
import javax.ws.rs._
import javax.ws.rs.core.Response.Status.NOT_FOUND
import javax.ws.rs.core._
import scala.collection.JavaConversions._

@Path("folder")
class FolderService @Inject()(folderSubsystem: FolderSubsystem) {
  @GET
  @Produces(Array(MediaType.APPLICATION_JSON))
  def get(@QueryParam("folder") @DefaultValue("") folderPathString: String,
          @QueryParam("type") @DefaultValue("") typeName: String,
          @Context request: HttpServletRequest, @Context u: UriInfo) = {
    val folderPath = AbsolutePath.of(folderPathString)
    val v = view(folderPath, typeName, u)
    Response.ok(v).cacheControl(noCache).build()
  }

  private def view(folderPath: AbsolutePath, typeName: String, u: UriInfo) = {
    try FolderView(folderSubsystem.names(folderPath, typeName), folderPath, typeName, u.getBaseUri)
    catch {
      case x: CppException if x.getCode == "SCHEDULER-161" => throw new WebApplicationException(x, NOT_FOUND)
    }
  }
}
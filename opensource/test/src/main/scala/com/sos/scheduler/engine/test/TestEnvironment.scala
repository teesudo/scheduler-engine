package com.sos.scheduler.engine.test

import TestEnvironment._
import _root_.scala.collection.immutable
import _root_.scala.collection.mutable
import com.google.common.base.Strings.nullToEmpty
import com.google.common.io.{Files ⇒ GuavaFiles}
import com.sos.scheduler.engine.common.scalautil.SideEffect._
import com.sos.scheduler.engine.common.system.Files.{removeDirectoryRecursivly, removeDirectoryContentRecursivly, makeDirectories, makeDirectory}
import com.sos.scheduler.engine.common.system.OperatingSystem
import com.sos.scheduler.engine.common.system.OperatingSystem.operatingSystem
import com.sos.scheduler.engine.data.filebased.TypedPath
import com.sos.scheduler.engine.data.job.JobPath
import com.sos.scheduler.engine.data.order.OrderKey
import com.sos.scheduler.engine.data.scheduler.SchedulerId
import com.sos.scheduler.engine.kernel.scheduler.SchedulerConstants.schedulerEncoding
import com.sos.scheduler.engine.kernel.util.ResourcePath
import com.sos.scheduler.engine.main.{CppBinaries, CppBinary}
import com.sos.scheduler.engine.test.configuration.TestConfiguration
import java.io.File
import java.nio.file.Files

/** Build the environment for the scheduler binary. */
final class TestEnvironment(
    resourcePath: ResourcePath,
    val directory: File,
    nameMap: Map[String, String],
    fileTransformer: ResourceToFileTransformer)
extends AutoCloseable {

  val configDirectory = new File(directory, configSubdir)
  val liveDirectory = configDirectory
  val logDirectory = directory
  val schedulerLog = new File(logDirectory, "scheduler.log")
  val databaseDirectory = directory
  val deletableTemporaryDirectories = mutable.Buffer[File]()
  private var isPrepared = false

  def close(): Unit = {
    deletableTemporaryDirectories foreach removeDirectoryRecursivly
  }

  private[test] def prepare() {
    if (!isPrepared) {
      prepareTemporaryConfigurationDirectory()
      isPrepared = true
    }
  }

  private def prepareTemporaryConfigurationDirectory() {
    makeDirectories(directory)
    removeDirectoryContentRecursivly(directory)
    makeDirectories(configDirectory)
    makeDirectories(logDirectory)
    TestEnvironmentFiles.copy(resourcePath, configDirectory, nameMap, fileTransformer)
  }

  private[test] def standardArgs(cppBinaries: CppBinaries, logCategories: String): immutable.Iterable[String] =
    List(
      cppBinaries.file(CppBinary.exeFilename).getPath,
      s"-job-java-options=$jobJavaOptions",
      s"-id=$schedulerId",
      s"-sos.ini=$sosIniFile",
      s"-ini=$iniFile",
      s"-log-level=debug9",
      s"-log-dir=${logDirectory.getPath}",
      s"-log=$logCategories> ${schedulerLog.getPath}") ++
    (if (OperatingSystem.isUnix) Some("-env=" + libraryPathEnv(cppBinaries.directory)) else None) ++
    Some(configDirectory.getPath)

  def sosIniFile =
    new File(configDirectory, "sos.ini").getAbsoluteFile

  def iniFile =
    new File(configDirectory, "factory.ini").getAbsoluteFile

  def fileFromPath(p: TypedPath) =
    p.file(configDirectory)

  /** @return Pfad der Auftragsprotokolldatei für einfache OrderKey */
  def orderLogFile(orderKey: OrderKey) =
    new File(logDirectory, s"order.${orderKey.jobChainPath.withoutStartingSlash}.${orderKey.id.string}.log")

  def taskLogFileString(jobPath: JobPath): String =
    GuavaFiles.toString(taskLogFile(jobPath), schedulerEncoding)

  /** @return Pfad einer Task-Potokolldatei für einfachen JobPath. */
  def taskLogFile(jobPath: JobPath) =
    new File(logDirectory, s"task.${jobPath.withoutStartingSlash}.log")

  def subdirectory(name: String) =
    new File(directory, name) sideEffect makeDirectory

  /** @return a temporary directory for use in &lt;file_order_source>.
    *         Under Windows, which allows not more than 250 character in a file path (the order log file),
    *         the directory is placed in the original Windows temporary directory as denoted by the environment variable TEMP. */
  def newFileOrderSourceDirectory(): File =
    (if (OperatingSystem.isWindows) sys.env.get("TEMP") else None) match {
      case Some(t) ⇒
        Files.createTempDirectory(new File(t).toPath, "sos-").toFile
          .sideEffect { o ⇒ deletableTemporaryDirectories += o }
      case None ⇒
        Files.createTempDirectory(null).toFile  // Directory based in java.io.tmpdir, which is modified by Maven pom.xml (target)
    }
}


object TestEnvironment {
  val schedulerId = new SchedulerId("test")
  private val jobJavaOptions = "-Xms5m -Xmx10m"
  private val configSubdir = "config"

  def apply(testConfiguration: TestConfiguration, directory: File) =
    new TestEnvironment(
      resourcePath = new ResourcePath(testConfiguration.testPackage getOrElse testConfiguration.testClass.getPackage),
      directory = directory,
      nameMap = testConfiguration.resourceNameMap.toMap,
      fileTransformer = testConfiguration.resourceToFileTransformer getOrElse StandardResourceToFileTransformer.singleton)

  /** Damit der Scheduler die libspidermonkey.so aus seinem Programmverzeichnis laden kann. */
  private def libraryPathEnv(directory: File): String = {
    val varName = operatingSystem.getDynamicLibraryEnvironmentVariableName
    val previous = nullToEmpty(System.getenv(varName))
    s"$varName="+ OperatingSystem.concatFileAndPathChain(directory, previous)
  }
}
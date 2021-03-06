﻿namespace sos.spooler
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.IO;
    using System.Linq;
    using System.Management.Automation;
    using System.Management.Automation.Runspaces;
    using System.Security;
    using System.Text;

    public class PowershellAdapter : ScriptAdapter
    {
        #region Constants and Fields

        private const string PROFILE_FILE_NAME = "JobScheduler.PowerShell_profile.ps1";
        private const string CONFIG_DIR = "config";
        private PowershellAdapterPSHost host;
        private bool isShellMode;
        private Runspace runspace;
        private PowershellSpoolerParams spoolerParams;

        #endregion

        #region Constructors and Destructors

        public PowershellAdapter(
            Log contextLog, Task contextTask, Job contextJob, Spooler contextSpooler, String contextStdErrLogLevel, String scriptContent)
            : base(contextLog, contextTask, contextJob, contextSpooler, contextStdErrLogLevel, scriptContent)
        {
            ParseScript();
            spoolerParams = new PowershellSpoolerParams(spooler_task, spooler, IsOrderJob, isShellMode);

            host = new PowershellAdapterPSHost(spooler_task, spooler_log);
            runspace = RunspaceFactory.CreateRunspace(host);
            runspace.Open();
            runspace.SessionStateProxy.SetVariable("spooler_log", spooler_log);
            runspace.SessionStateProxy.SetVariable("spooler_task", spooler_task);
            runspace.SessionStateProxy.SetVariable("spooler_job", spooler_job);
            runspace.SessionStateProxy.SetVariable("spooler", spooler);
            runspace.SessionStateProxy.SetVariable("spooler_params", spoolerParams);

            InvokeDollarProfile();
        }

        #endregion

        #region Public Methods

        public override void spooler_close()
        {
            if (isShellMode)
            {
                return;
            }

            try
            {
                InvokeFunction("spooler_close");
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_close", ex.ErrorRecord));
            }
        }

        public override void spooler_exit()
        {
            try
            {
                if (isShellMode)
                {
                }
                else
                {
                    InvokeFunction("spooler_exit");
                }
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_exit", ex.ErrorRecord));
            }
            finally
            {
                Close();
            }
        }

        public override bool spooler_init()
        {
            if (isShellMode)
            {
                return true;
            }

            try
            {
                InitializeScript(false);
                return InvokeFunction("spooler_init", true);
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_init", ex.ErrorRecord));
            }
        }

        public override void spooler_on_error()
        {
            if (isShellMode)
            {
                return;
            }
            try
            {
                InvokeFunction("spooler_on_error");
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_on_error", ex.ErrorRecord));
            }
        }

        public override void spooler_on_success()
        {
            if (isShellMode)
            {
                return;
            }
            try
            {
                InvokeFunction("spooler_on_success");
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_on_success", ex.ErrorRecord));
            }
        }

        public override bool spooler_open()
        {
            if (isShellMode)
            {
                return true;
            }

            try
            {
                return InvokeFunction("spooler_open", true);
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_open", ex.ErrorRecord));
            }
        }

        public override bool spooler_process()
        {
            try
            {
                if (isShellMode)
                {
                    spoolerParams.SetEnvVars();
                    InitializeScript(true);
                    HandleGlobalLastExitCode(true);
                    if (host.ExitCode != 0)
                    {
                        return false;
                    }
                    if (ExitOnStdError())
                    {
                        return false;
                    }
                    return IsOrderJob;
                }

                return InvokeFunction("spooler_process", true);
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage(isShellMode ? "" : "spooler_process", ex.ErrorRecord));
            }
        }

        public override bool spooler_process_after(bool spoolerProcessResult)
        {
            try
            {
                return InvokeFunction("spooler_process_after", true, spoolerProcessResult);
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_process_after", ex.ErrorRecord));
            }
        }

        public override bool spooler_process_before()
        {
            try
            {
                return InvokeFunction("spooler_process_before", true);
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_process_before", ex.ErrorRecord));
            }
        }

        public override void spooler_task_after()
        {
            try
            {
                InvokeFunction("spooler_task_after");
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_task_after", ex.ErrorRecord));
            }
            finally
            {
                Close();
            }
        }

        public override bool spooler_task_before()
        {
            try
            {
                InitializeScript(false);
                return InvokeFunction("spooler_task_before", true);
            }
            catch (RuntimeException ex)
            {
                throw new Exception(GetErrorMessage("spooler_task_before", ex.ErrorRecord));
            }
        }

        #endregion

        #region Methods

        #region Profile

        private PSObject GetDollarProfile(string allUsersAllHosts, string allUsersCurrentHost, string currentUserAllHosts, string currentUserCurrentHost)
        {
            PSObject returnValue = new PSObject(currentUserCurrentHost);
            returnValue.Properties.Add(new PSNoteProperty("AllUsersAllHosts", allUsersAllHosts));
            returnValue.Properties.Add(new PSNoteProperty("AllUsersCurrentHost", allUsersCurrentHost));
            returnValue.Properties.Add(new PSNoteProperty("CurrentUserAllHosts", currentUserAllHosts));
            returnValue.Properties.Add(new PSNoteProperty("CurrentUserCurrentHost", currentUserCurrentHost));
            return returnValue;
        }

        private bool IsSystemIdentity()
        {
            bool isSystem = false;
            try
            {
                using (var identity = System.Security.Principal.WindowsIdentity.GetCurrent())
                {
                    isSystem = identity.IsSystem;
                }
            }
            catch (SecurityException ex)
            {
                spooler_log.info(String.Format("[IsSystemIdentity][SecurityException]{0}", ex.ToString()));
                var userprofile = Environment.GetEnvironmentVariable("USERPROFILE");
                if (!string.IsNullOrEmpty(userprofile) && userprofile.EndsWith("systemprofile"))
                {
                    isSystem = true;
                }
            }
            return isSystem;
        }

        private void InvokeDollarProfile()
        {
            try
            {
                var allUsersAllHosts = "";
                var currentUserAllHosts = "";

                var dataDir = Environment.GetEnvironmentVariable("SCHEDULER_DATA");
                if (!string.IsNullOrEmpty(dataDir))
                {
                    var configDir = Path.Combine(dataDir, CONFIG_DIR);
                    var configDirAllUsers = Path.Combine(configDir, "powershell");

                    allUsersAllHosts = Path.Combine(configDirAllUsers, PROFILE_FILE_NAME);
                    if (IsSystemIdentity())
                    {
                        currentUserAllHosts = allUsersAllHosts;
                    }
                    else
                    {
                        var configDirCurrentUser = Path.Combine(configDir, "Users", Environment.GetEnvironmentVariable("USERNAME"), "powershell");
                        currentUserAllHosts = Path.Combine(configDirCurrentUser, PROFILE_FILE_NAME);
                    }
                }
                var allUsersCurrentHost = allUsersAllHosts;
                var currentUserCurrentHost = currentUserAllHosts;

                runspace.SessionStateProxy.SetVariable("profile", GetDollarProfile(allUsersAllHosts, allUsersCurrentHost, currentUserAllHosts, currentUserCurrentHost));
                InvokeProfiles(allUsersAllHosts, currentUserAllHosts);
            }
            catch (Exception ex)
            {
                spooler_log.warn(String.Format("[InvokeDollarProfile]{0}", ex.ToString()));
            }
        }

        private void InvokeProfiles(string allUsersAllHosts, string currentUserAllHosts)
        {
            if (allUsersAllHosts.Length > 0)
            {
                InvokeProfile(allUsersAllHosts);
            }
            if (!currentUserAllHosts.Equals(allUsersAllHosts))
            {
                InvokeProfile(currentUserAllHosts);
            }
        }

        private void InvokeProfile(string path)
        {
            try
            {
                if (File.Exists(path))
                {
                    InvokeFile(false, path);
                }
            }
            catch (RuntimeException ex)
            {
                spooler_log.warn(GetErrorMessage("InvokeProfile", ex.ErrorRecord));
            }
        }
        #endregion

        private string GetErrorMessage(String functionName, ErrorRecord errorRecord)
        {
            var sb = new StringBuilder();
            if (!String.IsNullOrEmpty(functionName))
            {
                sb.Append(String.Format("[{0}] ", functionName));
            }
            sb.Append(errorRecord.ToString());
            if (errorRecord.InvocationInfo != null)
            {
                sb.Append(errorRecord.InvocationInfo.PositionMessage);
            }
            return sb.ToString();
        }

        private bool ExitOnStdError(string functionName = null)
        {

            if (IsStdErrLogLevel)
            {
                var ui = (PowershellAdapterPSHostUserInterface)host.UI;
                if (ui.HasStdErr)
                {
                    if (isShellMode)
                    {
                        return true;
                    }
                    else
                    {
                        if (!String.IsNullOrEmpty(ui.LastFunctionWithStdErr)
                            && ui.LastFunctionWithStdErr.Equals(functionName))
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        private bool GetReturnValue(string functionName, string result)
        {
            if (!String.IsNullOrEmpty(host.LastFunctionWithExitCode)
                    && host.LastFunctionWithExitCode.Equals(functionName))
            {
                return false;
            }

            if (ExitOnStdError(functionName))
            {
                return false;
            }

            bool returnValue;
            if (!Boolean.TryParse(result, out returnValue))
            {
                returnValue = functionName.Equals("spooler_process") && !IsOrderJob ? false : true;
            }

            return returnValue;
        }

        private int GetGlobalLastExitCode(bool useLocalScope)
        {
            var lastExitCode = InvokeCommand(useLocalScope, "$Global:LastExitCode").FirstOrDefault();
            var exitCode = 0;
            if (lastExitCode != null)
            {
                try
                {
                    exitCode = Int32.Parse(lastExitCode.ToString());
                }
                catch (Exception)
                {
                }
            }
            return exitCode;
        }

        private void Close()
        {
            runspace.Close();
            runspace.Dispose();

            runspace = null;
            host = null;
            spoolerParams = null;
        }

        private void HandleGlobalLastExitCode(bool useLocalScope, String functionName = "")
        {
            int exitCode = GetGlobalLastExitCode(useLocalScope);
            if (exitCode != 0)
            {
                host.SetShouldExit(exitCode);
            }
            host.LastExitCode = exitCode;
        }

        private void InitializeScript(bool useLocalScope)
        {
            InvokeScript(useLocalScope, Script);
        }

        private IEnumerable<PSObject> InvokeCommand(bool useLocalScope, String command)
        {
            Collection<PSObject> result;
            using (var pipeline = runspace.CreatePipeline())
            {
                pipeline.Commands.AddScript(command, useLocalScope);
                result = pipeline.Invoke();
            }
            return result;
        }

        private IEnumerable<PSObject> InvokeFile(bool useLocalScope, String path)
        {
            Collection<PSObject> result;
            using (var pipeline = runspace.CreatePipeline())
            {
                pipeline.Commands.Add(new Command(File.ReadAllText(path), true, useLocalScope));
                pipeline.Commands.Add("Out-Default");
                pipeline.Commands[0].MergeMyResults(PipelineResultTypes.Error, PipelineResultTypes.Output);
                result = pipeline.Invoke();
            }
            return result;
        }

        private bool InvokeFunction(string functionName, bool doReturn = false, bool? param = null)
        {
            ((PowershellAdapterPSHostUserInterface)host.UI).CurrentFunctionName = functionName;

            var functionParams = "";
            if (param.HasValue)
            {
                functionParams = "($" + param.Value + ")";
            }

            var command = String.Format(
                "if($function:{0}){{ {1}{2} }}",
                functionName,
                functionName,
                functionParams);

            var result = InvokeScript(false, command);
            HandleGlobalLastExitCode(false, functionName);

            var returnValue = true;
            if (doReturn)
            {
                returnValue = GetReturnValue(functionName, result);
            }

            return returnValue;
        }

        private string InvokeScript(bool useLocalScope, String command)
        {
            using (var pipeline = runspace.CreatePipeline())
            {
                pipeline.Commands.AddScript(command, useLocalScope);
                pipeline.Commands.Add("Out-Default");
                pipeline.Commands[0].MergeMyResults(PipelineResultTypes.Error, PipelineResultTypes.Output);
                pipeline.Invoke();
            }
            return ((PowershellAdapterPSHostUserInterface)host.UI).LastInfoMessage;
        }

        private void ParseScript()
        {
            if (string.IsNullOrEmpty(Script))
            {
                throw new Exception("Script is null or empty.");
            }

            Collection<PSParseError> parseErrors;
            var tokens = PSParser.Tokenize(Script, out parseErrors);
            var apiFunction =
                tokens.FirstOrDefault(
                    t => t.Type.Equals(PSTokenType.CommandArgument) &&
                         (t.Content.Equals("spooler_init")
                          || t.Content.Equals("spooler_open")
                          || t.Content.Equals("spooler_process")
                          || t.Content.Equals("spooler_close")
                          || t.Content.Equals("spooler_on_success")
                          || t.Content.Equals("spooler_on_error")
                          || t.Content.Equals("spooler_exit")));
            isShellMode = apiFunction == null;
        }

        #endregion
    }
}

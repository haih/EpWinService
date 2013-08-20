/*! 
WinServiceTypeInterpreter for the EpWinServiceCLI

The MIT License (MIT)

Copyright (c) 2013 Woong Gyu La <juhgiyo@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "stdafx.h"
#include "epWinServiceTypeInterpreter.h"

ProcessObjectCommandPacketType WinServiceTypeInterpreter::GetProcessObjectCommandPacketType(CString subCommand)
{
	ProcessObjectCommandPacketType subCommandType=PROCESS_OBJECT_COMMAND_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("Start"))==0)
	{
		subCommandType= PROCESS_OBJECT_COMMAND_PACKET_TYPE_START;
	}
	else if(subCommand.Compare(_T("End"))==0)
	{
		subCommandType= PROCESS_OBJECT_COMMAND_PACKET_TYPE_END;
	}
	else if(subCommand.Compare(_T("Bounce"))==0)
	{
		subCommandType= PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE;
	}
	else if(subCommand.Compare(_T("CustomCommand"))==0)
	{
		subCommandType= PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS;
	}
	else if(subCommand.Compare(_T("RunCommand"))==0)
	{
		subCommandType= PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND;
	}
	else if(subCommand.Compare(_T("Deploy"))==0)
	{
		subCommandType= PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY;
	}
	return subCommandType;
}
ProcessObjectInfoGetPacketType WinServiceTypeInterpreter::GetProcessObjectInfoGetPacketType(CString subCommand)
{
	ProcessObjectInfoGetPacketType subCommandType=PROCESS_OBJECT_INFO_GET_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("CommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PreProcessCommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PostProcessCommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("CustomProcessCommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PreProcessWaitTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("PostProcessWaitTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("DomainName"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME;
	}
	else if(subCommand.Compare(_T("UserName"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERNAME;
	}
	else if(subCommand.Compare(_T("UserPassword"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("DelayStartTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME;
	}
	else if(subCommand.Compare(_T("DelayPauseEndTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME;
	}
	else if(subCommand.Compare(_T("IsRestart"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART;
	}
	else if(subCommand.Compare(_T("IsImpersonate"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE;
	}
	else if(subCommand.Compare(_T("IsUserInterface"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE;
	}
	else if(subCommand.Compare(_T("Status"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_STATUS;
	}

	else if(subCommand.Compare(_T("DeployRepositoryURL"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL;
	}
	else if(subCommand.Compare(_T("DeployLocalPath"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH;
	}
	else if(subCommand.Compare(_T("DeployUserName"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME;
	}
	else if(subCommand.Compare(_T("DeployUserPassword"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("DeployCurrentRevision"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION;
	}
	else if(subCommand.Compare(_T("DeployLatestRevision"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION;
	}

	else if(subCommand.Compare(_T("All"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_GET_PACKET_TYPE_ALL;
	}
	return subCommandType;
}
ProcessObjectInfoSetPacketType WinServiceTypeInterpreter::GetProcessObjectInfoSetPacketType(CString subCommand)
{
	ProcessObjectInfoSetPacketType subCommandType=PROCESS_OBJECT_INFO_SET_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("CommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PreProcessCommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PostProcessCommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("CustomProcessCommandLine"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PreProcessWaitTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("PostProcessWaitTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("DomainName"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME;
	}
	else if(subCommand.Compare(_T("UserName"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERNAME;
	}
	else if(subCommand.Compare(_T("UserPassword"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("DelayStartTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME;
	}
	else if(subCommand.Compare(_T("DelayPauseEndTime"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME;
	}
	else if(subCommand.Compare(_T("IsRestart"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART;
	}
	else if(subCommand.Compare(_T("IsImpersonate"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE;
	}
	else if(subCommand.Compare(_T("IsUserInterface"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE;
	}
	else if(subCommand.Compare(_T("DeployRepositoryURL"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL;
	}
	else if(subCommand.Compare(_T("DeployLocalPath"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH;
	}
	else if(subCommand.Compare(_T("DeployUserName"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME;
	}
	else if(subCommand.Compare(_T("DeployUserPassword"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD;
	}

	else if(subCommand.Compare(_T("All"))==0)
	{
		subCommandType= PROCESS_OBJECT_INFO_SET_PACKET_TYPE_ALL;
	}
	return subCommandType;
}
ServiceObjectCommandPacketType WinServiceTypeInterpreter::GetServiceObjectCommandPacketType(CString subCommand)
{
	ServiceObjectCommandPacketType subCommandType=SERVICE_OBJECT_COMMAND_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("Start"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_START;
	}
	else if(subCommand.Compare(_T("End"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_END;
	}
	else if(subCommand.Compare(_T("Pause"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_PAUSE;
	}
	else if(subCommand.Compare(_T("Continue"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_CONTINUE;
	}
	else if(subCommand.Compare(_T("Bounce"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE;
	}
	else if(subCommand.Compare(_T("CustomCommand"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS;
	}
	else if(subCommand.Compare(_T("RunCommand"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND;
	}
	else if(subCommand.Compare(_T("Deploy"))==0)
	{
		subCommandType= SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY;
	}
	return subCommandType;
}
ServiceObjectInfoGetPacketType WinServiceTypeInterpreter::GetServiceObjectInfoGetPacketType(CString subCommand)
{
	ServiceObjectInfoGetPacketType subCommandType=SERVICE_OBJECT_INFO_GET_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("ServiceName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_SERVICENAME;
	}
	else if(subCommand.Compare(_T("PreProcessCommandLine"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PostProcessCommandLine"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("CustomProcessCommandLine"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PreProcessWaitTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("PostProcessWaitTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("DomainName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME;
	}
	else if(subCommand.Compare(_T("UserName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERNAME;
	}
	else if(subCommand.Compare(_T("UserPassword"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("DelayStartTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME;
	}
	else if(subCommand.Compare(_T("DelayPauseEndTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME;
	}
	else if(subCommand.Compare(_T("IsRestart"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART;
	}
	else if(subCommand.Compare(_T("IsImpersonate"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE;
	}
	else if(subCommand.Compare(_T("IsUserInterface"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE;
	}
	else if(subCommand.Compare(_T("Status"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_STATUS;
	}

	else if(subCommand.Compare(_T("DeployRepositoryURL"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL;
	}
	else if(subCommand.Compare(_T("DeployLocalPath"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH;
	}
	else if(subCommand.Compare(_T("DeployUserName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME;
	}
	else if(subCommand.Compare(_T("DeployUserPassword"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("DeployCurrentRevision"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION;
	}
	else if(subCommand.Compare(_T("DeployLatestRevision"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION;
	}

	else if(subCommand.Compare(_T("All"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_GET_PACKET_TYPE_ALL;
	}
	return subCommandType;
}

ServiceObjectInfoSetPacketType WinServiceTypeInterpreter::GetServiceObjectInfoSetPacketType(CString subCommand)
{
	ServiceObjectInfoSetPacketType subCommandType=SERVICE_OBJECT_INFO_SET_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("ServiceName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_SERVICENAME;
	}
	else if(subCommand.Compare(_T("PreProcessCommandLine"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PostProcessCommandLine"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("CustomProcessCommandLine"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("PreProcessWaitTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("PostProcessWaitTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME;
	}
	else if(subCommand.Compare(_T("DomainName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME;
	}
	else if(subCommand.Compare(_T("UserName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERNAME;
	}
	else if(subCommand.Compare(_T("UserPassword"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("DelayStartTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME;
	}
	else if(subCommand.Compare(_T("DelayPauseEndTime"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME;
	}
	else if(subCommand.Compare(_T("IsRestart"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART;
	}
	else if(subCommand.Compare(_T("IsImpersonate"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE;
	}
	else if(subCommand.Compare(_T("IsUserInterface"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE;
	}

	else if(subCommand.Compare(_T("DeployRepositoryURL"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL;
	}
	else if(subCommand.Compare(_T("DeployLocalPath"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH;
	}
	else if(subCommand.Compare(_T("DeployUserName"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME;
	}
	else if(subCommand.Compare(_T("DeployUserPassword"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD;
	}

	else if(subCommand.Compare(_T("All"))==0)
	{
		subCommandType= SERVICE_OBJECT_INFO_SET_PACKET_TYPE_ALL;
	}
	return subCommandType;
}

MainServiceCommandPacketType WinServiceTypeInterpreter::GetMainServiceCommandPacketType(CString subCommand)
{
	MainServiceCommandPacketType subCommandType=MAIN_SERVICE_COMMAND_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("CustomCommand"))==0)
	{
		subCommandType= MAIN_SERVICE_COMMAND_PACKET_TYPE_CUSTOM_PROCESS;
	}
	else if(subCommand.Compare(_T("RunCommand"))==0)
	{
		subCommandType= MAIN_SERVICE_COMMAND_PACKET_TYPE_RUN_COMMAND;
	}
	return subCommandType;
}
MainServiceInfoGetPacketType WinServiceTypeInterpreter::GetMainServiceInfoGetPacketType(CString subCommand)
{
	MainServiceInfoGetPacketType subCommandType=MAIN_SERVICE_INFO_GET_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("ServiceName"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_SERVICE_NAME;
	}
	else if(subCommand.Compare(_T("DomainName"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_DOMAIN_NAME;
	}
	else if(subCommand.Compare(_T("UserName"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERNAME;
	}
	else if(subCommand.Compare(_T("UserPassword"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERPASSWORD;
	}
	else if(subCommand.Compare(_T("Dependency"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_DEPENDENCY;
	}
	else if(subCommand.Compare(_T("ProcessObjNum"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_PROCESSES;
	}
	else if(subCommand.Compare(_T("ServiceObjNum"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_SERVICES;
	}
	else if(subCommand.Compare(_T("CheckProcessObjInterval"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKPROCESSINTERVAL;
	}
	else if(subCommand.Compare(_T("CheckServiceObjInterval"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKSERVICEINTERVAL;
	}
	else if(subCommand.Compare(_T("CustomProcessCommandLine"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE;
	}
	else if(subCommand.Compare(_T("All"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_GET_PACKET_TYPE_ALL;
	}
	return subCommandType;
}

MainServiceInfoSetPacketType WinServiceTypeInterpreter::GetMainServiceInfoSetPacketType(CString subCommand)
{
	MainServiceInfoSetPacketType subCommandType=MAIN_SERVICE_INFO_SET_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("CheckProcessObjInterval"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL;
	}
	else if(subCommand.Compare(_T("CheckServiceObjInterval"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL;
	}
	else if(subCommand.Compare(_T("CustomProcessCommandLine"))==0)
	{
		subCommandType= MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE;
	}
	return subCommandType;
}

ServiceCommandPacketType WinServiceTypeInterpreter::GetServiceCommandPacketType(CString subCommand)
{
	ServiceCommandPacketType subCommandType=SERVICE_COMMAND_PACKET_TYPE_NULL;
	if(subCommand.Compare(_T("Start"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_START;
	}
	else if(subCommand.Compare(_T("Continue"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_CONTINUE;
	}
	else if(subCommand.Compare(_T("Stop"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_STOP;
	}
	else if(subCommand.Compare(_T("Pause"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_PAUSE;
	}
	else if(subCommand.Compare(_T("Control"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_CONTROL;
	}
	else if(subCommand.Compare(_T("Install"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_INSTALL;
	}
	else if(subCommand.Compare(_T("Uninstall"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_UNINSTALL;
	}
	else if(subCommand.Compare(_T("Edit"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_EDIT;
	}
	else if(subCommand.Compare(_T("GetStatus"))==0)
	{
		subCommandType= SERVICE_COMMAND_PACKET_TYPE_GET_STATUS;
	}
	return subCommandType;
}












CString WinServiceTypeInterpreter::GetPacketProcessStatusString(PacketProcessStatus status)
{
	CString retString=_T("");
	switch(status)
	{
	case PACKET_PROCESS_STATUS_SUCCESS:
		retString= _T("Success");
		break;
	case PACKET_PROCESS_STATUS_FAIL:
		retString= _T("Fail");
		break;
	case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
		retString= _T("Object Index Out of Range");
		break;
	case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
		retString= _T("Argument Error");
		break;
	case PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR:
		retString= _T("Service Handle Error");
		break;
	}
	return retString;
}

CString WinServiceTypeInterpreter::GetRetrieveStatusString(RetrieveStatus status)
{
	CString retString=_T("");
	switch(status)
	{
	case RETRIEVE_STATUS_SUCCESS:
		retString= _T("Success");
		break;
	case RETRIEVE_STATUS_FAIL:
		retString= _T("Retrieve Fail");
		break;
	case RETRIEVE_STATUS_FAIL_RESULT:
		retString= _T("Retrieve Result Fail");
		break;
	case RETRIEVE_STATUS_FAIL_OBJECTIDX:
		retString= _T("Retrieve Object Index Fail");
		break;
	case RETRIEVE_STATUS_FAIL_ARGUMENT:
		retString= _T("Retrieve Argument Fail");
		break;
	}
	return retString;
}

CString WinServiceTypeInterpreter::GetReturnTypeString(ReturnType type)
{
	CString retString=_T("");
	switch(type)
	{
	case RETURN_TYPE_VOID:
		retString= _T("Void");
		break;
	case RETURN_TYPE_BOOL:
		retString= _T("Bool");
		break;
	case RETURN_TYPE_INT:
		retString= _T("Int");
		break;
	case RETURN_TYPE_UINT:
		retString= _T("UInt");
		break;
	case RETURN_TYPE_STRING:
		retString= _T("String");
		break;
	case RETURN_TYPE_PROCESSOBJ_INFO:
		retString= _T("ProcessObjectInfo");
		break;
	case RETURN_TYPE_SERVICEOBJ_INFO:
		retString= _T("ServiceObjectInfo");
		break;
	case RETURN_TYPE_SERVICE_STATUS:
		retString= _T("ServiceStatus");
		break;
	case RETURN_TYPE_SERVICE_STATUS_PROCESS:
		retString= _T("ServiceStatusProcess");
		break;
	case RETURN_TYPE_PROCESS_STATUS_TYPE:
		retString= _T("ProcessStatusType");
		break;
	case RETURN_TYPE_SERVICE_STATUS_TYPE:
		retString= _T("ServiceStatusType");
		break;
	case RETURN_TYPE_SERVICE_HANDLE_ERROR_INFO:
		retString= _T("ServiceHandleErrorInfo");
		break;
	case RETURN_TYPE_DEPLOY_INFO:
		retString= _T("DeployInfo");
		break;
	case RETURN_TYPE_OJBECT_START_STATUS:
		retString= _T("ObjectStartStatus");
		break;
	}
	return retString;
}
CString WinServiceTypeInterpreter::getMainServiceCommandTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		retString =_T("CustomProcess");
		break;
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_RUN_COMMAND:
		retString =_T("RunCommand");
		break;
	}
	return retString;

}

CString WinServiceTypeInterpreter::getMainServiceInfoGetTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_SERVICE_NAME:
		retString =_T("ServiceName");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DOMAIN_NAME:
		retString =_T("DomainName");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERNAME:
		retString =_T("UserName");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERPASSWORD:
		retString =_T("UserPassword");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DEPENDENCY:
		retString =_T("Dependency");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_PROCESSES:
		retString =_T("ProcessObjNum");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_SERVICES:
		retString =_T("ServiceObjNum");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		retString =_T("CheckProcessObjInterval");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKSERVICEINTERVAL:
		retString =_T("CheckServiceObjInterval");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retString =_T("CustomProcessCommandLine");
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_ALL:
		retString =_T("All");
		break;
	}
	return retString;

}

CString WinServiceTypeInterpreter::getMainServiceInfoSetTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		retString =_T("CheckProcessObjInterval");
		break;
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
		retString =_T("CheckServiceObjInterval");
		break;
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retString =_T("CustomProcessCommandLine");
		break;
	}
	return retString;

}


CString WinServiceTypeInterpreter::getProcessObjectCommandTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
		retString =_T("Start");
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_END:
		retString =_T("End");
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
		retString =_T("Bounce");
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		retString =_T("CustomCommand");
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
		retString =_T("RunCommand");
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
		retString =_T("Deploy");
		break;
	}
	return retString;

}

CString WinServiceTypeInterpreter::getProcessObjectInfoGetTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_COMMANDLINE:
		retString =_T("CommandLine");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		retString =_T("PreProcessCommandLine");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		retString =_T("PostProcessCommandLine");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retString =_T("CustomProcessCommandLine");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		retString =_T("PreProcessWaitTime");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		retString =_T("PostProcessWaitTime");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
		retString =_T("DomainName");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
		retString =_T("UserName");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
		retString =_T("UserPassword");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
		retString =_T("DelayStartTime");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		retString =_T("DelayPauseEndTime");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
		retString =_T("IsRestart");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
		retString =_T("IsImpersonate");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
		retString =_T("IsUserInterface");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_STATUS:
		retString =_T("Status");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
		retString =_T("DeployRepositoryURL");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
		retString =_T("DeployLocalPath");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
		retString =_T("DeployUserName");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
		retString =_T("DeployUserPassword");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
		retString =_T("DeployCurrentRevision");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:
		retString =_T("DeployLatestRevision");
		break;
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_ALL:
		retString =_T("All");
		break;

	}
	return retString;

}

CString WinServiceTypeInterpreter::getProcessObjectInfoSetTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{

	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_COMMANDLINE:
		retString =_T("CommandLine");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		retString =_T("PreProcessCommandLine");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		retString =_T("PostProcessCommandLine");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retString =_T("CustomProcessCommandLine");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		retString =_T("PreProcessWaitTime");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		retString =_T("PostProcessWaitTime");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME:
		retString =_T("DomainName");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERNAME:
		retString =_T("UserName");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD:
		retString =_T("UserPassword");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME:
		retString =_T("DelayStartTime");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		retString =_T("DelayPauseEndTime");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART:
		retString =_T("IsRestart");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE:
		retString =_T("IsImpersonate");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE:
		retString =_T("IsUserInterface");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL:
		retString =_T("DeployRepositoryURL");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
		retString =_T("DeployLocalPath");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME:
		retString =_T("DeployUserName");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD:
		retString =_T("DeployUserPassword");
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_ALL:
		retString =_T("All");
		break;


	}
	return retString;

}

CString WinServiceTypeInterpreter::getServiceObjectCommandTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_START:
		retString =_T("Start");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_END:
		retString =_T("End");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_PAUSE:
		retString =_T("Pause");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CONTINUE:
		retString =_T("Continue");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
		retString =_T("Bounce");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		retString =_T("CustomCommand");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
		retString =_T("RunCommand");
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
		retString =_T("Deploy");
		break;

	}
	return retString;

}
CString WinServiceTypeInterpreter::getServiceObjectInfoGetTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_SERVICENAME:
		retString =_T("ServiceName");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		retString =_T("PreProcessCommandLine");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		retString =_T("PostProcessCommandLine");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retString =_T("CustomProcessCommandLine");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		retString =_T("PreProcessWaitTime");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		retString =_T("PostProcessWaitTime");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
		retString =_T("DomainName");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
		retString =_T("UserName");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
		retString =_T("UserPassword");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
		retString =_T("DelayStartTime");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		retString =_T("DelayPauseEndTime");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
		retString =_T("IsRestart");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
		retString =_T("IsImpersonate");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
		retString =_T("IsUserInterface");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_STATUS:
		retString =_T("Status");
		break;

	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
		retString =_T("DeployRepositoryURL");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
		retString =_T("DeployLocalPath");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
		retString =_T("DeployUserName");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
		retString =_T("DeployUserPassword");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
		retString =_T("DeployCurrentRevision");
		break;
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:
		retString =_T("DeployLatestRevision");
		break;

	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_ALL:
		retString =_T("All");
		break;

	}
	return retString;

}

CString WinServiceTypeInterpreter::getServiceObjectInfoSetTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{

	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_SERVICENAME:
		retString =_T("ServiceName");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		retString =_T("PreProcessCommandLine");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		retString =_T("PostProcessCommandLine");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retString =_T("CustomProcessCommandLine");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		retString =_T("PreProcessWaitTime");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		retString =_T("PostProcessWaitTime");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME:
		retString =_T("DomainName");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERNAME:
		retString =_T("UserName");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD:
		retString =_T("UserPassword");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME:
		retString =_T("DelayStartTime");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		retString =_T("DelayPauseEndTime");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART:
		retString =_T("IsRestart");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE:
		retString =_T("IsImpersonate");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE:
		retString =_T("IsUserInterface");
		break;

	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL:
		retString =_T("DeployRepositoryURL");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
		retString =_T("DeployLocalPath");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME:
		retString =_T("DeployUserName");
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD:
		retString =_T("DeployUserPassword");
		break;

	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_ALL:
		retString =_T("All");
		break;


	}
	return retString;

}
CString WinServiceTypeInterpreter::getServiceCommandTypeString(unsigned int subcommand)
{
	CString retString=_T("");
	switch(subcommand)
	{
	case SERVICE_COMMAND_PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_START:
		retString =_T("Start");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_CONTINUE:
		retString =_T("Continue");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_STOP:
		retString =_T("Stop");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_PAUSE:
		retString =_T("Pause");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_CONTROL:
		retString =_T("Control");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_INSTALL:
		retString =_T("Install");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_UNINSTALL:
		retString =_T("Uninstall");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_EDIT:
		retString =_T("Edit");
		break;
	case SERVICE_COMMAND_PACKET_TYPE_GET_STATUS:
		retString =_T("GetStatus");
		break;

	}
	return retString;

}

CString WinServiceTypeInterpreter::GetSubcommandTypeString(PacketType type, unsigned int subcommand)
{
	CString retString=_T("");
	switch(type)
	{
	case PACKET_TYPE_NULL:
		retString =_T("");
		break;
	case PACKET_TYPE_MAIN_SERVICE_COMMAND:
		retString =getMainServiceCommandTypeString(subcommand);
		break;
	case PACKET_TYPE_MAIN_SERVICE_INFO_GET:
		retString =getMainServiceInfoGetTypeString(subcommand);
		break;
	case PACKET_TYPE_MAIN_SERVICE_INFO_SET:
		retString =getMainServiceInfoSetTypeString(subcommand);
		break;
	case PACKET_TYPE_PROCESS_OBJECT_COMMAND:
		retString =getProcessObjectCommandTypeString(subcommand);
		break;
	case PACKET_TYPE_PROCESS_OBJECT_INFO_GET:
		retString =getProcessObjectInfoGetTypeString(subcommand);
		break;
	case PACKET_TYPE_PROCESS_OBJECT_INFO_SET:
		retString =getProcessObjectInfoSetTypeString(subcommand);
		break;
	case PACKET_TYPE_SERVICE_OBJECT_COMMAND:
		retString =getServiceObjectCommandTypeString(subcommand);
		break;
	case PACKET_TYPE_SERVICE_OBJECT_INFO_GET:
		retString =getServiceObjectInfoGetTypeString(subcommand);
		break;
	case PACKET_TYPE_SERVICE_OBJECT_INFO_SET:
		retString =getServiceObjectInfoSetTypeString(subcommand);
		break;
	case PACKET_TYPE_SERVICE_COMMAND:
		retString =getServiceCommandTypeString(subcommand);
		break;
	}
	return retString;
}
CString WinServiceTypeInterpreter::GetCommandTypeString(PacketType type)
{
	CString retString=_T("");
	switch(type)
	{
	case PACKET_TYPE_NULL:
		retString =_T("NULL");
		break;
	case PACKET_TYPE_MAIN_SERVICE_COMMAND:
		retString =_T("MainServiceCommand");
		break;
	case PACKET_TYPE_MAIN_SERVICE_INFO_GET:
		retString =_T("MainServiceInfoGet");
		break;
	case PACKET_TYPE_MAIN_SERVICE_INFO_SET:
		retString =_T("MainServiceInfoSet");
		break;
	case PACKET_TYPE_PROCESS_OBJECT_COMMAND:
		retString =_T("ProcessObjectCommand");
		break;
	case PACKET_TYPE_PROCESS_OBJECT_INFO_GET:
		retString =_T("ProcessObjectInfoGet");
		break;
	case PACKET_TYPE_PROCESS_OBJECT_INFO_SET:
		retString =_T("ProcessObjectInfoSet");
		break;
	case PACKET_TYPE_SERVICE_OBJECT_COMMAND:
		retString =_T("ServiceObjectCommand");
		break;
	case PACKET_TYPE_SERVICE_OBJECT_INFO_GET:
		retString =_T("ServiceObjectInfoGet");
		break;
	case PACKET_TYPE_SERVICE_OBJECT_INFO_SET:
		retString =_T("ServiceObjectInfoSet");
		break;
	case PACKET_TYPE_SERVICE_COMMAND:
		retString =_T("ServiceCommand");
		break;
	}
	return retString;
}
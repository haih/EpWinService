/*! 
WinServiceReturnXMLBuilder for the EpWinServiceCLI
Copyright (C) 2013  Woong Gyu La <juhgiyo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "epWinServiceReturnXMLBuilder.h"
#include "epWinServiceTypeInterpreter.h"

void WinServiceReturnXMLBuilder::addServiceStatusProcess(const WinServiceResultInfo & resultInfo,XNode *root)
{
	SERVICE_STATUS_PROCESS info = resultInfo.ToServiceStatusProcess();
	TCHAR itotBuffer[65];
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwServiceType,itotBuffer,10);
	root->AppendChild(_T("serviceType"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwCurrentState,itotBuffer,10);
	root->AppendChild(_T("currentState"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwControlsAccepted,itotBuffer,10);
	root->AppendChild(_T("controlsAccepted"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwWin32ExitCode,itotBuffer,10);
	root->AppendChild(_T("win32ExitCode"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwServiceSpecificExitCode,itotBuffer,10);
	root->AppendChild(_T("serviceSpecificExitCode"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwCheckPoint,itotBuffer,10);
	root->AppendChild(_T("checkPoint"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwWaitHint,itotBuffer,10);
	root->AppendChild(_T("waitHint"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwProcessId,itotBuffer,10);
	root->AppendChild(_T("processId"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwServiceFlags,itotBuffer,10);
	root->AppendChild(_T("serviceFlags"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);
}

void WinServiceReturnXMLBuilder::addServiceStatus(const WinServiceResultInfo & resultInfo,XNode *root)
{
	SERVICE_STATUS info = resultInfo.ToServiceStatus();
	TCHAR itotBuffer[65];
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwServiceType,itotBuffer,10);
	root->AppendChild(_T("serviceType"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwCurrentState,itotBuffer,10);
	root->AppendChild(_T("currentState"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwControlsAccepted,itotBuffer,10);
	root->AppendChild(_T("controlsAccepted"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwWin32ExitCode,itotBuffer,10);
	root->AppendChild(_T("win32ExitCode"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwServiceSpecificExitCode,itotBuffer,10);
	root->AppendChild(_T("serviceSpecificExitCode"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwCheckPoint,itotBuffer,10);
	root->AppendChild(_T("checkPoint"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.dwWaitHint,itotBuffer,10);
	root->AppendChild(_T("waitHint"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);
}

void WinServiceReturnXMLBuilder::addServiceHandleErrorInfo(const WinServiceResultInfo & resultInfo,XNode *root)
{
	ServiceHandleErrorInfo info = resultInfo.ToServiceHandleErrorInfo();
	TCHAR itotBuffer[65];
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	switch(info.m_serviceHandleError)
	{
	case SERVICE_HANDLER_ERROR_SUCCESS:
		root->AppendChild(_T("serviceHandleError"),_T("Success"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to open SCManager"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to open the service"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_STARTSERVICE:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to start the service"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_CREATESERVICE:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to create the service"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_DELETESERVICE:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to delete the service"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to control the service"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_CHANGESERVICECONFIG:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Failed to change the service configuration"));
		break;
	case SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME:
		root->AppendChild(_T("serviceHandleError"),_T("ERROR: Invalid service name"));
		break;
	}
	_itot(info.m_lastErrorCode,itotBuffer,10);
	root->AppendChild(_T("lastErrorCode"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);
}

void WinServiceReturnXMLBuilder::addServiceObjInfo(const WinServiceResultInfo & resultInfo,XNode *root)
{
	ServiceObjInfo info = resultInfo.ToServiceObjInfo();
	TCHAR itotBuffer[65];
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);
	switch(info.m_serviceStatusType)
	{
	case SERVICE_STATUS_TYPE_RUNNING:
		root->AppendChild(_T("serviceStatusType"),_T("Running"));
		break;
	case SERVICE_STATUS_TYPE_PAUSE_PENDING:
		root->AppendChild(_T("serviceStatusType"),_T("Pending"));
		break;
	case SERVICE_STATUS_TYPE_PAUSED:
		root->AppendChild(_T("serviceStatusType"),_T("Paused"));
		break;
	case SERVICE_STATUS_TYPE_CONTINUE_PENDING:
		root->AppendChild(_T("serviceStatusType"),_T("Continue Pending"));
		break;
	case SERVICE_STATUS_TYPE_START_PENDING:
		root->AppendChild(_T("serviceStatusType"),_T("Start Pending"));
		break;
	case SERVICE_STATUS_TYPE_STOP_PENDING:
		root->AppendChild(_T("serviceStatusType"),_T("Stop Pending"));
		break;
	case SERVICE_STATUS_TYPE_STOPPED:
		root->AppendChild(_T("serviceStatusType"),_T("Stopped"));
		break;
	case SERVICE_STATUS_TYPE_UNKNOWN:
		root->AppendChild(_T("serviceStatusType"),_T("Unknown"));
		break;
	}
	root->AppendChild(_T("serviceName"),info.m_serviceName.c_str());
	root->AppendChild(_T("preProcessCommandLine"),info.m_preProcessCommandLine.c_str());
	root->AppendChild(_T("postProcessCommandLine"),info.m_postProcessCommandLine.c_str());
	root->AppendChild(_T("customProcessCommandLine"),info.m_customProcessCommandLine.c_str());

	_itot(info.m_preProcessWaitTime,itotBuffer,10);
	root->AppendChild(_T("preProcessWaitTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.m_postProcessWaitTime,itotBuffer,10);
	root->AppendChild(_T("postProcessWaitTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	root->AppendChild(_T("domainName"),info.m_domainName.c_str());
	root->AppendChild(_T("userName"),info.m_userName.c_str());

	_itot(info.m_delayStartTime,itotBuffer,10);
	root->AppendChild(_T("delayStartTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.m_delayPauseEndTime,itotBuffer,10);
	root->AppendChild(_T("delayPauseEndTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	if(info.m_isRestart)
		root->AppendChild(_T("isRestart"),_T("true"));
	else
		root->AppendChild(_T("isRestart"),_T("false"));

	if(info.m_isImpersonate)
		root->AppendChild(_T("isImpersonate"),_T("true"));
	else
		root->AppendChild(_T("isImpersonate"),_T("false"));

	if(info.m_isUserInterface)
		root->AppendChild(_T("isUserInterface"),_T("true"));
	else
		root->AppendChild(_T("isUserInterface"),_T("false"));
}

void WinServiceReturnXMLBuilder::addProcessObjInfo(const WinServiceResultInfo & resultInfo,XNode *root)
{
	ProcessObjInfo info = resultInfo.ToProcessObjInfo();
	TCHAR itotBuffer[65];
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);
	switch(info.m_processStatusType)
	{
	case PROCESS_STATUS_TYPE_UNKNOWN:
		root->AppendChild(_T("processStatusType"),_T("Unknown"));
		break; 
	case PROCESS_STATUS_TYPE_RUNNING:
		root->AppendChild(_T("processStatusType"),_T("Running"));
		break;
	case PROCESS_STATUS_TYPE_STOPPED:
		root->AppendChild(_T("processStatusType"),_T("Stopped"));
		break;
	}
	root->AppendChild(_T("commandLine"),info.m_commandLine.c_str());
	root->AppendChild(_T("preProcessCommandLine"),info.m_preProcessCommandLine.c_str());
	root->AppendChild(_T("postProcessCommandLine"),info.m_postProcessCommandLine.c_str());
	root->AppendChild(_T("customProcessCommandLine"),info.m_customProcessCommandLine.c_str());

	_itot(info.m_preProcessWaitTime,itotBuffer,10);
	root->AppendChild(_T("preProcessWaitTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.m_postProcessWaitTime,itotBuffer,10);
	root->AppendChild(_T("postProcessWaitTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	root->AppendChild(_T("domainName"),info.m_domainName.c_str());
	root->AppendChild(_T("userName"),info.m_userName.c_str());

	_itot(info.m_delayStartTime,itotBuffer,10);
	root->AppendChild(_T("delayStartTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	_itot(info.m_delayPauseEndTime,itotBuffer,10);
	root->AppendChild(_T("delayPauseEndTime"),itotBuffer);
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);

	if(info.m_isRestart)
		root->AppendChild(_T("isRestart"),_T("true"));
	else
		root->AppendChild(_T("isRestart"),_T("false"));

	if(info.m_isImpersonate)
		root->AppendChild(_T("isImpersonate"),_T("true"));
	else
		root->AppendChild(_T("isImpersonate"),_T("false"));

	if(info.m_isUserInterface)
		root->AppendChild(_T("isUserInterface"),_T("true"));
	else
		root->AppendChild(_T("isUserInterface"),_T("false"));
}
void WinServiceReturnXMLBuilder::addReturnValue(const WinServiceResultInfo & resultInfo,XNode *root)
{
	TCHAR itotBuffer[65];
	System::Memset(itotBuffer,0,sizeof(TCHAR)*65);
	switch(resultInfo.GetReturnType())
	{
	case RETURN_TYPE_VOID:
		break;
	case RETURN_TYPE_BOOL:
		if(resultInfo.ToBoolean())
			root->AppendChild(_T("value"),_T("true"));
		else
			root->AppendChild(_T("value"),_T("false"));
		break;
	case RETURN_TYPE_INT:
		_itot(resultInfo.ToInt(),itotBuffer,10);
		root->AppendChild(_T("value"),itotBuffer);
		break;
	case RETURN_TYPE_UINT:
		_itot(resultInfo.ToInt(),itotBuffer,10);
		root->AppendChild(_T("value"),itotBuffer);
		break;
	case RETURN_TYPE_STRING:
		root->AppendChild(_T("value"),resultInfo.ToString().c_str());
		break;
	case RETURN_TYPE_PROCESS_STATUS_TYPE:
		switch(resultInfo.ToProcessStatusType())
		{
		case PROCESS_STATUS_TYPE_UNKNOWN:
			root->AppendChild(_T("value"),_T("Unknown"));
			break;
		case PROCESS_STATUS_TYPE_RUNNING:
			root->AppendChild(_T("value"),_T("Running"));
			break;
		case PROCESS_STATUS_TYPE_STOPPED:
			root->AppendChild(_T("value"),_T("Stopped"));
			break;
		}
		
		break;
	case RETURN_TYPE_SERVICE_STATUS_TYPE:
		switch(resultInfo.ToServiceStatusType())
		{

		case SERVICE_STATUS_TYPE_RUNNING:
			root->AppendChild(_T("value"),_T("Running"));
			break;
		case SERVICE_STATUS_TYPE_PAUSE_PENDING:
			root->AppendChild(_T("value"),_T("Pending"));
			break;
		case SERVICE_STATUS_TYPE_PAUSED:
			root->AppendChild(_T("value"),_T("Paused"));
			break;
		case SERVICE_STATUS_TYPE_CONTINUE_PENDING:
			root->AppendChild(_T("value"),_T("Continue Pending"));
			break;
		case SERVICE_STATUS_TYPE_START_PENDING:
			root->AppendChild(_T("value"),_T("Start Pending"));
			break;
		case SERVICE_STATUS_TYPE_STOP_PENDING:
			root->AppendChild(_T("value"),_T("Stop Pending"));
			break;
		case SERVICE_STATUS_TYPE_STOPPED:
			root->AppendChild(_T("value"),_T("Stopped"));
			break;
		case SERVICE_STATUS_TYPE_UNKNOWN:
			root->AppendChild(_T("value"),_T("Unknown"));
			break;
		}
		break;
	case RETURN_TYPE_PROCESSOBJ_INFO:
		addProcessObjInfo(resultInfo,root);
		break;
	case RETURN_TYPE_SERVICEOBJ_INFO:
		addServiceObjInfo(resultInfo,root);
		break;
	case RETURN_TYPE_SERVICE_STATUS:
		addServiceStatus(resultInfo,root);
		break;
	case RETURN_TYPE_SERVICE_STATUS_PROCESS:
		addServiceStatusProcess(resultInfo,root);
		break;
	case RETURN_TYPE_SERVICE_HANDLE_ERROR_INFO:
		addServiceHandleErrorInfo(resultInfo,root);
		break;
	}
}
bool WinServiceReturnXMLBuilder::BuildResultXML(const WinServiceResult & result,XMLFile retXMLFile)
{
	XNode *resultListNode=retXMLFile.AppendChild(_T("resultList"),_T(""));
	TCHAR buffer[65];
	if(resultListNode)
	{
		for(unsigned int resultIdx=0;resultIdx<result.GetResultCount();resultIdx++)
		{

			System::Memset(buffer,0,sizeof(TCHAR)*65);
			_itot(resultIdx,buffer,10);
			XNode *resultNode=resultListNode->AppendChild(_T("resultIndex"),buffer);

			const WinServiceResultInfo &info=result.GetAt(resultIdx);

			PacketProcessStatus packetProcessStatus=info.GetPacketProcessStatus();
			PacketType packetType=info.GetPacketType();
			unsigned int subPacketType=info.GetSubPacketType();
			RetrieveStatus retrieveStatus=info.GetRetrieveStatus();
			ReturnType retType=info.GetReturnType();

			resultNode->AppendChild(_T("command"),WinServiceTypeInterpreter::GetCommandTypeString(packetType).GetString());
			resultNode->AppendChild(_T("subcommand"),WinServiceTypeInterpreter::GetSubcommandTypeString(packetType,subPacketType).GetString());
			resultNode->AppendChild(_T("packetProcessStatus"),WinServiceTypeInterpreter::GetPacketProcessStatusString(packetProcessStatus).GetString());
			resultNode->AppendChild(_T("retrieveStatus"),WinServiceTypeInterpreter::GetRetrieveStatusString(retrieveStatus).GetString());
			XNode *retTypeNode=resultNode->AppendChild(_T("returnType"),WinServiceTypeInterpreter::GetReturnTypeString(retType).GetString());
			addReturnValue(info,retTypeNode);
			
		}
		return true;

	}
	return false;

}
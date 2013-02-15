/*! 
ServiceObject for the EpWinService
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
#include "epServiceObject.h"
#include "epLogWriter.h"
#include "epServiceDefines.h"
#include "epServiceHandler.h"
#include "epServiceProperties.h"

ServiceObject::ServiceObject(unsigned int serviceIndex):BaseManagementObject(MANAGEMENT_OBJECT_TYPE_SERVICE,serviceIndex)
{

	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("ServiceName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_serviceName=textBuffer;
	m_serviceName.Trim();
	
	m_isUserStopped=false;

	EP_DELETE[] textBuffer;
}

ServiceObject::~ServiceObject()
{

}



bool ServiceObject::Start()
{
	LockObj lock(&m_baseObjLock);
	m_isUserStopped=false;
	SERVICE_STATUS status;
	DWORD retCode;
	if(SERVICE_HANDLER_INSTANCE.ControlService(m_serviceName.GetString(),SERVICE_CONTROL_CODE_INTERROGATE,status,retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		if(status.dwCurrentState==SERVICE_STATUS_TYPE_RUNNING)
			return true;
	}
	else
		return false;
	//Pre-Process
	preProcess();
	if(SERVICE_HANDLER_INSTANCE.StartService(m_serviceName.GetString(),retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		::Sleep(m_delayStartTime);
		return true;
	}
	return false;
}

void ServiceObject::Stop()
{
	LockObj lock(&m_baseObjLock);
	DWORD retCode;
	SERVICE_HANDLER_INSTANCE.StopService(m_serviceName.GetString(),retCode);
	::Sleep(m_delayPauseEndTime>0?m_delayPauseEndTime:50);
}

void ServiceObject::Pause()
{
	DWORD retCode;
	if(SERVICE_HANDLER_INSTANCE.PauseService(m_serviceName.GetString(),retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
		::Sleep(m_delayPauseEndTime>0?m_delayPauseEndTime:50);
}

void ServiceObject::Continue()
{

	DWORD retCode;
	if(SERVICE_HANDLER_INSTANCE.ContinueService(m_serviceName.GetString(),retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		::Sleep(m_delayStartTime);
	}
}

bool ServiceObject::IsStarted()
{
	LockObj lock(&m_baseObjLock);
	SERVICE_STATUS status;
	DWORD retCode;
	if(SERVICE_HANDLER_INSTANCE.ControlService(m_serviceName.GetString(),SERVICE_CONTROL_CODE_INTERROGATE,status,retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		if(status.dwCurrentState==SERVICE_STATUS_TYPE_STOPPED)
			return false;
	}
	return true;
}

void ServiceObject::Reset()
{
	LockObj lock(&m_baseObjLock);
}

ServiceStatusType ServiceObject::GetStatus()
{
	LockObj lock(&m_baseObjLock);
	SERVICE_STATUS status;
	DWORD retCode;
	if(SERVICE_HANDLER_INSTANCE.ControlService(m_serviceName.GetString(),SERVICE_CONTROL_CODE_INTERROGATE,status,retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		return (ServiceStatusType)status.dwCurrentState;
	}
	return SERVICE_STATUS_TYPE_UNKNOWN;
}

void ServiceObject::CustomProcess(int waitTimeInMilliSec)
{
	LockObj lock(&m_baseObjLock);

	for(int listTrav=0;listTrav<m_customProcessCommandLineList.size();listTrav++)
	{
		executeCommand(m_customProcessCommandLineList.at(listTrav),listTrav,waitTimeInMilliSec,EXECUTE_COMMAND_TYPE_CUSTOMPROCESS);
	}


}

void ServiceObject::RunCommand(CString command, int waitTimeInMilliSec)
{
	LockObj lock(&m_baseObjLock);

	vector<CString> cmdList;
	BaseManagementObject::ParseCommand(command,cmdList);

	for(int listTrav=0;listTrav<cmdList.size();listTrav++)
	{
		executeCommand(cmdList.at(listTrav),listTrav,waitTimeInMilliSec,EXECUTE_COMMAND_TYPE_RUNCOMMAND);
	}
}



CString ServiceObject::GetServiceName()
{
	LockObj lock(&m_baseObjLock);
	return m_serviceName;

}
void ServiceObject::SetServiceName(CString cmd)
{
	LockObj lock(&m_baseObjLock);
	m_serviceName=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("ServiceName"),m_serviceName.GetString(),m_iniFileName.GetString());
}

bool ServiceObject::GetIsUserStopped()
{
	LockObj lock(&m_baseObjLock);
	return m_isUserStopped;

}
void ServiceObject::SetIsUserStopped(bool isUserStopped)
{
	LockObj lock(&m_baseObjLock);
	m_isUserStopped=isUserStopped;

}

void ServiceObject::replaceCommandArgument(CString &cmd)
{
	if(cmd.Find(_T("%n"))>=0)
		cmd.Replace(_T("%n"),m_serviceName.GetString());
	if(cmd.Find(_T("%N"))>=0)
		cmd.Replace(_T("%N"),m_serviceName.GetString());

	BaseManagementObject::replaceCommandArgument(cmd);
}
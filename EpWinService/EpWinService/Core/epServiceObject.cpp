/*! 
ServiceObject for the EpWinService

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
	m_serviceName=m_serviceName.Trim();
	
	m_isUserStopped=false;

	EP_DELETE[] textBuffer;
}

ServiceObject::~ServiceObject()
{

}



ObjectStartStatus ServiceObject::start()
{
	m_isUserStopped=false;
	SERVICE_STATUS status;
	DWORD retCode;
	if(SERVICE_HANDLER_INSTANCE.ControlService(m_serviceName.GetString(),SERVICE_CONTROL_CODE_INTERROGATE,status,retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		if(status.dwCurrentState==SERVICE_STATUS_TYPE_RUNNING)
			return OBJECT_START_STATUS_FAILED_ALREADY_STARTED;
	}
	else if(retCode!=1062)
		return OBJECT_START_STATUS_FAILED;
	//Pre-Process
	preProcess();
	if(SERVICE_HANDLER_INSTANCE.StartService(m_serviceName.GetString(),retCode)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		::Sleep(m_delayStartTime);
		return OBJECT_START_STATUS_SUCCESS;
	}
	return OBJECT_START_STATUS_FAILED;
}

void ServiceObject::stop()
{
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
	if(SERVICE_HANDLER_INSTANCE.ControlService(m_serviceName.GetString(),SERVICE_CONTROL_CODE_INTERROGATE,status,retCode,false)==SERVICE_HANDLER_ERROR_SUCCESS)
	{
		if(status.dwCurrentState==SERVICE_STATUS_TYPE_STOPPED)
			return false;
		return true;
	}
	else
		return false;
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
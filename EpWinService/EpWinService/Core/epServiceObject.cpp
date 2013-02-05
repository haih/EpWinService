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

	TCHAR *textBuffer=new TCHAR[MAX_STRING_LENGTH];

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("ServiceName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_serviceName=textBuffer;
	m_serviceName.Trim();
	
	m_isUserStopped=false;

	delete[] textBuffer;
}

ServiceObject::~ServiceObject()
{

}



bool ServiceObject::Start()
{
	LockObj lock(&m_lock);
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
	LockObj lock(&m_lock);
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
	LockObj lock(&m_lock);
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
	LockObj lock(&m_lock);
}

ServiceStatusType ServiceObject::GetStatus()
{
	LockObj lock(&m_lock);
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
	LockObj lock(&m_lock);
	CString cmd=_T("");

	for(int listTrav=0;listTrav<m_customProcessCommandLineList.size();listTrav++)
	{
		cmd=m_customProcessCommandLineList.at(listTrav);
		if(cmd.Find(_T("%n"))>=0)
			cmd.Replace(_T("%n"),m_serviceName.GetString());
		if(cmd.Find(_T("%N"))>=0)
			cmd.Replace(_T("%N"),m_serviceName.GetString());

		// start a process with given index
		STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,_T(""),NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
		PROCESS_INFORMATION	pProcInfo;
		if(m_isUserInterface)
			startUpInfo.wShowWindow = SW_SHOW;
		else
			startUpInfo.wShowWindow = SW_HIDE;
		startUpInfo.lpDesktop = NULL;

		// set the correct desktop for the process to be started
		if(m_isImpersonate==false)
		{

			// create the process
			if(CreateProcess(NULL, const_cast<wchar_t*>( cmd.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
			{
				WaitForSingleObject(pProcInfo.hProcess,waitTimeInMilliSec);
				continue;
			}
			else
			{
				TCHAR pTemp[256];
				long nError = GetLastError();

				_stprintf(pTemp,_T("Failed to start custom-process program(%d) '%s', error code = %d"),listTrav, cmd.GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
		}
		else
		{
			HANDLE hToken = NULL;
			if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
			{
				if(CreateProcessAsUser(hToken,NULL,const_cast<wchar_t*>(cmd.GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&pProcInfo))
				{
					WaitForSingleObject(pProcInfo.hProcess,waitTimeInMilliSec);
					continue;
				}
				long nError = GetLastError();
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to start custom-process program(%d) '%s' as user '%s', error code = %d"),listTrav,cmd.GetString(), m_userName.GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
			long nError = GetLastError();
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to logon as user '%s', error code = %d"), m_userName.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			continue;;
		}
	}


}

void ServiceObject::RunCommand(CString command, int waitTimeInMilliSec)
{
	LockObj lock(&m_lock);

	vector<CString> cmdList;
	BaseManagementObject::ParseCommand(command,cmdList);

	CString cmd=_T("");

	for(int listTrav=0;listTrav<cmdList.size();listTrav++)
	{
		cmd=cmdList.at(listTrav);
		if(cmd.Find(_T("%n"))>=0)
			cmd.Replace(_T("%n"),m_serviceName.GetString());
		if(cmd.Find(_T("%N"))>=0)
			cmd.Replace(_T("%N"),m_serviceName.GetString());

		// start a process with given index
		STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,_T(""),NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
		PROCESS_INFORMATION	pProcInfo;
		if(m_isUserInterface)
			startUpInfo.wShowWindow = SW_SHOW;
		else
			startUpInfo.wShowWindow = SW_HIDE;
		startUpInfo.lpDesktop = NULL;

		// set the correct desktop for the process to be started
		if(m_isImpersonate==false)
		{

			// create the process
			if(CreateProcess(NULL, const_cast<wchar_t*>( cmd.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
			{
				WaitForSingleObject(pProcInfo.hProcess,waitTimeInMilliSec);
				continue;
			}
			else
			{
				TCHAR pTemp[256];
				long nError = GetLastError();

				_stprintf(pTemp,_T("Failed to run command(%d) '%s', error code = %d"),listTrav, cmd.GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
		}
		else
		{
			HANDLE hToken = NULL;
			if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
			{
				if(CreateProcessAsUser(hToken,NULL,const_cast<wchar_t*>(cmd.GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&pProcInfo))
				{
					WaitForSingleObject(pProcInfo.hProcess,waitTimeInMilliSec);
					continue;
				}
				long nError = GetLastError();
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to run command(%d) '%s' as user '%s', error code = %d"),listTrav,cmd.GetString(), m_userName.GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
			long nError = GetLastError();
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to logon as user '%s', error code = %d"), m_userName.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			continue;;
		}
	}
}



CString ServiceObject::GetServiceName()
{
	LockObj lock(&m_lock);
	return m_serviceName;

}
void ServiceObject::SetServiceName(CString cmd)
{
	LockObj lock(&m_lock);
	m_serviceName=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("ServiceName"),m_serviceName.GetString(),m_iniFileName.GetString());
}

bool ServiceObject::GetIsUserStopped()
{
	LockObj lock(&m_lock);
	return m_isUserStopped;

}
void ServiceObject::SetIsUserStopped(bool isUserStopped)
{
	LockObj lock(&m_lock);
	m_isUserStopped=isUserStopped;

}
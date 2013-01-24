/*! 
ProcessObject for the EpWinService
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
#include "epProcessObject.h"
#include "epLogWriter.h"


ProcessObject::ProcessObject(unsigned int procIndex):BaseManagementObject(MANAGEMENT_OBJECT_TYPE_PROCESS,procIndex)
{
	m_pProcInfo.hProcess=0;
	m_pProcInfo.hThread=0;

	TCHAR *textBuffer=new TCHAR[MAX_PATH];

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_objectString.GetString(),_T("CommandLine"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_commandLine=textBuffer;
	m_commandLine.Trim();

	m_delayStartTime=GetPrivateProfileInt(m_objectString.GetString(),_T("DelayStartTime"),0,m_iniFileName.GetString());
	m_delayPauseEndTime=GetPrivateProfileInt(m_objectString.GetString(),_T("DelayPauseEndTime"),0,m_iniFileName.GetString());

	
	delete[] textBuffer;
}

ProcessObject::~ProcessObject()
{

}



bool ProcessObject::Start()
{
	LockObj lock(&m_lock);
	if(m_pProcInfo.hProcess)
		return true;

	//Pre-Process
	preProcess();
	// start a process with given index
	STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,_T(""),NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
	if(m_isUserInterface)
		startUpInfo.wShowWindow = SW_SHOW;
	else
		startUpInfo.wShowWindow = SW_HIDE;
	startUpInfo.lpDesktop = NULL;

	// set the correct desktop for the process to be started
	if(m_isImpersonate==false)
	{

		// create the process
		if(CreateProcess(NULL, const_cast<wchar_t*>(m_commandLine.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&m_pProcInfo))
		{
			Sleep(m_delayStartTime);
			return true;
		}
		else
		{
			TCHAR pTemp[256];
			long nError = GetLastError();

			_stprintf(pTemp,_T("Failed to start program '%s', error code = %d"), m_commandLine.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			return false;
		}
	}
	else
	{
		HANDLE hToken = NULL;
		if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
		{
			if(CreateProcessAsUser(hToken,NULL,const_cast<wchar_t*>(m_commandLine.GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&m_pProcInfo))
			{
				Sleep(m_delayStartTime);
				return true;
			}
			long nError = GetLastError();
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to start program '%s' as user '%s', error code = %d"), m_commandLine.GetString(), m_userName.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			return false;
		}
		long nError = GetLastError();
		TCHAR pTemp[256];
		_stprintf(pTemp,_T("Failed to logon as user '%s', error code = %d"), m_userName.GetString(), nError); 
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
		return false;
	}

}

void ProcessObject::Stop()
{
	LockObj lock(&m_lock);
	if(m_pProcInfo.hProcess)
	{
		// post a WM_QUIT message first
		PostThreadMessage(m_pProcInfo.dwThreadId,WM_QUIT,0,0);
		// sleep for a while so that the process has a chance to terminate itself
		::Sleep(m_delayPauseEndTime>0?m_delayPauseEndTime:50);
		// terminate the process by force
		TerminateProcess(m_pProcInfo.hProcess,0);
		try // close handles to avoid ERROR_NO_SYSTEM_RESOURCES
		{
			::CloseHandle(m_pProcInfo.hThread);
			::CloseHandle(m_pProcInfo.hProcess);
		}
		catch(...) {}
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("Process%d ended"),m_objIndex);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);

		m_pProcInfo.hProcess = 0;
		m_pProcInfo.hThread = 0;
		postProcess();
	}
}

bool ProcessObject::IsStarted()
{
	LockObj lock(&m_lock);
	DWORD dwCode;
	if(m_pProcInfo.hProcess && ::GetExitCodeProcess(m_pProcInfo.hProcess,&dwCode))
	{
		if(dwCode==STILL_ACTIVE)
			return true;
	}
	return false;
}

BOOL ProcessObject::GetExitCodeProcess(DWORD *dwCode)
{
	LockObj lock(&m_lock);
	return ::GetExitCodeProcess(m_pProcInfo.hProcess,dwCode);
}
void ProcessObject::Reset()
{
	LockObj lock(&m_lock);
	try // close handles to avoid ERROR_NO_SYSTEM_RESOURCES
	{
		::CloseHandle(m_pProcInfo.hThread);
		::CloseHandle(m_pProcInfo.hProcess);
	}
	catch(...) {}
	m_pProcInfo.hThread=0;
	m_pProcInfo.hProcess=0;
}


void ProcessObject::CustomProcess()
{
	LockObj lock(&m_lock);
	CString pidString=_T("");
	pidString.Format(_T("%d"),m_pProcInfo.dwProcessId);
	CString cmd=_T("");

	for(int listTrav=0;listTrav<m_customProcessCommandLineList.size();listTrav++)
	{
		cmd=m_customProcessCommandLineList.at(listTrav);
		if(cmd.Find(_T("%p"))>=0)
			cmd.Replace(_T("%p"),pidString.GetString());
		if(cmd.Find(_T("%P"))>=0)
			cmd.Replace(_T("%P"),pidString.GetString());

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
				WaitForSingleObject(pProcInfo.hProcess,INFINITE);
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
					WaitForSingleObject(pProcInfo.hProcess,INFINITE);
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
CString ProcessObject::GetCommandLine()
{
	LockObj lock(&m_lock);
	return m_commandLine;

}
void ProcessObject::SetCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	m_commandLine=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("CommandLine"),m_commandLine.GetString(),m_iniFileName.GetString());
}

unsigned int ProcessObject::GetDelayStartTime()
{
	LockObj lock(&m_lock);
	return m_delayStartTime;
}
void ProcessObject::SetDelayStartTime(unsigned int timeInMilli)
{
	LockObj lock(&m_lock);
	m_delayStartTime=timeInMilli;
	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_delayStartTime);
	WritePrivateProfileString(m_objectString.GetString(),_T("DelayStartTime"),valueString.GetString(),m_iniFileName.GetString());
}

unsigned int ProcessObject::GetDelayPauseEndTime()
{

	LockObj lock(&m_lock);
	return m_delayPauseEndTime;
}
void ProcessObject::SetDelayPauseEndTime(unsigned int timeInMilli)
{
	LockObj lock(&m_lock);
	m_delayPauseEndTime=timeInMilli;
	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_delayPauseEndTime);
	WritePrivateProfileString(m_objectString.GetString(),_T("DelayPauseEndTime"),valueString.GetString(),m_iniFileName.GetString());
}

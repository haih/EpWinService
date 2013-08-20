/*! 
ProcessObject for the EpWinService

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
#include "epProcessObject.h"
#include "epLogWriter.h"
#include "epServiceProperties.h"

ProcessObject::ProcessObject(unsigned int procIndex):BaseManagementObject(MANAGEMENT_OBJECT_TYPE_PROCESS,procIndex)
{
	m_pProcInfo.hProcess=0;
	m_pProcInfo.hThread=0;

	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("CommandLine"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_commandLine=textBuffer;
	m_commandLine=m_commandLine.Trim();


	EP_DELETE[] textBuffer;
}

ProcessObject::~ProcessObject()
{

}



ObjectStartStatus ProcessObject::start()
{
	
	if(m_pProcInfo.hProcess)
	{
		return OBJECT_START_STATUS_FAILED_ALREADY_STARTED;
	}

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
		if(CreateProcess(NULL, const_cast<TCHAR*>(m_commandLine.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&m_pProcInfo))
		{
			Sleep(m_delayStartTime);
			return OBJECT_START_STATUS_SUCCESS;
		}
		else
		{
			TCHAR pTemp[256];
			long nError = GetLastError();

			_stprintf(pTemp,_T("Failed to start program '%s', error code = %d"), m_commandLine.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			return OBJECT_START_STATUS_FAILED;
		}
	}
	else
	{
		HANDLE hToken = NULL;
		if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
		{
			if(CreateProcessAsUser(hToken,NULL,const_cast<TCHAR*>(m_commandLine.GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&m_pProcInfo))
			{
				Sleep(m_delayStartTime);
				return OBJECT_START_STATUS_SUCCESS;
			}
			long nError = GetLastError();
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to start program '%s' as user '%s', error code = %d"), m_commandLine.GetString(), m_userName.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			return OBJECT_START_STATUS_FAILED;
		}
		long nError = GetLastError();
		TCHAR pTemp[256];
		_stprintf(pTemp,_T("Failed to logon as user '%s', error code = %d"), m_userName.GetString(), nError); 
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
		return OBJECT_START_STATUS_FAILED_LOGON_FAILED;
	}

}

void ProcessObject::stop()
{
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
	LockObj lock(&m_baseObjLock);
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
	LockObj lock(&m_baseObjLock);
	return ::GetExitCodeProcess(m_pProcInfo.hProcess,dwCode);
}
void ProcessObject::Reset()
{
	LockObj lock(&m_baseObjLock);
	try // close handles to avoid ERROR_NO_SYSTEM_RESOURCES
	{
		::CloseHandle(m_pProcInfo.hThread);
		::CloseHandle(m_pProcInfo.hProcess);
	}
	catch(...) {}
	m_pProcInfo.hThread=0;
	m_pProcInfo.hProcess=0;
}


void ProcessObject::CustomProcess(int waitTimeInMilliSec)
{
	LockObj lock(&m_baseObjLock);
	CString pidString=_T("");
	pidString.Format(_T("%d"),m_pProcInfo.dwProcessId);

	for(int listTrav=0;listTrav<m_customProcessCommandLineList.size();listTrav++)
	{
		executeCommand(m_customProcessCommandLineList.at(listTrav),listTrav,waitTimeInMilliSec,EXECUTE_COMMAND_TYPE_CUSTOMPROCESS);
	}


}

void ProcessObject::RunCommand(CString command, int waitTimeInMilliSec)
{
	LockObj lock(&m_baseObjLock);

	vector<CString> cmdList;
	BaseManagementObject::ParseCommand(command,cmdList);

	CString pidString=_T("");
	pidString.Format(_T("%d"),m_pProcInfo.dwProcessId);

	for(int listTrav=0;listTrav<cmdList.size();listTrav++)
	{
		executeCommand(cmdList.at(listTrav),listTrav,waitTimeInMilliSec,EXECUTE_COMMAND_TYPE_CUSTOMPROCESS);
	}
}
CString ProcessObject::GetCommandLine()
{
	LockObj lock(&m_baseObjLock);
	return m_commandLine;

}
void ProcessObject::SetCommandLine(CString cmd)
{
	LockObj lock(&m_baseObjLock);
	m_commandLine=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("CommandLine"),m_commandLine.GetString(),m_iniFileName.GetString());
}

void ProcessObject::replaceCommandArgument(CString &cmd)
{
	CString pidString=_T("");
	pidString.Format(_T("%d"),m_pProcInfo.dwProcessId);
	if(cmd.Find(_T("%p"))>=0)
		cmd.Replace(_T("%p"),pidString.GetString());
	if(cmd.Find(_T("%P"))>=0)
		cmd.Replace(_T("%P"),pidString.GetString());

	BaseManagementObject::replaceCommandArgument(cmd);
}

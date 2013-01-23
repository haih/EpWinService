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

void ProcessObject::ParseCommand(CString cmd,  vector<CString>& retCmdList)
{
	retCmdList.clear();
	if(cmd.Find(_T(';'))==-1)
		retCmdList.push_back(cmd);
	else
	{
		int index=cmd.Find(_T(';'));
		CString tmpCommand=_T("");
		while(index>=0)
		{
			for(int strTrav=0;strTrav<index;strTrav++)
			{
				tmpCommand.AppendChar(cmd.GetAt(strTrav));
			}
			tmpCommand=tmpCommand.Trim();
			cmd.Delete(0,index+1);
			if(tmpCommand.GetLength()>0)
				retCmdList.push_back(tmpCommand);
		}
		cmd=cmd.Trim();
		if(cmd.GetLength()>0)
			retCmdList.push_back(cmd);
	}

}
ProcessObject::ProcessObject(unsigned int procIndex)
{
	m_procIndex=procIndex;
	m_pProcInfo.hProcess=0;
	m_pProcInfo.hThread=0;

	m_iniFileName=FolderHelper::GetModuleFileName().c_str();
	m_iniFileName.Replace(_T(".exe"),_T(".ini"));
	TCHAR *textBuffer=new TCHAR[MAX_PATH];
	m_processString=_T("Process");
	m_processString.AppendFormat(_T("%d"),procIndex);

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("CommandLine"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_commandLine=textBuffer;
	m_commandLine.Trim();

	m_delayStartTime=GetPrivateProfileInt(m_processString.GetString(),_T("DelayStartTime"),0,m_iniFileName.GetString());
	m_delayPauseEndTime=GetPrivateProfileInt(m_processString.GetString(),_T("DelayPauseEndTime"),0,m_iniFileName.GetString());

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("Restart"),_T("Y"),textBuffer,MAX_PATH,m_iniFileName.GetString());
	if(textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1')
		m_isRestart=true;
	else
		m_isRestart=false;

	CString tmpCmd;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("PreProcessCommandLine"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_preProcessCommandLine=textBuffer;
	m_preProcessCommandLine.Trim();
	ProcessObject::ParseCommand(m_preProcessCommandLine,m_preProcessCommandLineList);

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("PostProcessCommandLine"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_postProcessCommandLine=textBuffer;
	m_postProcessCommandLine.Trim();
	ProcessObject::ParseCommand(m_postProcessCommandLine,m_postProcessCommandLineList);


	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("CustomProcessCommandLine"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_customProcessCommandLine=textBuffer;
	m_customProcessCommandLine.Trim();
	ProcessObject::ParseCommand(m_customProcessCommandLine,m_customProcessCommandLineList);

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("Impersonate"),_T("N"),textBuffer,MAX_PATH,m_iniFileName.GetString());
	if(textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1')
		m_isImpersonate=true;
	else
		m_isImpersonate=false;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("UserInterface"),_T("N"),textBuffer,MAX_PATH,m_iniFileName.GetString());
	if(m_isImpersonate==false && (textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1'))
		m_isUserInterface=true;
	else
		m_isUserInterface=false;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("DomainName"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_domainName=textBuffer;
	m_domainName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("UserName"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_userName=textBuffer;
	m_userName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
	GetPrivateProfileString(m_processString.GetString(),_T("Password"),_T(""),textBuffer,MAX_PATH,m_iniFileName.GetString());
	m_userPassword=textBuffer;
	m_userPassword.Trim();

	delete[] textBuffer;
}

ProcessObject::~ProcessObject()
{

}

void ProcessObject::preProcess()
{
	for(int listTrav=0;listTrav<m_preProcessCommandLineList.size();listTrav++)
	{
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
			if(CreateProcess(NULL, const_cast<wchar_t*>(m_preProcessCommandLineList.at(listTrav).GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
			{
				WaitForSingleObject(pProcInfo.hProcess,INFINITE);
				continue;
			}
			else
			{
				TCHAR pTemp[256];
				long nError = GetLastError();

				_stprintf(pTemp,_T("Failed to start pre-process program(%d) '%s', error code = %d"),listTrav, m_preProcessCommandLineList.at(listTrav).GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
		}
		else
		{
			HANDLE hToken = NULL;
			if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
			{
				if(CreateProcessAsUser(hToken,NULL,const_cast<wchar_t*>(m_preProcessCommandLineList.at(listTrav).GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&pProcInfo))
				{
					WaitForSingleObject(pProcInfo.hProcess,INFINITE);
					continue;
				}
				long nError = GetLastError();
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to start pre-process program(%d) '%s' as user '%s', error code = %d"),listTrav, m_preProcessCommandLineList.at(listTrav).GetString(), m_userName.GetString(), nError); 
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

void ProcessObject::postProcess()
{
	for(int listTrav=0;listTrav<m_postProcessCommandLineList.size();listTrav++)
	{
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
			if(CreateProcess(NULL, const_cast<wchar_t*>(m_postProcessCommandLineList.at(listTrav).GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
			{
				WaitForSingleObject(pProcInfo.hProcess,INFINITE);
				continue;
			}
			else
			{
				TCHAR pTemp[256];
				long nError = GetLastError();

				_stprintf(pTemp,_T("Failed to start post-process program(%d) '%s', error code = %d"),listTrav, m_postProcessCommandLineList.at(listTrav).GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
		}
		else
		{
			HANDLE hToken = NULL;
			if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
			{
				if(CreateProcessAsUser(hToken,NULL,const_cast<wchar_t*>(m_postProcessCommandLineList.at(listTrav).GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&pProcInfo))
				{
					WaitForSingleObject(pProcInfo.hProcess,INFINITE);
					continue;
				}
				long nError = GetLastError();
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to start post-process program(%d) '%s' as user '%s', error code = %d"),listTrav, m_postProcessCommandLineList.at(listTrav).GetString(), m_userName.GetString(), nError); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				continue;
			}
			long nError = GetLastError();
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to logon as user '%s', error code = %d"), m_userName.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			continue;
		}
	}

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

bool ProcessObject::StartProcess()
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

void ProcessObject::EndProcess()
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
		_stprintf(pTemp, _T("Process%d ended"),m_procIndex);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);

		m_pProcInfo.hProcess = 0;
		m_pProcInfo.hThread = 0;
		postProcess();
	}
}

void ProcessObject::PostProcess()
{
	LockObj lock(&m_lock);
	postProcess();
}

bool ProcessObject::IsProcessStarted()
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


CString ProcessObject::GetCommandLine()
{
	LockObj lock(&m_lock);
	return m_commandLine;

}
void ProcessObject::SetCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	m_commandLine=cmd;
	WritePrivateProfileString(m_processString.GetString(),_T("CommandLine"),m_commandLine.GetString(),m_iniFileName.GetString());
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
	WritePrivateProfileString(m_processString.GetString(),_T("DelayStartTime"),valueString.GetString(),m_iniFileName.GetString());
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
	WritePrivateProfileString(m_processString.GetString(),_T("DelayPauseEndTime"),valueString.GetString(),m_iniFileName.GetString());
}

bool ProcessObject::GetIsProcessRestart()
{
	LockObj lock(&m_lock);
	return m_isRestart;
}
void ProcessObject::SetIsProcessRestart(bool isRestart)
{
	LockObj lock(&m_lock);
	m_isRestart=isRestart;
	if(m_isRestart)
		WritePrivateProfileString(m_processString.GetString(),_T("Restart"),_T("Y"),m_iniFileName.GetString());
	else
		WritePrivateProfileString(m_processString.GetString(),_T("Restart"),_T("N"),m_iniFileName.GetString());
}

CString ProcessObject::GetPreProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_preProcessCommandLine;
	
}
void ProcessObject::SetPreProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_preProcessCommandLine=cmd;
	WritePrivateProfileString(m_processString.GetString(),_T("PreProcessCommandLine"),m_preProcessCommandLine.GetString(),m_iniFileName.GetString());
	ProcessObject::ParseCommand(m_preProcessCommandLine,m_preProcessCommandLineList);
}

CString ProcessObject::GetPostProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_postProcessCommandLine;

}
void ProcessObject::SetPostProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_postProcessCommandLine=cmd;
	WritePrivateProfileString(m_processString.GetString(),_T("PostProcessCommandLine"),m_postProcessCommandLine.GetString(),m_iniFileName.GetString());
	ProcessObject::ParseCommand(m_postProcessCommandLine,m_postProcessCommandLineList);
}

CString ProcessObject::GetCustomProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_customProcessCommandLine;

}
void ProcessObject::SetCustomProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_customProcessCommandLine=cmd;
	WritePrivateProfileString(m_processString.GetString(),_T("CustomProcessCommandLine"),m_customProcessCommandLine.GetString(),m_iniFileName.GetString());
	ProcessObject::ParseCommand(m_customProcessCommandLine,m_customProcessCommandLineList);
}

bool ProcessObject::GetIsImpersonate()
{
	LockObj lock(&m_lock);
	return m_isImpersonate;
}

void ProcessObject::SetIsImpersonate(bool isImpersonate)
{
	LockObj lock(&m_lock);
	m_isImpersonate=isImpersonate;
	if(m_isImpersonate)
		WritePrivateProfileString(m_processString.GetString(),_T("Impersonate"),_T("Y"),m_iniFileName.GetString());
	else
		WritePrivateProfileString(m_processString.GetString(),_T("Impersonate"),_T("N"),m_iniFileName.GetString());
}

bool ProcessObject::GetIsUserInterface()
{
	LockObj lock(&m_lock);
	return m_isUserInterface;
}
void ProcessObject::SetIsUserInterface(bool isUserInterface)
{
	LockObj lock(&m_lock);
	m_isUserInterface=(isUserInterface && (m_isImpersonate==false));
	if(m_isUserInterface)
		WritePrivateProfileString(m_processString.GetString(),_T("UserInterface"),_T("Y"),m_iniFileName.GetString());
	else
		WritePrivateProfileString(m_processString.GetString(),_T("UserInterface"),_T("N"),m_iniFileName.GetString());
}

CString ProcessObject::GetDomainName()
{
	LockObj lock(&m_lock);
	return m_domainName;
}
void ProcessObject::SetDomainName(CString domainName)
{
	LockObj lock(&m_lock);
	m_domainName=domainName;
	WritePrivateProfileString(m_processString.GetString(),_T("DomainName"),m_domainName.GetString(),m_iniFileName.GetString());

}

CString ProcessObject::GetUserName()
{

	LockObj lock(&m_lock);
	return m_userName;
}
void ProcessObject::SetUserName(CString userName)
{
	LockObj lock(&m_lock);
	m_userName=userName;
	WritePrivateProfileString(m_processString.GetString(),_T("UserName"),m_userName.GetString(),m_iniFileName.GetString());

}

CString ProcessObject::GetUserPassword()
{
	LockObj lock(&m_lock);
	return m_userPassword;
}
void ProcessObject::SetUserPassword(CString userPassword)
{
	LockObj lock(&m_lock);
	m_userPassword=userPassword;
	WritePrivateProfileString(m_processString.GetString(),_T("Password"),m_userPassword.GetString(),m_iniFileName.GetString());

}
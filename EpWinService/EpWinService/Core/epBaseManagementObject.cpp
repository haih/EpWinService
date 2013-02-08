/*! 
BaseManagementObject for the EpWinService
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
#include "epBaseManagementObject.h"
#include "epLogWriter.h"
#include "epServiceProperties.h"

void BaseManagementObject::ParseCommand(CString cmd,  vector<CString>& retCmdList)
{
	retCmdList.clear();
	cmd.Trim();

	CString parsedCommand=_T("");
	while(cmd.GetLength())
	{
		bool isOpen=false;
		if(cmd.GetAt(0)==_T('\"'))
		{
			isOpen=true;
		}
		int stringTrav=1;
		for(;stringTrav<cmd.GetLength();stringTrav++)	
		{
			if(isOpen)
			{
				if((cmd.GetAt(stringTrav)==_T('\'')&& stringTrav+1==cmd.GetLength()))
				{
					stringTrav=stringTrav+1;
					break;
				}
				if(cmd.GetAt(stringTrav)==_T('\'')&& stringTrav+1<cmd.GetLength()&&cmd.GetAt(stringTrav+1)==_T(';'))
				{
					stringTrav=stringTrav+2;
					break;
				}
				parsedCommand.AppendChar(cmd.GetAt(stringTrav));
			}
			else
			{
				if(cmd.GetAt(stringTrav)==_T(';'))
				{
					stringTrav=stringTrav+1;
					break;
				}
				parsedCommand.AppendChar(cmd.GetAt(stringTrav));
			}
		}
		cmd.Delete(0,stringTrav);
		parsedCommand.Trim();
		if(parsedCommand.GetLength())
			retCmdList.push_back(parsedCommand);
		cmd.Trim();
	}
	

}

BaseManagementObject::BaseManagementObject(ManagementObjectType objType,unsigned int objIndex)
{
	m_objIndex=objIndex;
	m_objType=objType;
	

	m_iniFileName=FolderHelper::GetModuleFileName().c_str();
	m_iniFileName.Replace(_T(".exe"),_T(".ini"));
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];
	if(m_objType==MANAGEMENT_OBJECT_TYPE_PROCESS)
		m_objectString=_T("Process");
	else
		m_objectString=_T("Service");
	m_objectString.AppendFormat(_T("%d"),m_objIndex);

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("Restart"),_T("Y"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	if(textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1')
		m_isRestart=true;
	else
		m_isRestart=false;

	CString tmpCmd;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("PreProcessCommandLine"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_preProcessCommandLine=textBuffer;
	m_preProcessCommandLine.Trim();
	BaseManagementObject::ParseCommand(m_preProcessCommandLine,m_preProcessCommandLineList);

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("PostProcessCommandLine"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_postProcessCommandLine=textBuffer;
	m_postProcessCommandLine.Trim();
	BaseManagementObject::ParseCommand(m_postProcessCommandLine,m_postProcessCommandLineList);


	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("CustomProcessCommandLine"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_customProcessCommandLine=textBuffer;
	m_customProcessCommandLine.Trim();
	BaseManagementObject::ParseCommand(m_customProcessCommandLine,m_customProcessCommandLineList);

	m_preProcessWaitTime=GetPrivateProfileInt(m_objectString.GetString(),_T("PreProcessWaitTime"),WAITTIME_INIFINITE,m_iniFileName.GetString());
	m_postProcessWaitTime=GetPrivateProfileInt(m_objectString.GetString(),_T("PostProcessWaitTime"),WAITTIME_INIFINITE,m_iniFileName.GetString());
	
	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("Impersonate"),_T("N"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	if(textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1')
		m_isImpersonate=true;
	else
		m_isImpersonate=false;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("UserInterface"),_T("N"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	if(m_isImpersonate==false && (textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1'))
		m_isUserInterface=true;
	else
		m_isUserInterface=false;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("DomainName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_domainName=textBuffer;
	m_domainName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("UserName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userName=textBuffer;
	m_userName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("Password"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userPassword=textBuffer;
	m_userPassword.Trim();

	m_delayStartTime=GetPrivateProfileInt(m_objectString.GetString(),_T("DelayStartTime"),0,m_iniFileName.GetString());
	m_delayPauseEndTime=GetPrivateProfileInt(m_objectString.GetString(),_T("DelayPauseEndTime"),0,m_iniFileName.GetString());

	EP_DELETE[] textBuffer;
}

BaseManagementObject::~BaseManagementObject()
{

}

void BaseManagementObject::preProcess()
{
	for(int listTrav=0;listTrav<m_preProcessCommandLineList.size();listTrav++)
	{
		// start a process with given index
		executeCommand(m_preProcessCommandLineList.at(listTrav),listTrav,m_preProcessWaitTime,EXECUTE_COMMAND_TYPE_PREPROCESS);
	}

}

void BaseManagementObject::postProcess()
{
	for(int listTrav=0;listTrav<m_postProcessCommandLineList.size();listTrav++)
	{
		// start a process with given index
		executeCommand(m_postProcessCommandLineList.at(listTrav),listTrav,m_postProcessWaitTime,EXECUTE_COMMAND_TYPE_POSTPROCESS);
	}

}


void BaseManagementObject::CustomProcess(int waitTimeInMilliSec)
{
	LockObj lock(&m_lock);
	for(int listTrav=0;listTrav<m_customProcessCommandLineList.size();listTrav++)
	{
		executeCommand(m_customProcessCommandLineList.at(listTrav),listTrav,waitTimeInMilliSec,EXECUTE_COMMAND_TYPE_POSTPROCESS);
	}


}
void BaseManagementObject::RunCommand(CString command, int waitTimeInMilliSec)
{
	LockObj lock(&m_lock);

	vector<CString> cmdList;
	BaseManagementObject::ParseCommand(command,cmdList);

	for(int listTrav=0;listTrav<cmdList.size();listTrav++)
	{
		executeCommand(cmdList.at(listTrav),listTrav,waitTimeInMilliSec,EXECUTE_COMMAND_TYPE_POSTPROCESS);
	}
}

void BaseManagementObject::executeCommand(CString command,unsigned int cmdIdx, int waitTimeInMilliSec,ExecuteCommandType execCommandType)
{
	CString objectTypeString=_T("");
	if(m_objType==MANAGEMENT_OBJECT_TYPE_PROCESS)
	{
		objectTypeString=_T("ProcessObject");
	}
	else if(m_objType==MANAGEMENT_OBJECT_TYPE_SERVICE)
	{
		objectTypeString=_T("ServiceObject");
	}

	CString exeCommandTypeString=_T("");
	switch(execCommandType)
	{
	case EXECUTE_COMMAND_TYPE_PREPROCESS:
		exeCommandTypeString=_T("pre-process");
		break;
	case EXECUTE_COMMAND_TYPE_POSTPROCESS:
		exeCommandTypeString=_T("post-process");
		break;
	case EXECUTE_COMMAND_TYPE_CUSTOMPROCESS:
		exeCommandTypeString=_T("custom-process");
		break;
	case EXECUTE_COMMAND_TYPE_RUNCOMMAND:
		exeCommandTypeString=_T("run command");
		break;
	}

	CString cmd=command;
	replaceCommandArgument(cmd);

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
		if(CreateProcess(NULL, const_cast<TCHAR*>( cmd.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
		{
			WaitForSingleObject(pProcInfo.hProcess,(DWORD)waitTimeInMilliSec);
			return;
		}
		else
		{
			TCHAR pTemp[256];
			long nError = GetLastError();

			_stprintf(pTemp,_T("%s(%d) : Failed to %s(%d) '%s', error code = %d"),objectTypeString.GetString(),m_objIndex,exeCommandTypeString.GetString(),cmdIdx, cmd.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			return;
		}
	}
	else
	{
		HANDLE hToken = NULL;
		if(LogonUser(m_userName.GetString(),(m_domainName.GetLength()==0)?_T("."):m_domainName.GetString(),m_userPassword.GetString(),LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
		{
			if(CreateProcessAsUser(hToken,NULL,const_cast<TCHAR*>(cmd.GetString()),NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,NULL,&startUpInfo,&pProcInfo))
			{
				WaitForSingleObject(pProcInfo.hProcess,(DWORD)waitTimeInMilliSec);
				return;
			}
			long nError = GetLastError();
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("%s(%d) : Failed to %s(%d) '%s' as user '%s', error code = %d"),objectTypeString.GetString(),m_objIndex,exeCommandTypeString.GetString(),cmdIdx,cmd.GetString(), m_userName.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			return;
		}
		long nError = GetLastError();
		TCHAR pTemp[256];
		_stprintf(pTemp,_T("%s(%d) : Failed to logon as user '%s', error code = %d"),objectTypeString.GetString(),m_objIndex, m_userName.GetString(), nError); 
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
		return;
	}
}

void BaseManagementObject::replaceCommandArgument(CString &cmd)
{
	CString dateTime=DateTimeHelper::DateTimeToString(DateTimeHelper::GetCurrentDateTime()).c_str();
	if(cmd.Find(_T("%t"))>=0)
		cmd.Replace(_T("%t"),dateTime.GetString());
	if(cmd.Find(_T("%T"))>=0)
		cmd.Replace(_T("%T"),dateTime.GetString());

	CString objIndexString=_T("");
	objIndexString.Format(_T("%d"),m_objIndex);
	if(cmd.Find(_T("%x"))>=0)
		cmd.Replace(_T("%x"),objIndexString.GetString());
	if(cmd.Find(_T("%X"))>=0)
		cmd.Replace(_T("%X"),objIndexString.GetString());

	CString objTypeString=_T("");
	switch(m_objType)
	{
	case MANAGEMENT_OBJECT_TYPE_PROCESS:
		objTypeString=_T("ProcessObject");
		break;
	case MANAGEMENT_OBJECT_TYPE_SERVICE:
		objTypeString=_T("ServiceObject");
		break;
	}
	if(cmd.Find(_T("%o"))>=0)
		cmd.Replace(_T("%o"),objTypeString.GetString());
	if(cmd.Find(_T("%O"))>=0)
		cmd.Replace(_T("%O"),objTypeString.GetString());
}

void BaseManagementObject::PostProcess()
{
	LockObj lock(&m_lock);
	postProcess();
}


bool BaseManagementObject::GetIsRestart()
{
	LockObj lock(&m_lock);
	return m_isRestart;
}
void BaseManagementObject::SetIsRestart(bool isRestart)
{
	LockObj lock(&m_lock);
	m_isRestart=isRestart;
	if(m_isRestart)
		WritePrivateProfileString(m_objectString.GetString(),_T("Restart"),_T("Y"),m_iniFileName.GetString());
	else
		WritePrivateProfileString(m_objectString.GetString(),_T("Restart"),_T("N"),m_iniFileName.GetString());
}

CString BaseManagementObject::GetPreProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_preProcessCommandLine;

}
void BaseManagementObject::SetPreProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_preProcessCommandLine=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("PreProcessCommandLine"),m_preProcessCommandLine.GetString(),m_iniFileName.GetString());
	BaseManagementObject::ParseCommand(m_preProcessCommandLine,m_preProcessCommandLineList);
}

CString BaseManagementObject::GetPostProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_postProcessCommandLine;

}
void BaseManagementObject::SetPostProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_postProcessCommandLine=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("PostProcessCommandLine"),m_postProcessCommandLine.GetString(),m_iniFileName.GetString());
	BaseManagementObject::ParseCommand(m_postProcessCommandLine,m_postProcessCommandLineList);
}

CString BaseManagementObject::GetCustomProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_customProcessCommandLine;

}
void BaseManagementObject::SetCustomProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_customProcessCommandLine=cmd;
	WritePrivateProfileString(m_objectString.GetString(),_T("CustomProcessCommandLine"),m_customProcessCommandLine.GetString(),m_iniFileName.GetString());
	BaseManagementObject::ParseCommand(m_customProcessCommandLine,m_customProcessCommandLineList);
}

bool BaseManagementObject::GetIsImpersonate()
{
	LockObj lock(&m_lock);
	return m_isImpersonate;
}


int BaseManagementObject::GetPreProcessWaitTime()
{
	LockObj lock(&m_lock);
	return m_preProcessWaitTime;
}
int BaseManagementObject::GetPostProcessWaitTime()
{
	LockObj lock(&m_lock);
	return m_postProcessWaitTime;
}

void BaseManagementObject::SetPreProcessWaitTime(int waitTimeinMilliSec)
{
	LockObj lock(&m_lock);
	m_preProcessWaitTime=waitTimeinMilliSec;
	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_preProcessWaitTime);
	WritePrivateProfileString(m_objectString.GetString(),_T("PreProcessWaitTime"),valueString.GetString(),m_iniFileName.GetString());

}
void BaseManagementObject::SetPostProcessWaitTime(int waitTimeinMilliSec)
{
	LockObj lock(&m_lock);
	m_postProcessWaitTime=waitTimeinMilliSec;
	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_postProcessWaitTime);
	WritePrivateProfileString(m_objectString.GetString(),_T("PostProcessWaitTime"),valueString.GetString(),m_iniFileName.GetString());

}

void BaseManagementObject::SetIsImpersonate(bool isImpersonate)
{
	LockObj lock(&m_lock);
	m_isImpersonate=isImpersonate;
	if(m_isImpersonate)
		WritePrivateProfileString(m_objectString.GetString(),_T("Impersonate"),_T("Y"),m_iniFileName.GetString());
	else
		WritePrivateProfileString(m_objectString.GetString(),_T("Impersonate"),_T("N"),m_iniFileName.GetString());
}

bool BaseManagementObject::GetIsUserInterface()
{
	LockObj lock(&m_lock);
	return m_isUserInterface;
}
void BaseManagementObject::SetIsUserInterface(bool isUserInterface)
{
	LockObj lock(&m_lock);
	m_isUserInterface=(isUserInterface && (m_isImpersonate==false));
	if(m_isUserInterface)
		WritePrivateProfileString(m_objectString.GetString(),_T("UserInterface"),_T("Y"),m_iniFileName.GetString());
	else
		WritePrivateProfileString(m_objectString.GetString(),_T("UserInterface"),_T("N"),m_iniFileName.GetString());
}

CString BaseManagementObject::GetDomainName()
{
	LockObj lock(&m_lock);
	return m_domainName;
}
void BaseManagementObject::SetDomainName(CString domainName)
{
	LockObj lock(&m_lock);
	m_domainName=domainName;
	WritePrivateProfileString(m_objectString.GetString(),_T("DomainName"),m_domainName.GetString(),m_iniFileName.GetString());

}

CString BaseManagementObject::GetUserName()
{

	LockObj lock(&m_lock);
	return m_userName;
}
void BaseManagementObject::SetUserName(CString userName)
{
	LockObj lock(&m_lock);
	m_userName=userName;
	WritePrivateProfileString(m_objectString.GetString(),_T("UserName"),m_userName.GetString(),m_iniFileName.GetString());

}

CString BaseManagementObject::GetUserPassword()
{
	LockObj lock(&m_lock);
	return m_userPassword;
}
void BaseManagementObject::SetUserPassword(CString userPassword)
{
	LockObj lock(&m_lock);
	m_userPassword=userPassword;
	WritePrivateProfileString(m_objectString.GetString(),_T("Password"),m_userPassword.GetString(),m_iniFileName.GetString());

}


unsigned int BaseManagementObject::GetDelayStartTime()
{
	LockObj lock(&m_lock);
	return m_delayStartTime;
}
void BaseManagementObject::SetDelayStartTime(unsigned int timeInMilli)
{
	LockObj lock(&m_lock);
	m_delayStartTime=timeInMilli;
	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_delayStartTime);
	WritePrivateProfileString(m_objectString.GetString(),_T("DelayStartTime"),valueString.GetString(),m_iniFileName.GetString());
}

unsigned int BaseManagementObject::GetDelayPauseEndTime()
{

	LockObj lock(&m_lock);
	return m_delayPauseEndTime;
}
void BaseManagementObject::SetDelayPauseEndTime(unsigned int timeInMilli)
{
	LockObj lock(&m_lock);
	m_delayPauseEndTime=timeInMilli;
	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_delayPauseEndTime);
	WritePrivateProfileString(m_objectString.GetString(),_T("DelayPauseEndTime"),valueString.GetString(),m_iniFileName.GetString());
}


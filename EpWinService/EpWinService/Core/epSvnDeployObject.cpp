/*! 
SvnDeployObject for the EpWinService
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
#include "epSvnDeployObject.h"
#include "epServiceProperties.h"

SvnDeployObject::SvnDeployObject(CString objectString, CString iniFileName):BaseDeployObject(objectString,iniFileName)
{
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

// 	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
// 	GetPrivateProfileString(m_objectString.GetString(),_T("SVNRepositoryURL"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
// 	m_repoURL=textBuffer;
// 	m_repoURL=m_repoURL.Trim();
// 
// 	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
// 	GetPrivateProfileString(m_objectString.GetString(),_T("SVNLocalPath"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
// 	m_localPath=textBuffer;
// 	m_localPath=m_localPath.Trim();
// 
// 	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
// 	GetPrivateProfileString(m_objectString.GetString(),_T("SVNUserName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
// 	m_userName=textBuffer;
// 	m_userName=m_userName.Trim();
// 
// 	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
// 	GetPrivateProfileString(m_objectString.GetString(),_T("SVNUserPassword"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
// 	m_userPassword=textBuffer;
// 	m_userPassword=m_userPassword.Trim();

	EP_DELETE[] textBuffer;
}
SvnDeployObject::~SvnDeployObject()
{

}



DeployErrCode SvnDeployObject::Update(unsigned int & retRevNum,int rev)
{
	LockObj lock(&m_deployLock);
	if(m_localPath.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_LOCALPATH;
	if(m_userName.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_USERNAME;
	if(m_userPassword.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_PASSWORD;

	if(cleanUp()!=DEPLOY_ERR_CODE_SUCCESS)
	{
		return DEPLOY_ERR_CODE_FAIED_CLEANUP;
	}
	CString commandString=_T("svn update \"");
	commandString.Append(m_localPath);
	commandString.Append(_T("\" --username "));
	commandString.Append(m_userName);
	commandString.Append(_T(" --password "));
	commandString.Append(m_userPassword);
	if(rev>=0)
	{
		commandString.Append(_T(" --revision "));
		commandString.AppendFormat(_T("%d"), rev);
	}

	m_lastResult=ConsoleHelper::ExecuteConsoleCommand(commandString.GetString(),true).c_str();
	CString result=m_lastResult;

	int foundIdx=-1;
	if((foundIdx=result.Find(_T("Updated to revision "),0))!=-1)
	{
		result.Delete(0,foundIdx);
		result.Delete(0,20);
		for(int trav=result.GetLength()-1;trav>=0;trav--)
		{
			if(!Locale::IsDigit(result.GetAt(trav)))
				result.Delete(trav,0);
		}
		retRevNum=_tstoi(result.GetString());
		return DEPLOY_ERR_CODE_SUCCESS;
	}
	else if((foundIdx=result.Find(_T("At revision "),0))!=-1)
	{
		result.Delete(0,foundIdx);
		result.Delete(0,12);
		for(int trav=result.GetLength()-1;trav>=0;trav--)
		{
			if(!Locale::IsDigit(result.GetAt(trav)))
				result.Delete(trav,0);
		}
		retRevNum=_tstoi(result.GetString());
		return DEPLOY_ERR_CODE_SUCCESS;
	}
	return DEPLOY_ERR_CODE_FAIED_SVNCOMMAND;

}
DeployErrCode SvnDeployObject::GetCurrentRevision(unsigned int & retRevNum)
{
	LockObj lock(&m_deployLock);
	if(m_localPath.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_LOCALPATH;
	if(m_userName.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_USERNAME;
	if(m_userPassword.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_PASSWORD;

	if(cleanUp()!=DEPLOY_ERR_CODE_SUCCESS)
	{
		return DEPLOY_ERR_CODE_FAIED_CLEANUP;
	}

	CString commandString=_T("svn info \"");
	commandString.Append(m_localPath);
	commandString.Append(_T("\" --username "));
	commandString.Append(m_userName);
	commandString.Append(_T(" --password "));
	commandString.Append(m_userPassword);

	m_lastResult=ConsoleHelper::ExecuteConsoleCommand(commandString.GetString()).c_str();
	CString result=m_lastResult;
	int foundIdx=-1;
	if((foundIdx=result.Find(_T("Revision: "),0))!=-1)
	{
		result.Delete(0,foundIdx);
		result.Delete(0,10);
		int endLineIdx=-1;
		if((endLineIdx=result.Find(_T("\n"),0))!=-1)
		{
			result.Delete(endLineIdx,result.GetLength()-endLineIdx);
		}
		for(int trav=result.GetLength()-1;trav>=0;trav--)
		{
			if(!Locale::IsDigit(result.GetAt(trav)))
				result.Delete(trav,0);
		}
		retRevNum=_tstoi(result.GetString());
		return DEPLOY_ERR_CODE_SUCCESS;
	}
	return DEPLOY_ERR_CODE_FAIED_SVNCOMMAND;
}
DeployErrCode SvnDeployObject::GetLatestRevision(unsigned int & retRevNum)
{
	LockObj lock(&m_deployLock);
	if(m_repoURL.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_REPOURL;
	if(m_userName.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_USERNAME;
	if(m_userPassword.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_PASSWORD;

	CString commandString=_T("svn info ");
	commandString.Append(m_repoURL);
	commandString.Append(_T(" --username "));
	commandString.Append(m_userName);
	commandString.Append(_T(" --password "));
	commandString.Append(m_userPassword);

	m_lastResult=ConsoleHelper::ExecuteConsoleCommand(commandString.GetString()).c_str();
	CString result=m_lastResult;
	int foundIdx=-1;
	if((foundIdx=result.Find(_T("Revision: "),0))!=-1)
	{
		result.Delete(0,foundIdx);
		result.Delete(0,10);
		int endLineIdx=-1;
		if((endLineIdx=result.Find(_T("\n"),0))!=-1)
		{
			result.Delete(endLineIdx,result.GetLength()-endLineIdx);
		}
		for(int trav=result.GetLength()-1;trav>=0;trav--)
		{
			if(!Locale::IsDigit(result.GetAt(trav)))
				result.Delete(trav,0);
		}
		retRevNum=_tstoi(result.GetString());
		return DEPLOY_ERR_CODE_SUCCESS;
	}
	return DEPLOY_ERR_CODE_FAIED_SVNCOMMAND;
}

DeployErrCode SvnDeployObject::CleanUp()
{
	LockObj lock(&m_deployLock);
	if(m_localPath.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_LOCALPATH;
	if(m_userName.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_USERNAME;
	if(m_userPassword.GetLength()<=0)
		return DEPLOY_ERR_CODE_FAIED_NULL_PASSWORD;
	return cleanUp();
}
DeployErrCode SvnDeployObject::cleanUp()
{
	CString commandString=_T("svn cleanup \"");
	commandString.Append(m_localPath);
	commandString.Append(_T("\" --username "));
	commandString.Append(m_userName);
	commandString.Append(_T(" --password "));
	commandString.Append(m_userPassword);
	m_lastResult=ConsoleHelper::ExecuteConsoleCommand(commandString.GetString(),true).c_str();
	CString result=m_lastResult;
	result=result.Trim();
	if(result.GetLength())
	{
		return DEPLOY_ERR_CODE_FAIED_CLEANUP;
	}
	return DEPLOY_ERR_CODE_SUCCESS;
}
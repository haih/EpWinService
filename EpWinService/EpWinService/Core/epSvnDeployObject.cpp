/*! 
SvnDeployObject for the EpWinService

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
	if(m_localPath.GetAt(m_localPath.GetLength()-1)==_T('\\'))
	{
		commandString.Append(_T("\\"));
	}
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
	if(m_localPath.GetAt(m_localPath.GetLength()-1)==_T('\\'))
	{
		commandString.Append(_T("\\"));
	}
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
	if(m_localPath.GetAt(m_localPath.GetLength()-1)==_T('\\'))
	{
		commandString.Append(_T("\\"));
	}
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
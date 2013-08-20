/*! 
BaseDeployObject for the EpWinService

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
#include "epBaseDeployObject.h"
#include "epServiceProperties.h"

BaseDeployObject::BaseDeployObject(CString objectString, CString iniFileName)
{

	m_objectString=objectString;
	m_iniFileName=iniFileName;
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("DeployRepositoryURL"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_repoURL=textBuffer;
	m_repoURL=m_repoURL.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("DeployLocalPath"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_localPath=textBuffer;
	m_localPath=m_localPath.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("DeployUserName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userName=textBuffer;
	m_userName=m_userName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("DeployUserPassword"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userPassword=textBuffer;
	m_userPassword=m_userPassword.Trim();

	EP_DELETE[] textBuffer;
}
BaseDeployObject::~BaseDeployObject()
{

}

void BaseDeployObject::SetRepositoryURL(CString reposURL)
{
	LockObj lock(&m_deployLock);
	m_repoURL=reposURL.Trim();
	WritePrivateProfileString(m_objectString.GetString(),_T("DeployRepositoryURL"),m_repoURL.GetString(),m_iniFileName.GetString());
}
void BaseDeployObject::SetLocalPath(CString localPath)
{
	LockObj lock(&m_deployLock);
	m_localPath=localPath.Trim();
	WritePrivateProfileString(m_objectString.GetString(),_T("DeployLocalPath"),m_localPath.GetString(),m_iniFileName.GetString());
}
void BaseDeployObject::SetUserName(CString userName)
{
	LockObj lock(&m_deployLock);
	m_userName=userName.Trim();
	WritePrivateProfileString(m_objectString.GetString(),_T("DeployUserName"),m_userName.GetString(),m_iniFileName.GetString());
}
void BaseDeployObject::SetUserPassword(CString userPass)
{
	LockObj lock(&m_deployLock);
	m_userPassword=userPass.Trim();
	WritePrivateProfileString(m_objectString.GetString(),_T("DeployUserPassword"),m_userPassword.GetString(),m_iniFileName.GetString());
}

const TCHAR *BaseDeployObject::GetRepositoryURL()
{
	LockObj lock(&m_deployLock);
	return m_repoURL.GetString();
}
const TCHAR *BaseDeployObject::GetLocalPath()
{
	LockObj lock(&m_deployLock);
	return m_localPath.GetString();
}

const TCHAR *BaseDeployObject::GetUserName()
{
	LockObj lock(&m_deployLock);
	return m_userName.GetString();
}

const TCHAR *BaseDeployObject::GetUserPassword()
{
	LockObj lock(&m_deployLock);
	return m_userPassword.GetString();
}
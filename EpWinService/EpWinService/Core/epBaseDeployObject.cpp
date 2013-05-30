/*! 
BaseDeployObject for the EpWinService
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
#include "epBaseDeployObject.h"
#include "epServiceProperties.h"

BaseDeployObject::BaseDeployObject(CString objectString, CString iniFileName)
{

	m_objectString=objectString;
	m_iniFileName=iniFileName;
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("SVNRepositoryURL"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_repoURL=textBuffer;
	m_repoURL=m_repoURL.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("SVNLocalPath"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_localPath=textBuffer;
	m_localPath=m_localPath.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("SVNUserName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userName=textBuffer;
	m_userName=m_userName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(m_objectString.GetString(),_T("SVNUserPassword"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
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
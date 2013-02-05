/*! 
ServiceProperties for the EpWinService
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
#include "epServiceProperties.h"
#include "epBaseManagementObject.h"

ServiceProperties::ServiceProperties()
{
	m_iniFileName=FolderHelper::GetModuleFileName().c_str();
	m_iniFileName.Replace(_T(".exe"),_T(".ini"));
	TCHAR *textBuffer=new TCHAR[MAX_STRING_LENGTH];
	
	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("ServiceName"),_T("EpWinService"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_serviceName=textBuffer;
	m_serviceName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("DomainName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_domainName=textBuffer;
	m_domainName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("UserName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userName=textBuffer;
	m_userName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("UserPassword"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userPassword=textBuffer;
	m_userPassword.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("Dependencies"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_origDependency=textBuffer;
	m_origDependency.Trim();

	m_dependency=m_origDependency;
	m_dependency.Replace(_T(' '), _T('\0'));
	m_dependency.Replace(_T(';'), _T('\0'));

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("UseAdminServer"),_T("Y"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	if(textBuffer[0]=='y'||textBuffer[0]=='Y'||textBuffer[0]=='1')
		m_useAdminServer=true;
	else
		m_useAdminServer=false;

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("CustomProcessCommandLine"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_customProcessCommandLine=textBuffer;
	m_customProcessCommandLine.Trim();
	
	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("AdminServerPort"),_T("8988"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_adminServerPort=textBuffer;
	m_adminServerPort.Trim();

	m_checkProcessInterval=GetPrivateProfileInt(_T("Settings"),_T("CheckProcessInterval"),10,m_iniFileName.GetString());
	m_checkServiceInterval=GetPrivateProfileInt(_T("Settings"),_T("CheckServiceInterval"),10,m_iniFileName.GetString());

	delete[] textBuffer;

}

ServiceProperties::~ServiceProperties()
{

}

const TCHAR *ServiceProperties::GetServiceName()
{
	LockObj lock(&m_lock);
	if(m_serviceName.GetLength()==0 || m_serviceName.Compare(_T(""))==0)
		return NULL;
	return m_serviceName.GetString();
}

const TCHAR *ServiceProperties::GetDomainName()
{
	LockObj lock(&m_lock);
	if(m_domainName.GetLength()==0 || m_domainName.Compare(_T(""))==0)
		return NULL;
	return m_domainName.GetString();
}

const TCHAR * ServiceProperties::GetUserName()
{
	LockObj lock(&m_lock);
	if(m_userName.GetLength()==0 || m_userName.Compare(_T(""))==0)
		return NULL;
	return m_userName.GetString();
}

const TCHAR * ServiceProperties::GetUserPassword()
{
	LockObj lock(&m_lock);
	if(m_userPassword.GetLength()==0 || m_userPassword.Compare(_T(""))==0)
		return NULL;
	return m_userPassword.GetString();
}

const TCHAR * ServiceProperties::GetDependency()
{
	LockObj lock(&m_lock);
	if(m_dependency.GetLength()==0 ||m_dependency.Compare(_T(""))==0)
		return NULL;
	return m_dependency.GetString();
}
CString ServiceProperties::GetOriginalDependency()
{
	return m_origDependency;
}
bool ServiceProperties::GetUseAdminServer()
{
	LockObj lock(&m_lock);
	return m_useAdminServer;
}
const TCHAR *ServiceProperties::GetAdminServerPort()
{
	LockObj lock(&m_lock);
	if(m_adminServerPort.GetLength()==0 ||m_adminServerPort.Compare(_T(""))==0)
		return NULL;
	return m_adminServerPort.GetString();
}


const unsigned int ServiceProperties::GetCheckProcessInterval()
{
	LockObj lock(&m_lock);
	return m_checkProcessInterval;
}

void ServiceProperties::SetCheckProcessInterval(unsigned int timeInMilli)
{
	LockObj lock(&m_lock);
	m_checkProcessInterval=timeInMilli;


	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_checkProcessInterval);
	WritePrivateProfileString(_T("Settings"),_T("CheckProcessInterval"),valueString.GetString(),m_iniFileName.GetString());

}


const unsigned int ServiceProperties::GetCheckServiceInterval()
{
	LockObj lock(&m_lock);
	return m_checkServiceInterval;
}

void ServiceProperties::SetCheckServiceInterval(unsigned int timeInMilli)
{
	LockObj lock(&m_lock);
	m_checkServiceInterval=timeInMilli;


	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_checkServiceInterval);
	WritePrivateProfileString(_T("Settings"),_T("CheckServiceInterval"),valueString.GetString(),m_iniFileName.GetString());

}

CString ServiceProperties::GetCustomProcessCommandLine()
{
	LockObj lock(&m_lock);
	return m_customProcessCommandLine;
}

void ServiceProperties::SetCustomProcessCommandLine(CString cmd)
{
	LockObj lock(&m_lock);
	cmd.Trim();
	m_customProcessCommandLine=cmd;
	WritePrivateProfileString(_T("Settings"),_T("CustomProcessCommandLine"),m_customProcessCommandLine.GetString(),m_iniFileName.GetString());
}


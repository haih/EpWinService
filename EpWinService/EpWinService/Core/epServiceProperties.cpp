/*! 
ServiceProperties for the EpWinService

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
#include "epServiceProperties.h"
#include "epBaseManagementObject.h"

ServiceProperties::ServiceProperties()
{
	m_iniFileName=FolderHelper::GetModuleFileName().c_str();
	m_iniFileName.Replace(_T(".exe"),_T(".ini"));
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];
	
	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("ServiceName"),_T("EpWinService"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_serviceName=textBuffer;
	m_serviceName=m_serviceName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("DomainName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_domainName=textBuffer;
	m_domainName=m_domainName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("UserName"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userName=textBuffer;
	m_userName=m_userName.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("UserPassword"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_userPassword=textBuffer;
	m_userPassword=m_userPassword.Trim();

	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("Dependencies"),_T(""),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_origDependency=textBuffer;
	m_origDependency=m_origDependency.Trim();

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
	m_customProcessCommandLine=m_customProcessCommandLine.Trim();
	
	memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
	GetPrivateProfileString(_T("Settings"),_T("AdminServerPort"),_T("8988"),textBuffer,MAX_STRING_LENGTH,m_iniFileName.GetString());
	m_adminServerPort=textBuffer;
	m_adminServerPort=m_adminServerPort.Trim();

	m_checkProcessInterval=GetPrivateProfileInt(_T("Settings"),_T("CheckProcessInterval"),10,m_iniFileName.GetString());
	m_checkServiceInterval=GetPrivateProfileInt(_T("Settings"),_T("CheckServiceInterval"),10,m_iniFileName.GetString());

	EP_DELETE[] textBuffer;

}

ServiceProperties::~ServiceProperties()
{

}

const TCHAR *ServiceProperties::GetServiceName()
{
	LockObj lock(&m_propertiesLock);
	if(m_serviceName.GetLength()==0 || m_serviceName.Compare(_T(""))==0)
		return NULL;
	return m_serviceName.GetString();
}

const TCHAR *ServiceProperties::GetDomainName()
{
	LockObj lock(&m_propertiesLock);
	if(m_domainName.GetLength()==0 || m_domainName.Compare(_T(""))==0)
		return NULL;
	return m_domainName.GetString();
}

const TCHAR * ServiceProperties::GetUserName()
{
	LockObj lock(&m_propertiesLock);
	if(m_userName.GetLength()==0 || m_userName.Compare(_T(""))==0)
		return NULL;
	return m_userName.GetString();
}

const TCHAR * ServiceProperties::GetUserPassword()
{
	LockObj lock(&m_propertiesLock);
	if(m_userPassword.GetLength()==0 || m_userPassword.Compare(_T(""))==0)
		return NULL;
	return m_userPassword.GetString();
}

const TCHAR * ServiceProperties::GetDependency()
{
	LockObj lock(&m_propertiesLock);
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
	LockObj lock(&m_propertiesLock);
	return m_useAdminServer;
}
const TCHAR *ServiceProperties::GetAdminServerPort()
{
	LockObj lock(&m_propertiesLock);
	if(m_adminServerPort.GetLength()==0 ||m_adminServerPort.Compare(_T(""))==0)
		return NULL;
	return m_adminServerPort.GetString();
}


const unsigned int ServiceProperties::GetCheckProcessInterval()
{
	LockObj lock(&m_propertiesLock);
	return m_checkProcessInterval;
}

void ServiceProperties::SetCheckProcessInterval(unsigned int timeInMilli)
{
	LockObj lock(&m_propertiesLock);
	m_checkProcessInterval=timeInMilli;


	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_checkProcessInterval);
	WritePrivateProfileString(_T("Settings"),_T("CheckProcessInterval"),valueString.GetString(),m_iniFileName.GetString());

}


const unsigned int ServiceProperties::GetCheckServiceInterval()
{
	LockObj lock(&m_propertiesLock);
	return m_checkServiceInterval;
}

void ServiceProperties::SetCheckServiceInterval(unsigned int timeInMilli)
{
	LockObj lock(&m_propertiesLock);
	m_checkServiceInterval=timeInMilli;


	CString valueString=_T("");
	valueString.AppendFormat(_T("%d"),m_checkServiceInterval);
	WritePrivateProfileString(_T("Settings"),_T("CheckServiceInterval"),valueString.GetString(),m_iniFileName.GetString());

}

CString ServiceProperties::GetCustomProcessCommandLine()
{
	LockObj lock(&m_propertiesLock);
	return m_customProcessCommandLine;
}

void ServiceProperties::SetCustomProcessCommandLine(CString cmd)
{
	LockObj lock(&m_propertiesLock);
	m_customProcessCommandLine=cmd.Trim();
	WritePrivateProfileString(_T("Settings"),_T("CustomProcessCommandLine"),m_customProcessCommandLine.GetString(),m_iniFileName.GetString());
}


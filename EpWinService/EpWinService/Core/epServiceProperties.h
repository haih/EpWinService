/*! 
@file epServiceProperties.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Properties Interface
@version 1.0

@section LICENSE

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

@section DESCRIPTION

An Interface for Service Properties.

*/
#ifndef __EP_SERVICE_PROPERTIES_H__
#define __EP_SERVICE_PROPERTIES_H__
#include "epl.h"
using namespace epl;

/*!
@def SERVICE_PROPERTIES_INSTANCE
@brief Service Properties Singleton Instance

Macro for the Service Properties Singleton Instance.
*/
#define SERVICE_PROPERTIES_INSTANCE epl::SingletonHolder<ServiceProperties>::Instance()

/*! 
@class ServiceProperties epServiceProperties.h
@brief A class for Service Properties.
*/
class ServiceProperties 
{
public:
	friend SingletonHolder<ServiceProperties>;

	/*!
	Get the name of the service
	@return the name of the service
	*/
	const TCHAR *GetServiceName();

	/*!
	Get the domain name
	@return the domain name
	*/
	const TCHAR *GetDomainName();

	/*!
	Get the Username
	@return the Username
	*/
	const TCHAR *GetUserName();

	/*!
	Get the User Password
	@return the User Password
	*/
	const TCHAR *GetUserPassword();

	/*!
	Get the Service dependencies with terminating character in-between dependencies
	@return the Service dependencies with terminating character in-between dependencies
	*/
	const TCHAR *GetDependency();

	/*!
	Get the Service depedencies with space in-between dependencies
	@return the Service dependencies with space in-between dependencies
	*/
	CString GetOriginalDependency();

	/*!
	Get the Interval time to check processes
	@return the Interval time to check processes
	*/
	const unsigned int GetCheckProcessInterval();

	
	/*!
	Get the Interval time to check services
	@return the Interval time to check services
	*/
	const unsigned int GetCheckServiceInterval();

	/*!
	Get the flag for using Admin Server
	@return true if using Admin Server otherwise false
	*/
	bool GetUseAdminServer();
	/*!
	Get the port number of Admin Server
	@return the port number of Admin Server
	*/
	const TCHAR *GetAdminServerPort();

	/*!
	Set the Interval time to check processes
	@param[in] timeInMilli the Interval time to check processes
	*/
	void SetCheckProcessInterval(unsigned int timeInMilli);

	/*!
	Set the Interval time to check services
	@param[in] timeInMilli the Interval time to check services
	*/
	void SetCheckServiceInterval(unsigned int timeInMilli);

	/*!
	Get Custom-process CommandLine of the process
	@return Custom-process CommandLine of the process
	*/
	CString GetCustomProcessCommandLine();

	/*!
	Set Custom-process CommandLine of the process
	@param[in] cmd Custom-process CommandLine of the process
	*/
	void SetCustomProcessCommandLine(CString cmd);

private:
	/*!
	Default Constructor

	Initializes the Service Properties
	*/
	ServiceProperties();

	/*!
	Default Destructor

	Destroy the Service Properties
	*/
	~ServiceProperties();

	/// Name of the Service
	CString m_serviceName;
	/// Domain Name
	CString m_domainName;
	/// Username
	CString m_userName;
	/// User Password
	CString m_userPassword;
	/// Dependencies with terminating character in-between dependencies
	CString m_dependency;
	/// Dependencies with space in-between dependencies
	CString m_origDependency;

	/// Interval time to check processes
	unsigned int m_checkProcessInterval;
	/// Interval time to check services
	unsigned int m_checkServiceInterval;

	/// Custom-process CommandLine
	CString m_customProcessCommandLine;

	/// flag for using Admin Server
	bool m_useAdminServer;
	/// Admin Server Port
	CString m_adminServerPort;

	/// Lock
	CriticalSectionEx m_lock;
	/// INI Filename
	CString m_iniFileName;

};
#endif //__EP_SERVICE_PROPERTIES_H__
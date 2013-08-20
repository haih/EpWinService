/*! 
@file epServiceProperties.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Properties Interface
@version 1.0

@section LICENSE

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
@def MAX_STRING_LENGTH
@brief Maximum Byte length of the String

Macro for the Maximum Byte length of the String.
*/
#define MAX_STRING_LENGTH 1024

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
	CriticalSectionEx m_propertiesLock;
	/// INI Filename
	CString m_iniFileName;

};
#endif //__EP_SERVICE_PROPERTIES_H__
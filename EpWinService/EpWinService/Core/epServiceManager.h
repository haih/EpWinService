/*! 
@file epServiceManager.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief Service Manager Interface
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

An Interface for Service Manager.

*/
#ifndef __EP_SERVICE_MANAGER_H__
#define __EP_SERVICE_MANAGER_H__
#include "epl.h"
#include "epProcessHandler.h"
#include "epAdminServer.h"
using namespace epl;

/*!
@def SERVICE_MANAGER_INSTANCE
@brief Service Manager Singleton Instance

Macro for the Service Manager Singleton Instance.
*/
#define SERVICE_MANAGER_INSTANCE epl::SingletonHolder<ServiceManager>::Instance()

/*! 
@class ServiceManager epServiceManager.h
@brief A class for Service Manager.
*/
class ServiceManager{
public:

	friend SingletonHolder<ServiceManager>;

	/*!
	Start the process objects.
	*/
	void ExecuteSubProcess();

	/*!
	Start the Custom-process CommandLine of process object at given index.
	@param[in] idx the index of the process object
	@return true if successfully ran, otherwise false
	*/
	bool CustomProcess(int idx);

	/*!
	Stop the process object at given index
	@param[in] idx the index of the process object
	@return true if successfully stopped, otherwise false
	*/
	bool EndProcess(int idx);

	/*!
	Start the process object at given index
	@param[in] idx the index of the process object
	@return true if successfully started, otherwise false
	*/
	bool StartProcess(int idx);

	/*!
	Restart the process object at given index
	@param[in] idx the index of the process object
	@return true if successfully restarted, otherwise false
	*/
	bool BounceProcess(int idx);

	/*!
	Start the service
	@return true if successfully started, otherwise false
	*/
	bool RunService();

	/*!
	Stop the service
	@return true if successfully stopped, otherwise false
	*/
	bool KillService();

	/*!
	Install the service
	*/
	void Install();

	/*!
	Uninstall the service
	*/
	void UnInstall();

	/*!
	Start the admin server
	@return true if successfully started, otherwise false
	*/
	bool StartAdminServer();

	/*!
	Stop the admin server
	*/
	void StopAdminServer();

	/*!
	Get the service status
	@return the service status
	*/
	SERVICE_STATUS &GetServiceStatus()
	{
		return m_serviceStatus;
	}

	/*!
	Get the service status handle
	@return the service status handle
	*/
	SERVICE_STATUS_HANDLE &GetServiceStatusHandle()
	{
		return m_hServiceStatusHandle;
	}
private:

	/*!
	Default Constructor

	Initializes the Service Manager
	*/
	ServiceManager(){
	}

	/*!
	Default Destructor

	Destroy the Service Manager
	*/
	~ServiceManager(){}

	/// Service Status
	SERVICE_STATUS          m_serviceStatus; 
	/// Service Status Handle
	SERVICE_STATUS_HANDLE   m_hServiceStatusHandle; 

	/// Admin Server object
	AdminServer m_adminServer;


};

#endif //__EP_SERVICE_MANAGER_H__
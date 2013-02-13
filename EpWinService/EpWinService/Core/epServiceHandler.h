/*! 
@file epServiceHandler.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Handler Interface
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

An Interface for Service Handler.

*/
#ifndef __EP_SERVICE_HANDLER_H__
#define __EP_SERVICE_HANDLER_H__
#include "epl.h"
#include "epServiceDefines.h"
#include "epServiceObject.h"
using namespace epl;

/*!
@def SERVICE_HANDLER_INSTANCE
@brief Service Handler Singleton Instance

Macro for the Service Handler Singleton Instance.
*/
#define SERVICE_HANDLER_INSTANCE epl::SingletonHolder<ServiceHandler>::Instance()


/*!
@fn VOID ServiceMonitorThread(VOID *)
@brief A Thread Function which monitors the services' termination or fault.

Monitor the service's termination or fault and restart the service if stopped
*/

VOID ServiceMonitorThread(VOID *);

/*! 
@struct ServiceInfo epServiceHandler.h
@brief A struct for Service Info.
*/
struct ServiceInfo{
	/// Display Name
	EpTString displayName;
	/// Desired Access
	ServiceDesiredAccess desiredAccess;
	/// Service Type
	ServiceType serviceType;
	/// Start Type
	ServiceStartType startType;
	/// Error Control
	ServiceErrorControl errorControl;
	/// BinaryPathName
	EpTString binaryPathName;
	/// LoadOrderGroup
	EpTString loadOrderGroup;
	/// Dependencies
	EpTString dependencies;
	/// Domain Name
	EpTString domainName;
	/// User Name
	EpTString userName;
	/// UserPassword
	EpTString password;
	/// Edit Control Bit
	unsigned int editControlBit;
};




/*! 
@class ServiceHandler epServiceHandler.h
@brief A class for Service Handler.
*/
class ServiceHandler{
public:

	friend SingletonHolder<ServiceHandler>;

	/*!
	Start the service
	@param[in] serviceName the name of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError StartService(const TCHAR *serviceName, DWORD &retErrCode);

	/*!
	Continue the service
	@param[in] serviceName the name of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError ContinueService(const TCHAR *serviceName, DWORD &retErrCode);

	/*!
	Stop the service
	@param[in] serviceName the name of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError StopService(const TCHAR *serviceName, DWORD &retErrCode);

	/*!
	Pause the service
	@param[in] serviceName the name of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError PauseService(const TCHAR *serviceName, DWORD &retErrCode);

	/*!
	Pause the service
	@param[in] serviceName the name of the service
	@param[in] code the control code for the service
	@param[out] retStatus current status of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError ControlService(const TCHAR *serviceName,ServiceControlCode code, SERVICE_STATUS &retStatus , DWORD &retErrCode);
	
	

	/*!
	Install the service
	@param[in] serviceName the name of the service
	@param[in] info the information of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError InstallService(const TCHAR *serviceName, ServiceInfo info, DWORD &retErrCode);

	/*!
	Uninstall the service
	@param[in] serviceName the name of the service
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError UnInstallService(const TCHAR *serviceName, DWORD &retErrCode);

	/*!
	Edit configurations set when installing the service
	@param[in] serviceName the name of the service
	@param[in] info the information of the service to set
	@param[out] retErrCode the error code
	@return Service Process Status
	*/
	ServiceHandlerError EditService(const TCHAR *serviceName,ServiceInfo info, DWORD &retErrCode);


	/*!
	Return the status of service
	@param[in] serviceName the name of the service
	@param[out] retStatus current status of the service
	@param[out] retErrCode the error code
	@return Service Status
	*/
	ServiceHandlerError GetServiceStatus(const TCHAR *serviceName, SERVICE_STATUS_PROCESS &retStatus, DWORD &retErrCode);

	/*!
	Return the pointer to the service object at given index.
	@param[in] serviceIndex the index of the service object to retrieve
	@return the pointer to the service object
	*/
	ServiceObject *&At(unsigned int serviceIndex);

	/*!
	Return the number of services handling.
	@return number of services in the list
	*/
	unsigned int GetNumberOfServices() const
	{
		return m_serviceList.size();
	}
private:

	/*!
	Default Constructor

	Initializes the Service Manager
	*/
	ServiceHandler();

	/*!
	Default Destructor

	Destroy the Service Manager
	*/
	~ServiceHandler();

	SC_HANDLE m_scManager;

	/// Process List
	vector<ServiceObject*> m_serviceList;
};

#endif //__EP_SERVICE_HANDLER_H__
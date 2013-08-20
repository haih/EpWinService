/*! 
@file epServiceHandler.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Handler Interface
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
		return static_cast<unsigned int>(m_serviceList.size());
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
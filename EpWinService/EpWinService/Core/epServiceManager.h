/*! 
@file epServiceManager.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Manager Interface
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
	Start the Main Service.
	*/
	void ExecuteSubProcess();

	/*!
	Test the Main Service.
	*/
	void TestSubProcess();

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
	Run the Custom Process
	@param[in] waitTimeInMilliSec wait time in milli-seconds
	@remark waitTimeInMilliSec is equal to WAITTIME_INIFINITE (0xffffffff) then waits for infinite time.
	*/
	void RunCustomProcess(int waitTimeInMilliSec);

	/*!
	Run command.
	@param[in] command command to run
	@param[in] waitTimeInMilliSec wait time in milli-seconds
	@remark waitTimeInMilliSec is equal to WAITTIME_INIFINITE (0xffffffff) then waits for infinite time.
	*/
	void RunCommand(CString command, int waitTimeInMilliSec);

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
	Replace the given command's arguments
	@param[in] cmd the single command to replace
	*/
	void replaceCommandArgument(CString &cmd);

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

	/// Custom-process CommandLine List
	vector<CString> m_customProcessCommandLineList;


};

#endif //__EP_SERVICE_MANAGER_H__
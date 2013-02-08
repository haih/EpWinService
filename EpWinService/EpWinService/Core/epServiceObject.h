/*! 
@file epServiceObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Object Interface
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

An Interface for Service Object.

*/
#ifndef __EP_SERVICE_OBJECT_H__
#define __EP_SERVICE_OBJECT_H__
#include "epBaseManagementObject.h"
#include "epServiceDefines.h"

/*! 
@class ServiceObject epServiceObject.h
@brief A class for Service Object.
*/
class ServiceObject:public BaseManagementObject{

public:
	/*!
	Default Constructor

	Initializes the Service Object
	@param[in] serviceIndex the index of this service object
	*/
	ServiceObject(unsigned int serviceIndex);

	/*!
	Default Destructor

	Destroy the Service Object
	*/
	virtual ~ServiceObject();
	/*!
	Start the Service.
	@return true if started, otherwise false
	*/
	virtual bool Start();

	/*!
	Stop the Service.
	*/
	virtual void Stop();

	/*!
	Pause the Service.
	*/
	void Pause();

	/*!
	Continue the Service.
	*/
	void Continue();


	/*!
	Return whether this service is started or not
	@return true if started, otherwise false
	*/
	virtual bool IsStarted();

	/*!
	Reset the process to start again
	*/
	virtual void Reset();


	/*!
	Return the status of the service
	@return the status of the service
	*/	
	ServiceStatusType GetStatus();
	
	/*!
	Start the custom-Process.
	@param[in] waitTimeInMilliSec wait time in milli-seconds
	@remark waitTimeInMilliSec is equal to WAITTIME_INIFINITE (0xffffffff) then waits for infinite time.
	*/
	virtual void CustomProcess(int waitTimeInMilliSec);

	/*!
	Run command.
	@param[in] command command to run
	@param[in] waitTimeInMilliSec wait time in milli-seconds
	@remark waitTimeInMilliSec is equal to WAITTIME_INIFINITE (0xffffffff) then waits for infinite time.
	*/
	virtual void RunCommand(CString command, int waitTimeInMilliSec);

	/*!
	Get name of the service
	@return name of the service
	*/
	CString GetServiceName();
	
	/*!
	Set name of the service
	@param[in] name name of the service
	*/
	void SetServiceName(CString name);

	/*!
	Get flag for userStopped
	@return flag for userStopped
	*/
	bool GetIsUserStopped();
	
	/*!
	Set flag for userStopped
	@param[in] isUserStopped flag for userStopped
	*/
	void SetIsUserStopped(bool isUserStopped);



private:
	/*!
	Replace the given command's arguments
	@param[in] cmd the single command to replace
	*/
	virtual void replaceCommandArgument(CString &cmd);

	/// name of the service
	CString m_serviceName;
	/// flag whether user stopped the service
	bool m_isUserStopped;

};
#endif //__EP_SERVICE_OBJECT_H__
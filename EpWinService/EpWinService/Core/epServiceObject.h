/*! 
@file epServiceObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Object Interface
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
	Start the Service.
	@return ObjectStartStatus
	*/
	virtual ObjectStartStatus start();

	/*!
	Stop the Service.
	*/
	virtual void stop();

	/*!
	Replace the given command's arguments
	@param[in] cmd the single command to replace
	@remark "%t" or "%T" refers to current time <br/>
			"%x" or "%X" refers to object index <br/>
			"%o" or "%o" refers to object type <br/>
			"%n" or "%N" refers to Service Name <br/>
	*/
	virtual void replaceCommandArgument(CString &cmd);

	/// name of the service
	CString m_serviceName;
	/// flag whether user stopped the service
	bool m_isUserStopped;

};
#endif //__EP_SERVICE_OBJECT_H__
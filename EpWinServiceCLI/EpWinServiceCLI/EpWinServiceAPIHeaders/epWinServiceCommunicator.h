/*! 
@file epWinServiceCommunicator.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Communicator Interface
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

An Interface for WinService Communicator.

*/
#ifndef __EP_WINSERVICE_COMMUNICATOR_H__
#define __EP_WINSERVICE_COMMUNICATOR_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceClient.h"
#include "epWinServiceResult.h"
#include "epWinServicePacketGenerator.h"


namespace epws
{
	/// WinService Communicator Send Error Enum
	typedef enum _winServiceCommunicatorSendError{
		/// Sent successfully
		WINSERVICE_COMMUNICATOR_SEND_ERROR_SUCCESS=0,
		/// Connection failed
		WINSERVICE_COMMUNICATOR_SEND_ERROR_CONNECTION_FAILED,
		/// Send failed
		WINSERVICE_COMMUNICATOR_SEND_ERROR_SEND_FAILED,
		/// Receive failed
		WINSERVICE_COMMUNICATOR_SEND_ERROR_RECEIVE_FAILED,

	}WinServiceCommunicatorSendError;

	/*! 
	@class WinServiceCommunicator epWinServiceCommunicator.h
	@brief A class for WinService Communicator.
	*/
	class EP_WINSERVICE_API WinServiceCommunicator: public epl::SmartObject
	{
	public:
		/*!
		Default Constructor

		Initializes the Communicator
		@param[in] hostName the hostname string
		@param[in] port the port string
		@param[in] waitTimeMilliSec wait time for thread to terminate
		@param[in] lockPolicyType The lock policy
		*/
		WinServiceCommunicator(const TCHAR * hostName=_T(DEFAULT_HOSTNAME), const TCHAR * port=DEFAULT_WINSERVICE_PORT,unsigned int waitTimeMilliSec=WAITTIME_INIFINITE,LockPolicy lockPolicyType=EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Communicator
		*/
		~WinServiceCommunicator();

		/*!
		Default Copy Constructor

		Initializes the WinServiceCommunicator
		@param[in] b the second object
		*/
		WinServiceCommunicator(const WinServiceCommunicator& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServiceCommunicator & operator=(const WinServiceCommunicator&b);

		/*!
		Return the hostname
		@return the hostname
		*/
		const TCHAR *GetHostName() const;

		/*!
		Return the port number
		@return the port number
		*/
		const TCHAR *GetPort() const;

		/*!
		Set the hostname and the port number
		@param[in] hostName the hostname to set
		@param[in] port the port number to set
		*/
		void SetServerInfo(const TCHAR *hostName, const TCHAR *port);

		/*!
		Send generated packet to the server
		@param[in] packetGenerator the packet to send
		@param[out] retResult the result
		@param[in] waitTimeMilliSec wait time for receiving from server
		@return the error code for sending
		*/
		WinServiceCommunicatorSendError Send(const WinServicePacketGenerator& packetGenerator, WinServiceResult &retResult,unsigned int waitTimeMilliSec=WAITTIME_INIFINITE);
		


	private:
		/// Client object
		WinServiceClient m_client;
		/// Hostname
		EpTString m_hostName;
		/// Port Number
		EpTString m_port;
		/// the lock
		BaseLock * m_communicatorLock;
		/// Lock Policy
		LockPolicy m_lockPolicy;


	};



}

#endif //__EP_WINSERVICE_COMMUNICATOR_H__
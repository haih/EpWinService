/*! 
@file epWinServiceCommunicator.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Communicator Interface
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
		BaseLock * m_lock;
		/// Lock Policy
		LockPolicy m_lockPolicy;


	};



}

#endif //__EP_WINSERVICE_COMMUNICATOR_H__
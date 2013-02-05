/*! 
@file epWinServicePacketIDGenerator.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Packet ID Generator Interface
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

An Interface for WinService Packet ID Generator.

*/
#ifndef __EP_WINSERVICE_PACKET_ID_GENERATOR_H__
#define __EP_WINSERVICE_PACKET_ID_GENERATOR_H__

#include "epWinServiceAPILibrary.h"


namespace epws
{

	/*! 
	@class WinServicePacketIDGenerator epWinServicePacketIDGenerator.h
	@brief A class for WinService Packet ID Generator.
	*/
	class EP_WINSERVICE_API WinServicePacketIDGenerator
	{
	private:
		friend class WinServiceCommunicator;
		/*!
		Default Constructor

		Initializes the Packet Generator
		@param[in] lockPolicyType The lock policy
		*/
		WinServicePacketIDGenerator(LockPolicy lockPolicyType=EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Packet Generator
		*/
		~WinServicePacketIDGenerator();

		/*!
		Default Copy Constructor

		Initializes the WinServicePacketGenerator
		@param[in] b the second object
		*/
		WinServicePacketIDGenerator(const WinServicePacketIDGenerator& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServicePacketIDGenerator & operator=(const WinServicePacketIDGenerator&b);

		/*!
		Generate ID for Packet
		@return the generated packet ID
		*/
		unsigned int GenerateID();

	private:
		/// Packet ID incremental
		unsigned int m_packetID;

		/// the lock
		BaseLock * m_lock;
		/// Lock Policy
		LockPolicy m_lockPolicy;
	};



}

#endif //__EP_WINSERVICE_PACKET_ID_GENERATOR_H__
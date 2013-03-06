/*! 
@file epWinServicePacketGenerator.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Packet Generator Interface
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

An Interface for WinService Packet Generator.

*/
#ifndef __EP_WINSERVICE_PACKET_GENERATOR_H__
#define __EP_WINSERVICE_PACKET_GENERATOR_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceDefines.h"
#include "epWinServiceClientPacketInfo.h"
#include "epWinServiceInfoStruct.h"

namespace epws
{



	/*! 
	@class WinServicePacketGenerator epWinServicePacketGenerator.h
	@brief A class for WinService Packet Generator.
	*/
	class EP_WINSERVICE_API WinServicePacketGenerator:public epl::SmartObject
	{
	public:
		friend class WinServiceCommunicator;
		/*!
		Default Constructor

		Initializes the Packet Generator
		@param[in] lockPolicyType The lock policy
		*/
		WinServicePacketGenerator(LockPolicy lockPolicyType=EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Packet Generator
		*/
		~WinServicePacketGenerator();

		/*!
		Default Copy Constructor

		Initializes the WinServicePacketGenerator
		@param[in] b the second object
		*/
		WinServicePacketGenerator(const WinServicePacketGenerator& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServicePacketGenerator & operator=(const WinServicePacketGenerator&b);

		/*!
		Return the added processes count
		@return the added processes count
		*/
		unsigned int GetCount() const;

		/*!
		Clear all added processes
		*/
		void Clear();

		/*!
		Add Command Main Service frame to the packet
		@param[in] type type of the command
		@param[in] waitTime wait time for command to run (Optional)
		@param[in] cmd the command for RunCommand type.
		@remark waitTime is for RunCommand/CustomProcess command type
		@remark cmd is only for RunCommand command type
		*/
		void AddCommandMainService(CommandMainServicePackeType type,int waitTime=WAITTIME_INIFINITE, EpTString cmd =_T(""));

		/*!
		Add Get Main Service Info frame to the packet
		@param[in] type type of the information getting
		*/
		void AddGetMainServiceInfo(MainServiceInfoGetPacketType type);

		/*!
		Add Set Main Service Info frame to the packet
		@param[in] type type of the information setting
		@param[in] info the information to set
		*/
		void AddSetMainServiceInfo(MainServiceInfoSetPacketType type,MainServiceInfo info);

		/*!
		Add Command Service Object frame to the packet
		@param[in] type type of the command
		@param[in] objIndex the object index to command (OBJECT_IDX_ALL for all Service Objects)
		@param[in] waitTime wait time for command to run (Optional)
		@param[in] cmd the command for RunCommand type. (Optional)
		@remark waitTime is for RunCommand/CustomProcess command type
		@remark cmd is only for RunCommand command type
		*/
		void AddCommandServiceObj(CommandServiceObjectPacketType type, int objIndex,int waitTime=WAITTIME_INIFINITE, EpTString cmd =_T(""));

		/*!
		Add Get Service Object Info frame to the packet
		@param[in] type type of the information getting
		@param[in] serviceIndex the index of the service object to get info
		*/
		void AddGetServiceInfo(ServiceObjectInfoGetPacketType type, unsigned int serviceIndex);

		/*!
		Add Set Service Object Info frame to the packet
		@param[in] type type of the information setting
		@param[in] serviceIndex the index of the service object to get info
		@param[in] info the information to set
		*/
		void AddSetServiceInfo(ServiceObjectInfoSetPacketType type, unsigned int serviceIndex, ServiceObjInfo info);

		/*!
		Add Command Process Object frame to the packet
		@param[in] type type of the command
		@param[in] objIndex the object index to command (OBJECT_IDX_ALL for all Process Objects)
		@param[in] waitTime wait time for command to run (Optional)
		@param[in] cmd the command for RunCommand type. (Optional)
		@remark waitTime is for RunCommand/CustomProcess command type
		@remark cmd is only for RunCommand command type
		*/
		void AddCommandProcessObj(CommandProcessObjectPacketType type, int objIndex,int waitTime=WAITTIME_INIFINITE, EpTString cmd =_T(""));

		/*!
		Add Get Process Object Info frame to the packet
		@param[in] type type of the information getting
		@param[in] procIndex the index of the process object to get info
		*/
		void AddGetProcessInfo(ProcessObjectInfoGetPacketType type, unsigned int procIndex);

		/*!
		Add Set Process Object Info frame to the packet
		@param[in] type type of the information setting
		@param[in] procIndex the index of the process object to get info
		@param[in] info the information to set
		*/
		void AddSetProcessInfo(ProcessObjectInfoSetPacketType type, unsigned int procIndex,ProcessObjInfo info);

		/*!
		Add Command Service frame to the packet
		@param[in] type type of the command
		@param[in] serviceName the name of the service to command
		@param[in] info the information to set
		*/
		void AddCommandService(ServiceCommandPacketType type, const TCHAR *serviceName, ServiceInfo info);




	private:
		/*!
		Return the stream by unsigned char buffer
		@return the stream by unsigned char buffer
		*/
		const unsigned char *GetStream() const;

		/*!
		Return the byte size of the stream
		@return the byte size of the stream
		*/
		unsigned int GetStreamByteSize() const;

		/// stream
		epl::Stream m_stream;
		/// packet count
		unsigned int m_count;
		/// the lock
		BaseLock * m_packetGeneratorLock;
		/// Lock Policy
		LockPolicy m_lockPolicy;
	};



}

#endif //__EP_WINSERVICE_PACKET_GENERATOR_H__
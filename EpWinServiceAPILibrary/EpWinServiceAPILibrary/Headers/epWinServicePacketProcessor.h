/*! 
@file epWinServicePacketProcessor.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Client Packet Processor Interface
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

An Interface for WinService Client Packet Processor.

*/
#ifndef __EP_WINSERVICE_PACKET_PROCESSOR_H__
#define __EP_WINSERVICE_PACKET_PROCESSOR_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServicePacketParser.h"
#include "epWinServiceClientPacketInfo.h"
#include "epStream.h"
#include "epWinServiceResult.h"

namespace epws
{
	/*! 
	@class WinServicePacketProcessor epWinServicePacketProcessor.h
	@brief A class for  WinService Client Packet Processor.
	*/
	class EP_WINSERVICE_API WinServicePacketProcessor
	{
	private:
		friend class WinServiceCommunicator;
		/*!
		Default Constructor

		Initializes the Processor
		*/
		WinServicePacketProcessor()
		{

		}

		/*!
		Default Destructor

		Destroy the Processor
		*/
		~WinServicePacketProcessor()
		{

		}

		/*!
		Process the given packet relative to its type, and retrieve the results.
		@param[in] packet the packet to process
		@param[out] retResult the Result Object
		*/
		void Process(const epse::Packet *packet, WinServiceResult &retResult);

	private:
		/*!
		Process the Command Process Object type packet.
		@param[in] subPacketType the command type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus commandProcessObject(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo);

		/*!
		Process the Command Service Object type packet.
		@param[in] subPacketType the command type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus commandServiceObject(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo);

		/*!
		Process the Main Service Command type packet.
		@param[in] subPacketType the command type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus commandMainService(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo);
		/*!
		Process the GetMainServiceInfo type packet.
		@param[in] subPacketType the MainServiceInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus getMainServiceInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo);
		/*!
		Process the SetMainServiceInfo type packet.
		@param[in] subPacketType the MainServiceInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus setMainServiceInfo(unsigned int subPacketType,epl::Stream &stream, WinServiceResultInfo* retInfo);	
		/*!
		Process the GetProcessInfo type packet.
		@param[in] subPacketType the ProcessInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus getProcessInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo);
		/*!
		Process the SetProcessInfo type packet.
		@param[in] subPacketType the ProcessInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus setProcessInfo(unsigned int subPacketType,epl::Stream &stream, WinServiceResultInfo* retInfo);
		/*!
		Process the GetServiceInfo type packet.
		@param[in] subPacketType the ServiceInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus getServiceInfo(unsigned int subPacketType,epl::Stream &stream, WinServiceResultInfo* retInfo);
		/*!
		Process the SetServiceInfo type packet.
		@param[in] subPacketType the ServiceInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus setServiceInfo(unsigned int subPacketType,epl::Stream &stream, WinServiceResultInfo* retInfo);	

		/*!
		Process the CommandService type packet.
		@param[in] subPacketType the ProcessInfo type to process
		@param[in] stream the packet stream to process
		@param[out] retInfo the retrieved info
		@return the Retrieve Status
		*/
		RetrieveStatus commandService(unsigned int subPacketType,epl::Stream &stream, WinServiceResultInfo* retInfo);

	};



}

#endif //__EP_WINSERVICE_PACKET_PROCESSOR_H__
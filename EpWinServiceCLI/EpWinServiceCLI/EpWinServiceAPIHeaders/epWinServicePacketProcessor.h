/*! 
@file epWinServicePacketProcessor.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Client Packet Processor Interface
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

An Interface for WinService Client Packet Processor.

*/
#ifndef __EP_WINSERVICE_PACKET_PROCESSOR_H__
#define __EP_WINSERVICE_PACKET_PROCESSOR_H__

#include "epWinServiceAPILibrary.h"
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
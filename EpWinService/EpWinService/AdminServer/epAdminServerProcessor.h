/*! 
@file epAdminServerProcessor.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Packet Processor Interface
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

An Interface for Admin Server Packet Processor.

*/
#ifndef __EP_ADMIN_SERVER_PROCESSOR_H__
#define __EP_ADMIN_SERVER_PROCESSOR_H__

#include "epse.h"
#include "epAdminServerPacketParser.h"
#include "epAdminServerPacketInfo.h"
#include "epStream.h"
using namespace epl;
using namespace epse;


/*! 
@class AdminServerProcessor epAdminServerProcessor.h
@brief A class for Admin Server Packet Processor.
*/
class AdminServerProcessor
{
public:
	/*!
	Default Constructor

	Initializes the Processor
	*/
	AdminServerProcessor()
	{

	}

	/*!
	Default Destructor

	Destroy the Processor
	*/
	~AdminServerProcessor()
	{

	}

	/*!
	Process the given packet relative to its type, and send back the result to the client.
	@param[in] curClient the client that the packet received from
	@param[in] packet the packet to process
	*/
	void Process(AdminServerPacketParser *curClient,const Packet *packet);

private:

	/*!
	Actually process the Process Command type packet and save the result to the retOutStream.
	@param[in] subPacketType the command type to process
	@param[in] stream the packet stream received
	@param[out] retOutStream the stream to save the result status
	*/
	void commandProcessObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

	/*!
	Actually process the Service Command type packet and save the result to the retOutStream.
	@param[in] subPacketType the command type to process
	@param[in] stream the packet stream received
	@param[out] retOutStream the stream to save the result status
	*/
	void commandServiceObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

	/*!
	Process the Main Service Command type packet and save the result to the retOutStream.
	@param[in] subPacketType the command type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void commandMainServiceObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

	/*!
	Process the GetServiceInfo type packet and save the result to the retOutStream.
	@param[in] subPacketType the ServiceInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void getMainServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream);
	/*!
	Process the SetServiceInfo type packet and save the result to the retOutStream.
	@param[in] subPacketType the ServiceInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void setMainServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream);	
	/*!
	Process the GetProcessInfo type packet and save the result to the retOutStream.
	@param[in] subPacketType the ProcessInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void getProcessInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream);
	/*!
	Process the SetProcessInfo type packet and save the result to the retOutStream.
	@param[in] subPacketType the ProcessInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void setProcessInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

	/*!
	Process the GetServiceInfo type packet and save the result to the retOutStream.
	@param[in] subPacketType the ServiceInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void getServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream);
	/*!
	Process the SetServiceInfo type packet and save the result to the retOutStream.
	@param[in] subPacketType the ServiceInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void setServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

	/*!
	Process the CommandService type packet and save the result to the retOutStream.
	@param[in] subPacketType the ProcessInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void commandService(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

};



#endif //__EP_ADMIN_SERVER_PROCESSOR_H__
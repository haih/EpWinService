/*! 
@file epAdminServerProcessor.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief Admin Server Packet Processor Interface
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
@def ADMIN_SERVER_PROCESS_INSTANCE
@brief Admin Server Packet Processor Singleton Instance

Macro for the Admin Server Packet Processor Singleton Instance.
*/
#define ADMIN_SERVER_PROCESS_INSTANCE epl::SingletonHolder<AdminServerProcessor>::Instance()

/*! 
@class AdminServerProcessor epAdminServerProcessor.h
@brief A class for Admin Server Packet Processor.
*/
class AdminServerProcessor
{
public:
	friend class SingletonHolder<AdminServerProcessor>;

	/*!
	Process the given packet relative to its type, and send back the result to the client.
	@param[in] curClient the client that the packet received from
	@param[in] packet the packet to process
	*/
	void Process(AdminServerPacketParser *curClient,const Packet *packet);

private:
	/*!
	Process the Command type packet and save the result to the retOutStream.
	@param[in] subPacketType the command type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void commandProcess(unsigned int subPacketType,Stream &stream,Stream &retOutStream);
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
	Process the CommandService type packet and save the result to the retOutStream.
	@param[in] subPacketType the ProcessInfo type to process
	@param[in] stream the packet stream to process
	@param[out] retOutStream the stream to save the result status
	*/
	void commandService(unsigned int subPacketType,Stream &stream,Stream &retOutStream);

private:
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
};



#endif //__EP_ADMIN_SERVER_PROCESSOR_H__
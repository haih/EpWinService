/*! 
@file epAdminServerPacketParser.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Packet Parser Interface
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

An Interface for Admin Server Packet Parser.

*/
#ifndef __EP_ADMIN_SERVER_PACKET_PARSER_H__
#define __EP_ADMIN_SERVER_PACKET_PARSER_H__
#include "epse.h"

using namespace epl;
using namespace epse;

/*! 
@class AdminServerPacketParser epAdminServerPacketParser.h
@brief A class for Admin Server Packet Parser.
*/
class AdminServerPacketParser:public BasePacketParser
{
public:
	/*!
	Default Constructor

	Initializes the Parser
	@param[in] waitTimeMilliSec the wait time in millisecond for terminating
	*/
	AdminServerPacketParser(unsigned int waitTimeMilliSec=WAITTIME_INIFINITE);

	/*!
	Default Copy Constructor

	Initializes the AdminServerPacketParser
	@param[in] b the second object
	*/
	AdminServerPacketParser(const AdminServerPacketParser& b);

	/*!
	Default Destructor

	Destroy the Parser
	*/
	virtual ~AdminServerPacketParser();

	/*!
	Assignment operator overloading
	@param[in] b the second object
	@return the new copied object
	*/
	AdminServerPacketParser & operator=(const AdminServerPacketParser&b)
	{
		if(this!=&b)
		{
			BasePacketParser::operator =(b);
		}
		return *this;
	}

	/*!
	Parse the given packet and do relevant operation
	@param[in] packet the packet to parse
	*/
	virtual void ParsePacket(const Packet &packet );
};

#endif// __EP_ADMIN_SERVER_PACKET_PARSER_H__
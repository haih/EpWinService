/*! 
@file epAdminServerPacketParser.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Packet Parser Interface
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
	AdminServerPacketParser(unsigned int waitTimeMilliSec=DEFAULT_WAITTIME);

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
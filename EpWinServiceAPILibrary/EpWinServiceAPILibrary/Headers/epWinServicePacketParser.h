/*! 
@file epWinServicePacketParser.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Client Packet Parser Interface
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

An Interface for WinService Client Packet Parser.

*/
#ifndef __EP_WINSERVICE_PACKET_PARSER_H__
#define __EP_WINSERVICE_PACKET_PARSER_H__
#include "epWinServiceAPILibrary.h"
#include "epWinServiceParserList.h"
namespace epws
{

	class WinServiceParserList;
	/*! 
	@class WinSeriviceClientPacketParser epWinServicePacketParser.h
	@brief A class for WinService Client Packet Parser.
	*/
	class EP_WINSERVICE_API WinServicePacketParser:public epse::BasePacketParser
	{
	private:
		friend class WinServiceClient;
		/*!
		Default Constructor

		Initializes the Parser
		@param[in] parserList Parser List
		@param[in] waitTimeMilliSec the wait time in millisecond for terminating
		*/
		WinServicePacketParser(WinServiceParserList *parserList=NULL,unsigned int waitTimeMilliSec=DEFAULT_WAITTIME);

		/*!
		Default Copy Constructor

		Initializes the WinServicePacketParser
		@param[in] b the second object
		*/
		WinServicePacketParser(const WinServicePacketParser& b);

		/*!
		Default Destructor

		Destroy the Parser
		*/
		virtual ~WinServicePacketParser();

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServicePacketParser & operator=(const WinServicePacketParser&b)
		{
			if(this!=&b)
			{
				epse::BasePacketParser::operator =(b);
				if(m_parserList)
					m_parserList->ReleaseObj();
				m_parserList=b.m_parserList;
				if(m_parserList)
					m_parserList->RetainObj();
			}
			return *this;
		}

		/*!
		Parse the given packet and do relevant operation
		@param[in] packet the packet to parse
		*/
		virtual void ParsePacket(const epse::Packet &packet );

		/// Parser List Pointer
		WinServiceParserList *m_parserList;
	};
}


#endif// __EP_WINSERVICE_PACKET_PARSER_H__
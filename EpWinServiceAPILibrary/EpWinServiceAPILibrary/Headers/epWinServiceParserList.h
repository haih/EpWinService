/*! 
@file epWinServiceParserList.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Parser List Interface
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

An Interface for Parser List.

*/
#ifndef __EP_WINSERVICE_PARSER_LIST_H__
#define __EP_WINSERVICE_PARSER_LIST_H__

#include "epWinServiceAPILibrary.h"
#include <vector>

using namespace std;

namespace epws
{
	
	class WinServicePacketParser;

	/*! 
	@class WinServiceParserList epWinServiceParserList.h
	@brief A class for WinService Packet Parser List.
	*/
	class EP_WINSERVICE_API WinServiceParserList:public epl::SmartObject
	{
	private:
		friend class WinServiceCommunicator;
		friend class WinServicePacketParser;

		/*!
		Default Constructor

		Initializes the Parser List
		@param[in] lockPolicyType The lock policy
		*/
		WinServiceParserList(LockPolicy lockPolicyType=EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Parser List
		*/
		virtual ~WinServiceParserList();

		/*!
		Default Copy Constructor

		Initializes the WinServiceParserList
		@param[in] b the second object
		*/
		WinServiceParserList(const WinServiceParserList& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServiceParserList & operator=(const WinServiceParserList&b);

		/*!
		Add new Packet ID and Packet Parser pair to the list
		@param[in] packetId the packet ID
		@param[in] parser the parser of the packet received
		@remark the parser will be retained automatically
		*/
		void Push(unsigned int packetId,WinServicePacketParser *parser);

		/*!
		Get WinServicePacketParser with given Packet ID
		@param[in] packetId the packet ID to find WinServicePacketParser
		@return the pointer to the WinServicePacketParser object found
		@remark the caller MUST call "ReleaseObj" for returned parser to avoid memory leak.
		*/
		WinServicePacketParser *PopParser(unsigned int packetID);

		/*!
		Clear the Parser List.
		*/
		void Clear();

	private:
		/// Parser List
		vector<Pair<unsigned int,WinServicePacketParser*> > m_parserList;
		/// Lock Policy
		LockPolicy m_lockPolicy;
		/// the lock
		BaseLock * m_lock;
	};
}

#endif //__EP_WINSERVICE_PARSER_LIST_H__
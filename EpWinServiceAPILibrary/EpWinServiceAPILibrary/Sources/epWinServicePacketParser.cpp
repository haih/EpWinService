/*! 
WinService Client Packet Parser for the EpWinServiceAPILibrary
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
*/
#include "epWinServicePacketParser.h"
#include "epWinServiceClientPacketInfo.h"
#include "epWinServiceParserList.h"

using namespace epws;
WinServicePacketParser::WinServicePacketParser(WinServiceParserList *parserList,unsigned int waitTimeMilliSec):epse::BasePacketParser(waitTimeMilliSec)
{
	m_parserList=parserList;
	if(m_parserList)
		m_parserList->RetainObj();
}

WinServicePacketParser::WinServicePacketParser(const WinServicePacketParser& b):epse::BasePacketParser(b)
{
	if(m_parserList)
		m_parserList->ReleaseObj();
}

WinServicePacketParser::~WinServicePacketParser()
{

}

void WinServicePacketParser::ParsePacket(const epse::Packet &packet )
{
	//TODO: Parse Packet

	PacketContainer<ReceivePacket> receivePacketContainer=PacketContainer<ReceivePacket>(reinterpret_cast<const void*>(packet.GetPacket()),packet.GetPacketByteSize(),false);
	m_parserList->Push(receivePacketContainer.GetPacketPtr()->packetId,this);
}
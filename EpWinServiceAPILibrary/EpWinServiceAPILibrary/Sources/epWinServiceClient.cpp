/*! 
WinService Client for the EpWinServiceAPILibrary
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
#include "epWinServiceClient.h"
#include "epWinServicePacketParser.h"

using namespace epws;

WinServiceClient::WinServiceClient(WinServiceParserList *parserList,const TCHAR * hostName, const TCHAR * port,unsigned int waitTimeMilliSec) :epse::BaseClient(hostName,port,SYNC_POLICY_ASYNCHRONOUS,waitTimeMilliSec)
{
	m_parserList=parserList;
	if(m_parserList)
		m_parserList->RetainObj();
}

WinServiceClient::WinServiceClient(const WinServiceClient& b):epse::BaseClient(b)
{

}

WinServiceClient::~WinServiceClient()
{
	if(m_parserList)
		m_parserList->ReleaseObj();
}


epse::BasePacketParser* WinServiceClient::createNewPacketParser()
{
	return EP_NEW WinServicePacketParser(m_parserList,m_waitTime);
}
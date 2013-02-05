/*! 
WinService Communicator for the EpWinServiceAPILibrary
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
#include "epWinServiceCommunicator.h"
#include "epWinServicePacketIDGenerator.h"
#include "epWinServicePacketProcessor.h"

using namespace epws;
WinServiceCommunicator::WinServiceCommunicator(const TCHAR * hostName, const TCHAR * port,unsigned int waitTimeMilliSec,LockPolicy lockPolicyType):SmartObject(lockPolicyType)
{
	m_hostName=hostName;
	m_port=port;
	m_parserList=EP_NEW WinServiceParserList(lockPolicyType);
	m_client=WinServiceClient(m_parserList,hostName,port,waitTimeMilliSec);
	m_lockPolicy=lockPolicyType;
	switch(lockPolicyType)
	{
	case LOCK_POLICY_CRITICALSECTION:
		m_lock=EP_NEW CriticalSectionEx();
		break;
	case LOCK_POLICY_MUTEX:
		m_lock=EP_NEW Mutex();
		break;
	case LOCK_POLICY_NONE:
		m_lock=EP_NEW NoLock();
		break;
	default:
		m_lock=NULL;
		break;
	}
}

WinServiceCommunicator::~WinServiceCommunicator()
{
	if(m_client.IsConnected())
	{
		m_client.Disconnect();
	}
	if(m_parserList)
		m_parserList->ReleaseObj();
	if(m_lock)
		EP_DELETE m_lock;
}

WinServiceCommunicator::WinServiceCommunicator(const WinServiceCommunicator& b):SmartObject(b)
{
	m_hostName=b.m_hostName;
	m_port=b.m_port;
	m_client.SetHostName(m_hostName.c_str());
	m_client.SetPort(m_port.c_str());
	m_lockPolicy=b.m_lockPolicy;
	switch(m_lockPolicy)
	{
	case LOCK_POLICY_CRITICALSECTION:
		m_lock=EP_NEW CriticalSectionEx();
		break;
	case LOCK_POLICY_MUTEX:
		m_lock=EP_NEW Mutex();
		break;
	case LOCK_POLICY_NONE:
		m_lock=EP_NEW NoLock();
		break;
	default:
		m_lock=NULL;
		break;
	}
}

WinServiceCommunicator & WinServiceCommunicator::operator=(const WinServiceCommunicator&b)
{
	if(this!=&b)
	{
		SmartObject::operator =(b);
		LockObj lock(m_lock);
		m_hostName=b.m_hostName;
		m_port=b.m_port;
		if(m_client.IsConnected())
			m_client.Disconnect();
		m_client.SetHostName(m_hostName.c_str());
		m_client.SetPort(m_port.c_str());
		if(m_parserList)
			m_parserList->ReleaseObj();
		m_parserList=b.m_parserList;
		if(m_parserList)
			m_parserList->RetainObj();

	}
	return *this;
}

const TCHAR *WinServiceCommunicator::GetHostName() const
{
	LockObj lock(m_lock);
	return m_hostName.c_str();
}

const TCHAR *WinServiceCommunicator::GetPort() const
{
	LockObj lock(m_lock);
	return m_port.c_str();
}

void WinServiceCommunicator::SetServerInfo(const TCHAR *hostName, const TCHAR *port)
{
	LockObj lock(m_lock);
	if(m_client.IsConnected())
		m_client.Disconnect();
	m_hostName=hostName;
	m_port=port;
	m_client.SetHostName(hostName);
	m_client.SetPort(port);
}


WinServiceCommunicatorSendError WinServiceCommunicator::Send(const WinServicePacketGenerator& packetGenerator, WinServiceResult &retResult,unsigned int waitTimeMilliSec)
{
	LockObj lock(m_lock);
	retResult.Clear();
	m_parserList->Clear();
	PacketContainer<SendPacket> packetContainer=PacketContainer<SendPacket>();
	unsigned int packetID=m_idGenerator.GenerateID();
	packetContainer.GetPacketPtr()->packetId=packetID;
	packetContainer.GetPacketPtr()->count=packetGenerator.GetCount();
	packetContainer.SetArray(reinterpret_cast<const char*>(packetGenerator.GetStream()),(unsigned int)packetGenerator.GetStreamByteSize());
	Packet packet=Packet(packetContainer.GetPacketPtr(),packetContainer.GetPacketByteSize(),false);

	if(!m_client.IsConnected())
	{
		if(m_client.Connect())
		{
			if(!m_client.Send(packet))
				return WINSERVICE_COMMUNICATOR_SEND_ERROR_SEND_FAILED;
		}
		else
			return WINSERVICE_COMMUNICATOR_SEND_ERROR_CONNECTION_FAILED;

	}
	else
	{
		if(!m_client.Send(packet))
			return WINSERVICE_COMMUNICATOR_SEND_ERROR_SEND_FAILED;
	}
	WinServicePacketParser *parser=NULL;

	SYSTEMTIME startTime;
	__int64 timeUsed;
	__int64 waitTime=(__int64)waitTimeMilliSec;
	startTime=DateTimeHelper::GetCurrentDateTime();

	while(parser==NULL)
	{
		parser=m_parserList->PopParser(packetID);
		if(parser==NULL)
		{
			Sleep(0);

			if(waitTime!=WAITTIME_INIFINITE)
			{
				timeUsed=DateTimeHelper::AbsDiff(DateTimeHelper::GetCurrentDateTime(),startTime);
				waitTime=waitTime-timeUsed;
				startTime=DateTimeHelper::GetCurrentDateTime();
				if(waitTime<0)
					return WINSERVICE_COMMUNICATOR_SEND_ERROR_TIME_EXPIRED;
			}
			continue;
		}
	}
	WinServicePacketProcessor processor;
	processor.Process(parser->GetPacketReceived(),retResult);
	parser->ReleaseObj();


	return WINSERVICE_COMMUNICATOR_SEND_ERROR_SUCCESS;

}
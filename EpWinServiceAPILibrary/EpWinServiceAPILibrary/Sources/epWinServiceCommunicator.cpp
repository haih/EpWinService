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
#include "epWinServicePacketProcessor.h"

using namespace epws;
WinServiceCommunicator::WinServiceCommunicator(const TCHAR * hostName, const TCHAR * port,unsigned int waitTimeMilliSec,LockPolicy lockPolicyType):SmartObject(lockPolicyType)
{
	m_hostName=hostName;
	m_port=port;
	m_client=WinServiceClient(hostName,port);
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
	PacketContainer<SendPacket> packetContainer=PacketContainer<SendPacket>();
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
	

	WinServicePacketProcessor processor;
	Packet * packetReceived=m_client.Receive();
	if(!packetReceived)
		return WINSERVICE_COMMUNICATOR_SEND_ERROR_RECEIVE_FAILED;
	processor.Process(packetReceived,retResult);
	packetReceived->ReleaseObj();

	return WINSERVICE_COMMUNICATOR_SEND_ERROR_SUCCESS;

}
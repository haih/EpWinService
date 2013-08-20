/*! 
WinService Communicator for the EpWinServiceAPILibrary

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
		m_communicatorLock=EP_NEW CriticalSectionEx();
		break;
	case LOCK_POLICY_MUTEX:
		m_communicatorLock=EP_NEW Mutex();
		break;
	case LOCK_POLICY_NONE:
		m_communicatorLock=EP_NEW NoLock();
		break;
	default:
		m_communicatorLock=NULL;
		break;
	}
}

WinServiceCommunicator::~WinServiceCommunicator()
{
	if(m_client.IsConnected())
	{
		m_client.Disconnect();
	}
	if(m_communicatorLock)
		EP_DELETE m_communicatorLock;
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
		m_communicatorLock=EP_NEW CriticalSectionEx();
		break;
	case LOCK_POLICY_MUTEX:
		m_communicatorLock=EP_NEW Mutex();
		break;
	case LOCK_POLICY_NONE:
		m_communicatorLock=EP_NEW NoLock();
		break;
	default:
		m_communicatorLock=NULL;
		break;
	}
}

WinServiceCommunicator & WinServiceCommunicator::operator=(const WinServiceCommunicator&b)
{
	if(this!=&b)
	{
		SmartObject::operator =(b);
		LockObj lock(m_communicatorLock);
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
	LockObj lock(m_communicatorLock);
	return m_hostName.c_str();
}

const TCHAR *WinServiceCommunicator::GetPort() const
{
	LockObj lock(m_communicatorLock);
	return m_port.c_str();
}

void WinServiceCommunicator::SetServerInfo(const TCHAR *hostName, const TCHAR *port)
{
	LockObj lock(m_communicatorLock);
	if(m_client.IsConnected())
		m_client.Disconnect();
	m_hostName=hostName;
	m_port=port;
	m_client.SetHostName(hostName);
	m_client.SetPort(port);
}


WinServiceCommunicatorSendError WinServiceCommunicator::Send(const WinServicePacketGenerator& packetGenerator, WinServiceResult &retResult,unsigned int waitTimeMilliSec)
{
	LockObj lock(m_communicatorLock);
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
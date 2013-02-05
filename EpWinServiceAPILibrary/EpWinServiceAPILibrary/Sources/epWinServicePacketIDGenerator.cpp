/*! 
WinService Packet ID Generator for the EpWinServiceAPILibrary
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
#include "epWinServicePacketIDGenerator.h"
using namespace epws;


WinServicePacketIDGenerator::WinServicePacketIDGenerator(LockPolicy lockPolicyType)
{
	m_packetID=0;
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

WinServicePacketIDGenerator::~WinServicePacketIDGenerator()
{
	if(m_lock)
		EP_DELETE m_lock;
}

WinServicePacketIDGenerator::WinServicePacketIDGenerator(const WinServicePacketIDGenerator& b)
{
	m_packetID=b.m_packetID;
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

WinServicePacketIDGenerator & WinServicePacketIDGenerator::operator=(const WinServicePacketIDGenerator&b)
{
	if(this!=&b)
	{
		LockObj lock(m_lock);
		m_packetID=b.m_packetID;
	}
	return *this;
}


unsigned int WinServicePacketIDGenerator::GenerateID()
{
	LockObj lock(m_lock);
	m_packetID++;
	if(m_packetID==0xffffffff)
		m_packetID=0;
	return m_packetID;
}


/*! 
WinService Parser List for the EpWinServiceAPILibrary
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
#include "epWinServiceParserList.h"
#include "epWinServicePacketParser.h"

using namespace epws;
WinServiceParserList::WinServiceParserList(LockPolicy lockPolicyType):SmartObject(lockPolicyType)
{
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
WinServiceParserList::~WinServiceParserList()
{
	Clear();
	if(m_lock)
		EP_DELETE m_lock;
}


WinServiceParserList::WinServiceParserList(const WinServiceParserList& b):SmartObject(b)
{
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

WinServiceParserList & WinServiceParserList::operator=(const WinServiceParserList&b)
{
	if(this!=&b)
	{
		SmartObject::operator =(b);
		Clear();
		LockObj lock(m_lock);
		vector<Pair<unsigned int,WinServicePacketParser*> >::const_iterator iter;
		for(iter=b.m_parserList.begin();iter!=b.m_parserList.end();iter++)
		{
			iter->second->RetainObj();
			m_parserList.push_back(*iter);

		}
		
	}
	return *this;
}

CompResultType PairCompare(const void*a, const void *b)
{
	Pair<unsigned int, WinServicePacketParser*> *_a=(Pair<unsigned int, WinServicePacketParser*> *)a;
	Pair<unsigned int, WinServicePacketParser*> *_b=(Pair<unsigned int, WinServicePacketParser*> *)b;

	if(_a->first<_b->first)
		return COMP_RESULT_LESSTHAN;
	else if(_a->first>_b->first)
		return COMP_RESULT_GREATERTHAN;
	return COMP_RESULT_EQUAL;

}

void WinServiceParserList::Push(unsigned int packetId,WinServicePacketParser *parser)
{
	LockObj lock(m_lock);

	Pair<unsigned int, WinServicePacketParser*> insertObj;
	insertObj.first=packetId;
	insertObj.second=parser;
	insertObj.second->RetainObj();
	if(m_parserList.size())
	{
		int retIdx;
		if(BinarySearch(insertObj,&m_parserList.at(0),m_parserList.size(),PairCompare,retIdx))
			EP_ASSERT(0);
		m_parserList.insert(m_parserList.begin()+retIdx,insertObj);
	}
	else
	{
		m_parserList.push_back(insertObj);
	}
	
}

WinServicePacketParser *WinServiceParserList::PopParser(unsigned int packetID)
{
	LockObj lock(m_lock);

	Pair<unsigned int, WinServicePacketParser*> findObj;
	findObj.first=packetID;
	if(m_parserList.size())
	{
		int retIdx;
		if(BinarySearch(findObj,&m_parserList.at(0),m_parserList.size(),PairCompare,retIdx))
		{
			WinServicePacketParser* retPtr=m_parserList.at(retIdx).second;
			m_parserList.erase(m_parserList.begin()+retIdx);
			return retPtr;
		}
	}
	return NULL;
}

void WinServiceParserList::Clear()
{
	LockObj lock(m_lock);
	vector<Pair<unsigned int,WinServicePacketParser*> >::iterator iter;
	for(iter=m_parserList.begin();iter!=m_parserList.end();iter++)
	{
		iter->second->ReleaseObj();
	}
	m_parserList.clear();
}

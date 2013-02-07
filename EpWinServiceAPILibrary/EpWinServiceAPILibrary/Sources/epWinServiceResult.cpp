/*! 
WinService Result for the EpWinServiceAPILibrary
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
#include "epWinServiceResult.h"
using namespace epws;

WinServiceResult::WinServiceResult()
{
	m_procCnt=0;
}
WinServiceResult::~WinServiceResult()
{
	Clear();
}
WinServiceResult::WinServiceResult(const WinServiceResult& b)
{
	m_procCnt=b.m_procCnt;
	vector<WinServiceResultInfo*>::const_iterator iter;
	for(iter=b.m_resultList.begin();iter!=b.m_resultList.end();iter++)
	{
		WinServiceResultInfo *newObj=EP_NEW	WinServiceResultInfo(*(*iter));
		m_resultList.push_back(newObj);
	}
}
		
WinServiceResult & WinServiceResult::operator=(const WinServiceResult&b)
{
	if(this!=&b)
	{
		Clear();
		m_procCnt=b.m_procCnt;
		vector<WinServiceResultInfo*>::const_iterator iter;
		for(iter=b.m_resultList.begin();iter!=b.m_resultList.end();iter++)
		{
			WinServiceResultInfo *newObj=EP_NEW	WinServiceResultInfo(*(*iter));
			m_resultList.push_back(newObj);
		}

	}
	return *this;
}
void WinServiceResult::Clear()
{
	vector<WinServiceResultInfo*>::iterator iter;
	for(iter=m_resultList.begin();iter!=m_resultList.end();iter++)
	{
		if(*iter)
			EP_DELETE *iter;
	}
	m_resultList.clear();
	m_procCnt=0;
}

unsigned int WinServiceResult::GetResultCount() const
{
	return m_procCnt;
}

const vector<WinServiceResultInfo*>&WinServiceResult::GetResultList() const
{
	return m_resultList;
}

const WinServiceResultInfo&WinServiceResult::GetAt(unsigned int idx) const
{
	EP_ASSERT(idx<m_resultList.size());
	return *m_resultList.at(idx);
}


void WinServiceResult::SetResultCount(unsigned int resultCnt)
{
	m_procCnt=resultCnt;
}
void WinServiceResult::AddResultInfo(WinServiceResultInfo* info)
{
	m_resultList.push_back(info);
	m_procCnt++;
}


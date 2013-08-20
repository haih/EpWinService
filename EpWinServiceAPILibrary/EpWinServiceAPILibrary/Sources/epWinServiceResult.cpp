/*! 
WinService Result for the EpWinServiceAPILibrary

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
}


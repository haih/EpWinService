/*! 
@file epWinServiceResult.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Result Interface
@version 1.0

@section LICENSE

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

@section DESCRIPTION

An Interface for WinService Result.

*/
#ifndef __EP_WINSERVICE_RESULT_H__
#define __EP_WINSERVICE_RESULT_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceDefines.h"
#include "epWinServiceInfoStruct.h"
#include "epWinServiceResultInfo.h"
#include <vector>


using namespace std;

namespace epws
{

	/*! 
	@class WinServiceResult epWinServiceResult.h
	@brief A class for WinService Result.
	*/
	class EP_WINSERVICE_API WinServiceResult
	{
	public:
		/*!
		Default Constructor

		Initializes the Result
		*/
		WinServiceResult();

		/*!
		Default Destructor

		Destroy the Result
		*/
		~WinServiceResult();

		/*!
		Default Copy Constructor

		Initializes the WinServiceResult
		@param[in] b the second object
		*/
		WinServiceResult(const WinServiceResult& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServiceResult & operator=(const WinServiceResult&b);

		/*!
		Clear all WinServiceResultInfos.
		*/
		void Clear();

		/*!
		Return the WinServiceResultInfo count
		@return the WinServiceResultInfo count
		*/
		unsigned int GetResultCount() const;

		/*!
		Return the WinServiceResultInfo List
		@return the WinServiceResultInfo List
		*/
		const vector<WinServiceResultInfo*> &GetResultList() const;

		/*!
		Return the WinServiceResultInfo object at given index
		@param[in] idx the index of the list to get
		@return the WinServiceResultInfo object
		*/
		const WinServiceResultInfo &GetAt(unsigned int idx) const;

	private:
		friend class WinServicePacketProcessor;

		/*!
		Set Result Count with given value
		@param[in] resultCnt the result count to set
		*/
		void SetResultCount(unsigned int resultCnt);

		/*!
		Add new WinServiceResultInfo to the list
		@param[in] info the new WinServiceResultInfo object pointer to add
		*/
		void AddResultInfo(WinServiceResultInfo* info);
		
		/// Frame Count
		unsigned int m_procCnt;

		/// WinServiceResultInfo List
		vector<WinServiceResultInfo*> m_resultList;
	};
}
#endif //__EP_WINSERVICE_RESULT_H__
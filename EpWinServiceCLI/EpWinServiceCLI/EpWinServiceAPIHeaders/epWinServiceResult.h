/*! 
@file epWinServiceResult.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Result Interface
@version 1.0

@section LICENSE

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
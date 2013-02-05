/*! 
@file epWinServiceResultInfo.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Result Info Interface
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

An Interface for WinService Result Info.

*/
#ifndef __EP_WINSERVICE_RESULT_INFO_H__
#define __EP_WINSERVICE_RESULT_INFO_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceClientPacketInfo.h"
#include "epWinServiceInfoStruct.h"


namespace epws
{

	/// Return Type Enumeration
	typedef enum _retType{
		/// void Type
		RETURN_TYPE_VOID=0,
		/// bool Type
		RETURN_TYPE_BOOL,
		/// int Type
		RETURN_TYPE_INT,
		/// unsigned int Type
		RETURN_TYPE_UINT,
		/// EpTString type
		RETURN_TYPE_STRING,
		/// ProcessObjInfo Type
		RETURN_TYPE_PROCESSOBJ_INFO,
		/// ServiceObjInfo Type
		RETURN_TYPE_SERVICEOBJ_INFO,
		/// SERVICE_STATUS Type
		RETURN_TYPE_SERVICE_STATUS,
		/// SERVICE_STATUS_PROCESS Type
		RETURN_TYPE_SERVICE_STATUS_PROCESS,
		/// ProcessStatusType Type
		RETURN_TYPE_PROCESS_STATUS_TYPE,
		/// ServiceStatusType Type
		RETURN_TYPE_SERVICE_STATUS_TYPE,
		/// ServiceHandleErrorInfo Type
		RETURN_TYPE_SERVICE_HANDLE_ERROR_INFO,
	}ReturnType;

	/// Retrieve Status Enumeration
	typedef enum _retrieveStatus{
		/// Success
		RETRIEVE_STATUS_SUCCESS=0,
		/// Fail
		RETRIEVE_STATUS_FAIL,
		/// Fail to retrieve the Result
		RETRIEVE_STATUS_FAIL_RESULT,
		/// Fail to retrieve the object index
		RETRIEVE_STATUS_FAIL_OBJECTIDX,
		/// Fail to retrieve the argument/s
		RETRIEVE_STATUS_FAIL_ARGUMENT,
	}RetrieveStatus;


	/*! 
	@class WinServiceResultInfo epWinServiceResultInfo.h
	@brief A class for WinService Result Info.
	*/
	class EP_WINSERVICE_API WinServiceResultInfo
	{
	public:
		/*!
		Return the Packet Type
		@return the Packet Type
		*/
		PacketType GetPacketType() const;

		/*!
		Return the Sub Packet Type
		@return the Sub Packet Type
		*/
		unsigned int GetSubPacketType() const;

		/*!
		Return the Packet Process Status
		@return the Packet Process Status
		*/
		PacketProcessStatus GetPacketProcessStatus() const;

		/*!
		Return the Return Type of the Result
		@return the Return Type of the Result
		*/
		ReturnType GetReturnType() const;

		/*!
		Return the Retrieve Status
		@return the Retrieve Status
		*/
		RetrieveStatus GetRetrieveStatus() const;

		/*!
		Return the value in boolean
		@return the value in boolean
		*/
		const bool &ToBoolean() const;

		/*!
		Return the value in int
		@return the value in int
		*/
		const int &ToInt() const;

		/*!
		Return the value in unsigned int
		@return the value in unsigned int
		*/
		const unsigned int &ToUInt() const;

		/*!
		Return the value in EpTString
		@return the value in EpTString
		*/
		const EpTString &ToString() const;

		/*!
		Return the value in ProcessObjInfo
		@return the value in ProcessObjInfo
		*/
		const ProcessObjInfo &ToProcessObjInfo() const;

		/*!
		Return the value in ServiceObjInfo
		@return the value in ServiceObjInfo
		*/
		const ServiceObjInfo &ToServiceObjInfo() const;

		/*!
		Return the value in SERVICE_STATUS
		@return the value in SERVICE_STATUS
		*/
		const SERVICE_STATUS &ToServiceStatus() const;

		/*!
		Return the value in SERVICE_STATUS_PROCESS
		@return the value in SERVICE_STATUS_PROCESS
		*/
		const SERVICE_STATUS_PROCESS &ToServiceStatusProcess() const;

		/*!
		Return the value in ProcessStatusType
		@return the value in ProcessStatusType
		*/
		const ProcessStatusType &ToProcessStatusType() const;

		/*!
		Return the value in ServiceStatusType
		@return the value in ServiceStatusType
		*/
		const ServiceStatusType &ToServiceStatusType() const;

		/*!
		Return the value in ServiceHandleErrorInfo
		@return the value in ServiceHandleErrorInfo
		*/
		const ServiceHandleErrorInfo &ToServiceHandleErrorInfo() const;



	private:
		friend class WinServicePacketProcessor;
		friend class WinServiceResult;
		/*!
		Default Constructor

		Initializes the Result Info
		*/
		WinServiceResultInfo();

		/*!
		Default Destructor

		Destroy the Result Info
		*/
		~WinServiceResultInfo();

		/*!
		Default Copy Constructor

		Initializes the WinServiceResultInfo
		@param[in] b the second object
		*/
		WinServiceResultInfo(const WinServiceResultInfo& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServiceResultInfo & operator=(const WinServiceResultInfo&b);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in bool
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const bool &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in int
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const int &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in unsigned in
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const unsigned int &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in ProcessObjInfo
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const ProcessObjInfo &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in ServiceObjInfo
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const ServiceObjInfo &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in SERVICE_STATUS
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const SERVICE_STATUS &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in SERVICE_STATUS_PROCESS
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const SERVICE_STATUS_PROCESS &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in EpTString
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const EpTString &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in ProcessStatusType
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const ProcessStatusType &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in ServiceStatusType
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const ServiceStatusType &val);

		/*!
		Set the Result Value as given val
		@param[in] val the Result Value in ServiceHandleErrorInfo
		@return the reference to this object
		*/
		WinServiceResultInfo &  operator=(const ServiceHandleErrorInfo &val);

	private:
		/// Packet Type
		PacketType m_packetType;
		/// Sub Packet Type
		unsigned int m_subPacketType;
		/// Packet Process Result
		PacketProcessStatus m_packetProcessResult;
		/// Retrieve Status
		RetrieveStatus m_retrieveStatus;
		/// Object Index
		int m_objIdx;

		/// Return Type
		ReturnType m_retType;
		/// Result Value
		void *m_retVal;		

	};
}
#endif //__EP_WINSERVICE_RESULT_INFO_H__
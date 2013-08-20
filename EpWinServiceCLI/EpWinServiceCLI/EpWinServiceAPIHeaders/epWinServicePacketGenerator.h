/*! 
@file epWinServicePacketGenerator.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Packet Generator Interface
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

An Interface for WinService Packet Generator.

*/
#ifndef __EP_WINSERVICE_PACKET_GENERATOR_H__
#define __EP_WINSERVICE_PACKET_GENERATOR_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceDefines.h"
#include "epWinServiceClientPacketInfo.h"
#include "epWinServiceInfoStruct.h"

namespace epws
{



	/*! 
	@class WinServicePacketGenerator epWinServicePacketGenerator.h
	@brief A class for WinService Packet Generator.
	*/
	class EP_WINSERVICE_API WinServicePacketGenerator:public epl::SmartObject
	{
	public:
		friend class WinServiceCommunicator;
		/*!
		Default Constructor

		Initializes the Packet Generator
		@param[in] lockPolicyType The lock policy
		*/
		WinServicePacketGenerator(LockPolicy lockPolicyType=EP_LOCK_POLICY);

		/*!
		Default Destructor

		Destroy the Packet Generator
		*/
		~WinServicePacketGenerator();

		/*!
		Default Copy Constructor

		Initializes the WinServicePacketGenerator
		@param[in] b the second object
		*/
		WinServicePacketGenerator(const WinServicePacketGenerator& b);
		
		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServicePacketGenerator & operator=(const WinServicePacketGenerator&b);

		/*!
		Return the added processes count
		@return the added processes count
		*/
		unsigned int GetCount() const;

		/*!
		Clear all added processes
		*/
		void Clear();

		/*!
		Add Command Main Service frame to the packet
		@param[in] type type of the command
		@param[in] waitTime wait time for command to run (Optional)
		@param[in] cmd the command for RunCommand type.
		@remark waitTime is for RunCommand/CustomProcess command type
		@remark cmd is only for RunCommand command type
		*/
		void AddCommandMainService(MainServiceCommandPacketType type,int waitTime=WAITTIME_INIFINITE, const EpTString &cmd =_T(""));

		/*!
		Add Get Main Service Info frame to the packet
		@param[in] type type of the information getting
		*/
		void AddGetMainServiceInfo(MainServiceInfoGetPacketType type);

		/*!
		Add Set Main Service Info frame to the packet
		@param[in] type type of the information setting
		@param[in] info the information to set
		*/
		void AddSetMainServiceInfo(MainServiceInfoSetPacketType type,const MainServiceInfo &info);

		/*!
		Add Command Service Object frame to the packet
		@param[in] type type of the command
		@param[in] objIndex the object index to command (OBJECT_IDX_ALL for all Service Objects)
		@param[in] waitTime wait time for command to run (Optional)
		@param[in] cmd the command for RunCommand type. (Optional)
		@remark waitTime is for RunCommand/CustomProcess command type
		@remark cmd is only for RunCommand command type
		*/
		void AddCommandServiceObj(ServiceObjectCommandPacketType type, int objIndex,int waitTime=WAITTIME_INIFINITE,const EpTString &cmd =_T(""));

		/*!
		Add Deploy Command Service Object frame to the packet
		@param[in] objIndex the object index to command (OBJECT_IDX_ALL for all Service Objects)
		@param[in] revisionNum the revision number, updated to (Optional)
		@remark if revisionNum == REVISION_UNKNOWN then it updates to latest revision.
		*/
		void AddDeployCommandServiceObj(int objIndex,int revisionNum=REVISION_UNKNOWN);
		/*!
		Add Get Service Object Info frame to the packet
		@param[in] type type of the information getting
		@param[in] serviceIndex the index of the service object to get info
		*/
		void AddGetServiceInfo(ServiceObjectInfoGetPacketType type, unsigned int serviceIndex);

		/*!
		Add Set Service Object Info frame to the packet
		@param[in] type type of the information setting
		@param[in] serviceIndex the index of the service object to get info
		@param[in] info the information to set
		*/
		void AddSetServiceInfo(ServiceObjectInfoSetPacketType type, unsigned int serviceIndex, const ServiceObjInfo &info);

		/*!
		Add Command Process Object frame to the packet
		@param[in] type type of the command
		@param[in] objIndex the object index to command (OBJECT_IDX_ALL for all Process Objects)
		@param[in] waitTime wait time for command to run (Optional)
		@param[in] cmd the command for RunCommand type. (Optional)
		@remark waitTime is for RunCommand/CustomProcess command type
		@remark cmd is only for RunCommand command type
		*/
		void AddCommandProcessObj(ProcessObjectCommandPacketType type, int objIndex,int waitTime=WAITTIME_INIFINITE,const EpTString &cmd =_T(""));

		/*!
		Add Deploy Command Process Object frame to the packet
		@param[in] objIndex the object index to command (OBJECT_IDX_ALL for all Process Objects)
		@param[in] revisionNum the revision number, updated to (Optional)
		@remark if revisionNum == REVISION_UNKNOWN then it updates to latest revision.
		*/
		void AddDeployCommandProcessObj(int objIndex,int revisionNum=REVISION_UNKNOWN);

		/*!
		Add Get Process Object Info frame to the packet
		@param[in] type type of the information getting
		@param[in] procIndex the index of the process object to get info
		*/
		void AddGetProcessInfo(ProcessObjectInfoGetPacketType type, unsigned int procIndex);

		/*!
		Add Set Process Object Info frame to the packet
		@param[in] type type of the information setting
		@param[in] procIndex the index of the process object to get info
		@param[in] info the information to set
		*/
		void AddSetProcessInfo(ProcessObjectInfoSetPacketType type, unsigned int procIndex,const ProcessObjInfo &info);

		/*!
		Add Command Service frame to the packet
		@param[in] type type of the command
		@param[in] serviceName the name of the service to command
		@param[in] info the information to set
		*/
		void AddCommandService(ServiceCommandPacketType type, const TCHAR *serviceName,const ServiceInfo &info);




	private:
		/*!
		Return the stream by unsigned char buffer
		@return the stream by unsigned char buffer
		*/
		const unsigned char *GetStream() const;

		/*!
		Return the byte size of the stream
		@return the byte size of the stream
		*/
		unsigned int GetStreamByteSize() const;

		/// stream
		epl::Stream m_stream;
		/// packet count
		unsigned int m_count;
		/// the lock
		BaseLock * m_packetGeneratorLock;
		/// Lock Policy
		LockPolicy m_lockPolicy;
	};



}

#endif //__EP_WINSERVICE_PACKET_GENERATOR_H__
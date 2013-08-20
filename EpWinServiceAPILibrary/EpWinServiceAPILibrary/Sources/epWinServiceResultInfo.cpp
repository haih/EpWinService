/*! 
WinService Result Info for the EpWinServiceAPILibrary

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
#include "epWinServiceResultInfo.h"

using namespace epws;

const bool &WinServiceResultInfo::ToBoolean() const
{
	EP_ASSERT(m_retVal);
	return *(bool*)m_retVal;
}
const int &WinServiceResultInfo::ToInt() const
{
	EP_ASSERT(m_retVal);
	return *(int*)m_retVal;
}
const unsigned int &WinServiceResultInfo::ToUInt() const
{
	EP_ASSERT(m_retVal);
	return *(unsigned int*)m_retVal;
}
const EpTString &WinServiceResultInfo::ToString() const
{
	EP_ASSERT(m_retVal);
	return *(EpTString*)m_retVal;
}
const ProcessObjInfo &WinServiceResultInfo::ToProcessObjInfo() const
{
	EP_ASSERT(m_retVal);
	return *(ProcessObjInfo*)m_retVal;
}
const ServiceObjInfo &WinServiceResultInfo::ToServiceObjInfo() const
{
	EP_ASSERT(m_retVal);
	return *(ServiceObjInfo*)m_retVal;
}
const SERVICE_STATUS &WinServiceResultInfo::ToServiceStatus() const
{
	EP_ASSERT(m_retVal);
	return *(SERVICE_STATUS*)m_retVal;
}
const SERVICE_STATUS_PROCESS &WinServiceResultInfo::ToServiceStatusProcess() const
{
	EP_ASSERT(m_retVal);
	return *(SERVICE_STATUS_PROCESS*)m_retVal;
}

const ProcessStatusType &WinServiceResultInfo::ToProcessStatusType() const
{
	EP_ASSERT(m_retVal);
	return *(ProcessStatusType*)m_retVal;
}
const ServiceStatusType &WinServiceResultInfo::ToServiceStatusType() const
{
	EP_ASSERT(m_retVal);
	return *(ServiceStatusType*)m_retVal;
}

const ServiceHandleErrorInfo &WinServiceResultInfo::ToServiceHandleErrorInfo() const
{
	EP_ASSERT(m_retVal);
	return *(ServiceHandleErrorInfo*)m_retVal;
}

const DeployInfo &WinServiceResultInfo::ToDeployInfo() const
{
	EP_ASSERT(m_retVal);
	return *(DeployInfo*)m_retVal;
}

const ObjectStartStatus &WinServiceResultInfo::ToObjectStartStatus() const
{
	EP_ASSERT(m_retVal);
	return *(ObjectStartStatus*)m_retVal;
}
PacketType WinServiceResultInfo::GetPacketType() const
{
	return m_packetType;
}
unsigned int WinServiceResultInfo::GetSubPacketType() const
{
	return m_subPacketType;
}
PacketProcessStatus WinServiceResultInfo::GetPacketProcessStatus() const
{
	return m_packetProcessResult;
}
ReturnType WinServiceResultInfo::GetReturnType() const
{
	return m_retType;
}
RetrieveStatus WinServiceResultInfo::GetRetrieveStatus() const
{
	return m_retrieveStatus;
}
WinServiceResultInfo::WinServiceResultInfo()
{
	m_packetType=PACKET_TYPE_NULL;
	m_subPacketType=0;
	m_packetProcessResult=PACKET_PROCESS_STATUS_FAIL;
	m_retType=RETURN_TYPE_VOID;
	m_retVal=NULL;
	m_retrieveStatus=RETRIEVE_STATUS_SUCCESS;
	m_objIdx=OBJECT_IDX_NONE;
}
WinServiceResultInfo::~WinServiceResultInfo()
{
	if(m_retVal)
		EP_DELETE m_retVal;
}
WinServiceResultInfo::WinServiceResultInfo(const WinServiceResultInfo& b)
{
	m_packetType=b.m_packetType;
	m_subPacketType=b.m_subPacketType;
	m_packetProcessResult=b.m_packetProcessResult;
	m_retType=b.m_retType;
	m_retrieveStatus=b.m_retrieveStatus;
	m_objIdx=b.m_objIdx;
	if(b.m_retVal)
	{
		switch(m_retType)
		{
		case RETURN_TYPE_BOOL:
			m_retVal=EP_NEW bool();
			*(bool*)m_retVal=*(bool*)b.m_retVal;
			break;
		case RETURN_TYPE_INT:
			m_retVal=EP_NEW int();
			*(int*)m_retVal=*(int*)b.m_retVal;
			break;
		case RETURN_TYPE_UINT:
			m_retVal=EP_NEW unsigned int();
			*(unsigned int*)m_retVal=*(unsigned int*)b.m_retVal;
			break;
		case RETURN_TYPE_STRING:
			m_retVal=EP_NEW EpTString();
			*(EpTString*)m_retVal=*(EpTString*)b.m_retVal;
			break;
		case RETURN_TYPE_PROCESSOBJ_INFO:
			m_retVal=EP_NEW ProcessObjInfo();
			*(ProcessObjInfo*)m_retVal=*(ProcessObjInfo*)b.m_retVal;
			break;
		case RETURN_TYPE_SERVICEOBJ_INFO:
			m_retVal=EP_NEW ServiceObjInfo();
			*(ServiceObjInfo*)m_retVal=*(ServiceObjInfo*)b.m_retVal;
			break;
		case RETURN_TYPE_SERVICE_STATUS:
			m_retVal=EP_NEW SERVICE_STATUS();
			*(SERVICE_STATUS*)m_retVal=*(SERVICE_STATUS*)b.m_retVal;
			break;
		case RETURN_TYPE_SERVICE_STATUS_PROCESS:
			m_retVal=EP_NEW SERVICE_STATUS_PROCESS();
			*(SERVICE_STATUS_PROCESS*)m_retVal=*(SERVICE_STATUS_PROCESS*)b.m_retVal;
			break;
		case RETURN_TYPE_PROCESS_STATUS_TYPE:
			m_retVal=EP_NEW ProcessStatusType();
			*(ProcessStatusType*)m_retVal=*(ProcessStatusType*)b.m_retVal;
			break;
		case RETURN_TYPE_SERVICE_STATUS_TYPE:
			m_retVal=EP_NEW ServiceStatusType();
			*(ServiceStatusType*)m_retVal=*(ServiceStatusType*)b.m_retVal;
			break;
		case RETURN_TYPE_SERVICE_HANDLE_ERROR_INFO:
			m_retVal=EP_NEW ServiceHandleErrorInfo();
			*(ServiceHandleErrorInfo*)m_retVal=*(ServiceHandleErrorInfo*)b.m_retVal;
			break;
		case RETURN_TYPE_DEPLOY_INFO:
			m_retVal=EP_NEW DeployInfo();
			*(DeployInfo*)m_retVal=*(DeployInfo*)b.m_retVal;
			break;
		}
	}
}
WinServiceResultInfo & WinServiceResultInfo::operator=(const WinServiceResultInfo&b)
{
	if(this!=&b)
	{
		m_packetType=b.m_packetType;
		m_subPacketType=b.m_subPacketType;
		m_packetProcessResult=b.m_packetProcessResult;
		m_retType=b.m_retType;
		m_retrieveStatus=b.m_retrieveStatus;
		m_objIdx=b.m_objIdx;
		if(b.m_retVal)
		{
			switch(m_retType)
			{
			case RETURN_TYPE_BOOL:
				m_retVal=EP_NEW bool();
				*(bool*)m_retVal=*(bool*)b.m_retVal;
				break;
			case RETURN_TYPE_INT:
				m_retVal=EP_NEW int();
				*(int*)m_retVal=*(int*)b.m_retVal;
				break;
			case RETURN_TYPE_UINT:
				m_retVal=EP_NEW unsigned int();
				*(unsigned int*)m_retVal=*(unsigned int*)b.m_retVal;
				break;
			case RETURN_TYPE_STRING:
				m_retVal=EP_NEW EpTString();
				*(EpTString*)m_retVal=*(EpTString*)b.m_retVal;
				break;
			case RETURN_TYPE_PROCESSOBJ_INFO:
				m_retVal=EP_NEW ProcessObjInfo();
				*(ProcessObjInfo*)m_retVal=*(ProcessObjInfo*)b.m_retVal;
				break;
			case RETURN_TYPE_SERVICEOBJ_INFO:
				m_retVal=EP_NEW ServiceObjInfo();
				*(ServiceObjInfo*)m_retVal=*(ServiceObjInfo*)b.m_retVal;
				break;
			case RETURN_TYPE_SERVICE_STATUS:
				m_retVal=EP_NEW SERVICE_STATUS();
				*(SERVICE_STATUS*)m_retVal=*(SERVICE_STATUS*)b.m_retVal;
				break;
			case RETURN_TYPE_SERVICE_STATUS_PROCESS:
				m_retVal=EP_NEW SERVICE_STATUS_PROCESS();
				*(SERVICE_STATUS_PROCESS*)m_retVal=*(SERVICE_STATUS_PROCESS*)b.m_retVal;
				break;
			case RETURN_TYPE_PROCESS_STATUS_TYPE:
				m_retVal=EP_NEW ProcessStatusType();
				*(ProcessStatusType*)m_retVal=*(ProcessStatusType*)b.m_retVal;
				break;
			case RETURN_TYPE_SERVICE_STATUS_TYPE:
				m_retVal=EP_NEW ServiceStatusType();
				*(ServiceStatusType*)m_retVal=*(ServiceStatusType*)b.m_retVal;
				break;
			case RETURN_TYPE_SERVICE_HANDLE_ERROR_INFO:
				m_retVal=EP_NEW ServiceHandleErrorInfo();
				*(ServiceHandleErrorInfo*)m_retVal=*(ServiceHandleErrorInfo*)b.m_retVal;
				break;
			case RETURN_TYPE_DEPLOY_INFO:
				m_retVal=EP_NEW DeployInfo();
				*(DeployInfo*)m_retVal=*(DeployInfo*)b.m_retVal;
				break;
			}
		}
	}
	return *this;
}

WinServiceResultInfo &  WinServiceResultInfo::operator=(const bool &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW bool();
	*(bool*)m_retVal=val;
	m_retType=RETURN_TYPE_BOOL;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const int &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW int();
	*(int*)m_retVal=val;
	m_retType=RETURN_TYPE_INT;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const unsigned int &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW unsigned int();
	*(unsigned int*)m_retVal=val;
	m_retType=RETURN_TYPE_UINT;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const ProcessObjInfo &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW ProcessObjInfo();
	*(ProcessObjInfo*)m_retVal=val;
	m_retType=RETURN_TYPE_PROCESSOBJ_INFO;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const ServiceObjInfo &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW ServiceObjInfo();
	*(ServiceObjInfo*)m_retVal=val;
	m_retType=RETURN_TYPE_SERVICEOBJ_INFO;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const SERVICE_STATUS &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW SERVICE_STATUS();
	*(SERVICE_STATUS*)m_retVal=val;
	m_retType=RETURN_TYPE_SERVICE_STATUS;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const SERVICE_STATUS_PROCESS &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW SERVICE_STATUS_PROCESS();
	*(SERVICE_STATUS_PROCESS*)m_retVal=val;
	m_retType=RETURN_TYPE_SERVICE_STATUS_PROCESS;
	return *this;
}
WinServiceResultInfo &  WinServiceResultInfo::operator=(const EpTString &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW EpTString();
	*(EpTString*)m_retVal=val;
	m_retType=RETURN_TYPE_STRING;
	return *this;
}

WinServiceResultInfo &  WinServiceResultInfo::operator=(const ProcessStatusType &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW ProcessStatusType();
	*(ProcessStatusType*)m_retVal=val;
	m_retType=RETURN_TYPE_PROCESS_STATUS_TYPE;
	return *this;
}

WinServiceResultInfo &  WinServiceResultInfo::operator=(const ServiceStatusType &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW ServiceStatusType();
	*(ServiceStatusType*)m_retVal=val;
	m_retType=RETURN_TYPE_SERVICE_STATUS_TYPE;
	return *this;
}

WinServiceResultInfo &  WinServiceResultInfo::operator=(const ServiceHandleErrorInfo &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW ServiceHandleErrorInfo();
	*(ServiceHandleErrorInfo*)m_retVal=val;
	m_retType=RETURN_TYPE_SERVICE_HANDLE_ERROR_INFO;
	return *this;
}

WinServiceResultInfo &  WinServiceResultInfo::operator=(const DeployInfo &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW DeployInfo();
	*(DeployInfo*)m_retVal=val;
	m_retType=RETURN_TYPE_DEPLOY_INFO;
	return *this;
}

WinServiceResultInfo &  WinServiceResultInfo::operator=(const ObjectStartStatus &val)
{
	if(m_retVal)
		EP_DELETE m_retVal;
	m_retVal=(void*)EP_NEW ObjectStartStatus();
	*(ObjectStartStatus*)m_retVal=val;
	m_retType=RETURN_TYPE_OJBECT_START_STATUS;
	return *this;
}
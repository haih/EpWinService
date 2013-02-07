/*! 
WinService Client Packet Processor for the EpWinServiceAPILibrary
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
#include "epWinServicePacketProcessor.h"
#include "epWinServiceDefines.h"

using namespace epws;

void WinServicePacketProcessor::Process(const epse::Packet *packet, WinServiceResult &retResult)
{
	epl::Stream stream;
	epl::Stream outStream;
	epse::PacketContainer<ReceivePacket> receivePacketContainer=epse::PacketContainer<ReceivePacket>(reinterpret_cast<const void*>(packet->GetPacket()),packet->GetPacketByteSize(),false);
	unsigned int procCount=receivePacketContainer.GetPacketPtr()->count;
	stream.WriteBytes(reinterpret_cast<unsigned char*>(receivePacketContainer.GetArray()),receivePacketContainer.GetArrayLength());
	stream.SetSeek(Stream::STREAM_SEEK_TYPE_SEEK_SET);

	retResult.SetResultCount(procCount);

	for(int procTrav=0;procTrav<procCount;procTrav++)
	{
		WinServiceResultInfo* info=EP_NEW WinServiceResultInfo();
		retResult.AddResultInfo(info);
		

		unsigned int packetType;
		unsigned int subPacketType;
		if(!stream.ReadUInt(packetType))
			break;
		info->m_packetType=(PacketType)packetType;
		if(!stream.ReadUInt(subPacketType))
			break;
		info->m_subPacketType=subPacketType;
		switch(packetType)
		{
		case PACKET_TYPE_MAIN_SERVICE_COMMAND:
			info->m_retrieveStatus=commandMainService(subPacketType,stream,info);
			break;
		case PACKET_TYPE_MAIN_SERVICE_GET:
			info->m_retrieveStatus=getMainServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_MAIN_SERVICE_SET:
			info->m_retrieveStatus=setMainServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_COMMAND_PROCESS_OBJECT:
			info->m_retrieveStatus=commandProcessObject(subPacketType,stream,info);
			break;
		case PACKET_TYPE_PROCESS_GET:
			info->m_retrieveStatus=getProcessInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_PROCESS_SET:
			info->m_retrieveStatus=setProcessInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_COMMAND_SERVICE_OBJECT:
			info->m_retrieveStatus=commandServiceObject(subPacketType,stream,info);
			break;
		case PACKET_TYPE_SERVICE_GET:
			info->m_retrieveStatus=getServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_SERVICE_SET:
			info->m_retrieveStatus=setServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_SERVICE_COMMAND:
			info->m_retrieveStatus=commandService(subPacketType,stream,info);
			break;

		}
	}
}



RetrieveStatus WinServicePacketProcessor::commandProcessObject(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	int procIdx;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}

RetrieveStatus WinServicePacketProcessor::commandServiceObject(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	int procIdx;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}

RetrieveStatus WinServicePacketProcessor::commandMainService(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_SUCCESS:
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}

bool GetString(Stream &stream, EpTString &retString)
{
	unsigned short retChar;
	retString=_T("");
	bool status=false;
	while((status=stream.ReadUShort(retChar)) && (TCHAR)retChar!=_T('\0'))
	{
		retString=retString.append(1,static_cast<TCHAR>(retChar));
	}
	return status;
}


RetrieveStatus WinServicePacketProcessor::getMainServiceInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	EpTString val;
	unsigned int uintVal;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			switch(subPacketType)
			{
			case MAIN_SERVICE_GET_PACKET_TYPE_SERVICE_NAME:
				if(!GetString(stream,val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_DOMAIN_NAME:
				if(!GetString(stream,val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_USERNAME:
				if(!GetString(stream,val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_USERPASSWORD:
				if(!GetString(stream,val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_DEPENDENCY:
				if(!GetString(stream,val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_NUM_OF_PROCESSES:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_CHECKSERVICEINTERVAL:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				if(GetString(stream,val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			}

			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;

}
RetrieveStatus WinServicePacketProcessor::setMainServiceInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			switch(subPacketType)
			{
			case MAIN_SERVICE_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
				break;
			case MAIN_SERVICE_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
				break;
			case MAIN_SERVICE_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				break;
			}
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}




RetrieveStatus WinServicePacketProcessor::getProcessInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	int procIdx;

	unsigned int tempUInt;

	ProcessStatusType procStatus;
	unsigned int delayStartTime;
	unsigned int delayPauseEndTime;
	bool isProcessRestart;
	bool isImpersonate;
	bool isUserInterface;
	int preProcessWaitTime;
	int postProcessWaitTime;
	EpTString commandLine;
	EpTString preProcessCommandLine;
	EpTString postProcessCommandLine;
	EpTString customProcessCommandLine;
	EpTString domainName;
	EpTString userName;
	EpTString userPassword;

	ProcessObjInfo procObjInfo;
	
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;


			switch(subPacketType)
			{
			case PROCESS_GET_PACKET_TYPE_ALL:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procObjInfo.m_processStatusType=(ProcessStatusType)tempUInt;

				if(!stream.ReadUInt(procObjInfo.m_delayStartTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				
				if(!stream.ReadUInt(procObjInfo.m_delayPauseEndTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				
				if(!stream.ReadUInt(tempUInt))
				{	
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					procObjInfo.m_isRestart=true;
				else
					procObjInfo.m_isRestart=false;

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					procObjInfo.m_isImpersonate=true;
				else
					procObjInfo.m_isImpersonate=false;

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					procObjInfo.m_isUserInterface=true;
				else
					procObjInfo.m_isUserInterface=false;

				if(!stream.ReadInt(procObjInfo.m_preProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadInt(procObjInfo.m_postProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}

				if(!GetString(stream,procObjInfo.m_commandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,procObjInfo.m_preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,procObjInfo.m_postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,procObjInfo.m_customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,procObjInfo.m_domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,procObjInfo.m_userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,procObjInfo.m_userPassword))
				{		
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=procObjInfo;
				break;
			case PROCESS_GET_PACKET_TYPE_STATUS:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procStatus=(ProcessStatusType)tempUInt;
				(*retInfo)=procStatus;

				break;
			case PROCESS_GET_PACKET_TYPE_COMMANDLINE:
				if(!GetString(stream,commandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=commandLine;
				break;
			case PROCESS_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
				if(!GetString(stream,preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessCommandLine;
				break;
			case PROCESS_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
				if(!GetString(stream,postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessCommandLine;
				break;
			case PROCESS_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				if(!GetString(stream,customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=customProcessCommandLine;
				break;
			case PROCESS_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
				if(!stream.ReadInt(preProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessWaitTime;
				break;
			case PROCESS_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
				if(!stream.ReadInt(postProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessWaitTime;
				break;
			case PROCESS_GET_PACKET_TYPE_DOMAINNAME:
				if(!GetString(stream,domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=domainName;
				break;
			case PROCESS_GET_PACKET_TYPE_USERNAME:
				if(!GetString(stream,userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userName;
				break;
			case PROCESS_GET_PACKET_TYPE_USERPASSWORD:
				if(!GetString(stream,userPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userPassword;
				break;
			case PROCESS_GET_PACKET_TYPE_DELAY_START_TIME:
				if(!stream.ReadUInt(delayStartTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayStartTime;
				break;
			case PROCESS_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
				if(!stream.ReadUInt(delayPauseEndTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayPauseEndTime;
				break;
			case PROCESS_GET_PACKET_TYPE_IS_PROCESS_RESTART:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					isProcessRestart=true;
				else
					isProcessRestart=false;
				(*retInfo)=isProcessRestart;
				break;
			case PROCESS_GET_PACKET_TYPE_IS_IMPERSONATE:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					isImpersonate=true;
				else
					isImpersonate=false;
				(*retInfo)=isImpersonate;
				break;
			case PROCESS_GET_PACKET_TYPE_IS_USER_INTERFACE:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					isUserInterface=true;
				else
					isUserInterface=false;
				(*retInfo)=isUserInterface;
				break;
			}
			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}


RetrieveStatus WinServicePacketProcessor::setProcessInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{

	unsigned int result;
	int procIdx;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=procIdx;
			break;
		}

	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;

}


RetrieveStatus WinServicePacketProcessor::getServiceInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	int serviceIdx;

	unsigned int tempUInt;

	ServiceStatusType serviceStatus;
	unsigned int delayStartTime;
	unsigned int delayPauseEndTime;
	bool isServiceRestart;
	bool isImpersonate;
	bool isUserInterface;
	int preProcessWaitTime;
	int postProcessWaitTime;
	EpTString serviceName;
	EpTString preProcessCommandLine;
	EpTString postProcessCommandLine;
	EpTString customProcessCommandLine;
	EpTString domainName;
	EpTString userName;
	EpTString userPassword;

	ServiceObjInfo serviceObjInfo;

	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(serviceIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=serviceIdx;
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			if(!stream.ReadInt(serviceIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=serviceIdx;

			switch(subPacketType)
			{
			case SERVICE_GET_PACKET_TYPE_ALL:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceObjInfo.m_serviceStatusType=(ServiceStatusType)tempUInt;

				if(!stream.ReadUInt(serviceObjInfo.m_delayStartTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}

				if(!stream.ReadUInt(serviceObjInfo.m_delayPauseEndTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					serviceObjInfo.m_isRestart=true;
				else
					serviceObjInfo.m_isRestart=false;

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					serviceObjInfo.m_isImpersonate=true;
				else
					serviceObjInfo.m_isImpersonate=false;

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					serviceObjInfo.m_isUserInterface=true;
				else
					serviceObjInfo.m_isUserInterface=false;

				if(!stream.ReadInt(serviceObjInfo.m_preProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadInt(serviceObjInfo.m_postProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}

				if(!GetString(stream,serviceObjInfo.m_serviceName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,serviceObjInfo.m_preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,serviceObjInfo.m_postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,serviceObjInfo.m_customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,serviceObjInfo.m_domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,serviceObjInfo.m_userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!GetString(stream,serviceObjInfo.m_userPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=serviceObjInfo;

				break;
			case SERVICE_GET_PACKET_TYPE_STATUS:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceStatus=(ServiceStatusType)tempUInt;
				(*retInfo)=serviceStatus;
				break;
			case SERVICE_GET_PACKET_TYPE_SERVICENAME:
				if(!GetString(stream,serviceName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=serviceName;
				break;
			case SERVICE_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
				if(!GetString(stream,preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessCommandLine;
				break;
			case SERVICE_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
				if(!GetString(stream,postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessCommandLine;
				break;
			case SERVICE_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				if(!GetString(stream,customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=customProcessCommandLine;
				break;
			case SERVICE_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
				if(!stream.ReadInt(preProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessWaitTime;
				break;
			case SERVICE_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
				if(!stream.ReadInt(postProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessWaitTime;
				break;
			case SERVICE_GET_PACKET_TYPE_DOMAINNAME:
				if(!GetString(stream,domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=domainName;
				break;
			case SERVICE_GET_PACKET_TYPE_USERNAME:
				if(!GetString(stream,userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userName;
				break;
			case SERVICE_GET_PACKET_TYPE_USERPASSWORD:
				if(!GetString(stream,userPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userPassword;
				break;
			case SERVICE_GET_PACKET_TYPE_DELAY_START_TIME:
				if(!stream.ReadUInt(delayStartTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayStartTime;
				break;
			case SERVICE_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
				if(!stream.ReadUInt(delayPauseEndTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayPauseEndTime;
				break;
			case SERVICE_GET_PACKET_TYPE_IS_SERVICE_RESTART:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					isServiceRestart=true;
				else
					isServiceRestart=false;
				(*retInfo)=isServiceRestart;
				break;
			case SERVICE_GET_PACKET_TYPE_IS_IMPERSONATE:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					isImpersonate=true;
				else
					isImpersonate=false;
				(*retInfo)=isImpersonate;
				break;
			case SERVICE_GET_PACKET_TYPE_IS_USER_INTERFACE:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(tempUInt)
					isUserInterface=true;
				else
					isUserInterface=false;
				(*retInfo)=isUserInterface;
				break;
			}
			break;
		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}


RetrieveStatus WinServicePacketProcessor::setServiceInfo(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{

	unsigned int result;
	int serviceIdx;
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(serviceIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=serviceIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			if(!stream.ReadInt(serviceIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=serviceIdx;
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			if(!stream.ReadInt(serviceIdx))
			{
				return RETRIEVE_STATUS_FAIL_OBJECTIDX;
			}
			retInfo->m_objIdx=serviceIdx;
			break;
		}

	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}

RetrieveStatus WinServicePacketProcessor::commandService(unsigned int subPacketType,epl::Stream &stream,WinServiceResultInfo* retInfo)
{
	unsigned int result;
	
	unsigned int err;
	unsigned int errCode;

	SERVICE_STATUS status;
	SERVICE_STATUS_PROCESS statusProc;
	ServiceHandleErrorInfo serviceHandleErrorInfo;

	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			break;
		case PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR:
			if(!stream.ReadUInt(err))
			{
				return RETRIEVE_STATUS_FAIL_ARGUMENT;
			}
			serviceHandleErrorInfo.m_serviceHandleError=(ServiceHandlerError)err;
			if(!stream.ReadUInt(errCode))
			{
				return RETRIEVE_STATUS_FAIL_ARGUMENT;
			}
			serviceHandleErrorInfo.m_lastErrorCode=(unsigned long)errCode;
			(*retInfo)=serviceHandleErrorInfo;
			break;
		case PACKET_PROCESS_STATUS_SUCCESS:
			switch(subPacketType)
			{
			case SERVICE_COMMAND_PACKET_TYPE_START:
				break;
			case SERVICE_COMMAND_PACKET_TYPE_CONTINUE:
				break;
			case SERVICE_COMMAND_PACKET_TYPE_STOP:
				break;
			case SERVICE_COMMAND_PACKET_TYPE_PAUSE:
				break;
			case SERVICE_COMMAND_PACKET_TYPE_CONTROL:
				if(!stream.ReadBytes((unsigned char*)&status,sizeof(SERVICE_STATUS)))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=status;
				break;
			case SERVICE_COMMAND_PACKET_TYPE_INSTALL:
				break;
			case SERVICE_COMMAND_PACKET_TYPE_UNINSTALL:
				break;
			case SERVICE_COMMAND_PACKET_TYPE_EDIT:
				if(!stream.ReadBytes((unsigned char*)&statusProc,sizeof(SERVICE_STATUS_PROCESS)))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=statusProc;
				break;
			case SERVICE_COMMAND_PACKET_TYPE_GET_STATUS:
				if(!stream.ReadBytes((unsigned char*)&statusProc,sizeof(SERVICE_STATUS_PROCESS)))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=statusProc;
				break;
			}


			break;

		}
	}
	else
	{
		return RETRIEVE_STATUS_FAIL_RESULT;
	}
	return RETRIEVE_STATUS_SUCCESS;
}
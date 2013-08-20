/*! 
WinService Client Packet Processor for the EpWinServiceAPILibrary

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
		case PACKET_TYPE_MAIN_SERVICE_INFO_GET:
			info->m_retrieveStatus=getMainServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_MAIN_SERVICE_INFO_SET:
			info->m_retrieveStatus=setMainServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_PROCESS_OBJECT_COMMAND:
			info->m_retrieveStatus=commandProcessObject(subPacketType,stream,info);
			break;
		case PACKET_TYPE_PROCESS_OBJECT_INFO_GET:
			info->m_retrieveStatus=getProcessInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_PROCESS_OBJECT_INFO_SET:
			info->m_retrieveStatus=setProcessInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_SERVICE_OBJECT_COMMAND:
			info->m_retrieveStatus=commandServiceObject(subPacketType,stream,info);
			break;
		case PACKET_TYPE_SERVICE_OBJECT_INFO_GET:
			info->m_retrieveStatus=getServiceInfo(subPacketType,stream,info);
			break;
		case PACKET_TYPE_SERVICE_OBJECT_INFO_SET:
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
	unsigned int errCode;
	unsigned int startStatus;
	int curRevision;
	DeployInfo deployInfo;	

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
			


			switch((ProcessObjectCommandPacketType)subPacketType)
			{
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
				if(!stream.ReadUInt(errCode))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadUInt(startStatus))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadInt(curRevision))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_errCode=(DeployErrCode)errCode;
				deployInfo.m_startStatus=(ObjectStartStatus)startStatus;
				deployInfo.m_revisionNum=curRevision;
				*retInfo=deployInfo;
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
				if(!stream.ReadUInt(startStatus))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				*retInfo=(ObjectStartStatus)startStatus;
				break;

			}
			break;
		case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_ARGUMENT;
			}
			retInfo->m_objIdx=procIdx;
			break;
		case PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR:
			if(!stream.ReadInt(procIdx))
			{
				return RETRIEVE_STATUS_FAIL_ARGUMENT;
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
	unsigned int errCode;
	unsigned int startStatus;
	int curRevision;
	DeployInfo deployInfo;
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
			switch((ServiceObjectCommandPacketType)subPacketType)
			{
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
				if(!stream.ReadUInt(errCode))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadUInt(startStatus))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadInt(curRevision))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}

				deployInfo.m_errCode=(DeployErrCode)errCode;
				deployInfo.m_startStatus=(ObjectStartStatus)startStatus;
				deployInfo.m_revisionNum=curRevision;
				*retInfo=deployInfo;
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_START:
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
				if(!stream.ReadUInt(startStatus))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				*retInfo=(ObjectStartStatus)startStatus;
				break;

			}
			break;
		case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
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
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_SERVICE_NAME:
				if(!stream.ReadTString(val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DOMAIN_NAME:
				if(!stream.ReadTString(val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERNAME:
				if(!stream.ReadTString(val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERPASSWORD:
				if(!stream.ReadTString(val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DEPENDENCY:
				if(!stream.ReadTString(val))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=val;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_PROCESSES:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_SERVICES:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKSERVICEINTERVAL:
				if(!stream.ReadUInt(uintVal))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=uintVal;
				break;
			case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				if(stream.ReadTString(val))
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
			case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
				break;
			case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
				break;
			case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
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
	int tempInt;

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

	EpTString deployRepositoryURL;
	EpTString deployLocalPath;
	EpTString deployUserName;
	EpTString deployUserPassword;
	DeployInfo deployInfo;
	

	ProcessObjInfo procObjInfo;
	
	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
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
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_ALL:
				if(!stream.ReadTString(procObjInfo.m_deployRepositoryURL))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_deployLocalPath))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_deployUserName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_deployUserPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
			
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procObjInfo.m_deployCurrentInfo.m_errCode=(DeployErrCode)tempUInt;
				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procObjInfo.m_deployCurrentInfo.m_revisionNum=tempInt;

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procObjInfo.m_deployLatestInfo.m_errCode=(DeployErrCode)tempUInt;

				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procObjInfo.m_deployLatestInfo.m_revisionNum=tempInt;

				
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

				if(!stream.ReadTString(procObjInfo.m_commandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(procObjInfo.m_userPassword))
				{		
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=procObjInfo;
				break;

			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
				if(!stream.ReadTString(deployRepositoryURL))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployRepositoryURL;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
				if(!stream.ReadTString(deployLocalPath))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployLocalPath;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
				if(!stream.ReadTString(deployUserName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployUserName;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
				if(!stream.ReadTString(deployUserPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployUserPassword;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_errCode=(DeployErrCode)tempUInt;
				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_revisionNum=tempInt;
				(*retInfo)=deployInfo;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_errCode=(DeployErrCode)tempUInt;
				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_revisionNum=tempInt;
				(*retInfo)=deployInfo;
				break;

			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_STATUS:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				procStatus=(ProcessStatusType)tempUInt;
				(*retInfo)=procStatus;

				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_COMMANDLINE:
				if(!stream.ReadTString(commandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=commandLine;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
				if(!stream.ReadTString(preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessCommandLine;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
				if(!stream.ReadTString(postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessCommandLine;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				if(!stream.ReadTString(customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=customProcessCommandLine;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
				if(!stream.ReadInt(preProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessWaitTime;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
				if(!stream.ReadInt(postProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessWaitTime;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
				if(!stream.ReadTString(domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=domainName;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
				if(!stream.ReadTString(userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userName;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
				if(!stream.ReadTString(userPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userPassword;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
				if(!stream.ReadUInt(delayStartTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayStartTime;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
				if(!stream.ReadUInt(delayPauseEndTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayPauseEndTime;
				break;
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
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
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
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
			case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
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
		case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
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
	int tempInt;

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

	EpTString deployRepositoryURL;
	EpTString deployLocalPath;
	EpTString deployUserName;
	EpTString deployUserPassword;
	DeployInfo deployInfo;


	ServiceObjInfo serviceObjInfo;

	if(stream.ReadUInt(result))
	{
		retInfo->m_packetProcessResult=(PacketProcessStatus)result;
		switch(result)
		{
		case PACKET_PROCESS_STATUS_FAIL:
			break;
		case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
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
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_ALL:
				if(!stream.ReadTString(serviceObjInfo.m_deployRepositoryURL))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_deployLocalPath))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_deployUserName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_deployUserPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceObjInfo.m_deployCurrentInfo.m_errCode=(DeployErrCode)tempUInt;
				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceObjInfo.m_deployCurrentInfo.m_revisionNum=tempInt;

				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceObjInfo.m_deployLatestInfo.m_errCode=(DeployErrCode)tempUInt;

				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceObjInfo.m_deployLatestInfo.m_revisionNum=tempInt;

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

				if(!stream.ReadTString(serviceObjInfo.m_serviceName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				if(!stream.ReadTString(serviceObjInfo.m_userPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=serviceObjInfo;

				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
				if(!stream.ReadTString(deployRepositoryURL))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployRepositoryURL;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
				if(!stream.ReadTString(deployLocalPath))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployLocalPath;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
				if(!stream.ReadTString(deployUserName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployUserName;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
				if(!stream.ReadTString(deployUserPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=deployUserPassword;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_errCode=(DeployErrCode)tempUInt;
				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_revisionNum=tempInt;
				(*retInfo)=deployInfo;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_errCode=(DeployErrCode)tempUInt;
				if(!stream.ReadInt(tempInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				deployInfo.m_revisionNum=tempInt;
				(*retInfo)=deployInfo;
				break;

			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_STATUS:
				if(!stream.ReadUInt(tempUInt))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				serviceStatus=(ServiceStatusType)tempUInt;
				(*retInfo)=serviceStatus;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_SERVICENAME:
				if(!stream.ReadTString(serviceName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=serviceName;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
				if(!stream.ReadTString(preProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessCommandLine;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
				if(!stream.ReadTString(postProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessCommandLine;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
				if(!stream.ReadTString(customProcessCommandLine))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=customProcessCommandLine;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
				if(!stream.ReadInt(preProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=preProcessWaitTime;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
				if(!stream.ReadInt(postProcessWaitTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=postProcessWaitTime;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
				if(!stream.ReadTString(domainName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=domainName;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
				if(!stream.ReadTString(userName))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userName;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
				if(!stream.ReadTString(userPassword))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=userPassword;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
				if(!stream.ReadUInt(delayStartTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayStartTime;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
				if(!stream.ReadUInt(delayPauseEndTime))
				{
					return RETRIEVE_STATUS_FAIL_ARGUMENT;
				}
				(*retInfo)=delayPauseEndTime;
				break;
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
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
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
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
			case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
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
		case PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE:
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
/*! 
AdminServerProcessor for the EpWinService

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
#include "stdafx.h"
#include "epAdminServerProcessor.h"
#include "epProcessHandler.h"
#include "epServiceProperties.h"
#include "epServiceHandler.h"
#include "epServiceManager.h"



void AdminServerProcessor::Process(AdminServerPacketParser *curClient,const Packet *packet)
{
	Stream stream;
	Stream outStream;
	PacketContainer<ReceivePacket> receivePacketContainer=PacketContainer<ReceivePacket>(reinterpret_cast<const void*>(packet->GetPacket()),packet->GetPacketByteSize(),false);
	PacketContainer<SendPacket> sendPacketContainer=PacketContainer<SendPacket>();
	unsigned int procCount=receivePacketContainer.GetPacketPtr()->count;
	sendPacketContainer.GetPacketPtr()->count=procCount;
	stream.WriteBytes(reinterpret_cast<unsigned char*>(receivePacketContainer.GetArray()),receivePacketContainer.GetArrayLength());
	stream.SetSeek(Stream::STREAM_SEEK_TYPE_SEEK_SET);
	
	for(int procTrav=0;procTrav<procCount;procTrav++)
	{
		unsigned int packetType;
		unsigned int subPacketType;
		if(!stream.ReadUInt(packetType))
			break;
		if(!stream.ReadUInt(subPacketType))
			break;

		outStream.WriteUInt(packetType);
		outStream.WriteUInt(subPacketType);
		switch(packetType)
		{
		
		case PACKET_TYPE_MAIN_SERVICE_COMMAND:
			commandMainServiceObject(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_MAIN_SERVICE_INFO_GET:
			getMainServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_MAIN_SERVICE_INFO_SET:
			setMainServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_OBJECT_COMMAND:
			commandProcessObject(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_OBJECT_INFO_GET:
			getProcessInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_OBJECT_INFO_SET:
			setProcessInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_OBJECT_COMMAND:
			commandServiceObject(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_OBJECT_INFO_GET:
			getServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_OBJECT_INFO_SET:
			setServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_COMMAND:
			commandService(subPacketType,stream,outStream);
			break;

		}
	}
	sendPacketContainer.SetArray(reinterpret_cast<const char *>(outStream.GetBuffer()),static_cast<unsigned int>(outStream.GetStreamSize()));
	Packet sendPacket=Packet(reinterpret_cast<const void*>(sendPacketContainer.GetPacketPtr()),static_cast<unsigned int>(sendPacketContainer.GetPacketByteSize()),false);
	curClient->Send(sendPacket);
}




void AdminServerProcessor::commandProcessObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	int objIdx;
	if(!stream.ReadInt(objIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}


	int waitTime=WAITTIME_INIFINITE;
	int rev=REVISION_UNKNOWN;
	EpTString cmd=_T("");
	ObjectStartStatus startStatus=OBJECT_START_STATUS_SUCCESS;

	switch(subPacketType)
	{
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		if(!stream.ReadInt(waitTime))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
		if(!stream.ReadInt(waitTime))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		if(!stream.ReadTString(cmd))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
		if(!stream.ReadInt(rev))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		break;

	default:
		break;
	}


	int processCount=(int)PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();
	
	DeployErrCode errCode=DEPLOY_ERR_CODE_SUCCESS;
	unsigned int curRev=0;
	if(objIdx==OBJECT_IDX_ALL)
	{

		for(int procTrav=0;procTrav<processCount;procTrav++)
		{
			switch(subPacketType)
			{
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Start();			
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_END:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Start();
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->CustomProcess(waitTime);
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->RunCommand(cmd.c_str(),waitTime);
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Deploy(curRev,startStatus,rev);
				break;
			}

		}
		switch(subPacketType)
		{
		case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(objIdx);
			retOutStream.WriteUInt(errCode);
			retOutStream.WriteUInt(startStatus);
			retOutStream.WriteInt(curRev);
			return;
			break;
		case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(objIdx);
			retOutStream.WriteUInt(startStatus);
			return;
			break;
		case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(objIdx);
			retOutStream.WriteUInt(startStatus);
			return;
			break;
		}
	}
	else
	{
		if(objIdx>=0 && objIdx<processCount)
		{
			switch(subPacketType)
			{
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
				startStatus=PROCESS_HANDLER_INSTANCE.At(objIdx)->Start();
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(objIdx);
				retOutStream.WriteUInt(startStatus);
				return;
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_END:
				PROCESS_HANDLER_INSTANCE.At(objIdx)->Stop();
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
				PROCESS_HANDLER_INSTANCE.At(objIdx)->Stop();
				startStatus=PROCESS_HANDLER_INSTANCE.At(objIdx)->Start();
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(objIdx);
				retOutStream.WriteUInt(startStatus);
				return;
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(objIdx)->CustomProcess(waitTime);
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
				PROCESS_HANDLER_INSTANCE.At(objIdx)->RunCommand(cmd.c_str(),waitTime);
				break;
			case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
				errCode=PROCESS_HANDLER_INSTANCE.At(objIdx)->Deploy(curRev,startStatus,rev);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(objIdx);
				retOutStream.WriteUInt(errCode);
				retOutStream.WriteUInt(startStatus);
				retOutStream.WriteInt(curRev);
				return;
				break;
			}
		}
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE);
			retOutStream.WriteInt(objIdx);
			return;
		}
	}

	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	retOutStream.WriteInt(objIdx);

}



void AdminServerProcessor::commandServiceObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	int objIdx;
	if(!stream.ReadInt(objIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}


	int waitTime=WAITTIME_INIFINITE;
	int rev=REVISION_UNKNOWN;
	EpTString cmd=_T("");
	ObjectStartStatus startStatus=OBJECT_START_STATUS_SUCCESS;
	switch(subPacketType)
	{
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		if(!stream.ReadInt(waitTime))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
		if(!stream.ReadInt(waitTime))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		if(!stream.ReadTString(cmd))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
		if(!stream.ReadInt(rev))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			retOutStream.WriteInt(objIdx);
			return;
		}
	default:
		break;
	}

	int serviceCount=(int)SERVICE_HANDLER_INSTANCE.GetNumberOfServices();

	DeployErrCode errCode=DEPLOY_ERR_CODE_SUCCESS;
	unsigned int curRev=0;

	if(objIdx==OBJECT_IDX_ALL)
	{
		for(int serviceTrav=0;serviceTrav<serviceCount;serviceTrav++)
		{
			switch(subPacketType)
			{
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_START:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Start();			
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_END:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->SetIsUserStopped(true);
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Stop();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_PAUSE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Pause();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CONTINUE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Continue();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Stop();
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Start();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->CustomProcess(waitTime);
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->RunCommand(cmd.c_str(),waitTime);
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Deploy(curRev,startStatus,rev);
				break;
			}

		}
		switch(subPacketType)
		{
		case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(objIdx);
			retOutStream.WriteUInt(errCode);
			retOutStream.WriteUInt(startStatus);
			retOutStream.WriteInt(curRev);
			return;
			break;
		case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(objIdx);
			retOutStream.WriteUInt(startStatus);
			return;
			break;
		case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(objIdx);
			retOutStream.WriteUInt(startStatus);
			return;
			break;
		}
	}
	else
	{
		if(objIdx>=0 && objIdx<serviceCount)
		{
			switch(subPacketType)
			{
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_START:
				startStatus=SERVICE_HANDLER_INSTANCE.At(objIdx)->Start();
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(objIdx);
				retOutStream.WriteUInt(startStatus);
				return;
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_END:
				SERVICE_HANDLER_INSTANCE.At(objIdx)->SetIsUserStopped(true);
				SERVICE_HANDLER_INSTANCE.At(objIdx)->Stop();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_PAUSE:
				SERVICE_HANDLER_INSTANCE.At(objIdx)->Pause();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CONTINUE:
				SERVICE_HANDLER_INSTANCE.At(objIdx)->Continue();
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
				SERVICE_HANDLER_INSTANCE.At(objIdx)->Stop();
				startStatus=SERVICE_HANDLER_INSTANCE.At(objIdx)->Start();
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(objIdx);
				retOutStream.WriteUInt(startStatus);
				return;
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
				SERVICE_HANDLER_INSTANCE.At(objIdx)->CustomProcess(waitTime);
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
				SERVICE_HANDLER_INSTANCE.At(objIdx)->RunCommand(cmd.c_str(),waitTime);
				break;
			case SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
				errCode=SERVICE_HANDLER_INSTANCE.At(objIdx)->Deploy(curRev,startStatus,rev);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(objIdx);
				retOutStream.WriteUInt(errCode);
				retOutStream.WriteUInt(startStatus);
				retOutStream.WriteInt(curRev);
				return;
				break;
			}
		}
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE);
			retOutStream.WriteInt(objIdx);
			return;
		}
	}

	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	retOutStream.WriteInt(objIdx);

}
void AdminServerProcessor::commandMainServiceObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	int waitTime=WAITTIME_INIFINITE;
	EpTString cmd=_T("");
	switch(subPacketType)
	{
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		if(!stream.ReadInt(waitTime))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		SERVICE_MANAGER_INSTANCE.RunCustomProcess(waitTime);
		break;
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_RUN_COMMAND:
		if(!stream.ReadInt(waitTime))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString(cmd))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		SERVICE_MANAGER_INSTANCE.RunCommand(cmd.c_str(),waitTime);
		break;
	}

	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
}

void AdminServerProcessor::getMainServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int strLen=0;
	
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	
	switch(subPacketType)
	{
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_SERVICE_NAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetServiceName());
		if(strLen)
			retOutStream.WriteTString(SERVICE_PROPERTIES_INSTANCE.GetServiceName());
		else
			retOutStream.WriteTString(_T("\0"));
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DOMAIN_NAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetDomainName());
		if(strLen)
			retOutStream.WriteTString(SERVICE_PROPERTIES_INSTANCE.GetDomainName());
		else
			retOutStream.WriteTString(_T("\0"));
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERNAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetUserName());
		if(strLen)
			retOutStream.WriteTString(SERVICE_PROPERTIES_INSTANCE.GetUserName());
		else
			retOutStream.WriteTString(_T("\0"));
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERPASSWORD:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetUserPassword());
		if(strLen)
			retOutStream.WriteTString(SERVICE_PROPERTIES_INSTANCE.GetUserPassword());
		else
			retOutStream.WriteTString(_T("\0"));
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DEPENDENCY:
		retOutStream.WriteTString(SERVICE_PROPERTIES_INSTANCE.GetOriginalDependency().GetString());		
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_PROCESSES:
		retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses());
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_SERVICES:
		retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.GetNumberOfServices());
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		retOutStream.WriteUInt(SERVICE_PROPERTIES_INSTANCE.GetCheckProcessInterval());
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKSERVICEINTERVAL:
		retOutStream.WriteUInt(SERVICE_PROPERTIES_INSTANCE.GetCheckServiceInterval());
		break;
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		retOutStream.WriteTString(SERVICE_PROPERTIES_INSTANCE.GetCustomProcessCommandLine().GetString());
		break;

	}
}
void AdminServerProcessor::setMainServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{

	unsigned int interval;
	EpTString retString;
	


	switch(subPacketType)
	{
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
		if(!stream.ReadUInt(interval))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
			return;
		}
		break;

	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		if(!stream.ReadTString(retString))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}	
		break;
	default:
		break;

	}

	switch(subPacketType)
	{
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		SERVICE_PROPERTIES_INSTANCE.SetCheckProcessInterval(interval);
		break;
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
		SERVICE_PROPERTIES_INSTANCE.SetCheckServiceInterval(interval);
		break;

	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		SERVICE_PROPERTIES_INSTANCE.SetCustomProcessCommandLine(retString.c_str());
		break;

	}
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	
}

void AdminServerProcessor::getProcessInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int procIdx;
	if(!stream.ReadUInt(procIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(procIdx>=0 && procIdx<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses())
	{
		int rev=REVISION_UNKNOWN;
		unsigned int retRev=0;
		DeployErrCode deployErrCode=DEPLOY_ERR_CODE_SUCCESS;
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		retOutStream.WriteInt(procIdx);
		switch(subPacketType)
		{
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_ALL:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployRepositoryURL());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployLocalPath());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployUserName());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployUserPassword());
			if((deployErrCode=PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCurrentRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);
			if((deployErrCode=PROCESS_HANDLER_INSTANCE.At(procIdx)->GetLatestRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);


			if(PROCESS_HANDLER_INSTANCE.At(procIdx)->IsStarted())
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_RUNNING);
			else
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_STOPPED);
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsRestart());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsImpersonate());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsUserInterface());
			retOutStream.WriteInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessWaitTime());
			retOutStream.WriteInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessWaitTime());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCommandLine().GetString());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetString());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetString());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetString());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetString());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetString());
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployRepositoryURL());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployLocalPath());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployUserName());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDeployUserPassword());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
			if((deployErrCode=PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCurrentRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:
			if((deployErrCode=PROCESS_HANDLER_INSTANCE.At(procIdx)->GetLatestRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);
			break;

		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_STATUS:
			if(PROCESS_HANDLER_INSTANCE.At(procIdx)->IsStarted())
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_RUNNING);
			else
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_STOPPED);
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_COMMANDLINE:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCommandLine().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
			retOutStream.WriteInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessWaitTime());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
			retOutStream.WriteInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessWaitTime());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
			retOutStream.WriteTString(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetString());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsRestart());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsImpersonate());
			break;
		case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsUserInterface());
			break;
		}
	}
	else
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE);
		retOutStream.WriteInt(procIdx);
		return;
	}
}




void AdminServerProcessor::setProcessInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int procIdx;
	int waitTime;
	if(!stream.ReadUInt(procIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(procIdx>=0 && procIdx<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses())
	{
		EpTString retString;
		unsigned int val;
		switch(subPacketType)
		{
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
			}

			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPreProcessCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPostProcessCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCustomProcessCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			break;


		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
			if(stream.ReadInt(waitTime))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPreProcessWaitTime(waitTime);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
			if(stream.ReadInt(waitTime))
			{

				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPostProcessWaitTime(waitTime);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;

		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDomainName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERNAME:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserPassword(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			break;


		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME:
			if(stream.ReadUInt(val))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDelayStartTime(val);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			if(stream.ReadUInt(val))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDelayPauseEndTime(val);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART:
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(false);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE:
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(false);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE:
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(false);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployRepositoryURL(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployLocalPath(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployUserName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			break;
		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployUserPassword(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			break;

		case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_ALL:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPreProcessCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPostProcessCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCustomProcessCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(stream.ReadInt(waitTime))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPreProcessWaitTime(waitTime);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadInt(waitTime))
			{

				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPostProcessWaitTime(waitTime);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDomainName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}		
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserPassword(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(stream.ReadUInt(val))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDelayStartTime(val);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDelayPauseEndTime(val);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(false);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(false);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(false);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}

			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployRepositoryURL(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
		
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployLocalPath(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	

			
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployUserName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
	
			
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDeployUserPassword(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}

			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(procIdx);
			break;
		}
	}
	else
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE);
		retOutStream.WriteInt(procIdx);
		return;
	}
}

void AdminServerProcessor::getServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int serviceIdx;
	if(!stream.ReadUInt(serviceIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(serviceIdx>=0 && serviceIdx<SERVICE_HANDLER_INSTANCE.GetNumberOfServices())
	{
		int rev=REVISION_UNKNOWN;
		unsigned int retRev=0;
		DeployErrCode deployErrCode=DEPLOY_ERR_CODE_SUCCESS;

		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		retOutStream.WriteInt(serviceIdx);
		switch(subPacketType)
		{
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_ALL:

			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployRepositoryURL());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployLocalPath());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployUserName());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployUserPassword());
			if((deployErrCode=SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetCurrentRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);
			if((deployErrCode=SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetLatestRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);

			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetStatus());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDelayStartTime());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDelayPauseEndTime());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetIsRestart());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetIsImpersonate());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetIsUserInterface());
			retOutStream.WriteInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPreProcessWaitTime());
			retOutStream.WriteInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPostProcessWaitTime());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetServiceName().GetString());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPreProcessCommandLine().GetString());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPostProcessCommandLine().GetString());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetCustomProcessCommandLine().GetString());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDomainName().GetString());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetUserName().GetString());
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetUserPassword().GetString());
			break;

		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployRepositoryURL());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployLocalPath());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployUserName());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDeployUserPassword());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
			if((deployErrCode=SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetCurrentRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:
			if((deployErrCode=SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetLatestRevision(retRev))==DEPLOY_ERR_CODE_SUCCESS)
				rev=(int)retRev;
			retOutStream.WriteUInt((unsigned int)deployErrCode);
			retOutStream.WriteInt(rev);
			break;

		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_STATUS:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetStatus());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_SERVICENAME:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetServiceName().GetString());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPreProcessCommandLine().GetString());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPostProcessCommandLine().GetString());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetCustomProcessCommandLine().GetString());
			break;

		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
			retOutStream.WriteInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPreProcessWaitTime());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
			retOutStream.WriteInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetPostProcessWaitTime());
			break;

		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDomainName().GetString());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetUserName().GetString());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
			retOutStream.WriteTString(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetUserPassword().GetString());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDelayStartTime());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetDelayPauseEndTime());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetIsRestart());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetIsImpersonate());
			break;
		case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(serviceIdx)->GetIsUserInterface());
			break;
		}
	}
	else
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE);
		retOutStream.WriteInt(serviceIdx);
		return;
	}
}
void AdminServerProcessor::setServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int serviceIdx;
	if(!stream.ReadUInt(serviceIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(serviceIdx>=0 && serviceIdx<SERVICE_HANDLER_INSTANCE.GetNumberOfServices())
	{
		EpTString retString;
		unsigned int val;
		int waitTime;
		switch(subPacketType)
		{
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_SERVICENAME:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetServiceName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
			}

			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPreProcessCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPostProcessCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetCustomProcessCommandLine(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			break;

		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
			if(stream.ReadInt(waitTime))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPreProcessWaitTime(waitTime);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
			if(stream.ReadInt(waitTime))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPostProcessWaitTime(waitTime);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetDomainName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERNAME:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetUserName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetUserPassword(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			break;


		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME:
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetDelayStartTime(val);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetDelayPauseEndTime(val);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART:
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsRestart(true);
				else
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsRestart(false);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE:
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsImpersonate(true);
				else
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsImpersonate(false);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE:
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsUserInterface(true);
				else
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsUserInterface(false);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;

		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployRepositoryURL(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployLocalPath(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployUserName(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			break;
		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD:
			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployUserPassword(retString.c_str());
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(serviceIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			break;

		case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_ALL:
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetServiceName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPreProcessCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPostProcessCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetCustomProcessCommandLine(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	

			if(stream.ReadInt(waitTime))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPreProcessWaitTime(waitTime);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadInt(waitTime))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetPostProcessWaitTime(waitTime);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}

			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetDomainName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetUserName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}		
			if(stream.ReadTString(retString))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetUserPassword(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetDelayStartTime(val);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetDelayPauseEndTime(val);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsRestart(true);
				else
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsRestart(false);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsImpersonate(true);
				else
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsImpersonate(false);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsUserInterface(true);
				else
					SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsUserInterface(false);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}

			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployRepositoryURL(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	

			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployLocalPath(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	


			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployUserName(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}	

			if(stream.ReadTString(retString))
			{
				PROCESS_HANDLER_INSTANCE.At(serviceIdx)->SetDeployUserPassword(retString.c_str());
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(serviceIdx);
				return;
			}

			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(serviceIdx);
			break;
		}
	}
	else
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_OBJECT_IDX_OUT_OF_RANCE);
		retOutStream.WriteInt(serviceIdx);
		return;
	}
}


void AdminServerProcessor::commandService(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	EpTString serviceName;
	if(!stream.ReadTString(serviceName))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}
	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;
	DWORD errCode;
	SERVICE_STATUS_PROCESS statusProc;
	SERVICE_STATUS status;
	unsigned int code;
	unsigned int tmpVal;

	ServiceInfo info;
	
	switch(subPacketType)
	{
	case SERVICE_COMMAND_PACKET_TYPE_START:
		err=SERVICE_HANDLER_INSTANCE.StartService(serviceName.c_str(),errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_CONTINUE:
		err=SERVICE_HANDLER_INSTANCE.ContinueService(serviceName.c_str(),errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_STOP:
		err=SERVICE_HANDLER_INSTANCE.StopService(serviceName.c_str(),errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_PAUSE:
		err=SERVICE_HANDLER_INSTANCE.PauseService(serviceName.c_str(),errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_CONTROL:
		if(!stream.ReadUInt(code))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		err=SERVICE_HANDLER_INSTANCE.ControlService(serviceName.c_str(),(ServiceControlCode)code,status,errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteBytes((unsigned char*)&status,sizeof(SERVICE_STATUS));
		}
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_INSTALL:
		if(!stream.ReadTString( info.displayName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.desiredAccess=(ServiceDesiredAccess)tmpVal;

		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.serviceType=(ServiceType)tmpVal;
		
		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.startType=(ServiceStartType)tmpVal;
		
		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.errorControl=(ServiceErrorControl)tmpVal;
		
		if(!stream.ReadTString(info.binaryPathName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.loadOrderGroup))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.dependencies))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.domainName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.userName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.password))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		err=SERVICE_HANDLER_INSTANCE.InstallService(serviceName.c_str(),info,errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_UNINSTALL:
		err=SERVICE_HANDLER_INSTANCE.UnInstallService(serviceName.c_str(),errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_EDIT:
		if(!stream.ReadTString( info.displayName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.desiredAccess=(ServiceDesiredAccess)tmpVal;

		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.serviceType=(ServiceType)tmpVal;

		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.startType=(ServiceStartType)tmpVal;

		if(!stream.ReadUInt(tmpVal))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		info.errorControl=(ServiceErrorControl)tmpVal;

		if(!stream.ReadTString(info.binaryPathName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.loadOrderGroup))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.dependencies))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.domainName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.userName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadTString( info.password))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadUInt(info.editControlBit))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		err=SERVICE_HANDLER_INSTANCE.EditService(serviceName.c_str(),info,errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;
	case SERVICE_COMMAND_PACKET_TYPE_GET_STATUS:
		err=SERVICE_HANDLER_INSTANCE.GetServiceStatus(serviceName.c_str(),statusProc,errCode);
		if(err==SERVICE_HANDLER_ERROR_SUCCESS)	
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteBytes((unsigned char*)&statusProc,sizeof(SERVICE_STATUS_PROCESS));
		}
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR);
			retOutStream.WriteUInt(err);
			retOutStream.WriteUInt(errCode);
		}
		break;

	}
}
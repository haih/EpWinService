#include "stdafx.h"
#include "epAdminServerProcessor.h"
#include "epProcessHandler.h"
#include "epServiceProperties.h"
#include "epServiceHandler.h"

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
		case PACKET_TYPE_COMMAND:
			commandProcess(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_GET:
			getServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_SET:
			setServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_GET:
			getProcessInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_SET:
			setProcessInfo(subPacketType,stream,outStream);
		case PACKET_TYPE_SERVICE_COMMAND:

			break;

		}
	}
	sendPacketContainer.SetArray(reinterpret_cast<const char *>(outStream.GetBuffer()),outStream.GetStreamSize());
	Packet sendPacket=Packet(reinterpret_cast<const void*>(sendPacketContainer.GetPacketPtr()),sendPacketContainer.GetPacketByteSize(),false);
	curClient->Send(sendPacket);
}
void AdminServerProcessor::commandProcess(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	int procIdx;
	if(!stream.ReadInt(procIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}
	

	int processCount=(int)PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();
	if(procIdx==-1)
	{
		for(int procTrav=0;procTrav<processCount;procTrav++)
		{
			switch(subPacketType)
			{
			case COMMAND_PACKET_TYPE_START_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->StartProcess();			
				break;
			case COMMAND_PACKET_TYPE_END_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->EndProcess();
				break;
			case COMMAND_PACKET_TYPE_BOUNCE_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->EndProcess();
				PROCESS_HANDLER_INSTANCE.At(procTrav)->StartProcess();
				break;
			case COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->CustomProcess();
				break;
			}
		}

	}
	else
	{
		if(procIdx>=0 && procIdx<processCount)
		{
			switch(subPacketType)
			{
			case COMMAND_PACKET_TYPE_START_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procIdx)->StartProcess();			
				break;
			case COMMAND_PACKET_TYPE_END_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procIdx)->EndProcess();
				break;
			case COMMAND_PACKET_TYPE_BOUNCE_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procIdx)->EndProcess();
				PROCESS_HANDLER_INSTANCE.At(procIdx)->StartProcess();
				break;
			case COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procIdx)->CustomProcess();
				break;
			}
		}
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE);
			retOutStream.WriteInt(procIdx);
			return;
		}
	}
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	retOutStream.WriteInt(procIdx);

}
void AdminServerProcessor::getServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int strLen=0;
	
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	
	switch(subPacketType)
	{
	case SERVICE_GET_PACKET_TYPE_SERVICE_NAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetServiceName());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetServiceName()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case SERVICE_GET_PACKET_TYPE_DOMAIN_NAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetDomainName());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetDomainName()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case SERVICE_GET_PACKET_TYPE_USERNAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetUserName());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetUserName()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case SERVICE_GET_PACKET_TYPE_USERPASSWORD:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetUserPassword());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetUserPassword()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case SERVICE_GET_PACKET_TYPE_DEPENDENCY:
		retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetOriginalDependency().GetString()),(SERVICE_PROPERTIES_INSTANCE.GetOriginalDependency().GetLength()+1)*sizeof(TCHAR));		
		break;
	case SERVICE_GET_PACKET_TYPE_NUM_OF_PROCESSES:
		retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses());
		break;
	case SERVICE_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		retOutStream.WriteUInt(SERVICE_PROPERTIES_INSTANCE.GetCheckProcessInterval());
		break;
	}
}
void AdminServerProcessor::setServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{

	unsigned int interval;
	if(!stream.ReadUInt(interval))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	SERVICE_PROPERTIES_INSTANCE.SetCheckProcessInterval(interval);
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
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		retOutStream.WriteInt(procIdx);
		switch(subPacketType)
		{
		case PROCESS_GET_PACKET_TYPE_ALL:
			if(PROCESS_HANDLER_INSTANCE.At(procIdx)->IsProcessStarted())
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_RUNNING);
			else
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_STOPPED);
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsProcessRestart());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsImpersonate());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsUserInterface());
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_STATUS:
			if(PROCESS_HANDLER_INSTANCE.At(procIdx)->IsProcessStarted())
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_RUNNING);
			else
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_STOPPED);
			break;
		case PROCESS_GET_PACKET_TYPE_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_DOMAINNAME:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_USERNAME:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_USERPASSWORD:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetString()),(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetLength()+1)*sizeof(TCHAR));
			break;
		case PROCESS_GET_PACKET_TYPE_DELAY_START_TIME:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			break;
		case PROCESS_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			break;
		case PROCESS_GET_PACKET_TYPE_IS_PROCESS_RESTART:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsProcessRestart());
			break;
		case PROCESS_GET_PACKET_TYPE_IS_IMPERSONATE:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsImpersonate());
			break;
		case PROCESS_GET_PACKET_TYPE_IS_USER_INTERFACE:
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsUserInterface());
			break;
		}
	}
	else
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE);
		retOutStream.WriteInt(procIdx);
		return;
	}
}

bool GetString(Stream &stream, CString &retString)
{
	unsigned short retChar;
	retString=_T("");
	bool status=false;
	while((status=stream.ReadUShort(retChar)) && (TCHAR)retChar!=_T('\0'))
	{
		retString.AppendChar(static_cast<TCHAR>(retChar));
	}
	return status;
}


void AdminServerProcessor::setProcessInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int procIdx;
	if(!stream.ReadUInt(procIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(procIdx>=0 && procIdx<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses())
	{
		CString retString;
		unsigned int val;
		switch(subPacketType)
		{
		case PROCESS_SET_PACKET_TYPE_COMMANDLINE:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCommandLine(retString);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
			}

			break;
		case PROCESS_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPreProcessCommandLine(retString);
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
		case PROCESS_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPostProcessCommandLine(retString);
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
		case PROCESS_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCustomProcessCommandLine(retString);
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
		case PROCESS_SET_PACKET_TYPE_DOMAINNAME:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDomainName(retString);
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
		case PROCESS_SET_PACKET_TYPE_USERNAME:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserName(retString);
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
		case PROCESS_SET_PACKET_TYPE_USERPASSWORD:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserPassword(retString);
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


		case PROCESS_SET_PACKET_TYPE_DELAY_START_TIME:
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
		case PROCESS_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
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
		case PROCESS_SET_PACKET_TYPE_IS_PROCESS_RESTART:
			if(stream.ReadUInt(val))
			{
				if(val)
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsProcessRestart(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsProcessRestart(false);
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
		case PROCESS_SET_PACKET_TYPE_IS_IMPERSONATE:
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
		case PROCESS_SET_PACKET_TYPE_IS_USER_INTERFACE:
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
		case PROCESS_SET_PACKET_TYPE_ALL:
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPreProcessCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetPostProcessCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetCustomProcessCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetDomainName(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserName(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}		
			if(GetString(stream,retString))
			{
				PROCESS_HANDLER_INSTANCE.At(procIdx)->SetUserPassword(retString);
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
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsProcessRestart(true);
				else
					PROCESS_HANDLER_INSTANCE.At(procIdx)->SetIsProcessRestart(false);
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
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
			retOutStream.WriteInt(procIdx);
			break;
		}
	}
	else
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE);
		retOutStream.WriteInt(procIdx);
		return;
	}
}


void AdminServerProcessor::commandService(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	CString serviceName;
	if(!GetString(stream,serviceName))
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
		err=SERVICE_HANDLER_INSTANCE.StartService(serviceName.GetString(),errCode);
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
		err=SERVICE_HANDLER_INSTANCE.ContinueService(serviceName.GetString(),errCode);
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
		err=SERVICE_HANDLER_INSTANCE.StopService(serviceName.GetString(),errCode);
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
		err=SERVICE_HANDLER_INSTANCE.PauseService(serviceName.GetString(),errCode);
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
		err=SERVICE_HANDLER_INSTANCE.ControlService(serviceName.GetString(),(ServiceControlCode)code,status,errCode);
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
		if(!GetString(stream, info.displayName))
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
		
		if(!GetString(stream,info.binaryPathName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.loadOrderGroup))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.dependencies))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.domainName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.userName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.password))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadUInt(info.editControlBit))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		err=SERVICE_HANDLER_INSTANCE.InstallService(serviceName.GetString(),info,errCode);
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
		err=SERVICE_HANDLER_INSTANCE.UnInstallService(serviceName.GetString(),errCode);
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
		if(!GetString(stream, info.displayName))
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

		if(!GetString(stream,info.binaryPathName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.loadOrderGroup))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.dependencies))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.domainName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.userName))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!GetString(stream, info.password))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		if(!stream.ReadUInt(info.editControlBit))
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
			return;
		}
		err=SERVICE_HANDLER_INSTANCE.EditService(serviceName.GetString(),info,errCode);
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
		err=SERVICE_HANDLER_INSTANCE.GetServiceStatus(serviceName.GetString(),statusProc,errCode);
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
/*! 
AdminServerProcessor for the EpWinService
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
	sendPacketContainer.GetPacketPtr()->packetId=receivePacketContainer.GetPacketPtr()->packetId;
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
		case PACKET_TYPE_MAIN_SERVICE_GET:
			getMainServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_MAIN_SERVICE_SET:
			setMainServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_GET:
			getProcessInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_PROCESS_SET:
			setProcessInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_GET:
			getServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_SET:
			setServiceInfo(subPacketType,stream,outStream);
			break;
		case PACKET_TYPE_SERVICE_COMMAND:
			commandService(subPacketType,stream,outStream);
			break;

		}
	}
	sendPacketContainer.SetArray(reinterpret_cast<const char *>(outStream.GetBuffer()),outStream.GetStreamSize());
	Packet sendPacket=Packet(reinterpret_cast<const void*>(sendPacketContainer.GetPacketPtr()),sendPacketContainer.GetPacketByteSize(),false);
	curClient->Send(sendPacket);
}

void AdminServerProcessor::commandServiceObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	int serviceIdx;
	if(!stream.ReadInt(serviceIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}


	int serviceCount=(int)SERVICE_HANDLER_INSTANCE.GetNumberOfServices();
	if(serviceIdx==-1)
	{
		for(int serviceTrav=0;serviceTrav<serviceCount;serviceTrav++)
		{
			switch(subPacketType)
			{
			case COMMAND_PACKET_TYPE_START_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Start();			
				break;
			case COMMAND_PACKET_TYPE_END_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->SetIsUserStopped(true);
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Stop();
				break;
			case COMMAND_PACKET_TYPE_PAUSE_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Pause();
				break;
			case COMMAND_PACKET_TYPE_CONTINUE_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Continue();
				break;
			case COMMAND_PACKET_TYPE_BOUNCE_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Stop();
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Start();
				break;
			case COMMAND_PACKET_TYPE_CUSTOM_PROCESS_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->CustomProcess();
				break;
			}

		}
	}
	else
	{
		if(serviceIdx>=0 && serviceIdx<serviceCount)
		{
			switch(subPacketType)
			{
			case COMMAND_PACKET_TYPE_START_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->Start();			
				break;
			case COMMAND_PACKET_TYPE_END_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->SetIsUserStopped(true);
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->Stop();
				break;
			case COMMAND_PACKET_TYPE_PAUSE_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->Pause();
				break;
			case COMMAND_PACKET_TYPE_CONTINUE_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->Continue();
				break;
			case COMMAND_PACKET_TYPE_BOUNCE_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->Stop();
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->Start();
				break;
			case COMMAND_PACKET_TYPE_CUSTOM_PROCESS_SERVICE:
				SERVICE_HANDLER_INSTANCE.At(serviceIdx)->CustomProcess();
				break;
			}
		}
		else
		{
			retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE);
			retOutStream.WriteInt(serviceIdx);
			return;
		}
	}
	
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	retOutStream.WriteInt(serviceIdx);

}
void AdminServerProcessor::commandProcessObject(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
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
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Start();			
				break;
			case COMMAND_PACKET_TYPE_END_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
				break;
			case COMMAND_PACKET_TYPE_BOUNCE_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
				PROCESS_HANDLER_INSTANCE.At(procTrav)->Start();
				break;
			case COMMAND_PACKET_TYPE_CUSTOM_PROCESS_PROCESS:
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
				PROCESS_HANDLER_INSTANCE.At(procIdx)->Start();			
				break;
			case COMMAND_PACKET_TYPE_END_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procIdx)->Stop();
				break;
			case COMMAND_PACKET_TYPE_BOUNCE_PROCESS:
				PROCESS_HANDLER_INSTANCE.At(procIdx)->Stop();
				PROCESS_HANDLER_INSTANCE.At(procIdx)->Start();
				break;
			case COMMAND_PACKET_TYPE_CUSTOM_PROCESS_PROCESS:
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
void AdminServerProcessor::commandProcess(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	if((unsigned int)subPacketType<=(unsigned int)COMMAND_PACKET_TYPE_CUSTOM_PROCESS_PROCESS)
	{
		commandProcessObject(subPacketType,stream,retOutStream);
	}
	else
	{
		commandServiceObject(subPacketType,stream,retOutStream);
	}
	
}
void AdminServerProcessor::getMainServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int strLen=0;
	
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	
	switch(subPacketType)
	{
	case MAIN_SERVICE_GET_PACKET_TYPE_SERVICE_NAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetServiceName());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetServiceName()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_DOMAIN_NAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetDomainName());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetDomainName()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_USERNAME:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetUserName());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetUserName()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_USERPASSWORD:
		strLen=System::TcsLen(SERVICE_PROPERTIES_INSTANCE.GetUserPassword());
		if(strLen)
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetUserPassword()),(strLen+1)*sizeof(TCHAR));
		else
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(_T("\0")),(strLen+1)*sizeof(TCHAR));
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_DEPENDENCY:
		retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_PROPERTIES_INSTANCE.GetOriginalDependency().GetString()),(SERVICE_PROPERTIES_INSTANCE.GetOriginalDependency().GetLength()+1)*sizeof(TCHAR));		
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_NUM_OF_PROCESSES:
		retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses());
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		retOutStream.WriteUInt(SERVICE_PROPERTIES_INSTANCE.GetCheckProcessInterval());
		break;
	case MAIN_SERVICE_GET_PACKET_TYPE_CHECKSERVICEINTERVAL:
		retOutStream.WriteUInt(SERVICE_PROPERTIES_INSTANCE.GetCheckServiceInterval());
		break;

	}
}
void AdminServerProcessor::setMainServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{

	unsigned int interval;
	if(!stream.ReadUInt(interval))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}
	retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
	switch(subPacketType)
	{
	case MAIN_SERVICE_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		SERVICE_PROPERTIES_INSTANCE.SetCheckProcessInterval(interval);
		break;
	case MAIN_SERVICE_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
		SERVICE_PROPERTIES_INSTANCE.SetCheckServiceInterval(interval);
		break;

	}
	
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
			if(PROCESS_HANDLER_INSTANCE.At(procIdx)->IsStarted())
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_RUNNING);
			else
				retOutStream.WriteUInt(PROCESS_STATUS_TYPE_STOPPED);
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsRestart());
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
			if(PROCESS_HANDLER_INSTANCE.At(procIdx)->IsStarted())
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
			retOutStream.WriteUInt(PROCESS_HANDLER_INSTANCE.At(procIdx)->GetIsRestart());
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

void AdminServerProcessor::getServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int procIdx;
	if(!stream.ReadUInt(procIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(procIdx>=0 && procIdx<SERVICE_HANDLER_INSTANCE.GetNumberOfServices())
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
		retOutStream.WriteInt(procIdx);
		switch(subPacketType)
		{
		case SERVICE_GET_PACKET_TYPE_ALL:

			
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetStatus());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetIsRestart());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetIsImpersonate());
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetIsUserInterface());
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetServiceName().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetServiceName().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetLength()+1)*sizeof(TCHAR));
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_STATUS:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetStatus());
			break;
		case SERVICE_GET_PACKET_TYPE_SERVICENAME:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetServiceName().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetServiceName().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPreProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetPostProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetCustomProcessCommandLine().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_DOMAINNAME:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDomainName().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_USERNAME:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserName().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_USERPASSWORD:
			retOutStream.WriteBytes(reinterpret_cast<const unsigned char*>(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetString()),(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetUserPassword().GetLength()+1)*sizeof(TCHAR));
			break;
		case SERVICE_GET_PACKET_TYPE_DELAY_START_TIME:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDelayStartTime());
			break;
		case SERVICE_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetDelayPauseEndTime());
			break;
		case SERVICE_GET_PACKET_TYPE_IS_SERVICE_RESTART:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetIsRestart());
			break;
		case SERVICE_GET_PACKET_TYPE_IS_IMPERSONATE:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetIsImpersonate());
			break;
		case SERVICE_GET_PACKET_TYPE_IS_USER_INTERFACE:
			retOutStream.WriteUInt(SERVICE_HANDLER_INSTANCE.At(procIdx)->GetIsUserInterface());
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
void AdminServerProcessor::setServiceInfo(unsigned int subPacketType,Stream &stream,Stream &retOutStream)
{
	unsigned int procIdx;
	if(!stream.ReadUInt(procIdx))
	{
		retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL);
		return;
	}

	if(procIdx>=0 && procIdx<SERVICE_HANDLER_INSTANCE.GetNumberOfServices())
	{
		CString retString;
		unsigned int val;
		switch(subPacketType)
		{
		case SERVICE_SET_PACKET_TYPE_SERVICENAME:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetServiceName(retString);
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_SUCCESS);
				retOutStream.WriteInt(procIdx);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
			}

			break;
		case SERVICE_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetPreProcessCommandLine(retString);
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
		case SERVICE_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetPostProcessCommandLine(retString);
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
		case SERVICE_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetCustomProcessCommandLine(retString);
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
		case SERVICE_SET_PACKET_TYPE_DOMAINNAME:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetDomainName(retString);
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
		case SERVICE_SET_PACKET_TYPE_USERNAME:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetUserName(retString);
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
		case SERVICE_SET_PACKET_TYPE_USERPASSWORD:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetUserPassword(retString);
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


		case SERVICE_SET_PACKET_TYPE_DELAY_START_TIME:
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetDelayStartTime(val);
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
		case SERVICE_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetDelayPauseEndTime(val);
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
		case SERVICE_SET_PACKET_TYPE_IS_SERVICE_RESTART:
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(true);
				else
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(false);
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
		case SERVICE_SET_PACKET_TYPE_IS_IMPERSONATE:
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(true);
				else
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(false);
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
		case SERVICE_SET_PACKET_TYPE_IS_USER_INTERFACE:
			if(stream.ReadUInt(val))
			{
				if(val)
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(true);
				else
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(false);
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
		case SERVICE_SET_PACKET_TYPE_ALL:
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetServiceName(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetPreProcessCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetPostProcessCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetCustomProcessCommandLine(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetDomainName(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetUserName(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}		
			if(GetString(stream,retString))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetUserPassword(retString);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}	
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetDelayStartTime(val);
			}
			else
			{
				retOutStream.WriteUInt(PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR);
				retOutStream.WriteInt(procIdx);
				return;
			}
			if(stream.ReadUInt(val))
			{
				SERVICE_HANDLER_INSTANCE.At(procIdx)->SetDelayPauseEndTime(val);
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
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(true);
				else
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsRestart(false);
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
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(true);
				else
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsImpersonate(false);
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
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(true);
				else
					SERVICE_HANDLER_INSTANCE.At(procIdx)->SetIsUserInterface(false);
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
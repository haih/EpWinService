/*! 
WinService Packet Generator for the EpWinServiceAPILibrary
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
#include "epWinServicePacketGenerator.h"

using namespace epws;

WinServicePacketGenerator::WinServicePacketGenerator(LockPolicy lockPolicyType):SmartObject(lockPolicyType)
{
	m_count=0;
	m_lockPolicy=lockPolicyType;
	switch(lockPolicyType)
	{
	case LOCK_POLICY_CRITICALSECTION:
		m_lock=EP_NEW CriticalSectionEx();
		break;
	case LOCK_POLICY_MUTEX:
		m_lock=EP_NEW Mutex();
		break;
	case LOCK_POLICY_NONE:
		m_lock=EP_NEW NoLock();
		break;
	default:
		m_lock=NULL;
		break;
	}
}
WinServicePacketGenerator::~WinServicePacketGenerator()
{
	if(m_lock)
		EP_DELETE m_lock;
}
WinServicePacketGenerator::WinServicePacketGenerator(const WinServicePacketGenerator& b):SmartObject(b)
{
	m_count=b.m_count;
	m_stream=b.m_stream;
	m_lockPolicy=b.m_lockPolicy;
	switch(m_lockPolicy)
	{
	case LOCK_POLICY_CRITICALSECTION:
		m_lock=EP_NEW CriticalSectionEx();
		break;
	case LOCK_POLICY_MUTEX:
		m_lock=EP_NEW Mutex();
		break;
	case LOCK_POLICY_NONE:
		m_lock=EP_NEW NoLock();
		break;
	default:
		m_lock=NULL;
		break;
	}

}
WinServicePacketGenerator & WinServicePacketGenerator::operator=(const WinServicePacketGenerator&b)
{
	if(this!=&b)
	{	
		SmartObject::operator =(b);
		LockObj lock(m_lock);
		m_count=b.m_count;
		m_stream=b.m_stream;

	}
	return *this;
}

unsigned int WinServicePacketGenerator::GetCount() const
{
	LockObj lock(m_lock);
	return m_count;
}

void WinServicePacketGenerator::Clear()
{
	LockObj lock(m_lock);
	m_stream.Clear();
	m_stream.SetSeek(epl::Stream::STREAM_SEEK_TYPE_SEEK_SET);
	m_count=0;
}
void WinServicePacketGenerator::AddCommandProcessObj(CommandProcessObjectPacketType type, int objIndex,int waitTime, EpTString cmd)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_COMMAND_PROCESS_OBJECT);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteInt(objIndex);
	switch(type)
	{
	case COMMAND_PROCESS_OBJECT_PACKET_TYPE_CUSTOM_PROCESS:
		m_stream.WriteInt(waitTime);
		break;
	case COMMAND_PROCESS_OBJECT_PACKET_TYPE_RUN_COMMAND:
		m_stream.WriteInt(waitTime);
		m_stream.WriteBytes((unsigned char*)cmd.c_str(),sizeof(TCHAR)*(cmd.size()+1));
		break;
	default:
		break;

	}
}
void WinServicePacketGenerator::AddCommandServiceObj(CommandServiceObjectPacketType type, int objIndex,int waitTime, EpTString cmd)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_COMMAND_SERVICE_OBJECT);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteInt(objIndex);
	switch(type)
	{
	case COMMAND_PROCESS_OBJECT_PACKET_TYPE_CUSTOM_PROCESS:
		m_stream.WriteInt(waitTime);
		break;
	case COMMAND_PROCESS_OBJECT_PACKET_TYPE_RUN_COMMAND:
		m_stream.WriteInt(waitTime);
		m_stream.WriteBytes((unsigned char*)cmd.c_str(),sizeof(TCHAR)*(cmd.size()+1));
		break;
	default:
		break;

	}
}

void WinServicePacketGenerator::AddCommandMainService(CommandMainServicePackeType type,int waitTime, EpTString cmd)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_MAIN_SERVICE_COMMAND);
	m_stream.WriteUInt((unsigned int)type);
	switch(type)
	{
	case COMMAND_MAIN_SERVICE_PACKET_TYPE_CUSTOM_PROCESS:
		m_stream.WriteInt(waitTime);
		break;
	case COMMAND_MAIN_SERVICE_PACKET_TYPE_RUN_COMMAND:
		m_stream.WriteInt(waitTime);
		m_stream.WriteBytes((unsigned char*)cmd.c_str(),(cmd.size()+1)*sizeof(TCHAR));
		break;
	}
}


void WinServicePacketGenerator::AddGetMainServiceInfo(MainServiceGetPacketType type)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_MAIN_SERVICE_GET);
	m_stream.WriteUInt((unsigned int)type);
}

void WinServicePacketGenerator::AddSetMainServiceInfo(MainServiceSetPacketType type,MainServiceInfo info)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_MAIN_SERVICE_SET);
	m_stream.WriteUInt((unsigned int)type);
	
	switch(type)
	{
	case MAIN_SERVICE_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
	case MAIN_SERVICE_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
		m_stream.WriteUInt(info.m_interval);
		break;
	case MAIN_SERVICE_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		m_stream.WriteBytes((unsigned char*)info.m_command.c_str(),(info.m_command.size()+1)*sizeof(TCHAR));
		break;
	default:
		break;

	}
}

void WinServicePacketGenerator::AddGetServiceInfo(ServiceGetPacketType type, unsigned int serviceIndex)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_SERVICE_GET);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteUInt(serviceIndex);
}
void WinServicePacketGenerator::AddSetServiceInfo(ServiceSetPacketType type, unsigned int serviceIndex, ServiceObjInfo info)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_SERVICE_SET);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteUInt(serviceIndex);
	switch(type)
	{
	case SERVICE_SET_PACKET_TYPE_SERVICENAME:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_serviceName.c_str()),(info.m_serviceName.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_preProcessCommandLine.c_str()),(info.m_preProcessCommandLine.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_postProcessCommandLine.c_str()),(info.m_postProcessCommandLine.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_customProcessCommandLine.c_str()),(info.m_customProcessCommandLine.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		m_stream.WriteInt(info.m_preProcessWaitTime);
		break;
	case SERVICE_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		m_stream.WriteInt(info.m_postProcessWaitTime);
		break;
	case SERVICE_SET_PACKET_TYPE_DOMAINNAME:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_domainName.c_str()),(info.m_domainName.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_SET_PACKET_TYPE_USERNAME:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userName.c_str()),(info.m_userName.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_SET_PACKET_TYPE_USERPASSWORD:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userPassword.c_str()),(info.m_userPassword.size()+1)*sizeof(TCHAR));
		break;


	case SERVICE_SET_PACKET_TYPE_DELAY_START_TIME:
		m_stream.WriteUInt(info.m_delayStartTime);
		break;
	case SERVICE_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		m_stream.WriteUInt(info.m_delayPauseEndTime);
		break;
	case SERVICE_SET_PACKET_TYPE_IS_SERVICE_RESTART:
		if(info.m_isRestart)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	case SERVICE_SET_PACKET_TYPE_IS_IMPERSONATE:
		if(info.m_isImpersonate)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	case SERVICE_SET_PACKET_TYPE_IS_USER_INTERFACE:
		if(info.m_isUserInterface)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	case SERVICE_SET_PACKET_TYPE_ALL:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_serviceName.c_str()),(info.m_serviceName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_preProcessCommandLine.c_str()),(info.m_preProcessCommandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_postProcessCommandLine.c_str()),(info.m_postProcessCommandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_customProcessCommandLine.c_str()),(info.m_customProcessCommandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteInt(info.m_preProcessWaitTime);
		m_stream.WriteInt(info.m_postProcessWaitTime);
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_domainName.c_str()),(info.m_domainName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userName.c_str()),(info.m_userName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userPassword.c_str()),(info.m_userPassword.size()+1)*sizeof(TCHAR));
		m_stream.WriteUInt(info.m_delayStartTime);
		m_stream.WriteUInt(info.m_delayPauseEndTime);
		if(info.m_isRestart)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		if(info.m_isImpersonate)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		if(info.m_isUserInterface)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	}
}
void WinServicePacketGenerator::AddGetProcessInfo(ProcessGetPacketType type, unsigned int procIndex)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_PROCESS_GET);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteUInt(procIndex);
}
void WinServicePacketGenerator::AddSetProcessInfo(ProcessSetPacketType type, unsigned int procIndex,ProcessObjInfo info)
{
	LockObj lock(m_lock);
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_PROCESS_SET);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteUInt(procIndex);
	switch(type)
	{
	case PROCESS_SET_PACKET_TYPE_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_commandLine.c_str()),(info.m_commandLine.size()+1)*sizeof(TCHAR));
		break;
	case PROCESS_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_preProcessCommandLine.c_str()),(info.m_preProcessCommandLine.size()+1)*sizeof(TCHAR));
		break;
	case PROCESS_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_postProcessCommandLine.c_str()),(info.m_postProcessCommandLine.size()+1)*sizeof(TCHAR));
		break;
	case PROCESS_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_customProcessCommandLine.c_str()),(info.m_customProcessCommandLine.size()+1)*sizeof(TCHAR));
		break;
	case PROCESS_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		m_stream.WriteInt(info.m_preProcessWaitTime);
		break;
	case PROCESS_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		m_stream.WriteInt(info.m_postProcessWaitTime);
		break;
	case PROCESS_SET_PACKET_TYPE_DOMAINNAME:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_domainName.c_str()),(info.m_domainName.size()+1)*sizeof(TCHAR));
		break;
	case PROCESS_SET_PACKET_TYPE_USERNAME:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userName.c_str()),(info.m_userName.size()+1)*sizeof(TCHAR));
		break;
	case PROCESS_SET_PACKET_TYPE_USERPASSWORD:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userPassword.c_str()),(info.m_userPassword.size()+1)*sizeof(TCHAR));
		break;


	case PROCESS_SET_PACKET_TYPE_DELAY_START_TIME:
		m_stream.WriteUInt(info.m_delayStartTime);
		break;
	case PROCESS_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		m_stream.WriteUInt(info.m_delayPauseEndTime);
		break;
	case PROCESS_SET_PACKET_TYPE_IS_PROCESS_RESTART:
		if(info.m_isRestart)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	case PROCESS_SET_PACKET_TYPE_IS_IMPERSONATE:
		if(info.m_isImpersonate)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	case PROCESS_SET_PACKET_TYPE_IS_USER_INTERFACE:
		if(info.m_isUserInterface)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	case PROCESS_SET_PACKET_TYPE_ALL:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_commandLine.c_str()),(info.m_commandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_preProcessCommandLine.c_str()),(info.m_preProcessCommandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_postProcessCommandLine.c_str()),(info.m_postProcessCommandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_customProcessCommandLine.c_str()),(info.m_customProcessCommandLine.size()+1)*sizeof(TCHAR));
		m_stream.WriteInt(info.m_preProcessWaitTime);
		m_stream.WriteInt(info.m_postProcessWaitTime);
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_domainName.c_str()),(info.m_domainName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userName.c_str()),(info.m_userName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userPassword.c_str()),(info.m_userPassword.size()+1)*sizeof(TCHAR));
		m_stream.WriteUInt(info.m_delayStartTime);
		m_stream.WriteUInt(info.m_delayPauseEndTime);
		if(info.m_isRestart)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		if(info.m_isImpersonate)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		if(info.m_isUserInterface)
			m_stream.WriteUInt(1);
		else
			m_stream.WriteUInt(0);
		break;
	}
}
void WinServicePacketGenerator::AddCommandService(ServiceCommandPacketType type, const TCHAR *serviceName, ServiceInfo info)
{
	LockObj lock(m_lock);
	EpTString serviceNameString=serviceName;
	if(serviceNameString.size()<=0)
		serviceNameString=_T("");
	m_count++;
	m_stream.WriteUInt((unsigned int)PACKET_TYPE_SERVICE_COMMAND);
	m_stream.WriteUInt((unsigned int)type);
	m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(serviceNameString.c_str()),(serviceNameString.size()+1)*sizeof(TCHAR));

	switch(type)
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
		m_stream.WriteUInt((unsigned int)info.m_code);
		break;
	case SERVICE_COMMAND_PACKET_TYPE_INSTALL:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_displayName.c_str()),(info.m_displayName.size()+1)*sizeof(TCHAR));
		m_stream.WriteUInt((unsigned int)info.m_desiredAccess);
		m_stream.WriteUInt((unsigned int)info.m_serviceType);
		m_stream.WriteUInt((unsigned int)info.m_serviceStartType);
		m_stream.WriteUInt((unsigned int)info.m_serviceErrorControl);
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_binaryPathName.c_str()),(info.m_binaryPathName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_loadOrderGroup.c_str()),(info.m_loadOrderGroup.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_dependencies.c_str()),(info.m_dependencies.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_domainName.c_str()),(info.m_domainName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userName.c_str()),(info.m_userName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userPassword.c_str()),(info.m_userPassword.size()+1)*sizeof(TCHAR));
		break;
	case SERVICE_COMMAND_PACKET_TYPE_UNINSTALL:
		break;
	case SERVICE_COMMAND_PACKET_TYPE_EDIT:
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_displayName.c_str()),(info.m_displayName.size()+1)*sizeof(TCHAR));
		m_stream.WriteUInt((unsigned int)info.m_desiredAccess);
		m_stream.WriteUInt((unsigned int)info.m_serviceType);
		m_stream.WriteUInt((unsigned int)info.m_serviceStartType);
		m_stream.WriteUInt((unsigned int)info.m_serviceErrorControl);
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_binaryPathName.c_str()),(info.m_binaryPathName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_loadOrderGroup.c_str()),(info.m_loadOrderGroup.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_dependencies.c_str()),(info.m_dependencies.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_domainName.c_str()),(info.m_domainName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userName.c_str()),(info.m_userName.size()+1)*sizeof(TCHAR));
		m_stream.WriteBytes(reinterpret_cast<const unsigned char*>(info.m_userPassword.c_str()),(info.m_userPassword.size()+1)*sizeof(TCHAR));
		m_stream.WriteUInt(info.m_editControlBits);
		break;
	case SERVICE_COMMAND_PACKET_TYPE_GET_STATUS:
		break;

	}

}

const unsigned char * WinServicePacketGenerator::GetStream() const
{
	LockObj lock(m_lock);
	return m_stream.GetBuffer();
}
int WinServicePacketGenerator::GetStreamByteSize() const
{
	LockObj lock(m_lock);
	return m_stream.GetStreamSize();
}
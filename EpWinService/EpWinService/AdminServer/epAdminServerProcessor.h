#ifndef __EP_ADMIN_SERVER_PROCESSOR_H__
#define __EP_ADMIN_SERVER_PROCESSOR_H__

#include "epse.h"
#include "epAdminServerPacketParser.h"
#include "epAdminServerPacketInfo.h"
#include "epStream.h"
using namespace epl;
using namespace epse;

#define ADMIN_SERVER_PROCESS_INSTANCE epl::SingletonHolder<AdminServerProcessor>::Instance()

class AdminServerProcessor
{
public:
	friend class SingletonHolder<AdminServerProcessor>;
	void Process(AdminServerPacketParser *curClient,const Packet *packet);
	void CommandProcess(Stream &stream,Stream &retOutStream,unsigned int subPacketType);
	void GetServiceInfo(Stream &stream,Stream &retOutStream,unsigned int subPacketType);
	void SetServiceInfo(Stream &stream,Stream &retOutStream,unsigned int subPacketType);	
	void GetProcessInfo(Stream &stream,Stream &retOutStream,unsigned int subPacketType);
	void SetProcessInfo(Stream &stream,Stream &retOutStream,unsigned int subPacketType);

private:
	AdminServerProcessor()
	{

	}
	~AdminServerProcessor()
	{

	}
	CriticalSectionEx m_commandLock;
};



#endif //__EP_ADMIN_SERVER_PROCESSOR_H__
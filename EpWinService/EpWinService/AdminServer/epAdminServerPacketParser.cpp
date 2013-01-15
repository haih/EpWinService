#include "stdafx.h"
#include "epAdminServerPacketParser.h"
#include "epAdminServerPacketInfo.h"
#include "epAdminServerProcessor.h"

AdminServerPacketParser::AdminServerPacketParser(unsigned int waitTimeMilliSec):BasePacketParser(waitTimeMilliSec)
{

}

AdminServerPacketParser::AdminServerPacketParser(const AdminServerPacketParser& b):BasePacketParser(b)
{

}

AdminServerPacketParser::~AdminServerPacketParser()
{

}

void AdminServerPacketParser::ParsePacket(const Packet &packet )
{
	//TODO: Parse Packet
	ADMIN_SERVER_PROCESS_INSTANCE.Process(this,&packet);
}
#ifndef __EP_ADMIN_SERVER_PACKET_PARSER_H__
#define __EP_ADMIN_SERVER_PACKET_PARSER_H__
#include "epse.h"

using namespace epl;
using namespace epse;
class AdminServerPacketParser:public BasePacketParser
{
public:
	AdminServerPacketParser(unsigned int waitTimeMilliSec=DEFAULT_WAITTIME);

	AdminServerPacketParser(const AdminServerPacketParser& b);

	virtual ~AdminServerPacketParser();

	AdminServerPacketParser & operator=(const AdminServerPacketParser&b)
	{
		if(this!=&b)
		{
			BasePacketParser::operator =(b);
		}
		return *this;
	}

	virtual void ParsePacket(const Packet &packet );
};

#endif// __EP_ADMIN_SERVER_PACKET_PARSER_H__
#include "stdafx.h"
#include "epAdminServerWorker.h"
#include "epAdminServerPacketParser.h"
using namespace epl;
using namespace std;

AdminServerWorker::AdminServerWorker():BaseServerWorker()
{

}


AdminServerWorker::AdminServerWorker(const AdminServerWorker& b):BaseServerWorker(b)
{

}

AdminServerWorker::~AdminServerWorker()
{

}


BasePacketParser* AdminServerWorker::createNewPacketParser()
{
	return EP_NEW AdminServerPacketParser();
}
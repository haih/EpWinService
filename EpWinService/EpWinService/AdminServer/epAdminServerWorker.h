#ifndef __EP_ADMIN_SERVER_WORKER_H__
#define __EP_ADMIN_SERVER_WORKER_H__

#include "epse.h"

using namespace epl;
using namespace epse;

class AdminServerWorker:public BaseServerWorker
{
public:
	AdminServerWorker();


	AdminServerWorker(const AdminServerWorker& b);

	virtual ~AdminServerWorker();

	AdminServerWorker & operator=(const AdminServerWorker&b)
	{
		if(this!=&b)
		{
			BaseServerWorker::operator =(b);
		}
		return *this;
	}
protected:
	virtual BasePacketParser* createNewPacketParser();
};

#endif __EP_ADMIN_SERVER_WORKER_H__
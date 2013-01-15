#ifndef __EP_ADMIN_SERVER_H__
#define __EP_ADMIN_SERVER_H__

#include "epse.h"
#include "epAdminServerWorker.h"


using namespace epl;
using namespace epse;

class AdminServer : public BaseServer
{
public:

	AdminServer(const TCHAR * port=_T("8988"));

	AdminServer(const AdminServer& b);

	virtual ~AdminServer();

	AdminServer & operator=(const AdminServer&b)
	{
		if(this!=&b)
		{
			BaseServer::operator =(b);
		}
		return *this;
	}

protected:
	virtual BaseServerWorker* createNewWorker();

};

#endif //__EP_ADMIN_SERVER_H__
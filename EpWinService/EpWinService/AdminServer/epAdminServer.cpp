#include "stdafx.h"
#include "epAdminServer.h"

AdminServer::AdminServer(const TCHAR * port) :BaseServer(port)
{

}

AdminServer::AdminServer(const AdminServer& b):BaseServer(b)
{

}

AdminServer::~AdminServer()
{

}


BaseServerWorker* AdminServer::createNewWorker()
{
	return new AdminServerWorker();
}
/*! 
AdminServer for the EpWinService
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
#include "epAdminServer.h"

AdminServer::AdminServer(const TCHAR * port) :BaseServer(port,SYNC_POLICY_SYNCHRONOUS)
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
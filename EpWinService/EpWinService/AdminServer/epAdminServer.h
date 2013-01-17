/*! 
@file epAdminServer.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/eplibrary>
@date January 16, 2013
@brief Admin Server Class Interface
@version 2.0

@section LICENSE

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

@section DESCRIPTION

An Interface for the Admin Server.

*/
#ifndef __EP_ADMIN_SERVER_H__
#define __EP_ADMIN_SERVER_H__

#include "epse.h"
#include "epAdminServerWorker.h"
#include "epAdminServerPacketInfo.h"

using namespace epl;
using namespace epse;

/*! 
@class AdminServer epAdminServer.h
@brief This is a class for Admin Server Class
*/
class AdminServer : public BaseServer
{
public:
	/*!
	Default Constructor

	Initializes the Server
	@param[in] port the port string
	*/
	AdminServer(const TCHAR * port=DEFAULT_ADMIN_SERVER_PORT);

	/*!
	Default Copy Constructor

	Initializes the AdminServer
	@param[in] b the second object
	*/
	AdminServer(const AdminServer& b);

	/*!
	Default Destructor

	Destroy the Server
	*/
	virtual ~AdminServer();

	/*!
	Assignment operator overloading
	@param[in] b the second object
	@return the new copied object
	*/
	AdminServer & operator=(const AdminServer&b)
	{
		if(this!=&b)
		{
			BaseServer::operator =(b);
		}
		return *this;
	}

protected:
	/*!
	Return the new server worker.
	@return the new server worker
	*/
	virtual BaseServerWorker* createNewWorker();

};

#endif //__EP_ADMIN_SERVER_H__
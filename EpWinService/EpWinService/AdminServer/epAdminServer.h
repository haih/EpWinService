/*! 
@file epAdminServer.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Class Interface
@version 2.0

@section LICENSE

The MIT License (MIT)

Copyright (c) 2013 Woong Gyu La <juhgiyo@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

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
@brief A class for Admin Server Class
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
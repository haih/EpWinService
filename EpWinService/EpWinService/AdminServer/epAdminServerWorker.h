/*! 
@file epAdminServerWorker.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Worker Interface
@version 1.0

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

An Interface for Base Server Worker.

*/
#ifndef __EP_ADMIN_SERVER_WORKER_H__
#define __EP_ADMIN_SERVER_WORKER_H__

#include "epse.h"

using namespace epl;
using namespace epse;

/*! 
@class AdminServerWorker epAdminServerWorker.h
@brief A class for Admin Server Worker.
*/
class AdminServerWorker:public BaseServerWorker
{
public:
	/*!
	Default Constructor

	Initializes the Worker
	*/
	AdminServerWorker();

	/*!
	Default Copy Constructor

	Initializes the BaseServerWorker
	@param[in] b the second object
	*/
	AdminServerWorker(const AdminServerWorker& b);

	/*!
	Default Destructor

	Destroy the Worker
	*/
	virtual ~AdminServerWorker();

	/*!
	Assignment operator overloading
	@param[in] b the second object
	@return the new copied object
	*/
	AdminServerWorker & operator=(const AdminServerWorker&b)
	{
		if(this!=&b)
		{
			BaseServerWorker::operator =(b);
		}
		return *this;
	}
protected:
	/*!
	Return the new packet parser
	@return the new packet parser
	*/
	virtual BasePacketParser* createNewPacketParser();
};

#endif __EP_ADMIN_SERVER_WORKER_H__
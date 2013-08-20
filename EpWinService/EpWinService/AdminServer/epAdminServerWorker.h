/*! 
@file epAdminServerWorker.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Worker Interface
@version 1.0

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
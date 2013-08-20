/*! 
@file epWinServiceClient.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/eplibrary>
@date January 16, 2013
@brief WinService Client Class Interface
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

An Interface for the WinService Client.

*/
#ifndef __EP_WINSERVICE_CLIENT_H__
#define __EP_WINSERVICE_CLIENT_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceClientPacketInfo.h"
namespace epws
{

	/*! 
	@class WinServiceClient epWinServiceClient.h
	@brief This is a class for WinService Client Class

	*/
	class EP_WINSERVICE_API WinServiceClient : public epse::BaseClientManual
	{
	private:
		friend class WinServiceCommunicator;
		/*!
		Default Constructor

		Initializes the Client
		@param[in] hostName the hostname string
		@param[in] port the port string
		*/
		WinServiceClient(const TCHAR * hostName=_T(DEFAULT_HOSTNAME), const TCHAR * port=DEFAULT_WINSERVICE_PORT);

		/*!
		Default Copy Constructor

		Initializes the WinServiceClient
		@param[in] b the second object
		*/
		WinServiceClient(const WinServiceClient& b);

		/*!
		Default Destructor

		Destroy the Client
		*/
		virtual ~WinServiceClient();

		/*!
		Assignment operator overloading
		@param[in] b the second object
		@return the new copied object
		*/
		WinServiceClient & operator=(const WinServiceClient&b)
		{
			if(this!=&b)
			{
				BaseClientManual::operator =(b);
			}
			return *this;
		}
	};
}


#endif //__EP_WINSERVICE_CLIENT_H__
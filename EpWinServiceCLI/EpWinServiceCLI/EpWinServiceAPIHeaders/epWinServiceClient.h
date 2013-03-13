/*! 
@file epWinServiceClient.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/eplibrary>
@date January 16, 2013
@brief WinService Client Class Interface
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
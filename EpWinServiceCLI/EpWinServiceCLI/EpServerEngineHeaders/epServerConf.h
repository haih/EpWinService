/*! 
@file epServerConf.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date July 19, 2012
@brief Server Configuration Defines
@version 1.0

@section LICENSE

Copyright (C) 2012  Woong Gyu La <juhgiyo@gmail.com>

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

An Interface for Server Configuration Defines.

*/
#ifndef __EP_SERVER_CONF_H__
#define __EP_SERVER_CONF_H__

#include "epServerEngine.h"
namespace epse{

	/*!
	@def DEFAULT_HOSTNAME
	@brief default hostname

	Macro for the default hostname.
	*/
	#define DEFAULT_HOSTNAME "localhost"

	/*!
	@def DEFAULT_PORT
	@brief default port

	Macro for the default port.
	*/
	#define DEFAULT_PORT "80808"


	/// Synchronous Policy
	typedef enum _syncPolicy{
		/// Asynchronoous
		SYNC_POLICY_ASYNCHRONOUS=0,
		/// Synchronous as a whole
		SYNC_POLICY_SYNCHRONOUS,
		/// Synchronous by each client (Same as Synchronous if used in BaseClient)
		SYNC_POLICY_SYNCHRONOUS_BY_CLIENT,
		
	}SyncPolicy;

	/*!
	@def CONNECTION_LIMIT_INFINITE
	@brief No limit for the connection count

	Macro for No limit for the connection count.
	*/
	#define CONNECTION_LIMIT_INFINITE 0

	/*!
	@def PARSER_LIMIT_INFINITE
	@brief No limit for the parser count

	Macro for No limit for the parser count.
	*/
	#define PARSER_LIMIT_INFINITE 0
	
}
#endif //__EP_SERVER_CONF_H__
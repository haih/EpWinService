/*! 
@file epWinServiceAPILibrary.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief EpWinService API Library Interface
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

An Interface for EpWinService API Library.
*/

#ifndef __EP_WINSERVICE_API_LIBRARY_H__
#define __EP_WINSERVICE_API_LIBRARY_H__

#ifdef EP_WINSERVICE_API_DLL_EXPORT

#define EP_WINSERVICE_API __declspec(dllexport)
#ifndef EP_SERVER_ENGINE_DLL_IMPORT
#define EP_SERVER_ENGINE_DLL_IMPORT
#endif //EP_SERVER_ENGINE_DLL_IMPORT
#ifndef EP_LIBRARY_DLL_IMPORT
#define EP_LIBRARY_DLL_IMPORT
#endif //EP_LIBRARY_DLL_IMPORT

#else   //EP_WINSERVICE_API_DLL_EXPORT

#ifdef EP_WINSERVICE_API_DLL_IMPORT

#define EP_WINSERVICE_API __declspec(dllimport)
#ifndef EP_SERVER_ENGINE_DLL_IMPORT
#define EP_SERVER_ENGINE_DLL_IMPORT
#endif //EP_SERVER_ENGINE_DLL_IMPORT
#ifndef EP_LIBRARY_DLL_IMPORT
#define EP_LIBRARY_DLL_IMPORT
#endif //EP_LIBRARY_DLL_IMPORT

#else   //EP_WINSERVICE_API_DLL_IMPORT

#define EP_WINSERVICE_API

#endif  //EP_WINSERVICE_API_DLL_IMPORT
#endif  //EP_WINSERVICE_API_DLL_EXPORT

#include "epl.h"
using namespace epl;
#include "epse.h"
using namespace epse;

#endif //__EP_WINSERVICE_API_LIBRARY_H__
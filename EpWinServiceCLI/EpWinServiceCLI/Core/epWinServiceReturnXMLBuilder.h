/*! 
@file epWinServiceReturnXMLBuilder.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief WinService Return XML Builder Interface
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

An Interface for WinService Return XML Builder.

*/
#ifndef __EP_WINSERVICE_RETURN_XML_BUILDER_H__
#define __EP_WINSERVICE_RETURN_XML_BUILDER_H__

#include "epws.h"

using namespace epws;

/*! 
@class WinServiceReturnXMLBuilder epWinServiceReturnXMLBuilder.h
@brief A class for WinService Return XML Builder.
*/
class WinServiceReturnXMLBuilder
{
public:
	/*!
	Build Result XML with given result
	@param[in] result the result information to build Return XML
	@param[out] retXMLFile the Return XML built
	@return true if successfully built otherwise false
	*/
	static bool BuildResultXML(const WinServiceResult & result,XMLFile &retXMLFile);

private:
	/*!
	Add return value of ResultInfo to the given root node
	@param[in] resultInfo the information to retrieve the value
	@param[in] root the root XML node to add the value as a child
	*/
	static void addReturnValue(const WinServiceResultInfo & resultInfo,XNode *root);

	/*!
	Add ProcessObjInfo value to the given root node
	@param[in] resultInfo the information to retrieve the value
	@param[in] root the root XML node to add the value as a child
	*/
	static void addProcessObjInfo(const WinServiceResultInfo & resultInfo,XNode *root);

	/*!
	Add ServiceObjInfo value to the given root node
	@param[in] resultInfo the information to retrieve the value
	@param[in] root the root XML node to add the value as a child
	*/
	static void addServiceObjInfo(const WinServiceResultInfo & resultInfo,XNode *root);

	/*!
	Add SERVICE_STATUS value to the given root node
	@param[in] resultInfo the information to retrieve the value
	@param[in] root the root XML node to add the value as a child
	*/
	static void addServiceStatus(const WinServiceResultInfo & resultInfo,XNode *root);

	/*!
	Add SERVICE_STATUS_PROCESS value to the given root node
	@param[in] resultInfo the information to retrieve the value
	@param[in] root the root XML node to add the value as a child
	*/
	static void addServiceStatusProcess(const WinServiceResultInfo & resultInfo,XNode *root);

	/*!
	Add ServiceHandleError value to the given root node
	@param[in] resultInfo the information to retrieve the value
	@param[in] root the root XML node to add the value as a child
	*/
	static void addServiceHandleErrorInfo(const WinServiceResultInfo & resultInfo,XNode *root);
};
#endif //__EP_WINSERVICE_RETURN_XML_BUILDER_H__
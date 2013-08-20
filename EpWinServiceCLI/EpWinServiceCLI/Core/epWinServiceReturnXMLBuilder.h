/*! 
@file epWinServiceReturnXMLBuilder.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief WinService Return XML Builder Interface
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
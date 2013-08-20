/*! 
@file epWinServiceXMLParser.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief WinService XML Parser Interface
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

An Interface for WinService XML Parser.

*/
#ifndef __EP_WINSERVICE_XML_PARSER_H__
#define __EP_WINSERVICE_XML_PARSER_H__

#include "epws.h"

using namespace epws;

/// WinService XML Parser Error Enumeration
typedef enum _winServiceXMLParserError{
	/// Success
	WINSERVICE_XML_PARSER_ERROR_SUCCESS=0,
	/// Parse Failed
	WINSERVICE_XML_PARSER_ERROR_PARSE_FAIL,
	/// Invalid Command
	WINSERVICE_XML_PARSER_ERROR_INVALID_COMMAND,
	/// Invalid Sub-command
	WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND,
	/// Invalid arguments
	WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT,

}WinServiceXMLParserError;

/*! 
@class WinServiceXMLParser epWinServiceXMLParser.h
@brief A class for WinService XML Parser.
*/
class WinServiceXMLParser
{
public:
	/*!
	Process the parse of given XML and return the result
	@param[in] root the XML to parse
	@param[out] retResult the result to return
	@return true if successfully processed otherwise false
	*/
	static bool ProcessParse(XNode * root, WinServiceResult &retResult);

private:
	/*!
	parse the given XML and add packet to given packet generator
	@param[in] root the XML to parse
	@param[out] retPacketGen the packet generator created
	@return true if successfully parsed otherwise false
	*/
	static bool parse(XNode *root,WinServicePacketGenerator &retPacketGen );

	/*!
	Process the command and add packet to given packet generator
	@param[in] root the XML to parse
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processCommand(XNode * root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ServiceCommand's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processServiceCommand(ServiceCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ServiceObjectInfoSet's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processServiceObjectInfoSet(ServiceObjectInfoSetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ServiceObjectInfoGet's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processServiceObjectInfoGet(ServiceObjectInfoGetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ServiceObjectCommand's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processServiceObjectCommand(ServiceObjectCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ProcessObjectInfoSet's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processProcessObjectInfoSet(ProcessObjectInfoSetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ProcessObjectInfoGet's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processProcessObjectInfoGet(ProcessObjectInfoGetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the ProcessObjectCommand's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processProcessObjectCommand(ProcessObjectCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the MainServiceInfoSet's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processMainServiceInfoSet(MainServiceInfoSetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the MainServiceInfoGet's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processMainServiceInfoGet(MainServiceInfoGetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);

	/*!
	Process the MainServiceCommand's sub-command and add packet to given packet generator
	@param[in] subCommandType the sub-command to process the command
	@param[in] root the root XML node to get relevant argument
	@param[out] retPacketGen the packet generator to add packet
	@return WinServiceXMLParserError
	*/
	static WinServiceXMLParserError processMainServiceCommand(MainServiceCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen);


};
#endif //__EP_WINSERVICE_XML_PARSER_H__
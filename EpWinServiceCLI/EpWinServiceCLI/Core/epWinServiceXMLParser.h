/*! 
@file epWinServiceXMLParser.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief WinService XML Parser Interface
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
/*! 
@file epWinServiceTypeInterpreter.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief WinService Type Interpreter Interface
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

An Interface for WinService Type Interpreter.

*/
#ifndef __EP_WINSERVICE_TYPE_INTERPRETER_H__
#define __EP_WINSERVICE_TYPE_INTERPRETER_H__

#include "epws.h"

using namespace epws;

/*! 
@class WinServiceTypeInterpreter epWinServiceTypeInterpreter.h
@brief A class for WinService Type Interpreter.
*/
class WinServiceTypeInterpreter
{
public:
	/*!
	Interpret given MainServiceCommmand's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static MainServiceCommandPacketType GetMainServiceCommandPacketType(CString subCommand);
	/*!
	Interpret given MainServiceInfoGet's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static MainServiceInfoGetPacketType GetMainServiceInfoGetPacketType(CString subCommand);
	/*!
	Interpret given MainServiceInfoSet's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static MainServiceInfoSetPacketType GetMainServiceInfoSetPacketType(CString subCommand);
	/*!
	Interpret given ProcessObjectCommand's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ProcessObjectCommandPacketType GetProcessObjectCommandPacketType(CString subCommand);
	/*!
	Interpret given ProcessObjectInfoGet's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ProcessObjectInfoGetPacketType GetProcessObjectInfoGetPacketType(CString subCommand);
	/*!
	Interpret given ProcessObjectInfoSet's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ProcessObjectInfoSetPacketType GetProcessObjectInfoSetPacketType(CString subCommand);
	/*!
	Interpret given ServiceObjectCommand's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ServiceObjectCommandPacketType GetServiceObjectCommandPacketType(CString subCommand);
	/*!
	Interpret given ServiceObjectInfoGet's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ServiceObjectInfoGetPacketType GetServiceObjectInfoGetPacketType(CString subCommand);
	/*!
	Interpret given ServiceObjectInfoSet's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ServiceObjectInfoSetPacketType GetServiceObjectInfoSetPacketType(CString subCommand);
	/*!
	Interpret given ServiceCommand's sub-command string to relevant type
	@param[in] subCommand the sub-command string to interpret to relevant type
	@return the type interpreted
	*/
	static ServiceCommandPacketType GetServiceCommandPacketType(CString subCommand);


	
	/*!
	Interpret given PacketProcessStatus type to relevant string
	@param[in] status the status to interpret
	@return the string interpreted
	*/
	static CString GetPacketProcessStatusString(PacketProcessStatus status);

	/*!
	Interpret given Command type to relevant string
	@param[in] type the type to interpret
	@return the string interpreted
	*/
	static CString GetCommandTypeString(PacketType type);

	/*!
	Interpret given Sub-command type to relevant string
	@param[in] type the command type to branch right sub-command
	@param[in] subcommand the sub-command type to interpret
	@return the string interpreted
	*/
	static CString GetSubcommandTypeString(PacketType type, unsigned int subcommand);

	/*!
	Interpret given RetrieveStatus type to relevant string
	@param[in] status the status to interpret
	@return the string interpreted
	*/
	static CString GetRetrieveStatusString(RetrieveStatus status);

	/*!
	Interpret given ReturnType type to relevant string
	@param[in] type the type to interpret
	@return the string interpreted
	*/
	static CString GetReturnTypeString(ReturnType type);

private:
	/*!
	Interpret given MainServiceCommand's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getMainServiceCommandTypeString(unsigned int subcommand);

	/*!
	Interpret given MainServiceInfoGet's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getMainServiceInfoGetTypeString(unsigned int subcommand);
	/*!
	Interpret given MainServiceInfoset's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getMainServiceInfoSetTypeString(unsigned int subcommand);
	/*!
	Interpret given ProcessObjectCommand's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getProcessObjectCommandTypeString(unsigned int subcommand);
	/*!
	Interpret given ProcessObjectInfoGet's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getProcessObjectInfoGetTypeString(unsigned int subcommand);
	/*!
	Interpret given ProcessObjectInfoSet's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getProcessObjectInfoSetTypeString(unsigned int subcommand);
	/*!
	Interpret given ServiceObjectCommand's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getServiceObjectCommandTypeString(unsigned int subcommand);
	/*!
	Interpret given ServiceObjectInfoGet's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getServiceObjectInfoGetTypeString(unsigned int subcommand);
	/*!
	Interpret given ServiceObjectInfoSet's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getServiceObjectInfoSetTypeString(unsigned int subcommand);
	/*!
	Interpret given ServiceCommand's sub-command type to relevant string
	@param[in] subcommand the sub-command to interpret
	@return the string interpreted
	*/
	static CString getServiceCommandTypeString(unsigned int subcommand);
	
	
};
#endif //__EP_WINSERVICE_TYPE_INTERPRETER_H__
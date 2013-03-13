/*! 
@file epWinServiceTypeInterpreter.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief WinService Type Interpreter Interface
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
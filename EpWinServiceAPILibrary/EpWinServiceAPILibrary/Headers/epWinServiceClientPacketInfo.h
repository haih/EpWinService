/*! 
@file epWinServiceClientPacketInfo.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Client Packet Information Interface
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

An Interface for WinService Client Packet Information.

*/
#ifndef __EP_WINSERVICE_CLIENT_PACKET_INFO_H__
#define __EP_WINSERVICE_CLIENT_PACKET_INFO_H__

#include "epWinServiceAPILibrary.h"

namespace epws
{

	/*!
	@def DEFAULT_WINSERVICE_PORT
	@brief Default WinService Port

	Macro for the Default WinService Port.
	*/
	#define DEFAULT_WINSERVICE_PORT _T("8988")

	/// Packet Type
	typedef enum _packetType{
		/// NULL Command Type
		PACKET_TYPE_NULL=0,
		/// Set Main Service Command
		PACKET_TYPE_MAIN_SERVICE_COMMAND,
		/// Get Main Service Info Type
		PACKET_TYPE_MAIN_SERVICE_INFO_GET,
		/// Set Main Service Info Type
		PACKET_TYPE_MAIN_SERVICE_INFO_SET,	
		/// Command Process Object Type
		PACKET_TYPE_PROCESS_OBJECT_COMMAND,
		/// Get Process Info type
		PACKET_TYPE_PROCESS_OBJECT_INFO_GET,
		/// Set Process Info Type
		PACKET_TYPE_PROCESS_OBJECT_INFO_SET,
		/// Command Service Object Type
		PACKET_TYPE_SERVICE_OBJECT_COMMAND,
		/// Get Service Info type
		PACKET_TYPE_SERVICE_OBJECT_INFO_GET,
		/// Set Service Info Type
		PACKET_TYPE_SERVICE_OBJECT_INFO_SET,
		/// Service Command type
		PACKET_TYPE_SERVICE_COMMAND,
		
	}PacketType;

	/// Sub-type for Command Process Object Packet
	typedef enum _processObjectCommandPacketType{
		/// Start the Process
		PROCESS_OBJECT_COMMAND_PACKET_TYPE_START=0,
		/// End the Process
		PROCESS_OBJECT_COMMAND_PACKET_TYPE_END,
		/// Restart the Process
		PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE,
		/// Start the Custom Process
		PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS,
		/// Run Command for Process
		PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND,
	}ProcessObjectCommandPacketType;

	/// Sub-type for Command Service Object Packet
	typedef enum _serviceObjectCommandPacketType{
		/// Start the Service
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_START,
		/// End the Service
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_END,
		/// Pause the Service
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_PAUSE,
		/// Continue the Service
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_CONTINUE,
		/// Restart the Service
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE,
		/// Start the Service's Custom Process
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS,
		/// Run Command for Service
		SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND

	}ServiceObjectCommandPacketType;

	typedef enum _mainServiceCommandPacketType{
		/// Start the Main Service's Custom Process
		MAIN_SERVICE_COMMAND_PACKET_TYPE_CUSTOM_PROCESS=0,
		/// Run Command for Main Service
		MAIN_SERVICE_COMMAND_PACKET_TYPE_RUN_COMMAND
	}MainServiceCommandPackeType;

	/// Sub-type for Get Service Info Packet
	typedef enum _mainServiceInfoGetPacketType{
		/// Get Service Name
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_SERVICE_NAME=0,
		/// Get Domain Name
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_DOMAIN_NAME,
		/// Get User Name
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERNAME,
		/// Get User Password
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERPASSWORD,
		/// Get Dependencies
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_DEPENDENCY,
		/// Get Number of Processes
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_PROCESSES,
		/// Get Number of Services
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_SERVICES,
		/// Get Interval time for checking processes
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKPROCESSINTERVAL,
		/// Get Interval time for checking services
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKSERVICEINTERVAL,
		/// Get Main Service's Custom Process CommandLine
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
		/// Get all information above
		MAIN_SERVICE_INFO_GET_PACKET_TYPE_ALL,
	}MainServiceInfoGetPacketType;

	/// Sub-type for Set Service Info Packet
	typedef enum _mainServiceInfoSetPacketType{
		/// Set Interval time for checking processes
		MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL=0,
		/// Set Interval time for checking services
		MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL,
		/// Set Main Service's Custom Process CommandLine
		MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,

	}MainServiceInfoSetPacketType;

	/// Sub-type for Get Process Info Packet
	typedef enum _processObjectInfoGetPacketType{
		/// Get Process's CommandLine
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_COMMANDLINE=0,
		/// Get Process's Pre-process CommandLine
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
		/// Get Process's Post-process CommandLine
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
		/// Get Process's Custom Process CommandLine
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
		/// Get Process's PreProcess Wait Time
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
		/// Get Process's PostProcess Wait Time
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
		/// Get Process's Domain Name
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME,
		/// Get Process's Username
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERNAME,
		/// Get Process's User Password
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD,

		/// Get Process's delay start time
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME,
		/// Get Process's delay pause/end time
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME,
		/// Get Process's restart flag when fault.
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_PROCESS_RESTART,
		/// Get Process's impersonation flag
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE,
		/// Get Process's user-interface flag
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE,

		/// Get current Process's status
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_STATUS,

		/// Get all information above
		PROCESS_OBJECT_INFO_GET_PACKET_TYPE_ALL,
	}ProcessObjectInfoGetPacketType;


	/// Sub-type for Set Process Info Packet
	typedef enum _processObjectInfoSetPacketType{
		/// Set Process's CommandLine
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_COMMANDLINE=0,
		/// Set Process's Pre-process CommandLine
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
		/// Set Process's Post-process CommandLine
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
		/// Set Process's Custom Process CommandLine
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
		/// Set Process's PreProcess Wait Time
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
		/// Set Process's PostProcess Wait  Time
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
		/// Set Process's Domain Name
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME,
		/// Set Process's Username
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERNAME,
		/// Set Process's User Password
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD,

		/// Set Process's delay start time
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME,
		/// Set Process's delay pause/end time
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME,
		/// Set Process's restart flag when fault
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_PROCESS_RESTART,
		/// Set Process's impersonate flag
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE,
		/// Set Process's user-interface flag
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE,

		/// Set all information above
		PROCESS_OBJECT_INFO_SET_PACKET_TYPE_ALL

	}ProcessObjectInfoSetPacketType;



	/// Sub-type for Get Service Info Packet
	typedef enum _serviceObjectInfoGetPacketType{
		/// Get Service's Service Name
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_SERVICENAME=0,
		/// Get Service's Pre-process CommandLine
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
		/// Get Service's Post-process CommandLine
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
		/// Get Service's Custom Process CommandLine
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
		/// Get Service's PreProcess Wait Time
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
		/// Get Service's PostProcess Wait Time
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
		/// Get Service's Domain Name
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME,
		/// Get Service's Username
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERNAME,
		/// Get Service's User Password
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD,

		/// Get Service's delay start time
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME,
		/// Get Service's delay pause/end time
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME,

		/// Get Service's restart flag when fault.
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_SERVICE_RESTART,
		/// Get Service's impersonation flag
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE,
		/// Get Service's user-interface flag
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE,

		/// Get current Service's status
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_STATUS,

		/// Get all information above
		SERVICE_OBJECT_INFO_GET_PACKET_TYPE_ALL,
	}ServiceObjectInfoGetPacketType;


	/// Sub-type for Set Service Info Packet
	typedef enum _serviceObjectInfoSetPacketType{
		/// Set Service's Service Name
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_SERVICENAME=0,
		/// Set Service's Pre-process CommandLine
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
		/// Set Service's Post-process CommandLine
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
		/// Set Service's Custom Process CommandLine
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
		/// Set Service's PreProcess Wait Time
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
		/// Set Service's PostProcess Wait Time
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
		/// Set Service's Domain Name
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME,
		/// Set Service's Username
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERNAME,
		/// Set Service's User Password
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD,

		/// Set Service's delay start time
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME,
		/// Set Service's delay pause/end time
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME,

		/// Set Service's restart flag when fault
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_SERVICE_RESTART,
		/// Set Service's impersonate flag
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE,
		/// Set Service's user-interface flag
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE,

		/// Set all information above
		SERVICE_OBJECT_INFO_SET_PACKET_TYPE_ALL

	}ServiceObjectInfoSetPacketType;


	/// Sub-type for Service Command Packet
	typedef enum _serviceCommandPacketType{
		/// Service Start Command
		SERVICE_COMMAND_PACKET_TYPE_START=0,
		/// Service Continue Command
		SERVICE_COMMAND_PACKET_TYPE_CONTINUE,
		/// Service Stop Command
		SERVICE_COMMAND_PACKET_TYPE_STOP,
		/// Service Pause Command
		SERVICE_COMMAND_PACKET_TYPE_PAUSE,
		/// Service Control Command
		SERVICE_COMMAND_PACKET_TYPE_CONTROL,
		/// Service Install Command
		SERVICE_COMMAND_PACKET_TYPE_INSTALL,
		/// Service Uninstall Command
		SERVICE_COMMAND_PACKET_TYPE_UNINSTALL,
		/// Service Edit Command
		SERVICE_COMMAND_PACKET_TYPE_EDIT,
		/// Service Get Status command
		SERVICE_COMMAND_PACKET_TYPE_GET_STATUS
	}ServiceCommandPacketType;

	/// Packet Process Result Type
	typedef enum _packetProcessStatus{
		/// Sucess
		PACKET_PROCESS_STATUS_SUCCESS=0,
		/// Failed
		PACKET_PROCESS_STATUS_FAIL,
		/// Process Index is out of range
		PACKET_PROCESS_STATUS_FAIL_PROCESS_IDX_OUT_OF_RANCE,
		/// Packet have argument error
		PACKET_PROCESS_STATUS_FAIL_ARGUMENT_ERROR,
		/// Processing Service Handle error
		PACKET_PROCESS_STATUS_FAIL_SERVICE_HANDLE_ERROR,
	}PacketProcessStatus;

	/// Process's Status Type
	typedef enum _processStatusType{
		/// Unknown
		PROCESS_STATUS_TYPE_UNKNOWN=0,
		/// Running
		PROCESS_STATUS_TYPE_RUNNING,
		/// Stopped
		PROCESS_STATUS_TYPE_STOPPED,
	}ProcessStatusType;

	/*!
	@def OBJECT_IDX_NONE
	@brief Object Index None Declaration

	Macro for the Object Index None.
	*/
	#define OBJECT_IDX_NONE 0xfffffffe
	/*!
	@def OBJECT_IDX_ALL
	@brief Object Index All Declaration

	Macro for the Object Index All.
	*/
	#define OBJECT_IDX_ALL  0xffffffff

	/*!
	@struct ReceivePacket epWinServiceClientPacketInfo.h
	@brief A Class for the Receive Packet.	
	*/
	struct EP_WINSERVICE_API ReceivePacket{
		/// Processing Count
		unsigned int count;
	};

	/*!
	@struct SendPacket epWinServiceClientPacketInfo.h
	@brief A Class for the Send Packet.	
	*/
	struct EP_WINSERVICE_API SendPacket{
		/// Processing Result Count
		unsigned int count;
	};
}
#endif //__EP_WINSERVICE_CLIENT_PACKET_INFO_H__
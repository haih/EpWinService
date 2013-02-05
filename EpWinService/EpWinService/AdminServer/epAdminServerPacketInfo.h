/*! 
@file epAdminServerPacketInfo.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Admin Server Packet Information Interface
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

An Interface for Admin Server Packet Information.

*/
#ifndef __EP_ADMIN_SERVER_PACKET_INFO_H__
#define __EP_ADMIN_SERVER_PACKET_INFO_H__

/*!
@def DEFAULT_ADMIN_SERVER_PORT
@brief Default Admin Server Port

Macro for the Default Admin Server Port.
*/
#define DEFAULT_ADMIN_SERVER_PORT _T("8988")

/// Packet Type
typedef enum _packetType{
	/// NULL Command Type
	PACKET_TYPE_NULL=0,
	/// Set Main Service Command
	PACKET_TYPE_MAIN_SERVICE_COMMAND,
	/// Get Main Service Info Type
	PACKET_TYPE_MAIN_SERVICE_GET,
	/// Set Main Service Info Type
	PACKET_TYPE_MAIN_SERVICE_SET,	
	/// Command Process Object Type
	PACKET_TYPE_COMMAND_PROCESS_OBJECT,
	/// Get Process Info type
	PACKET_TYPE_PROCESS_GET,
	/// Set Process Info Type
	PACKET_TYPE_PROCESS_SET,
	/// Command Service Object Type
	PACKET_TYPE_COMMAND_SERVICE_OBJECT,
	/// Get Service Info type
	PACKET_TYPE_SERVICE_GET,
	/// Set Service Info Type
	PACKET_TYPE_SERVICE_SET,
	/// Service Command type
	PACKET_TYPE_SERVICE_COMMAND,
	
}PacketType;

/// Sub-type for Command Process Object Packet
typedef enum _commandProcessObjectPacketType{
	/// Start the Process
	COMMAND_PROCESS_OBJECT_PACKET_TYPE_START=0,
	/// End the Process
	COMMAND_PROCESS_OBJECT_PACKET_TYPE_END,
	/// Restart the Process
	COMMAND_PROCESS_OBJECT_PACKET_TYPE_BOUNCE,
	/// Start the Custom Process
	COMMAND_PROCESS_OBJECT_PACKET_TYPE_CUSTOM_PROCESS,
	/// Run Command for Process
	COMMAND_PROCESS_OBJECT_PACKET_TYPE_RUN_COMMAND,
}CommandProcessObjectPacketType;

/// Sub-type for Command Service Object Packet
typedef enum _commandServiceObjectPacketType{
	/// Start the Service
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_START,
	/// End the Service
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_END,
	/// Pause the Service
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_PAUSE,
	/// Continue the Service
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_CONTINUE,
	/// Restart the Service
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_BOUNCE,
	/// Start the Service's Custom Process
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_CUSTOM_PROCESS,
	/// Run Command for Service
	COMMAND_SERVICE_OBJECT_PACKET_TYPE_RUN_COMMAND

}CommandServiceObjectPacketType;

typedef enum _commandMainServicePacketType{
	/// Start the Main Service's Custom Process
	COMMAND_MAIN_SERVICE_PACKET_TYPE_CUSTOM_PROCESS=0,
	/// Run Command for Main Service
	COMMAND_MAIN_SERVICE_PACKET_TYPE_RUN_COMMAND
}CommandMainServicePackeType;

/// Sub-type for Get Service Info Packet
typedef enum _mainServiceGetPacketType{
	/// Get Service Name
	MAIN_SERVICE_GET_PACKET_TYPE_SERVICE_NAME=0,
	/// Get Domain Name
	MAIN_SERVICE_GET_PACKET_TYPE_DOMAIN_NAME,
	/// Get User Name
	MAIN_SERVICE_GET_PACKET_TYPE_USERNAME,
	/// Get User Password
	MAIN_SERVICE_GET_PACKET_TYPE_USERPASSWORD,
	/// Get Dependencies
	MAIN_SERVICE_GET_PACKET_TYPE_DEPENDENCY,
	/// Get Number of Processes
	MAIN_SERVICE_GET_PACKET_TYPE_NUM_OF_PROCESSES,
	/// Get Interval time for checking processes
	MAIN_SERVICE_GET_PACKET_TYPE_CHECKPROCESSINTERVAL,
	/// Get Interval time for checking services
	MAIN_SERVICE_GET_PACKET_TYPE_CHECKSERVICEINTERVAL,
	/// Get Main Service's Custom Process CommandLine
	MAIN_SERVICE_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
	/// Get all information above
	MAIN_SERVICE_GET_PACKET_TYPE_ALL,
}MainServiceGetPacketType;

/// Sub-type for Set Service Info Packet
typedef enum _mainServiceSetPacketType{
	/// Set Interval time for checking processes
	MAIN_SERVICE_SET_PACKET_TYPE_CHECKPROCESSINTERVAL=0,
	/// Set Interval time for checking services
	MAIN_SERVICE_SET_PACKET_TYPE_CHECKSERVICESINTERVAL,
	/// Set Main Service's Custom Process CommandLine
	MAIN_SERVICE_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,

}MainServiceSetPacketType;

/// Sub-type for Get Process Info Packet
typedef enum _processGetPacketType{
	/// Get Process's CommandLine
	PROCESS_GET_PACKET_TYPE_COMMANDLINE=0,
	/// Get Process's Pre-process CommandLine
	PROCESS_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
	/// Get Process's Post-process CommandLine
	PROCESS_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
	/// Get Process's Custom Process CommandLine
	PROCESS_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
	/// Get Process's PreProcess Wait Time
	PROCESS_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
	/// Get Process's PostProcess Wait Time
	PROCESS_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
	/// Get Process's Domain Name
	PROCESS_GET_PACKET_TYPE_DOMAINNAME,
	/// Get Process's Username
	PROCESS_GET_PACKET_TYPE_USERNAME,
	/// Get Process's User Password
	PROCESS_GET_PACKET_TYPE_USERPASSWORD,

	/// Get Process's delay start time
	PROCESS_GET_PACKET_TYPE_DELAY_START_TIME,
	/// Get Process's delay pause/end time
	PROCESS_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME,
	/// Get Process's restart flag when fault.
	PROCESS_GET_PACKET_TYPE_IS_PROCESS_RESTART,
	/// Get Process's impersonation flag
	PROCESS_GET_PACKET_TYPE_IS_IMPERSONATE,
	/// Get Process's user-interface flag
	PROCESS_GET_PACKET_TYPE_IS_USER_INTERFACE,

	/// Get current Process's status
	PROCESS_GET_PACKET_TYPE_STATUS,

	/// Get all information above
	PROCESS_GET_PACKET_TYPE_ALL,
}ProcessGetPacketType;


/// Sub-type for Set Process Info Packet
typedef enum _processSetPacketType{
	/// Set Process's CommandLine
	PROCESS_SET_PACKET_TYPE_COMMANDLINE=0,
	/// Set Process's Pre-process CommandLine
	PROCESS_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
	/// Set Process's Post-process CommandLine
	PROCESS_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
	/// Set Process's Custom Process CommandLine
	PROCESS_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
	/// Set Process's PreProcess Wait Time
	PROCESS_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
	/// Set Process's PostProcess Wait  Time
	PROCESS_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
	/// Set Process's Domain Name
	PROCESS_SET_PACKET_TYPE_DOMAINNAME,
	/// Set Process's Username
	PROCESS_SET_PACKET_TYPE_USERNAME,
	/// Set Process's User Password
	PROCESS_SET_PACKET_TYPE_USERPASSWORD,

	/// Set Process's delay start time
	PROCESS_SET_PACKET_TYPE_DELAY_START_TIME,
	/// Set Process's delay pause/end time
	PROCESS_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME,
	/// Set Process's restart flag when fault
	PROCESS_SET_PACKET_TYPE_IS_PROCESS_RESTART,
	/// Set Process's impersonate flag
	PROCESS_SET_PACKET_TYPE_IS_IMPERSONATE,
	/// Set Process's user-interface flag
	PROCESS_SET_PACKET_TYPE_IS_USER_INTERFACE,

	/// Set all information above
	PROCESS_SET_PACKET_TYPE_ALL

}ProcessSetPacketType;



/// Sub-type for Get Service Info Packet
typedef enum _serviceGetPacketType{
	/// Get Service's Service Name
	SERVICE_GET_PACKET_TYPE_SERVICENAME=0,
	/// Get Service's Pre-process CommandLine
	SERVICE_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
	/// Get Service's Post-process CommandLine
	SERVICE_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
	/// Get Service's Custom Process CommandLine
	SERVICE_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
	/// Get Service's PreProcess Wait Time
	SERVICE_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
	/// Get Service's PostProcess Wait Time
	SERVICE_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
	/// Get Service's Domain Name
	SERVICE_GET_PACKET_TYPE_DOMAINNAME,
	/// Get Service's Username
	SERVICE_GET_PACKET_TYPE_USERNAME,
	/// Get Service's User Password
	SERVICE_GET_PACKET_TYPE_USERPASSWORD,

	/// Get Service's delay start time
	SERVICE_GET_PACKET_TYPE_DELAY_START_TIME,
	/// Get Service's delay pause/end time
	SERVICE_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME,

	/// Get Service's restart flag when fault.
	SERVICE_GET_PACKET_TYPE_IS_SERVICE_RESTART,
	/// Get Service's impersonation flag
	SERVICE_GET_PACKET_TYPE_IS_IMPERSONATE,
	/// Get Service's user-interface flag
	SERVICE_GET_PACKET_TYPE_IS_USER_INTERFACE,

	/// Get current Service's status
	SERVICE_GET_PACKET_TYPE_STATUS,

	/// Get all information above
	SERVICE_GET_PACKET_TYPE_ALL,
}ServiceGetPacketType;


/// Sub-type for Set Service Info Packet
typedef enum _serviceSetPacketType{
	/// Set Service's Service Name
	SERVICE_SET_PACKET_TYPE_SERVICENAME=0,
	/// Set Service's Pre-process CommandLine
	SERVICE_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE,
	/// Set Service's Post-process CommandLine
	SERVICE_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE,
	/// Set Service's Custom Process CommandLine
	SERVICE_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE,
	/// Set Service's PreProcess Wait Time
	SERVICE_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME,
	/// Set Service's PostProcess Wait Time
	SERVICE_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME,
	/// Set Service's Domain Name
	SERVICE_SET_PACKET_TYPE_DOMAINNAME,
	/// Set Service's Username
	SERVICE_SET_PACKET_TYPE_USERNAME,
	/// Set Service's User Password
	SERVICE_SET_PACKET_TYPE_USERPASSWORD,

	/// Set Service's delay start time
	SERVICE_SET_PACKET_TYPE_DELAY_START_TIME,
	/// Set Service's delay pause/end time
	SERVICE_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME,

	/// Set Service's restart flag when fault
	SERVICE_SET_PACKET_TYPE_IS_SERVICE_RESTART,
	/// Set Service's impersonate flag
	SERVICE_SET_PACKET_TYPE_IS_IMPERSONATE,
	/// Set Service's user-interface flag
	SERVICE_SET_PACKET_TYPE_IS_USER_INTERFACE,

	/// Set all information above
	SERVICE_SET_PACKET_TYPE_ALL

}ServiceSetPacketType;


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
	/// Running
	PROCESS_STATUS_TYPE_RUNNING=0,
	/// Stopped
	PROCESS_STATUS_TYPE_STOPPED,
}ProcessStatusType;

/*!
@def OBJECT_ID_NONE
@brief Object ID None Declaration

Macro for the Object ID None.
*/
#define OBJECT_ID_NONE 0xfffffffe
/*!
@def OBJECT_ID_ALL
@brief Object ID All Declaration

Macro for the Object ID All.
*/
#define OBJECT_ID_ALL  0xffffffff

/*!
@struct ReceivePacket epAdminServerPacketInfo.h
@brief A Class for the Receive Packet.	
*/
struct ReceivePacket{
	/// Packet ID
	unsigned int packetId;
	/// Processing Count
	unsigned int count;
};

/*!
@struct SendPacket epAdminServerPacketInfo.h
@brief A Class for the Send Packet.	
*/
struct SendPacket{
	/// Packet ID
	unsigned int packetId;
	/// Processing Result Count
	unsigned int count;
};
#endif //__EP_ADMIN_SERVER_PACKET_INFO_H__
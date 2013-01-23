/*! 
@file epServiceDefines.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Service Definition Interface
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

An Interface for Service Definition.

*/
#ifndef __EP_SERVICE_DEFINES_H__
#define __EP_SERVICE_DEFINES_H__


#include "winsvc.h"

/// Control Bit for Service Configuration
typedef enum _serviceEditControlBit{
	/// Change BinaryPathName
	SERVICE_EDIT_CONTROL_BINARYPATHNAME=0x00000001,
	/// Change LoadOrderGroup
	SERVICE_EDIT_CONTROL_LOADORDERGROUP=0x00000002,
	/// Change Dependencies
	SERVICE_EDIT_CONTROL_DEPENDENCIES=0x00000004,
	/// Change Username
	SERVICE_EDIT_CONTROL_USERNAME=0x00000008,
	/// Change UserPassword
	SERVICE_EDIT_CONTROL_USERPASSWORD=0x00000010,
	/// Change Service Display Name
	SERVICE_EDIT_CONTROL_DISPLAYNAME=0x00000020,
}ServiceEditControlBit;

/// Service Desired Access Enumerators
typedef enum _serviceDesiredAccess{
	/// Includes STANDARD_RIGHTS_REQUIRED in addition to all access rights in this table.
	SERVICE_DESIRED_ACCESS_ALL_ACCESS=SERVICE_ALL_ACCESS ,
	/// Required to call the ChangeServiceConfig or ChangeServiceConfig2 function to change the service configuration.</br>
	/// Because this grants the caller the right to change the executable file that the system runs, it should be granted only to administrators.
	SERVICE_DESIRED_ACCESS_CHANGE_CONFIG=SERVICE_CHANGE_CONFIG ,
	/// Required to call the EnumDependentServices function to enumerate all the services dependent on the service.
	SERVICE_DESIRED_ACCESS_ENUMERATE_DEPENDENTS=SERVICE_ENUMERATE_DEPENDENTS,
	/// Required to call the ControlService function to ask the service to report its status immediately.
	SERVICE_DESIRED_ACCESS_INTERROGATE=SERVICE_INTERROGATE ,
	/// Required to call the ControlService function to pause or continue the service.
	SERVICE_DESIRED_ACCESS_PAUSE_CONTINUE=SERVICE_PAUSE_CONTINUE ,
	/// Required to call the QueryServiceConfig and QueryServiceConfig2 functions to query the service configuration.
	SERVICE_DESIRED_ACCESS_QUERY_CONFIG=SERVICE_QUERY_CONFIG ,
	/// Required to call the QueryServiceStatus or QueryServiceStatusEx function to ask the service control manager about the status of the service.</br>
	/// Required to call the NotifyServiceStatusChange function to receive notification when a service changes status.
	SERVICE_DESIRED_ACCESS_QUERY_STATUS=SERVICE_QUERY_STATUS ,
	/// Required to call the StartService function to start the service.
	SERVICE_DESIRED_ACCESS_START=SERVICE_START ,
	/// Required to call the ControlService function to stop the service.
	SERVICE_DESIRED_ACCESS_STOP=SERVICE_STOP ,
	/// Required to call the ControlService function to specify a user-defined control code.
	SERVICE_DESIRED_ACCESS_USER_DEFINED_CONTROL=SERVICE_USER_DEFINED_CONTROL,
	/// No Change
	SERVICE_DESIRED_ACCESS_NO_CHANGE=SERVICE_NO_CHANGE,
	/// Default Parameter
	SERVICE_DESIRED_ACCESS_DEFAULT_PARAM=SERVICE_NO_CHANGE,
}ServiceDesiredAccess;

/// Service Type Enumerators
typedef enum _serviceType{
	/// File system driver service.
	SERVICE_TYPE_FILE_SYSTEM_DRIVER=SERVICE_FILE_SYSTEM_DRIVER,
	/// Driver service.
	SERVICE_TYPE_KERNEL_DRIVER=SERVICE_KERNEL_DRIVER,
	/// Service that runs in its own process.
	SERVICE_TYPE_WIN32_OWN_PROCESS=SERVICE_WIN32_OWN_PROCESS,
	/// Service that shares a process with one or more other services.</br>
	/// For more information, see Service Programs.
	SERVICE_TYPE_WIN32_SHARE_PROCESS=SERVICE_WIN32_SHARE_PROCESS,
	/// The service can interact with the desktop. </br>
	/// Note: If you specify either SERVICE_WIN32_OWN_PROCESS or SERVICE_WIN32_SHARE_PROCESS, and the service is running in the context of the LocalSystem account, you can also specify the following value.
	SERVICE_TYPE_INTERACTIVE_PROCESS=SERVICE_INTERACTIVE_PROCESS,
	/// No Change
	SERVICE_TYPE_NO_CHANGE=SERVICE_NO_CHANGE,
	/// Default Parameter
	SERVICE_TYPE_DEFAULT_PARAM=SERVICE_NO_CHANGE,
}ServiceType;

/// Service Start Type Enumerators
typedef enum _serviceStartType{
	/// A service started automatically by the service control manager during system startup.</br>
	/// For more information, see Automatically Starting Services.
	SERVICE_START_TYPE_AUTO_START=SERVICE_AUTO_START,
	/// A device driver started by the system loader.</br>
	/// This value is valid only for driver services.
	SERVICE_START_TYPE_BOOT_START=SERVICE_BOOT_START,
	/// A service started by the service control manager when a process calls the StartService function.</br>
	/// For more information, see Starting Services on Demand.
	SERVICE_START_TYPE_DEMAND_START=SERVICE_DEMAND_START,
	/// A service that cannot be started.</br>
	/// Attempts to start the service result in the error code ERROR_SERVICE_DISABLED.
	SERVICE_START_TYPE_DISABLED=SERVICE_DISABLED,
	/// A device driver started by the IoInitSystem function.</br>
	/// This value is valid only for driver services.
	SERVICE_START_TYPE_SYSTEM_START=SERVICE_SYSTEM_START,
	/// No Change
	SERVICE_START_TYPE_NO_CHANGE=SERVICE_NO_CHANGE,
	/// Default Parameter
	SERVICE_START_TYPE_DEFAULT_PARAM=SERVICE_NO_CHANGE,
}ServiceStartType;

/// Service Error Control Type Enumerators
typedef enum _serviceErrorControl{
	/// The startup program logs the error in the event log, if possible.</br>
	/// If the last-known-good configuration is being started, the startup operation fails.</br>
	/// Otherwise, the system is restarted with the last-known good configuration.
	SERVICE_ERROR_CONTROL_CRITICAL=SERVICE_ERROR_CRITICAL,
	/// The startup program ignores the error and continues the startup operation.
	SERVICE_ERROR_CONTROL_IGNORE=SERVICE_ERROR_IGNORE,
	/// The startup program logs the error in the event log but continues the startup operation.
	SERVICE_ERROR_CONTROL_NORMAL=SERVICE_ERROR_NORMAL,
	/// The startup program logs the error in the event log.</br>
	/// If the last-known-good configuration is being started, the startup operation continues.</br>
	/// Otherwise, the system is restarted with the last-known-good configuration.
	SERVICE_ERROR_CONTROL_SEVERE=SERVICE_ERROR_SEVERE,
	/// No Change
	SERVICE_ERROR_CONTROL_NO_CHANGE=SERVICE_NO_CHANGE,
	/// Default Parameter
	SERVICE_ERROR_CONTROL_DEFAULT_PARAM=SERVICE_NO_CHANGE,
}ServiceErrorControl;




/// Service Error Code for OpenSCManager Function
typedef enum _serviceOpenSCManageErrCode{
	/// The requested access was denied.
	SERVICE_OPEN_SCMANAGER_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// The specified database does not exist.
	SERVICE_OPEN_SCMANAGER_ERR_CODE_DATABASE_DOES_NOT_EXIST=ERROR_DATABASE_DOES_NOT_EXIST,

}ServiceOpenSCManageErrCode;

/// Service Error Code for OpenService Function
typedef enum _serviceOpenServiceErrCode{
	/// The handle does not have access to the service.
	SERVICE_OPEN_SERVICE_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// The specified handle is invalid.
	SERVICE_OPEN_SERVICE_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// The specified service name is invalid.
	SERVICE_OPEN_SERVICE_ERR_CODE_INVALID_NAME=ERROR_INVALID_NAME,
	/// The specified service does not exist.
	SERVICE_OPEN_SERVICE_ERR_CODE_SERVICE_DOES_NOT_EXIST=ERROR_SERVICE_DOES_NOT_EXIST,

}ServiceOpenServiceErrCode;

/// Service Error Code for StartService Function
typedef enum _serviceStartServiceErrCode{
	/// The handle does not have the SERVICE_START access right.
	SERVICE_START_SERVICE_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// The handle is invalid.
	SERVICE_START_SERVICE_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// The service binary file could not be found.
	SERVICE_START_SERVICE_ERR_CODE_PATH_NOT_FOUND=ERROR_PATH_NOT_FOUND,
	/// An instance of the service is already running.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_ALREADY_RUNNING=ERROR_SERVICE_ALREADY_RUNNING,
	/// The database is locked.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_DATABASE_LOCKED=ERROR_SERVICE_DATABASE_LOCKED,
	/// The service depends on a service that does not exist or has been marked for deletion.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_DEPENDENCY_DELETED=ERROR_SERVICE_DEPENDENCY_DELETED,
	/// The service depends on another service that has failed to start.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_DEPENDENCY_FAIL=ERROR_SERVICE_DEPENDENCY_FAIL,
	/// The service has been disabled.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_DISABLED=ERROR_SERVICE_DISABLED,
	/// The service did not start due to a logon failure.</br>
	/// This error occurs if the service is configured to run under an account that does not have the "Log on as a service" right.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_LOGON_FAILED=ERROR_SERVICE_LOGON_FAILED,
	/// The service has been marked for deletion.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_MARKED_FOR_DELETE=ERROR_SERVICE_MARKED_FOR_DELETE,
	/// A thread could not be created for the service.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_NO_THREAD=ERROR_SERVICE_NO_THREAD,
	/// The process for the service was started, but it did not call StartServiceCtrlDispatcher, or the thread that called StartServiceCtrlDispatcher may be blocked in a control handler function.
	SERVICE_START_SERVICE_ERR_CODE_SERVICE_REQUEST_TIMEOUT=ERROR_SERVICE_REQUEST_TIMEOUT,

}ServiceStartServiceErrCode;

/// Service Error Code for CreateService Function
typedef enum _serviceCreateServiceErrCode{
	/// The handle to the SCM database does not have the SC_MANAGER_CREATE_SERVICE access right.
	SERVICE_CREATE_SERVICE_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// A circular service dependency was specified.
	SERVICE_CREATE_SERVICE_ERR_CODE_CIRCULAR_DEPENDENCY=ERROR_CIRCULAR_DEPENDENCY,
	/// The display name already exists in the service control manager database either as a service name or as another display name.
	SERVICE_CREATE_SERVICE_ERR_CODE_DUPLICATE_SERVICE_NAME=ERROR_DUPLICATE_SERVICE_NAME,
	/// The handle to the specified service control manager database is invalid.
	SERVICE_CREATE_SERVICE_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// The specified service name is invalid.
	SERVICE_CREATE_SERVICE_ERR_CODE_INVALID_NAME=ERROR_INVALID_NAME,
	/// A parameter that was specified is invalid.
	SERVICE_CREATE_SERVICE_ERR_CODE_INVALID_PARAMETER=ERROR_INVALID_PARAMETER,
	/// The user account name specified in the lpServiceStartName parameter does not exist.
	SERVICE_CREATE_SERVICE_ERR_CODE_INVALID_SERVICE_ACCOUNT=ERROR_INVALID_SERVICE_ACCOUNT,
	/// The specified service already exists in this database.
	SERVICE_CREATE_SERVICE_ERR_CODE_SERVICE_EXISTS=ERROR_SERVICE_EXISTS,
	/// The specified service already exists in this database and has been marked for deletion.
	SERVICE_CREATE_SERVICE_ERR_CODE_SERVICE_MARKED_FOR_DELETE=ERROR_SERVICE_MARKED_FOR_DELETE,
}ServiceCreateServiceErrCode;

/// Service Error Code for DeleteService Function
typedef enum _serviceDeleteServiceErrCode{
	/// The handle does not have the DELETE access right.
	SERVICE_DELETE_SERVICE_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// The specified handle is invalid.
	SERVICE_DELETE_SERVICE_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// The specified service has already been marked for deletion.
	SERVICE_DELETE_SERVICE_ERR_CODE_SERVICE_MARKED_FOR_DELETE=ERROR_SERVICE_MARKED_FOR_DELETE,
}ServiceDeleteServiceErrCode;

/// Service Error Code for ControlService Function
typedef enum _serviceControlServiceErrCode{
	/// The handle does not have the required access right.
	SERVICE_CONTROL_SERVICE_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// The service cannot be stopped because other running services are dependent on it.
	SERVICE_CONTROL_SERVICE_ERR_CODE_DEPENDENT_SERVICES_RUNNING=ERROR_DEPENDENT_SERVICES_RUNNING,
	/// The specified handle was not obtained using CreateService or OpenService, or the handle is no longer valid.
	SERVICE_CONTROL_SERVICE_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// The requested control code is undefined.
	SERVICE_CONTROL_SERVICE_ERR_CODE_INVALID_PARAMETER=ERROR_INVALID_PARAMETER,
	/// The requested control code is not valid, or it is unacceptable to the service.
	SERVICE_CONTROL_SERVICE_ERR_CODE_INVALID_SERVICE_CONTROL=ERROR_INVALID_SERVICE_CONTROL,
	/// The requested control code cannot be sent to the service because the state of the service is SERVICE_STOPPED, SERVICE_START_PENDING, or SERVICE_STOP_PENDING.
	SERVICE_CONTROL_SERVICE_ERR_CODE_SERVICE_CANNOT_ACCEPT_CTRL=ERROR_SERVICE_CANNOT_ACCEPT_CTRL,
	/// The service has not been started.
	SERVICE_CONTROL_SERVICE_ERR_CODE_SERVICE_NOT_ACTIVE=ERROR_SERVICE_NOT_ACTIVE,
	/// The process for the service was started, but it did not call StartServiceCtrlDispatcher, or the thread that called StartServiceCtrlDispatcher may be blocked in a control handler function.
	SERVICE_CONTROL_SERVICE_ERR_CODE_SERVICE_REQUEST_TIMEOUT=ERROR_SERVICE_REQUEST_TIMEOUT,
	/// The system is shutting down.
	SERVICE_CONTROL_SERVICE_ERR_CODE_SHUTDOWN_IN_PROGRESS=ERROR_SHUTDOWN_IN_PROGRESS,
}ServiceControlServiceErrCode;

/// Service Error Code for ChangeServiceConfig Function
typedef enum _serviceChangeServiceConfigErrCode{
	/// The handle does not have the SERVICE_CHANGE_CONFIG access right.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// A circular service dependency was specified.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_CIRCULAR_DEPENDENCY=ERROR_CIRCULAR_DEPENDENCY,
	/// The display name already exists in the service controller manager database, either as a service name or as another display name.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_DUPLICATE_SERVICE_NAME=ERROR_DUPLICATE_SERVICE_NAME,
	/// The specified handle is invalid.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// A parameter that was specified is invalid.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_INVALID_PARAMETER=ERROR_INVALID_PARAMETER,
	/// The account name does not exist, or a service is specified to share the same binary file as an already installed service but with an account name that is not the same as the installed service.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_INVALID_SERVICE_ACCOUNT=ERROR_INVALID_SERVICE_ACCOUNT,
	/// The service has been marked for deletion.
	SERVICE_CHANGE_SERVICE_CONFIG_ERR_CODE_SERVICE_MARKED_FOR_DELETE=ERROR_SERVICE_MARKED_FOR_DELETE,
}ServiceChangeServiceErrCode;

/// Service Error Code for QueryServiceStatusEx Function
typedef enum _serviceQueryServiceStatusExErrCode{
	/// The handle is invalid.
	SERVICE_QUERY_SERVICE_STATUS_EX_ERR_CODE_INVALID_HANDLE=ERROR_INVALID_HANDLE,
	/// The handle does not have the SERVICE_QUERY_STATUS access right.
	SERVICE_QUERY_SERVICE_STATUS_EX_ERR_CODE_ACCESS_DENIED=ERROR_ACCESS_DENIED,
	/// The buffer is too small for the SERVICE_STATUS_PROCESS structure. Nothing was written to the structure.
	SERVICE_QUERY_SERVICE_STATUS_EX_ERR_CODE_INSUFFICIENT_BUFFER=ERROR_INSUFFICIENT_BUFFER,
	/// The cbSize member of SERVICE_STATUS_PROCESS is not valid.
	SERVICE_QUERY_SERVICE_STATUS_EX_ERR_CODE_INVALID_PARAMETER=ERROR_INVALID_PARAMETER,
	/// The InfoLevel parameter contains an unsupported value.
	SERVICE_QUERY_SERVICE_STATUS_EX_ERR_CODE_INVALID_LEVEL=ERROR_INVALID_LEVEL,
	/// The system is shutting down; this function cannot be called.
	SERVICE_QUERY_SERVICE_STATUS_EX_ERR_CODE_SHUTDOWN_IN_PROGRESS=ERROR_SHUTDOWN_IN_PROGRESS,
}ServiceQueryServiceStatusExErrCode;

/// Service Handle Error Code
typedef enum _serviceHandlerError{
	/// Service Handle Success
	SERVICE_HANDLER_ERROR_SUCCESS=0,
	/// OpenSCManager Error
	SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER,
	/// OpenService Error
	SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE,
	/// StartService Error
	SERVICE_HANDLER_ERROR_FAIL_STARTSERVICE,
	/// CreateService Error
	SERVICE_HANDLER_ERROR_FAIL_CREATESERVICE,
	/// DeleteService Error
	SERVICE_HANDLER_ERROR_FAIL_DELETESERVICE,
	/// ControlService Error
	SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE,
	/// ChangeServiceConfig Error
	SERVICE_HANDLER_ERROR_FAIL_CHANGESERVICECONFIG,
	/// Invalid Service Name Error
	SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME,

}ServiceHandlerError;

/// Service Status Type
typedef enum _serviceStatus{
	/// The service is running.
	SERVICE_STATUS_RUNNING=SERVICE_RUNNING,
	/// The service is pausing.
	SERVICE_STATUS_PAUSE_PENDING=SERVICE_PAUSE_PENDING,
	/// The service is paused.
	SERVICE_STATUS_PAUSED=SERVICE_PAUSED,
	/// The service is about to continue.
	SERVICE_STATUS_CONTINUE_PENDING=SERVICE_CONTINUE_PENDING,
	/// The service is starting.
	SERVICE_STATUS_START_PENDING=SERVICE_START_PENDING,
	/// The service is stopping.
	SERVICE_STATUS_STOP_PENDING=SERVICE_STOP_PENDING,
	/// The service has stopped.
	SERVICE_STATUS_STOPPED=SERVICE_STOPPED,
}ServiceStatus;


/// Service Control Code Enumerators
typedef enum _serviceControlCode{
	/// NO Control
	SERVICE_CONTROL_CODE_NONE=0,
	/// Notifies a service that it should stop.</br>
	/// The hService handle must have the SERVICE_STOP access right.</br>
	/// After sending the stop request to a service, you should not send other controls to the service.
	SERVICE_CONTROL_CODE_STOP=SERVICE_CONTROL_STOP,
	/// Notifies a service that it should pause.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.
	SERVICE_CONTROL_CODE_PAUSE=SERVICE_CONTROL_PAUSE,
	/// Notifies a paused service that it should resume.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.
	SERVICE_CONTROL_CODE_CONTINUE=SERVICE_CONTROL_CONTINUE,
	/// Notifies a service that it should report its current status information to the service control manager.</br>
	/// The hService handle must have the SERVICE_INTERROGATE access right.</br>
	/// Note that this control is not generally useful as the SCM is aware of the current state of the service.
	SERVICE_CONTROL_CODE_INTERROGATE=SERVICE_CONTROL_INTERROGATE,
	/// Notifies a service that its startup parameters have changed.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.
	SERVICE_CONTROL_CODE_PARAMCHANGE=SERVICE_CONTROL_PARAMCHANGE,
	/// Notifies a network service that there is a new component for binding.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.</br>
	/// However, this control code has been deprecated; use Plug and Play functionality instead.
	SERVICE_CONTROL_CODE_NETBINDADD=SERVICE_CONTROL_NETBINDADD,
	/// Notifies a network service that a component for binding has been removed.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.</br>
	/// However, this control code has been deprecated; use Plug and Play functionality instead.
	SERVICE_CONTROL_CODE_NETBINDREMOVE=SERVICE_CONTROL_NETBINDREMOVE,
	/// Notifies a network service that a disabled binding has been enabled.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.</br>
	/// However, this control code has been deprecated; use Plug and Play functionality instead.
	SERVICE_CONTROL_CODE_NETBINDENABLE=SERVICE_CONTROL_NETBINDENABLE,
	/// Notifies a network service that one of its bindings has been disabled.</br>
	/// The hService handle must have the SERVICE_PAUSE_CONTINUE access right.</br>
	/// However, this control code has been deprecated; use Plug and Play functionality instead.
	SERVICE_CONTROL_CODE_NETBINDDISABLE=SERVICE_CONTROL_NETBINDDISABLE,
}ServiceControlCode;

/*!
@def SERVICE_DEFAULT_PARAM
@brief Service Default Param Declaration

Macro for the Service Default Param.
*/
#define SERVICE_DEFAULT_PARAM SERVICE_NO_CHANGE

#endif //__EP_SERVICE_DEFINES_H__
/*! 
@file epWinServiceInfoStruct.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epserverengine>
@date January 16, 2013
@brief WinService Information Structure Interface
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

An Interface for WinService Information Structure.

*/
#ifndef __EP_WINSERVICE_INFO_STRUCT_H__
#define __EP_WINSERVICE_INFO_STRUCT_H__

#include "epWinServiceAPILibrary.h"
#include "epWinServiceDefines.h"
#include "epWinServiceClientPacketInfo.h"

namespace epws
{


	/*! 
	@struct DeployInfo epWinServiceInfoStruct.h
	@brief A class for Deploy Information.
	*/
	struct EP_WINSERVICE_API DeployInfo{
		/*!
		Default Constructor

		Initializes the DeployInfo
		*/
		DeployInfo()
		{
			m_errCode=DEPLOY_ERR_CODE_SUCCESS;
			m_startStatus=OBJECT_START_STATUS_SUCCESS;
			m_revisionNum=0;
		}
		/// Deploy Error Code
		DeployErrCode m_errCode;
		/// Object Start Status
		ObjectStartStatus m_startStatus;
		/// Revision Number
		int m_revisionNum;
	};



	/*! 
	@struct MainServiceInfo epWinServiceInfoStruct.h
	@brief A class for Main Service Information.
	*/
	struct EP_WINSERVICE_API MainServiceInfo{

		/*!
		Default Constructor

		Initializes the MainServiceInfo
		*/
		MainServiceInfo()
		{
			m_interval=50;
			m_command=_T("");
		}
		/// Time interval in milliseconds
		unsigned int m_interval;
		/// Command String
		EpTString m_command;
	};

	/*! 
	@struct ServiceObjInfo epWinServiceInfoStruct.h
	@brief A class for Service Object Information.
	*/
	struct EP_WINSERVICE_API ServiceObjInfo{
		/*!
		Default Constructor

		Initializes the ServiceObjInfo
		*/
		ServiceObjInfo()
		{
			m_serviceStatusType=SERVICE_STATUS_TYPE_UNKNOWN;

			m_serviceName=_T("");
			m_preProcessCommandLine=_T("");
			m_postProcessCommandLine=_T("");
			m_customProcessCommandLine=_T("");
			m_preProcessWaitTime=WAITTIME_INIFINITE;
			m_postProcessWaitTime=WAITTIME_INIFINITE;
			m_domainName=_T("");
			m_userName=_T("");
			m_userPassword=_T("");
			m_delayStartTime=0;
			m_delayPauseEndTime=0;
			m_isRestart=true;
			m_isImpersonate=false;
			m_isUserInterface=false;

			m_deployRepositoryURL=_T("");
			m_deployLocalPath=_T("");
			m_deployUserName=_T("");
			m_deployUserPassword=_T("");
			m_deployCurrentInfo.m_errCode=DEPLOY_ERR_CODE_SUCCESS;
			m_deployCurrentInfo.m_revisionNum=REVISION_UNKNOWN;
			m_deployLatestInfo.m_errCode=DEPLOY_ERR_CODE_SUCCESS;
			m_deployLatestInfo.m_revisionNum=REVISION_UNKNOWN;
		}
		/// Service Status Type
		ServiceStatusType m_serviceStatusType;

		/// Service Name
		EpTString m_serviceName;
		/// Pre-Process Command String
		EpTString m_preProcessCommandLine;
		/// Post-Process Command String
		EpTString m_postProcessCommandLine;
		/// Custom-Process Command String
		EpTString m_customProcessCommandLine;
		/// Pre-Process Wait Time in milliseconds
		int m_preProcessWaitTime;
		/// Post-Process Wait Time in milliseconds
		int m_postProcessWaitTime;
		/// Domain Name
		EpTString m_domainName;
		/// User Name
		EpTString m_userName;
		/// User Password
		EpTString m_userPassword;
		/// Delay Start Time in milliseconds
		unsigned int m_delayStartTime;
		/// Delay Pause/End Time in milliseconds
		unsigned int m_delayPauseEndTime;
		/// Flag for restart when fault
		bool m_isRestart;
		/// Flag for Impersonation
		bool m_isImpersonate;
		/// Flag for User-Interface
		bool m_isUserInterface;


		/// Repository URL
		EpTString m_deployRepositoryURL;
		/// Local Path
		EpTString m_deployLocalPath;
		/// Deploy User Name
		EpTString m_deployUserName;
		/// Deploy User Password
		EpTString m_deployUserPassword;
		/// Current Deploy Info
		DeployInfo m_deployCurrentInfo;
		/// Latest Deploy Info
		DeployInfo m_deployLatestInfo;
	};
	


	/*! 
	@struct ProcessObjInfo epWinServiceInfoStruct.h
	@brief A class for Process Object Information.
	*/
	struct EP_WINSERVICE_API ProcessObjInfo{
		/*!
		Default Constructor

		Initializes the ProcessObjInfo
		*/
		ProcessObjInfo()
		{
			m_processStatusType=PROCESS_STATUS_TYPE_UNKNOWN;
			m_commandLine=_T("");
			m_preProcessCommandLine=_T("");
			m_postProcessCommandLine=_T("");
			m_customProcessCommandLine=_T("");
			m_preProcessWaitTime=WAITTIME_INIFINITE;
			m_postProcessWaitTime=WAITTIME_INIFINITE;
			m_domainName=_T("");
			m_userName=_T("");
			m_userPassword=_T("");
			m_delayStartTime=0;
			m_delayPauseEndTime=0;
			m_isRestart=true;
			m_isImpersonate=false;
			m_isUserInterface=false;

			m_deployRepositoryURL=_T("");
			m_deployLocalPath=_T("");
			m_deployUserName=_T("");
			m_deployUserPassword=_T("");
			m_deployCurrentInfo.m_errCode=DEPLOY_ERR_CODE_SUCCESS;
			m_deployCurrentInfo.m_revisionNum=REVISION_UNKNOWN;
			m_deployLatestInfo.m_errCode=DEPLOY_ERR_CODE_SUCCESS;
			m_deployLatestInfo.m_revisionNum=REVISION_UNKNOWN;


		}
		/// Process Status Type
		ProcessStatusType m_processStatusType;

		/// Command Line String
		EpTString m_commandLine;
		/// Pre-Process Command String
		EpTString m_preProcessCommandLine;
		/// Post-Process Command String
		EpTString m_postProcessCommandLine;
		/// Custom-Process Command String
		EpTString m_customProcessCommandLine;
		/// Pre-Process Wait Time in milliseconds
		int m_preProcessWaitTime;
		/// Post-Process Wait Time in milliseconds
		int m_postProcessWaitTime;
		/// Domain Name
		EpTString m_domainName;
		/// User Name
		EpTString m_userName;
		/// User Password
		EpTString m_userPassword;
		/// Delay Start Time in milliseconds
		unsigned int m_delayStartTime;
		/// Delay Pause/End Time in milliseconds
		unsigned int m_delayPauseEndTime;
		/// Flag for restart when fault
		bool m_isRestart;
		/// Flag for Impersonation
		bool m_isImpersonate;
		/// Flag for User-Interface
		bool m_isUserInterface;

		/// Repository URL
		EpTString m_deployRepositoryURL;
		/// Local Path
		EpTString m_deployLocalPath;
		/// Deploy User Name
		EpTString m_deployUserName;
		/// Deploy User Password
		EpTString m_deployUserPassword;
		/// Current Deploy Info
		DeployInfo m_deployCurrentInfo;
		/// Latest Deploy Info
		DeployInfo m_deployLatestInfo;

	};

	


	/*! 
	@struct ServiceInfo epWinServiceInfoStruct.h
	@brief A class for Service Information.
	*/
	struct EP_WINSERVICE_API ServiceInfo{
		/*!
		Default Constructor

		Initializes the ServiceInfo
		*/
		ServiceInfo()
		{
			m_code=SERVICE_CONTROL_CODE_NONE;

			m_displayName=_T("");
			m_desiredAccess=SERVICE_DESIRED_ACCESS_ALL_ACCESS;
			m_serviceType=SERVICE_TYPE_WIN32_OWN_PROCESS;
			m_serviceStartType=SERVICE_START_TYPE_AUTO_START;
			m_serviceErrorControl=SERVICE_ERROR_CONTROL_NORMAL;
			m_binaryPathName=_T("");
			m_loadOrderGroup=_T("");
			m_dependencies=_T("");
			m_domainName=_T("");
			m_userName=_T("");
			m_userPassword=_T("");
			m_editControlBits=0;
		}

		/// Service Control Code
		ServiceControlCode m_code;

		/// Service Display Name
		EpTString m_displayName;
		/// Service Desired Access
		ServiceDesiredAccess m_desiredAccess;
		/// Service Type
		ServiceType m_serviceType;
		/// Service Start Type
		ServiceStartType m_serviceStartType;
		/// Service Error Control
		ServiceErrorControl m_serviceErrorControl;
		/// Binary Path Name
		EpTString m_binaryPathName;
		/// Load Order Group
		EpTString m_loadOrderGroup;
		/// Dependencies
		EpTString m_dependencies;
		/// Domain Name
		EpTString m_domainName;
		/// User Name
		EpTString m_userName;
		/// User Password
		EpTString m_userPassword;

		/// Edit Control Bits
		unsigned int m_editControlBits;

	};

	/*! 
	@struct ServiceHandleErrorInfo epWinServiceInfoStruct.h
	@brief A class for Service Handle Error Information.
	*/
	struct EP_WINSERVICE_API ServiceHandleErrorInfo{
		/*!
		Default Constructor

		Initializes the ServiceHandleErrorInfo
		*/
		ServiceHandleErrorInfo()
		{
			m_serviceHandleError=SERVICE_HANDLER_ERROR_SUCCESS;
			m_lastErrorCode=0;
		}
		/// Service Handle Error
		ServiceHandlerError m_serviceHandleError;
		/// Last Error Code
		unsigned long m_lastErrorCode;
	};
}


#endif //__EP_WINSERVICE_INFO_STRUCT_H__
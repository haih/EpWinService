/*! 
ServiceHandler for the EpWinService

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
*/
#include "stdafx.h"
#include "epServiceHandler.h"
#include "epServiceProperties.h"
#include "epLogWriter.h"

ServiceObject *&ServiceHandler::At(unsigned int serviceIndex)
{
	return m_serviceList.at(serviceIndex);
}

ServiceHandler::ServiceHandler()
{
	m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (m_scManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("ServiceHandler::ServiceHandler : OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}

	CString iniFileName=FolderHelper::GetModuleFileName().c_str();
	iniFileName.Replace(_T(".exe"),_T(".ini"));
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

	int serviceIndex=0;

	while(1)
	{
		CString serviceString=_T("Service");
		serviceString.AppendFormat(_T("%d"),serviceIndex);

		memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
		GetPrivateProfileString(serviceString.GetString(),_T("ServiceName"),_T(""),textBuffer,MAX_STRING_LENGTH,iniFileName.GetString());
		CString serviceName=textBuffer;
		if(serviceName.GetLength()>0)
		{
			ServiceObject *newObj=EP_NEW ServiceObject(serviceIndex);
			m_serviceList.push_back(newObj);
		}
		else
			break;
		serviceIndex++;
	}
	EP_DELETE[] textBuffer;
}

ServiceHandler::~ServiceHandler()
{
	if(m_scManager)
	{
		CloseServiceHandle(m_scManager); 
	}
}

VOID ServiceMonitorThread(VOID *)
{
	unsigned int checkServiceTime=SERVICE_PROPERTIES_INSTANCE.GetCheckServiceInterval();
	unsigned int serviceSize=SERVICE_HANDLER_INSTANCE.GetNumberOfServices();
	while(checkServiceTime)
	{
		Sleep(checkServiceTime);
		for(int serviceTrav=0;serviceTrav<serviceSize;serviceTrav++)
		{
			if(!SERVICE_HANDLER_INSTANCE.At(serviceTrav)->IsStarted() && 
				!SERVICE_HANDLER_INSTANCE.At(serviceTrav)->GetIsUserStopped())
			{
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->PostProcess();
				SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Reset();

				if(SERVICE_HANDLER_INSTANCE.At(serviceTrav)->GetIsRestart())
				{
					if(SERVICE_HANDLER_INSTANCE.At(serviceTrav)->Start())
					{
						TCHAR pTemp[121];
						_stprintf(pTemp, _T("Service[%d] Restarted"),serviceTrav);
						LOG_WRITER_INSTANCE.WriteLog( pTemp);
					}
				}
		
				
			}
		}		
	}
}

ServiceHandlerError ServiceHandler::StartService(const TCHAR *serviceName, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;
	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to start service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		// open the service
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to start service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call StartService to run the service
			if(!::StartService(schService, 0, (const TCHAR**)NULL))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_STARTSERVICE;
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to start service '%s' (StartService), error code = %d"), serviceName, retErrCode); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}
	}
	return err;
}

ServiceHandlerError ServiceHandler::StopService(const TCHAR *serviceName, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to stop service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		// open the service
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to stop service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(!::ControlService(schService,SERVICE_CONTROL_CODE_STOP,&status))
			{
				retErrCode = GetLastError();
				if(retErrCode!=1062)
				{
					err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
					TCHAR pTemp[256];
					_stprintf(pTemp,_T("Failed to stop service '%s' (ControlService), error code = %d"), serviceName, retErrCode); 
					LOG_WRITER_INSTANCE.WriteLog( pTemp);
				}
				else
					retErrCode=0;
			}
			CloseServiceHandle(schService); 
		}

	}
	return err;
}
ServiceHandlerError ServiceHandler::PauseService(const TCHAR *serviceName, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to pause service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		// open the service
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to pause service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(!::ControlService(schService,SERVICE_CONTROL_CODE_PAUSE,&status))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
				TCHAR pTemp[256];
				if(retErrCode==1062)
				{
					_stprintf(pTemp,_T("Failed to pause service '%s' (Service has not been started) "), serviceName); 
				}
				else
				{
					_stprintf(pTemp,_T("Failed to pause service '%s' (ControlService), error code = %d"), serviceName, retErrCode); 
				}
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}

	}
	return err;
}

ServiceHandlerError ServiceHandler::ContinueService(const TCHAR *serviceName, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to continue service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		// open the service
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to continue service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(!::ControlService(schService,SERVICE_CONTROL_CODE_CONTINUE,&status))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
				TCHAR pTemp[256];
				if(retErrCode==1062)
				{
					_stprintf(pTemp,_T("Failed to continue service '%s' (Service has not been started) "), serviceName); 
				}
				else
				{
					_stprintf(pTemp,_T("Failed to continue service '%s' (ControlService), error code = %d"), serviceName, retErrCode); 
				}
				
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}

	}
	return err;
}

ServiceHandlerError ServiceHandler::ControlService(const TCHAR *serviceName,ServiceControlCode code, SERVICE_STATUS &retStatus , DWORD &retErrCode, bool shouldLog)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to control service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			if(shouldLog)
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		// open the service
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to control service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			if(shouldLog)
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			
			if(!::ControlService(schService,code,&retStatus))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to control service '%s' (ControlService), error code = %d"), serviceName, retErrCode); 
				if(shouldLog)
					LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}

	}
	return err;
}

CString TCHARToCString(const TCHAR *tString)
{
	if(tString)
		return CString(tString);
	return CString(_T(""));
}

ServiceHandlerError ServiceHandler::InstallService(const TCHAR *serviceName,ServiceInfo info , DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to install service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{

		CString displayName=info.displayName.c_str();
		CString domainName=info.domainName.c_str();
		CString userName=info.userName.c_str();
		CString dependencies=info.dependencies.c_str();
		CString startUserName=_T("");
		unsigned long desiredAccess=info.desiredAccess;
		unsigned long serviceType=info.startType;
		unsigned long startType=info.errorControl;
		unsigned long errorControl=info.serviceType;

		if(displayName.GetLength()<=0)
		{
			displayName=serviceName;
		}
		dependencies.Replace(_T(' '), _T('\0'));
		dependencies.Replace(_T(';'), _T('\0'));

		if(info.desiredAccess==SERVICE_DEFAULT_PARAM)
		{
			desiredAccess=SERVICE_ALL_ACCESS;
		}
		if(info.startType==SERVICE_DEFAULT_PARAM)
		{
			startType=SERVICE_AUTO_START;
		}
		if(info.errorControl==SERVICE_DEFAULT_PARAM)
		{
			errorControl=SERVICE_ERROR_NORMAL;
		}


		SC_HANDLE schService;
		
		if(userName.Compare(_T(""))==0)
		{
			if(info.serviceType==SERVICE_DEFAULT_PARAM)
			{
				serviceType=SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;
			}
			schService = CreateService
				( 
				m_scManager,	/* SCManager database      */ 
				serviceName,			/* name of service         */ 
				displayName.GetString(),			/* service name to display */ 
				desiredAccess,        /* desired access          */ 
				serviceType , /* service type            */ 
				startType,      /* start type              */ 
				errorControl,      /* error control type      */ 
				info.binaryPathName.c_str(),			/* service's binary        */ 
				info.loadOrderGroup.c_str(),                      /* no load ordering group  */ 
				NULL,                      /* no tag identifier       */ 
				dependencies.GetString(),                      /* no dependencies         */ 
				NULL,                      /* LocalSystem account     */ 
				NULL
				);                     /* no password             */ 

		}
		else
		{
			if(info.serviceType==SERVICE_DEFAULT_PARAM)
			{
				serviceType=SERVICE_WIN32_OWN_PROCESS;
			}

			startUserName=_T("");

			if(domainName.GetLength())
			{
				startUserName.AppendFormat(_T("%s\\%s"),domainName,userName);
			}
			else
			{
				startUserName.AppendFormat(_T(".\\%s"),userName);
			}
			schService = CreateService
				( 
				m_scManager,	/* SCManager database      */ 
				serviceName,			/* name of service         */ 
				displayName.GetString(),			/* service name to display */ 
				desiredAccess,        /* desired access          */ 
				serviceType, /* service type            */ 
				startType,      /* start type              */ 
				errorControl,      /* error control type      */ 
				info.binaryPathName.c_str(),			/* service's binary        */ 
				info.loadOrderGroup.c_str(),                      /* no load ordering group  */ 
				NULL,                      /* no tag identifier       */ 
				dependencies.GetString(),                      /* no dependencies         */ 
				startUserName.GetString(),                      /* LocalSystem account     */ 
				info.password.c_str()
				);                     /* no password             */ 

		}
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_CREATESERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to install service '%s' (CreateService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}	
	return err;
}

ServiceHandlerError ServiceHandler::UnInstallService(const TCHAR *serviceName, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to uninstall service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to uninstall service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_DELETESERVICE;
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to uninstall service '%s' (DeleteService), error code = %d"), serviceName, retErrCode); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}
	}
	return err;
}

ServiceHandlerError ServiceHandler::EditService(const TCHAR *serviceName,ServiceInfo info, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;


	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to edit service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to edit service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			CString displayName=info.displayName.c_str();
			CString domainName=info.domainName.c_str();
			CString userName=info.userName.c_str();
			CString dependencies=info.dependencies.c_str();
			CString startUserName=_T("");
			startUserName=_T("");

			if(userName.Compare(_T(""))!=0)
			{
				if(domainName.GetLength())
				{
					startUserName.AppendFormat(_T("%s\\%s"),domainName,userName);
				}
				else
				{
					startUserName.AppendFormat(_T(".\\%s"),userName);
				}
			}

			if(displayName.GetLength()<=0)
			{
				displayName=serviceName;
			}

			dependencies.Replace(_T(' '), _T('\0'));
			dependencies.Replace(_T(';'), _T('\0'));

			const TCHAR *tBinaryPathName=NULL;
			const TCHAR *tLoadOrderGroup=NULL;
			const TCHAR *tDisplayName=NULL;
			const TCHAR *tDependencies=NULL;
			const TCHAR *tStartUserName=NULL;
			const TCHAR *tUserPassword=NULL;

			if((info.editControlBit&SERVICE_EDIT_CONTROL_BINARYPATHNAME)==SERVICE_EDIT_CONTROL_BINARYPATHNAME)
			{
				tBinaryPathName=info.binaryPathName.c_str();
			}
			if((info.editControlBit&SERVICE_EDIT_CONTROL_LOADORDERGROUP)==SERVICE_EDIT_CONTROL_LOADORDERGROUP)
			{
				tLoadOrderGroup=info.loadOrderGroup.c_str();
			}
			if((info.editControlBit&SERVICE_EDIT_CONTROL_DEPENDENCIES)==SERVICE_EDIT_CONTROL_DEPENDENCIES)
			{
				tDependencies=dependencies.GetString();
			}
			if((info.editControlBit&SERVICE_EDIT_CONTROL_USERNAME)==SERVICE_EDIT_CONTROL_USERNAME)
			{
				tStartUserName=startUserName.GetString();
			}
			if((info.editControlBit&SERVICE_EDIT_CONTROL_USERPASSWORD)==SERVICE_EDIT_CONTROL_USERPASSWORD)
			{
				tUserPassword=info.password.c_str();
			}

			if((info.editControlBit&SERVICE_EDIT_CONTROL_DISPLAYNAME)==SERVICE_EDIT_CONTROL_DISPLAYNAME)
			{
				tDisplayName=displayName;
			}
			

			BOOL retStatus=ChangeServiceConfig
				( 
				schService,	             /* Service Handle      */ 
				info.serviceType ,       /* service type            */ 
				info.startType,          /* start type              */ 
				info.errorControl,       /* error control type      */ 
				tBinaryPathName,	  	 /* service's binary        */ 
				tLoadOrderGroup,         /* load ordering group  */ 
				NULL,                    /* no tag identifier       */ 
				tDependencies,           /* dependencies         */ 
				tStartUserName,          /* account     */ 
				tUserPassword,           /* password             */ 
				tDisplayName			 /* service name to display */ 
				);   
			if(!retStatus)
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CHANGESERVICECONFIG;
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to edit service '%s' (ChangeServiceConfig), error code = %d"), serviceName, retErrCode); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}


		}
	}
	return err;
}


ServiceHandlerError ServiceHandler::GetServiceStatus(const TCHAR *serviceName,SERVICE_STATUS_PROCESS &retStatus, DWORD &retErrCode)
{
	retErrCode=0;
	if(!serviceName)
		return SERVICE_HANDLER_ERROR_FAIL_INVALIDSERVICENAME;

	ServiceHandlerError err=SERVICE_HANDLER_ERROR_SUCCESS;

	if (m_scManager==0) 
	{
		m_scManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
		if (m_scManager==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSCMANAGER;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to get ServiceStatus of service '%s' (OpenSCManager), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(m_scManager)
	{
		
		
		// open the service
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
			TCHAR pTemp[256];
			_stprintf(pTemp,_T("Failed to get ServiceStatus of service '%s' (OpenService), error code = %d"), serviceName, retErrCode); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS_PROCESS status;
			DWORD byteNeeded;
			if(!::QueryServiceStatusEx(schService,SC_STATUS_PROCESS_INFO,(BYTE*)&status,sizeof(SERVICE_STATUS_PROCESS),&byteNeeded))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
				TCHAR pTemp[256];
				_stprintf(pTemp,_T("Failed to get ServiceStatus of service '%s' (QueryServiceStatusEx), error code = %d"), serviceName, retErrCode); 
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			else
			{
				retStatus=status;
			}
			CloseServiceHandle(schService); 
		}

	}
	return err;
}
#include "stdafx.h"
#include "epServiceHandler.h"
#include "epLogWriter.h"

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
}

ServiceHandler::~ServiceHandler()
{
	if(m_scManager)
	{
		CloseServiceHandle(m_scManager); 
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
		}
		else
		{
			// call StartService to run the service
			if(!::StartService(schService, 0, (const TCHAR**)NULL))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_STARTSERVICE;
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
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(!::ControlService(schService,SERVICE_CONTROL_CODE_STOP,&status))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
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
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(!::ControlService(schService,SERVICE_CONTROL_CODE_PAUSE,&status))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
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
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(!::ControlService(schService,SERVICE_CONTROL_CODE_CONTINUE,&status))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
			}
			CloseServiceHandle(schService); 
		}

	}
	return err;
}

ServiceHandlerError ServiceHandler::ControlService(const TCHAR *serviceName,ServiceControlCode code, SERVICE_STATUS &retStatus , DWORD &retErrCode)
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
		}
		else
		{
			// call ControlService to kill the given service
			
			if(!::ControlService(schService,code,&retStatus))
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_CONTROLSERVICE;
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
		}
	}

	if(m_scManager)
	{

		CString displayName=info.displayName;
		CString domainName=info.domainName;
		CString userName=info.userName;
		CString dependencies=info.dependencies;
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
				info.binaryPathName.GetString(),			/* service's binary        */ 
				info.loadOrderGroup.GetString(),                      /* no load ordering group  */ 
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
				info.binaryPathName.GetString(),			/* service's binary        */ 
				info.loadOrderGroup.GetString(),                      /* no load ordering group  */ 
				NULL,                      /* no tag identifier       */ 
				dependencies.GetString(),                      /* no dependencies         */ 
				startUserName.GetString(),                      /* LocalSystem account     */ 
				info.password.GetString()
				);                     /* no password             */ 

		}
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_CREATESERVICE;
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
		}
	}

	if(m_scManager)
	{
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				retErrCode = GetLastError();
				err=SERVICE_HANDLER_ERROR_FAIL_DELETESERVICE;
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
		}
	}

	if(m_scManager)
	{
		SC_HANDLE schService = OpenService( m_scManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			retErrCode = GetLastError();
			err=SERVICE_HANDLER_ERROR_FAIL_OPENSERVICE;
		}
		else
		{
			CString displayName=info.displayName;
			CString domainName=info.domainName;
			CString userName=info.userName;
			CString dependencies=info.dependencies;
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
				tBinaryPathName=info.binaryPathName;
			}
			if((info.editControlBit&SERVICE_EDIT_CONTROL_LOADORDERGROUP)==SERVICE_EDIT_CONTROL_LOADORDERGROUP)
			{
				tLoadOrderGroup=info.loadOrderGroup;
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
				tUserPassword=info.password;
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
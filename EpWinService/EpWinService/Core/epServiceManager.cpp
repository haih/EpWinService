/*! 
ServiceManager for the EpWinService
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
*/
#include "stdafx.h"
#include "epServiceManager.h"
#include "epServiceProperties.h"
#include "epProcessHandler.h"
#include "epLogWriter.h"
#include "epServiceHandler.h"

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);

void MainServiceStart();

#define SERVICE_CONTROL_PROCESS_START  0x80
#define SERVICE_CONTROL_PROCESS_END    0xc0
#define SERVICE_CONTROL_CUSTOM_PROCESS 0xe0
#define SERVICE_CONTROL_PROCESS_BOUNCE 0xa0
#define SERVICE_CONTROL_INDEX          0x1f

bool ServiceManager::BounceProcess(int idx)
{
	if(idx<OBJECT_IDX_ALL || idx>31)
	{
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("Invalid argument to BounceProcess: %d"), idx); 
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
		}
		else
		{
			// call ControlService to invoke handler
			SERVICE_STATUS status;
			DWORD dwControl=0;
			if(idx<0)
				dwControl=SERVICE_CONTROL_PROCESS_BOUNCE|SERVICE_CONTROL_INDEX;
			else
				dwControl=SERVICE_CONTROL_PROCESS_BOUNCE|idx;

			if(ControlService(schService,dwControl,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("ControlService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}

bool ServiceManager::StartProcess(int idx)
{
	if(idx<OBJECT_IDX_ALL || idx>31)
	{
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("Invalid argument to StartProcess: %d"), idx); 
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
		}
		else
		{
			// call ControlService to invoke handler
			SERVICE_STATUS status;
			DWORD dwControl=0;
			if(idx<0)
				dwControl=SERVICE_CONTROL_PROCESS_START|SERVICE_CONTROL_INDEX;
			else
				dwControl=SERVICE_CONTROL_PROCESS_START|idx;

			if(ControlService(schService,dwControl,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("ControlService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}

bool ServiceManager::EndProcess(int idx)
{
	if(idx<OBJECT_IDX_ALL || idx>31)
	{
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("Invalid argument to EndProcess: %d"), idx); 
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
		}
		else
		{
			// call ControlService to invoke handler
			SERVICE_STATUS status;
			DWORD dwControl=0;
			if(idx<0)
				dwControl=SERVICE_CONTROL_PROCESS_END|SERVICE_CONTROL_INDEX;
			else
				dwControl=SERVICE_CONTROL_PROCESS_END|idx;

			if(ControlService(schService,dwControl,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("ControlService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}

bool ServiceManager::CustomProcess(int idx)
{
	if(idx<OBJECT_IDX_ALL || idx>31)
	{
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("Invalid argument to CustomProcess: %d"), idx); 
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog(pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
		}
		else
		{
			// call ControlService to invoke handler
			SERVICE_STATUS status;
			DWORD dwControl=0;
			if(idx<0)
				dwControl=SERVICE_CONTROL_CUSTOM_PROCESS|SERVICE_CONTROL_INDEX;
			else
				dwControl=SERVICE_CONTROL_CUSTOM_PROCESS|idx;

			if(ControlService(schService,dwControl,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("ControlService failed, error code = %d"), nError); 
			LOG_WRITER_INSTANCE.WriteLog(pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;
}


void ServiceManager::ExecuteSubProcess()
{
	SetLastError(0);
	SERVICE_TABLE_ENTRY	m_lpServiceStartTable;
	m_lpServiceStartTable.lpServiceName=const_cast<TCHAR*>(SERVICE_PROPERTIES_INSTANCE.GetServiceName());
	m_lpServiceStartTable.lpServiceProc=ServiceMain;

	if(!StartServiceCtrlDispatcher(&m_lpServiceStartTable))
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("StartServiceCtrlDispatcher failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
		return;
	}
	TCHAR pTemp[121];
	_stprintf(pTemp, _T("Service %s running\n"), SERVICE_PROPERTIES_INSTANCE.GetServiceName());
	LOG_WRITER_INSTANCE.WriteLog( pTemp);
}

void ServiceManager::TestSubProcess()
{
	MainServiceStart();
	while(1)
	{
		Sleep(0);
	}
}

bool ServiceManager::RunService()
{
	// run service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call StartService to run the service
			if(StartService(schService, 0, (const TCHAR**)NULL))
			{
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("Service %s started"), SERVICE_PROPERTIES_INSTANCE.GetServiceName());
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return true;
			}
			else
			{
				long nError = GetLastError();
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("StartService failed, error code = %d"), nError);
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return false;

}


bool ServiceManager::KillService() 
{ 
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("Service %s killed"), SERVICE_PROPERTIES_INSTANCE.GetServiceName());
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("ControlService failed, error code = %d"), nError);
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

void ServiceManager::Install()
{
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		CString pathName=FolderHelper::GetModuleFileName().c_str();
		pathName.AppendFormat(_T(" -e"));
		SC_HANDLE schService;
		CString userName=SERVICE_PROPERTIES_INSTANCE.GetUserName();

		
		if(userName.Compare(_T(""))==0)
		{
			schService = CreateService
				( 
				schSCManager,	/* SCManager database      */ 
				SERVICE_PROPERTIES_INSTANCE.GetServiceName(),			/* name of service         */ 
				SERVICE_PROPERTIES_INSTANCE.GetServiceName(),			/* service name to display */ 
				SERVICE_ALL_ACCESS,        /* desired access          */ 
				SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , /* service type            */ 
				SERVICE_AUTO_START,      /* start type              */ 
				SERVICE_ERROR_NORMAL,      /* error control type      */ 
				pathName.GetString(),			/* service's binary        */ 
				NULL,                      /* no load ordering group  */ 
				NULL,                      /* no tag identifier       */ 
				SERVICE_PROPERTIES_INSTANCE.GetDependency(),                      /* no dependencies         */ 
				NULL,                      /* LocalSystem account     */ 
				NULL
				);                     /* no password             */ 

		}
		else
		{
			CString startUserName=_T("");
			CString domainName=SERVICE_PROPERTIES_INSTANCE.GetDomainName();
			
			if(domainName.GetLength())
			{
				startUserName.AppendFormat(_T("%s\\%s"),domainName.GetString(),userName.GetString());
			}
			else
			{
				startUserName.AppendFormat(_T(".\\%s"),userName.GetString());
			}
			schService = CreateService
				( 
				schSCManager,	/* SCManager database      */ 
				SERVICE_PROPERTIES_INSTANCE.GetServiceName(),			/* name of service         */ 
				SERVICE_PROPERTIES_INSTANCE.GetServiceName(),			/* service name to display */ 
				SERVICE_ALL_ACCESS,        /* desired access          */ 
				SERVICE_WIN32_OWN_PROCESS, /* service type            */ 
				SERVICE_AUTO_START,      /* start type              */ 
				SERVICE_ERROR_NORMAL,      /* error control type      */ 
				pathName.GetString(),			/* service's binary        */ 
				NULL,                      /* no load ordering group  */ 
				NULL,                      /* no tag identifier       */ 
				SERVICE_PROPERTIES_INSTANCE.GetDependency(),                      /* no dependencies         */ 
				startUserName.GetString(),                      /* LocalSystem account     */ 
				SERVICE_PROPERTIES_INSTANCE.GetUserPassword()
				);                     /* no password             */ 

		}
		if (schService==0) 
		{
			long nError =  GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("Failed to create service %s, error code = %d"), SERVICE_PROPERTIES_INSTANCE.GetServiceName(), nError);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("Service %s installed"), SERVICE_PROPERTIES_INSTANCE.GetServiceName());
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);
	}	
}

void ServiceManager::UnInstall()
{
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("Failed to delete service %s"), SERVICE_PROPERTIES_INSTANCE.GetServiceName());
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
	}

	CString logFileName=FolderHelper::GetModuleFileName().c_str();
	logFileName.Replace(_T(".exe"),_T(".log"));
	DeleteFile(logFileName);
}

bool ServiceManager::StartAdminServer()
{
	m_adminServer.SetPort(SERVICE_PROPERTIES_INSTANCE.GetAdminServerPort());
	return m_adminServer.StartServer();
}

void ServiceManager::StopAdminServer()
{
	m_adminServer.StopServer();
}

void ServiceManager::replaceCommandArgument(CString &cmd)
{
	if(cmd.Find(_T("%n"))>=0)
		cmd.Replace(_T("%n"),SERVICE_PROPERTIES_INSTANCE.GetServiceName());
	if(cmd.Find(_T("%N"))>=0)
		cmd.Replace(_T("%N"),SERVICE_PROPERTIES_INSTANCE.GetServiceName());

	CString dateTime=DateTimeHelper::DateTimeToString(DateTimeHelper::GetCurrentDateTime()).c_str();
	if(cmd.Find(_T("%t"))>=0)
		cmd.Replace(_T("%t"),dateTime.GetString());
	if(cmd.Find(_T("%T"))>=0)
		cmd.Replace(_T("%T"),dateTime.GetString());
}

void ServiceManager::RunCustomProcess(int waitTimeInMilliSec)
{
	CString cmd=_T("");

	BaseManagementObject::ParseCommand(SERVICE_PROPERTIES_INSTANCE.GetCustomProcessCommandLine(),m_customProcessCommandLineList);

	for(int listTrav=0;listTrav<m_customProcessCommandLineList.size();listTrav++)
	{
		cmd=m_customProcessCommandLineList.at(listTrav);

		replaceCommandArgument(cmd);

		// start a process with given index
		STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,_T(""),NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
		PROCESS_INFORMATION	pProcInfo;
		startUpInfo.wShowWindow = SW_HIDE;
		startUpInfo.lpDesktop = NULL;

		
		// create the process
		if(CreateProcess(NULL, const_cast<TCHAR*>( cmd.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
		{
			WaitForSingleObject(pProcInfo.hProcess,(DWORD)waitTimeInMilliSec);
			continue;
		}
		else
		{
			TCHAR pTemp[256];
			long nError = GetLastError();

			_stprintf(pTemp,_T("MainService : Failed to start custom-process program(%d) '%s', error code = %d"),listTrav, cmd.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			continue;
		}
		
	}

}
void ServiceManager::RunCommand(CString command, int waitTimeInMilliSec)
{
	CString cmd=_T("");

	vector<CString> cmdList;
	BaseManagementObject::ParseCommand(command,cmdList);

	for(int listTrav=0;listTrav<cmdList.size();listTrav++)
	{
		cmd=cmdList.at(listTrav);

		replaceCommandArgument(cmd);
	
		// start a process with given index
		STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,_T(""),NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
		PROCESS_INFORMATION	pProcInfo;
		startUpInfo.wShowWindow = SW_HIDE;
		startUpInfo.lpDesktop = NULL;


		// create the process
		if(CreateProcess(NULL, const_cast<TCHAR*>( cmd.GetString()),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS, NULL,NULL,&startUpInfo,&pProcInfo))
		{
			WaitForSingleObject(pProcInfo.hProcess,(DWORD)waitTimeInMilliSec);
			continue;
		}
		else
		{
			TCHAR pTemp[256];
			long nError = GetLastError();

			_stprintf(pTemp,_T("MainService : Failed to run command(%d) '%s', error code = %d"),listTrav, cmd.GetString(), nError); 
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
			continue;
		}

	}
}
void WINAPI ServiceHandler(DWORD fdwControl)
{
	switch(fdwControl) 
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwWin32ExitCode = 0; 
		SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCurrentState  = SERVICE_STOPPED; 
		SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCheckPoint    = 0; 
		SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwWaitHint      = 0;
		// terminate all processes started by this service before shutdown
		for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
		{
			PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
		}
		if(SERVICE_PROPERTIES_INSTANCE.GetUseAdminServer())
		{
			SERVICE_MANAGER_INSTANCE.StopAdminServer();
		}
		break; 
	case SERVICE_CONTROL_PAUSE:
		SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCurrentState = SERVICE_PAUSED; 
		break;
	case SERVICE_CONTROL_CONTINUE:
		SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCurrentState = SERVICE_RUNNING; 
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:

		if((fdwControl&SERVICE_CONTROL_CUSTOM_PROCESS)==SERVICE_CONTROL_CUSTOM_PROCESS)
		{
			unsigned int idx= SERVICE_CONTROL_INDEX&fdwControl;
			if(idx==SERVICE_CONTROL_INDEX)
			{
				for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
				{
					PROCESS_HANDLER_INSTANCE.At(procTrav)->CustomProcess(0);
				}
			}
			else
			{
				PROCESS_HANDLER_INSTANCE.At(idx)->CustomProcess(0);
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("ControlService: Run Custom Process%d"), idx);
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
		}
		else if((fdwControl&SERVICE_CONTROL_PROCESS_END)==SERVICE_CONTROL_PROCESS_END)
		{
			unsigned int idx= SERVICE_CONTROL_INDEX&fdwControl;
			if(idx==SERVICE_CONTROL_INDEX)
			{
				for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
				{
					PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
				}
			}
			else
			{
				PROCESS_HANDLER_INSTANCE.At(idx)->Stop();
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("ControlService: End Process%d"), idx);
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
		}
		else if((fdwControl&SERVICE_CONTROL_PROCESS_BOUNCE)==SERVICE_CONTROL_PROCESS_BOUNCE)
		{
			unsigned int idx= SERVICE_CONTROL_INDEX&fdwControl;
			if(idx==SERVICE_CONTROL_INDEX)
			{
				for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
				{
					PROCESS_HANDLER_INSTANCE.At(procTrav)->Stop();
				}
				for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
				{
					PROCESS_HANDLER_INSTANCE.At(procTrav)->Start();
				}
			}
			else
			{
				PROCESS_HANDLER_INSTANCE.At(idx)->Stop();
				PROCESS_HANDLER_INSTANCE.At(idx)->Start();
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("ControlService: Bounce Process%d"), idx);
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
		}
		else if((fdwControl&SERVICE_CONTROL_PROCESS_START)==SERVICE_CONTROL_PROCESS_START)
		{
			unsigned int idx= SERVICE_CONTROL_INDEX&fdwControl;

			if(idx==SERVICE_CONTROL_INDEX)
			{
				for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
				{
					PROCESS_HANDLER_INSTANCE.At(procTrav)->Start();
				}
			}
			else
			{
				PROCESS_HANDLER_INSTANCE.At(idx)->Start();
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("ControlService: Start Process%d"), idx);
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
		}
		else
		{
			TCHAR pTemp[121];
			_stprintf(pTemp,  _T("Unrecognized opcode %d"), fdwControl);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		break;
	};
	if (!SetServiceStatus(SERVICE_MANAGER_INSTANCE.GetServiceStatusHandle(),  &SERVICE_MANAGER_INSTANCE.GetServiceStatus())) 
	{ 
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("SetServiceStatus failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	} 
}
void MainServiceStart()
{

	if(_beginthread(ProcMonitorThread, 0, NULL) == -1)
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("ProcMonitorThread failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("ProcMonitorThread started"));
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	if(_beginthread(ServiceMonitorThread, 0, NULL) == -1)
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("ServiceMonitorThread failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("ServiceMonitorThread started"));
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}

	for(int procTrav=0;procTrav<PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();procTrav++)
	{
		if(PROCESS_HANDLER_INSTANCE.At(procTrav)->Start())
		{
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("Process%d started"),procTrav);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}

	if(SERVICE_PROPERTIES_INSTANCE.GetUseAdminServer())
	{
		if(!SERVICE_MANAGER_INSTANCE.StartAdminServer())
		{
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("Unable to start the Admin Server"));
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
	}
}
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	DWORD   status = 0; 
	DWORD   specificError = 0xfffffff; 

	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwServiceType        = SERVICE_WIN32; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCurrentState       = SERVICE_START_PENDING; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwWin32ExitCode      = 0; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwServiceSpecificExitCode = 0; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCheckPoint         = 0; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwWaitHint           = 0; 

	SetLastError(0);
	SERVICE_MANAGER_INSTANCE.GetServiceStatusHandle() = RegisterServiceCtrlHandler(SERVICE_PROPERTIES_INSTANCE.GetServiceName(), ServiceHandler); 
	if (SERVICE_MANAGER_INSTANCE.GetServiceStatusHandle()==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("RegisterServiceCtrlHandler failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
		return; 
	} 

	// Initialization complete - report running status 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCurrentState       = SERVICE_RUNNING; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwCheckPoint         = 0; 
	SERVICE_MANAGER_INSTANCE.GetServiceStatus().dwWaitHint           = 0;  
	if(!SetServiceStatus(SERVICE_MANAGER_INSTANCE.GetServiceStatusHandle(), &SERVICE_MANAGER_INSTANCE.GetServiceStatus())) 
	{ 
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("SetServiceStatus failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	} 

	MainServiceStart();

}


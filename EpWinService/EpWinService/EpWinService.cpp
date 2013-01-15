// EpWinService.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "epServiceProperties.h"
#include "epServiceManager.h"
#include "epProcessHandler.h"
#include "epLogWriter.h"

const int nBufferSize = 500;
TCHAR *lpCmdLineData;
TCHAR *lpCmdLineOption;
VOID ServiceMainProc();

int _tmain(int argc, _TCHAR* argv[])
{
	lpCmdLineData=new TCHAR[nBufferSize+1];
	lpCmdLineOption=new TCHAR[nBufferSize+1];
	if(argc >= 1)
	{
		_tcscpy(lpCmdLineData, argv[1]);

		if(_tcsicmp(_T("-b"),lpCmdLineData) == 0 || _tcsicmp(_T("-B"),lpCmdLineData) == 0
			||_tcsicmp(_T("-r"),lpCmdLineData) == 0 || _tcsicmp(_T("-R"),lpCmdLineData) == 0
			||_tcsicmp(_T("-n"),lpCmdLineData) == 0 || _tcsicmp(_T("-N"),lpCmdLineData) == 0
			||_tcsicmp(_T("-c"),lpCmdLineData) == 0 || _tcsicmp(_T("-C"),lpCmdLineData) == 0)
		{
			if(argc!=3)
			{
				_tprintf(_T("USAGE ERROR\n"));
				_tprintf(_T("USAGE: EpWinService <Command:-b/-r/-n/-c> <Process Index>\n"));
				_tprintf(_T("Command:-b (Bounce the process)\n"));
				_tprintf(_T("Command:-r (Start the process)\n"));
				_tprintf(_T("Command:-n (End the process)\n"));
				_tprintf(_T("Command:-c (Run the custom process)\n"));
				_tprintf(_T("Process Index:The index of the process to give the command (-1 for all processes)\n\n"));
				return 0;
			}
			_tcscpy(lpCmdLineOption,argv[2]);
		}
	}
	else
	{
		_tprintf(_T("USAGE ERROR\n"));
		_tprintf(_T("USAGE: EpWinService <Command:-i/-s/-k/-u/-e/-b/-r/-n/-c> <Optional:Process Index>\n"));
		_tprintf(_T("Command:-i (Install Service)\n"));
		_tprintf(_T("Command:-s (Start Service)\n"));
		_tprintf(_T("Command:-k (Stop Service)\n"));
		_tprintf(_T("Command:-u (Uninstall Service)\n"));
		_tprintf(_T("Command:-e (Execute Service)\n"));
		_tprintf(_T("Command:-b (Bounce the process)\n"));
		_tprintf(_T("Command:-r (Start the process)\n"));
		_tprintf(_T("Command:-n (End the process)\n"));
		_tprintf(_T("Command:-c (Run the custom process)\n"));
		_tprintf(_T("Process Index:The index of the process to give the command (-1 for all processes)\n\n"));
		return 0;
	}
	ServiceMainProc();
	delete[] lpCmdLineData;
	delete[] lpCmdLineOption;

	return 0;
}

VOID ServiceMainProc()
{
	SERVICE_PROPERTIES_INSTANCE;
	SERVICE_MANAGER_INSTANCE;
	PROCESS_HANDLER_INSTANCE;
	LOG_WRITER_INSTANCE;


	// initialize variables for .exe and .log file names
	if(_tcsicmp(_T("-i"),lpCmdLineData) == 0 || _tcsicmp(_T("-I"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.Install();
	else if(_tcsicmp(_T("-s"),lpCmdLineData) == 0 || _tcsicmp(_T("-S"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.RunService();
	else if(_tcsicmp(_T("-k"),lpCmdLineData) == 0 || _tcsicmp(_T("-K"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.KillService();
	else if(_tcsicmp(_T("-u"),lpCmdLineData) == 0 || _tcsicmp(_T("-U"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.UnInstall();
	else if(_tcsicmp(_T("-e"),lpCmdLineData) == 0 || _tcsicmp(_T("-E"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.ExecuteSubProcess();	

	else if(_tcsicmp(_T("-b"),lpCmdLineData) == 0 || _tcsicmp(_T("-B"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.BounceProcess(_ttoi(lpCmdLineOption));
	else if(_tcsicmp(_T("-r"),lpCmdLineData) == 0 || _tcsicmp(_T("-R"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.StartProcess(_ttoi(lpCmdLineOption));	
	else if(_tcsicmp(_T("-n"),lpCmdLineData) == 0 || _tcsicmp(_T("-N"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.EndProcess(_ttoi(lpCmdLineOption));	
	else if(_tcsicmp(_T("-c"),lpCmdLineData) == 0 || _tcsicmp(_T("-C"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.CustomProcess(_ttoi(lpCmdLineOption));	

}
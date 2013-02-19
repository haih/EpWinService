/*! 
EpWinService for the EpWinService
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
	_tprintf(_T("\n"));
	_tprintf(_T("*********************************************************************\n"));
	_tprintf(_T("EpWinService is a Visual C++ framework that supports making multiple\n   custom applications as Windows Services under a GPL3.0 license.\n"));
	_tprintf(_T("Copyright (C) 2013  Woong Gyu La <juhgiyo@gmail.com>\n\n"));
	_tprintf(_T("This program is free software: you can redistribute it and/or modify\n"));
	_tprintf(_T("it under the terms of the GNU General Public License as published by\n"));
	_tprintf(_T("the Free Software Foundation, either version 3 of the License, or\n"));
	_tprintf(_T("(at your option) any later version.\n\n"));
	_tprintf(_T("This program is distributed in the hope that it will be useful,\n"));
	_tprintf(_T("but WITHOUT ANY WARRANTY; without even the implied warranty of\n"));
	_tprintf(_T("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"));
	_tprintf(_T("GNU General Public License for more details.\n\n"));
	_tprintf(_T("You should have received a copy of the GNU General Public License\n"));
	_tprintf(_T("along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"));
	_tprintf(_T("*********************************************************************\n"));
	_tprintf(_T("\n\n"));

	lpCmdLineData=EP_NEW TCHAR[nBufferSize+1];
	lpCmdLineOption=EP_NEW TCHAR[nBufferSize+1];
	if(argc > 1)
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
				_tprintf(_T("USAGE: EpWinService <Command:-b/-r/-n/-c> <Process Index:-1~31>\n"));
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
		_tprintf(_T("USAGE1: EpWinService <Command:-i/-s/-k/-u/-e/-t>\n"));
		_tprintf(_T("USAGE2: EpWinService <Command:-e/-b/-r/-n/-c> <Optional:Process Index:-1~31>\n"));
		_tprintf(_T("Command:-i (Install Service)\n"));
		_tprintf(_T("Command:-s (Start Service)\n"));
		_tprintf(_T("Command:-k (Stop Service)\n"));
		_tprintf(_T("Command:-u (Uninstall Service)\n"));
		_tprintf(_T("Command:-e (Execute Service)\n"));
		_tprintf(_T("Command:-t (Test Service)\n"));
		_tprintf(_T("Command:-b <Process Index:-1~31>(Bounce the process)\n"));
		_tprintf(_T("Command:-r <Process Index:-1~31>(Start the process)\n"));
		_tprintf(_T("Command:-n <Process Index:-1~31>(End the process)\n"));
		_tprintf(_T("Command:-c <Process Index:-1~31>(Run the custom process)\n"));
		_tprintf(_T("Process Index:The index of the process to give the command (-1 for all processes)\n\n"));
		EP_DELETE[] lpCmdLineData;
		EP_DELETE[] lpCmdLineOption;
		return 0;
	}
	ServiceMainProc();
	EP_DELETE[] lpCmdLineData;
	EP_DELETE[] lpCmdLineOption;

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
	else if(_tcsicmp(_T("-t"),lpCmdLineData) == 0 || _tcsicmp(_T("-T"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.TestSubProcess();	

	else if(_tcsicmp(_T("-b"),lpCmdLineData) == 0 || _tcsicmp(_T("-B"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.BounceProcess(_ttoi(lpCmdLineOption));
	else if(_tcsicmp(_T("-r"),lpCmdLineData) == 0 || _tcsicmp(_T("-R"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.StartProcess(_ttoi(lpCmdLineOption));	
	else if(_tcsicmp(_T("-n"),lpCmdLineData) == 0 || _tcsicmp(_T("-N"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.EndProcess(_ttoi(lpCmdLineOption));	
	else if(_tcsicmp(_T("-c"),lpCmdLineData) == 0 || _tcsicmp(_T("-C"),lpCmdLineData) == 0)
		SERVICE_MANAGER_INSTANCE.CustomProcess(_ttoi(lpCmdLineOption));	

}
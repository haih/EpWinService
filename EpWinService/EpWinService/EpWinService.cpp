/*! 
EpWinService for the EpWinService

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
	_tprintf(_T("EpWinService is a Visual C++ framework that supports making multiple\n   custom applications as Windows Services under a MIT license.\n\n"));
	_tprintf(_T("Copyright (C) 2013  Woong Gyu La <juhgiyo@gmail.com>\n"));
	_tprintf(_T("            <http://github.com/juhgiyo/epWinService>\n\n"));
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
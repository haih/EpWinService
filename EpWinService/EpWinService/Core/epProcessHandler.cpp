/*! 
ProcessHandler for the EpWinService

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
#include "epProcessHandler.h"
#include "epLogWriter.h"
#include "epServiceProperties.h"

ProcessObject *&ProcessHandler::At(unsigned int procIndex)
{
	return m_processList.at(procIndex);
}

ProcessHandler::ProcessHandler()
{
	CString iniFileName=FolderHelper::GetModuleFileName().c_str();
	iniFileName.Replace(_T(".exe"),_T(".ini"));
	TCHAR *textBuffer=EP_NEW TCHAR[MAX_STRING_LENGTH];

	int procIndex=0;

	while(1)
	{
		CString processString=_T("Process");
		processString.AppendFormat(_T("%d"),procIndex);

		memset(textBuffer,0,sizeof(TCHAR)*MAX_STRING_LENGTH);
		GetPrivateProfileString(processString.GetString(),_T("CommandLine"),_T(""),textBuffer,MAX_STRING_LENGTH,iniFileName.GetString());
		CString commandLine=textBuffer;
		if(commandLine.GetLength()>0)
		{
			ProcessObject *newObj=EP_NEW ProcessObject(procIndex);
			m_processList.push_back(newObj);
		}
		else
			break;
		procIndex++;
	}
	EP_DELETE[] textBuffer;


	

}
ProcessHandler::~ProcessHandler()
{

	vector<ProcessObject*>::iterator iter;
	for(iter=m_processList.begin();iter!=m_processList.end();iter++)
	{
		delete (*iter);
	}
}

VOID ProcMonitorThread(VOID *)
{
	unsigned int checkProcessTime=SERVICE_PROPERTIES_INSTANCE.GetCheckProcessInterval();
	unsigned int processSize=PROCESS_HANDLER_INSTANCE.GetNumberOfProcesses();
	while(checkProcessTime)
	{
		Sleep(checkProcessTime);
		for(int procTrav=0;procTrav<processSize;procTrav++)
		{
			DWORD dwCode;
			if(PROCESS_HANDLER_INSTANCE.At(procTrav)->GetExitCodeProcess(&dwCode))
			{

				if(dwCode!=STILL_ACTIVE)
				{
					PROCESS_HANDLER_INSTANCE.At(procTrav)->PostProcess();
					PROCESS_HANDLER_INSTANCE.At(procTrav)->Reset();

					if(PROCESS_HANDLER_INSTANCE.At(procTrav)->GetIsRestart())
					{
						if(PROCESS_HANDLER_INSTANCE.At(procTrav)->Start())
						{
							TCHAR pTemp[121];
							_stprintf(pTemp, _T("Process[%d] Restarted"),procTrav);
							LOG_WRITER_INSTANCE.WriteLog( pTemp);
						}
					}
				}
			}
		}		
	}
}

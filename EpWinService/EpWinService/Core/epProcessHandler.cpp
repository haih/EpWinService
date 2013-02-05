/*! 
ProcessHandler for the EpWinService
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
	TCHAR *textBuffer=new TCHAR[MAX_STRING_LENGTH];

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
			ProcessObject *newObj=new ProcessObject(procIndex);
			m_processList.push_back(newObj);
		}
		else
			break;
		procIndex++;
	}


	

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

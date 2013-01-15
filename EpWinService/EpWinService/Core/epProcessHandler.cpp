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
	TCHAR *textBuffer=new TCHAR[MAX_PATH];

	int procIndex=0;

	while(1)
	{
		CString processString=_T("Process");
		processString.AppendFormat(_T("%d"),procIndex);

		memset(textBuffer,0,sizeof(TCHAR)*MAX_PATH);
		GetPrivateProfileString(processString.GetString(),_T("CommandLine"),_T(""),textBuffer,MAX_PATH,iniFileName.GetString());
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

					if(PROCESS_HANDLER_INSTANCE.At(procTrav)->GetIsProcessRestart())
					{
						if(PROCESS_HANDLER_INSTANCE.At(procTrav)->StartProcess())
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

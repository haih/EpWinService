#include "stdafx.h"
#include "epLogWriter.h"


LogWriter::LogWriter()
{
	CString logMutexName=FolderHelper::GetModuleFileName().c_str();
	logMutexName.Replace(_T(".exe"),_T("Mutex"));
	m_mux=new Mutex(logMutexName.GetString());
}

LogWriter::~LogWriter()
{
	if(m_mux)
		delete m_mux;
}

void LogWriter::WriteLog(const  TCHAR* pMsg)
{
	// write error or other information into log file
	EP_ASSERT(m_mux);
	LockObj m_lock(m_mux);
	static CString m_logFileName=_T("");
	if(m_logFileName.Compare(_T(""))==0)
	{
		m_logFileName=FolderHelper::GetModuleFileName().c_str();
		m_logFileName.Replace(_T(".exe"),_T(".log"));
	}
	try
	{
		SYSTEMTIME oT;
		::GetLocalTime(&oT);
		FILE* pLog = _tfopen(m_logFileName,_T("a"));
		_ftprintf(pLog,_T("%02d/%02d/%04d, %02d:%02d:%02d\n    %s\n"),oT.wMonth,oT.wDay,oT.wYear,oT.wHour,oT.wMinute,oT.wSecond,pMsg); 
		fclose(pLog);
	} catch(...) {}
}
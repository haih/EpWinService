/*! 
LogWriter for the EpWinService
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
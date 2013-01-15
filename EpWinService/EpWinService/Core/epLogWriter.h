#ifndef __EP_LOG_WRITER_H__
#define __EP_LOG_WRITER_H__

#include "epl.h"

using namespace epl;

#define LOG_WRITER_INSTANCE epl::SingletonHolder<LogWriter>::Instance()

class LogWriter{
public:
	friend SingletonHolder<LogWriter>;
	
	void WriteLog(const TCHAR* pMsg);

private:
	LogWriter()
	{
		m_mux=new Mutex(_T("LogMutex"));
	}
	~LogWriter()
	{
		if(m_mux)
			delete m_mux;
	}

	Mutex *m_mux;
};
#endif //__EP_LOG_WRITER_H__
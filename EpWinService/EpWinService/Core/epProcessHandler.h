#ifndef __EP_PROCESS_HANDLER_H__
#define __EP_PROCESS_HANDLER_H__

#include "epl.h"
#include <vector>
#include "epProcessObject.h"
#include "Wtsapi32.h"
#include "Winsvc.h"
#include <UserEnv.h>
#include <tlhelp32.h>

#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib,"UserEnv.lib")

using namespace epl;
#define PROCESS_HANDLER_INSTANCE epl::SingletonHolder<ProcessHandler>::Instance()

VOID ProcMonitorThread(VOID *);

class ProcessHandler
{
public:

	friend SingletonHolder<ProcessHandler>;

	ProcessObject *&At(unsigned int procIndex);

	unsigned int GetNumberOfProcesses()
	{
		return m_processList.size();
	}

private:
	ProcessHandler();
	~ProcessHandler();

	vector<ProcessObject*> m_processList;
	
};

#endif //__EP_PROCESS_HANDLER_H__
/*! 
@file epProcessHandler.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Process Handler Interface
@version 1.0

@section LICENSE

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

@section DESCRIPTION

An Interface for Process Handler.

*/
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
/*!
@def PROCESS_HANDLER_INSTANCE
@brief Process Handler Singleton Instance

Macro for the Process Handler Singleton Instance.
*/
#define PROCESS_HANDLER_INSTANCE epl::SingletonHolder<ProcessHandler>::Instance()

/*!
@fn VOID ProcMonitorThread(VOID *)
@brief A Thread Function which monitors the processes' termination or fault.

Monitor the process's termination or fault and restart the process if terminated
*/

VOID ProcMonitorThread(VOID *);

/*! 
@class ProcessHandler epProcessHandler.h
@brief A class for Process Handler.
*/
class ProcessHandler
{
public:

	friend SingletonHolder<ProcessHandler>;

	/*!
	Return the pointer to the process object at given index.
	@param[in] procIndex the index of the process object to retrieve
	@return the pointer to the process object
	*/
	ProcessObject *&At(unsigned int procIndex);

	/*!
	Return the number of processes handling.
	@return number of processes in the list
	*/
	unsigned int GetNumberOfProcesses() const
	{
		return static_cast<unsigned int>(m_processList.size());
	}

private:
	/*!
	Default Constructor

	Initializes the Process Handler
	*/
	ProcessHandler();

	/*!
	Default Destructor

	Destroy the Process Handler
	*/
	~ProcessHandler();

	/// Process List
	vector<ProcessObject*> m_processList;
	
};

#endif //__EP_PROCESS_HANDLER_H__
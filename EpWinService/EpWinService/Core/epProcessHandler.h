/*! 
@file epProcessHandler.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Process Handler Interface
@version 1.0

@section LICENSE

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
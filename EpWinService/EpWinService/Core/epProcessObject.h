/*! 
@file epProcessObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Process Object Interface
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

An Interface for Process Object.

*/
#ifndef __EP_PROCESS_OBJECT_H__
#define __EP_PROCESS_OBJECT_H__

#include "epBaseManagementObject.h"

/*! 
@class ProcessObject epProcessObject.h
@brief A class for Process Object.
*/
class ProcessObject:public BaseManagementObject
{

public:
	/*!
	Default Constructor

	Initializes the Process Object
	@param[in] procIndex the index of this process object
	*/
	ProcessObject(unsigned int procIndex);

	/*!
	Default Destructor

	Destroy the Process Object
	*/
	virtual ~ProcessObject();


	/*!
	Return whether this process is started or not
	@return true if started, otherwise false
	*/
	virtual bool IsStarted();

	/*!
	Reset the process to start again
	*/
	virtual void Reset();

	/*!
	Get Exit code of the process
	@param[out] dwCode the exit code
	@return true if exit code is successfully retrieved, otherwise false
	*/
	BOOL GetExitCodeProcess(DWORD *dwCode);

	/*!
	Start the custom-Process.
	@param[in] waitTimeInMilliSec wait time in milli-seconds
	@remark waitTimeInMilliSec is equal to WAITTIME_INIFINITE (0xffffffff) then waits for infinite time.
	*/
	virtual void CustomProcess(int waitTimeInMilliSec);

	/*!
	Run command.
	@param[in] command command to run
	@param[in] waitTimeInMilliSec wait time in milli-seconds
	@remark waitTimeInMilliSec is equal to WAITTIME_INIFINITE (0xffffffff) then waits for infinite time.
	*/
	virtual void RunCommand(CString command, int waitTimeInMilliSec);

	/*!
	Get CommandLine of the process
	@return CommandLine of the process
	*/
	CString GetCommandLine();
	
	/*!
	Set CommandLine of the process
	@param[in] cmd CommandLine of the process
	*/
	void SetCommandLine(CString cmd);



	

private:

	
	/*!
	Start the Process.
	@return true if started, otherwise false
	*/
	virtual bool start();

	/*!
	Stop the Process.
	*/
	virtual void stop();

	/*!
	Replace the given command's arguments
	@param[in] cmd the single command to replace
	@remark "%t" or "%T" refers to current time <br/>
			"%x" or "%X" refers to object index <br/>
			"%o" or "%o" refers to object type <br/>
			"%p" or "%P" refers to Process ID <br/>
	*/
	virtual void replaceCommandArgument(CString &cmd);

	/// Process Information (internal use)
	PROCESS_INFORMATION	m_pProcInfo;

	/// CommandLine
	CString m_commandLine;


};
#endif //__EP_PROCESS_OBJECT_H__
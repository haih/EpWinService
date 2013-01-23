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

/*! 
@class ProcessObject epProcessObject.h
@brief A class for Process Object.
*/
class ProcessObject{

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
	~ProcessObject();

	static void ParseCommand(CString cmd, vector<CString>& retCmdList);
	/*!
	Start the Process.
	@return true if started, otherwise false
	*/
	bool StartProcess();

	/*!
	End the Process.
	*/
	void EndProcess();

	/*!
	Start the post-Process.
	*/
	void PostProcess();

	/*!
	Start the custom-Process.
	*/
	void CustomProcess();

	/*!
	Return whether this process is started or not
	@return true if started, otherwise false
	*/
	bool IsProcessStarted();

	/*!
	Reset the process to start again
	*/
	void Reset();

	/*!
	Get Exit code of the process
	@param[out] dwCode the exit code
	@return true if exit code is successfully retrieved, otherwise false
	*/
	BOOL GetExitCodeProcess(DWORD *dwCode);


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

	/*!
	Get delay start time of the process
	@return delay start time of the process
	*/
	unsigned int GetDelayStartTime();
	/*!
	Set delay start time of the process
	@param[in] timeInMilli delay start time of the process
	*/
	void SetDelayStartTime(unsigned int timeInMilli);

	/*!
	Get delay pause/end time of the process
	@return delay start time of the process
	*/
	unsigned int GetDelayPauseEndTime();
	/*!
	Set delay pause/end time of the process
	@param[in] timeInMilli delay start time of the process
	*/
	void SetDelayPauseEndTime(unsigned int timeInMilli);

	/*!
	Get restart when fault/termination flag
	@return true if restart when fault/termination otherwise false
	*/
	bool GetIsProcessRestart();

	/*!
	Set restart when fault/termination flag
	@param[in] isRestart restart when fault/termination flag
	*/
	void SetIsProcessRestart(bool isRestart);

	/*!
	Get Pre-process CommandLine of the process
	@return Pre-process CommandLine of the process
	*/
	CString GetPreProcessCommandLine();
	/*!
	Set Pre-process CommandLine of the process
	@param[in] cmd Pre-process CommandLine of the process
	*/
	void SetPreProcessCommandLine(CString cmd);
	
	/*!
	Get Post-process CommandLine of the process
	@return Post-process CommandLine of the process
	*/
	CString GetPostProcessCommandLine();
	/*!
	Set Post-process CommandLine of the process
	@param[in] cmd Post-process CommandLine of the process
	*/
	void SetPostProcessCommandLine(CString cmd);

	/*!
	Get Custom-process CommandLine of the process
	@return Custom-process CommandLine of the process
	*/
	CString GetCustomProcessCommandLine();
	/*!
	Set Custom-process CommandLine of the process
	@param[in] cmd Custom-process CommandLine of the process
	*/
	void SetCustomProcessCommandLine(CString cmd);

	/*!
	Get Impersonation flag
	@return true if Impersonation otherwise false
	*/
	bool GetIsImpersonate();
	/*!
	Set Impersonation flag
	@param[in] isImpersonate Impersonation flag
	@remark Impersonation flag must be set before User-Interface flag for correct operation
	@remark Impersonation flag must be false to use User-Interface
	*/
	void SetIsImpersonate(bool isImpersonate);

	/*!
	Get User-Interface flag
	@return true if User-Interface otherwise false
	*/
	bool GetIsUserInterface();
	/*!
	Set User-Interface flag
	@param[in] isUserInterface User-Interface flag
	@remark Impersonation flag must be set before User-Interface flag for correct operation
	@remark Impersonation flag must be false to use User-Interface
	*/
	void SetIsUserInterface(bool isUserInterface);

	/*!
	Get Domain Name of the process
	@return Domain Name of the process
	*/
	CString GetDomainName();
	/*!
	Set Domain Name of the process
	@param[in] domainName Domain Name of the process
	*/
	void SetDomainName(CString domainName);

	/*!
	Get UserName of the process
	@return UserName of the process
	*/
	CString GetUserName();
	/*!
	Set UserName of the process
	@param[in] userName UserName of the process
	*/
	void SetUserName(CString userName);

	/*!
	Get User Password of the process
	@return User Password of the process
	*/
	CString GetUserPassword();
	/*!
	Set User Password of the process
	@param[in] userPassword User Password of the process
	*/
	void SetUserPassword(CString userPassword);


private:
	/*!
	Actually start the post-Process.
	*/
	void postProcess();
	
	/*!
	Start the pre-Process.
	*/
	void preProcess();

	/// Process Object's index
	unsigned int m_procIndex;
	
	/// Process Information (internal use)
	PROCESS_INFORMATION	m_pProcInfo;

	/// CommandLine
	CString m_commandLine;
	/// Delay start time
	unsigned int m_delayStartTime;
	/// Delay pause/end time
	unsigned int m_delayPauseEndTime;
	/// Restart when termination/fault
	bool m_isRestart;
	/// Pre-process CommandLine List
	vector<CString> m_preProcessCommandLineList;
	/// Post-process CommandLine List
	vector<CString> m_postProcessCommandLineList;
	/// Custom-process CommandLine List
	vector<CString> m_customProcessCommandLineList;

	/// Pre-process CommandLine
	CString m_preProcessCommandLine;
	/// Post-process CommandLine
	CString m_postProcessCommandLine;
	/// Custom-process CommandLine
	CString m_customProcessCommandLine;

	/// Impersonation flag
	bool m_isImpersonate;
	/// User-Interface flag
	bool m_isUserInterface;
	/// Domain Name
	CString m_domainName;
	/// Username
	CString m_userName;
	/// User Password
	CString m_userPassword;

	/// Lock
	CriticalSectionEx m_lock;
	/// INI Filename
	CString m_iniFileName;
	/// Process Name in INI File (Internal use)
	CString m_processString;

};
#endif //__EP_PROCESS_OBJECT_H__
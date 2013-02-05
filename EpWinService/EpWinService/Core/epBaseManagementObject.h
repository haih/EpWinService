/*! 
@file epBaseManagementObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Base Management Object Interface
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

An Interface for Base Management Object.

*/
#ifndef __EP_BASE_MANAGEMENT_OBJECT_H__
#define __EP_BASE_MANAGEMENT_OBJECT_H__


/// Management Object Type
typedef enum _managementObjectType{
	/// Process Type
	MANAGEMENT_OBJECT_TYPE_PROCESS=0,
	/// Service Type
	MANAGEMENT_OBJECT_TYPE_SERVICE
}ManagementObjectType;


/*! 
@class BaseManagementObject epBaseManagementObject.h
@brief A class for Base Management Object.
*/
class BaseManagementObject{

public:
	/*!
	Default Constructor

	Initializes the Base Management Object
	@param[in] objType the management object type
	@param[in] objIndex the index of this base management object
	*/
	BaseManagementObject(ManagementObjectType objType,unsigned int objIndex);

	/*!
	Default Destructor

	Destroy the Base Management Object
	*/
	virtual ~BaseManagementObject();

	/*!
	Parser the command given to list of the commands
	@param[in] cmd the command to parse
	@param[out] retCmdList the list of the command parsed
	*/
	static void ParseCommand(CString cmd, vector<CString>& retCmdList);
	/*!
	Start the object.
	@return true if started, otherwise false
	*/
	virtual bool Start()=0;

	/*!
	End the object.
	*/
	virtual void Stop()=0;

	/*!
	Start the post-Process.
	*/
	void PostProcess();

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
	Return whether this object is started or not
	@return true if started, otherwise false
	*/
	virtual bool IsStarted()=0;

	/*!
	Reset the object to start again
	*/
	virtual void Reset()=0;

	
	/*!
	Get restart when fault/termination flag
	@return true if restart when fault/termination otherwise false
	*/
	bool GetIsRestart();

	/*!
	Set restart when fault/termination flag
	@param[in] isRestart restart when fault/termination flag
	*/
	void SetIsRestart(bool isRestart);

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
	Return Pre-Process wait time in milliseconds
	@return wait time in milliseconds
	@remark WAITTIME_INIFINITE means waiting infinitely
	*/
	int GetPreProcessWaitTime();
	/*!
	Return Post-Process wait time in milliseconds
	@return wait time in milliseconds
	@remark WAITTIME_INIFINITE means waiting infinitely
	*/
	int GetPostProcessWaitTime();

	/*!
	Set Pre-Process wait time
	@param[in] waitTimeinMilliSec wait time in milliseconds
	@remark waitTimeinMilliSec==WAITTIME_INIFINITE means waiting infinitely
	*/
	void SetPreProcessWaitTime(int waitTimeinMilliSec);
	/*!
	Set Post-Process  wait time
	@param[in] waitTimeinMilliSec wait time in milliseconds
	@remark waitTimeinMilliSec==WAITTIME_INIFINITE means waiting infinitely
	*/
	void SetPostProcessWaitTime(int waitTimeinMilliSec);

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

protected:
	/*!
	Actually start the post-Process.
	*/
	void postProcess();
	
	/*!
	Start the pre-Process.
	*/
	void preProcess();

	/// Object's index
	unsigned int m_objIndex;
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

	/// Pre-Process wait time in milli-seconds
	int m_preProcessWaitTime;
	/// Post-Process wait time in milli-seconds
	int m_postProcessWaitTime;
		
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

	/// Delay start time
	unsigned int m_delayStartTime;
	/// Delay pause/end time
	unsigned int m_delayPauseEndTime;

	/// Lock
	CriticalSectionEx m_lock;
	/// INI Filename
	CString m_iniFileName;
	/// Object Name in INI File (Internal use)
	CString m_objectString;

	/// Management Object Type
	ManagementObjectType m_objType;

};
#endif //__EP_BASE_MANAGEMENT_OBJECT_H__
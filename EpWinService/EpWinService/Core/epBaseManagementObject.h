/*! 
@file epBaseManagementObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Base Management Object Interface
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

An Interface for Base Management Object.

*/
#ifndef __EP_BASE_MANAGEMENT_OBJECT_H__
#define __EP_BASE_MANAGEMENT_OBJECT_H__

#include "epBaseDeployObject.h"
/// Management Object Type
typedef enum _managementObjectType{
	/// Process Type
	MANAGEMENT_OBJECT_TYPE_PROCESS=0,
	/// Service Type
	MANAGEMENT_OBJECT_TYPE_SERVICE
}ManagementObjectType;

/// Execute Command Type
typedef enum _executeCommandType{
	/// Pre-Process Type
	EXECUTE_COMMAND_TYPE_PREPROCESS=0,
	/// Post-Process Type
	EXECUTE_COMMAND_TYPE_POSTPROCESS,
	/// Custom-Process Type
	EXECUTE_COMMAND_TYPE_CUSTOMPROCESS,
	/// Run-Command Type
	EXECUTE_COMMAND_TYPE_RUNCOMMAND,
}ExecuteCommandType;

/// Object Start Status
typedef enum _objectStartStatus{
	/// Success
	OBJECT_START_STATUS_SUCCESS=0,
	/// Failed due to object started already
	OBJECT_START_STATUS_FAILED_ALREADY_STARTED,
	/// Failed due to log on failure
	OBJECT_START_STATUS_FAILED_LOGON_FAILED,
	/// Failed to start the object
	OBJECT_START_STATUS_FAILED,
	/// Stopped by user (for Deploy Use Only)
	OBJECT_START_STATUS_STOPPED,
}ObjectStartStatus;

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
	@return ObjectStartStatus
	*/
	ObjectStartStatus Start();

	/*!
	End the object.
	*/
	void Stop();

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

	/*!
	Get Ini Filename
	@return Ini Filename
	*/
	CString GetIniFileName();

	/*!
	Get Object String
	@return Object String
	*/
	CString GetObjectString();

	
	/*!
	Deploy the Local path as given revision
	@param[in] properties the properties
	@param[out] retRevNum the revision after the update
	@param[out] retStartStatus the start status of the object
	@param[in] rev the revision to be updated to
	@return the Deploy Error Code
	@remark if rev is REVISION_UNKNOWN then Local path is updated to latest revision
	*/
	DeployErrCode Deploy(unsigned int & retRevNum,ObjectStartStatus &retStartStatus,int rev=REVISION_UNKNOWN);

	/*!
	Return the current revision of the local path
	@param[out] retRevNum the current revision of the local path
	@return the Deploy Error Code
	*/
	DeployErrCode GetCurrentRevision(unsigned int & retRevNum);

	/*!
	Return the latest revision of the repository
	@param[out] retRevNum the latest revision of the repository
	@return the Deploy Error Code
	*/
	DeployErrCode GetLatestRevision(unsigned int & retRevNum);

	/*!
	Get the Deploy repository URL
	@return the Deploy repository URL
	*/
	const TCHAR *GetDeployRepositoryURL();

	/*!
	Get the Deploy local path
	@return the Deploy local path
	*/
	const TCHAR *GetDeployLocalPath();

	/*!
	Get the Deploy Username
	@return the Username
	*/
	const TCHAR *GetDeployUserName();

	/*!
	Get the User Password
	@return the User Password
	*/
	const TCHAR *GetDeployUserPassword();

	/*!
	Set Repository URL
	@param[in] reposURL Repository URL
	*/
	void SetDeployRepositoryURL(CString reposURL);

	/*!
	Set Local Path
	@param[in] localPath Local Path
	*/
	void SetDeployLocalPath(CString localPath);

	/*!
	Set User Name
	@param[in] userName User Name
	*/
	void SetDeployUserName(CString userName);

	/*!
	Set User Password
	@param[in] userPass User Password
	*/
	void SetDeployUserPassword(CString userPass);
protected:

	/*!
	Start the object.
	@return ObjectStartStatus
	*/
	virtual ObjectStartStatus start()=0;

	/*!
	End the object.
	*/
	virtual void stop()=0;
	/*!
	Run a single command given.
	@param[in] command a single command to run
	@param[in] cmdIdx the index of the command
	@param[in] waitTimeInMilliSec wait time for the run in milliseconds
	@param[in] execCommandType the executing command type
	*/
	void executeCommand(CString command,unsigned int cmdIdx, int waitTimeInMilliSec,ExecuteCommandType execCommandType);

	/*!
	Replace the given command's arguments
	@param[in] cmd the single command to replace
	@remark "%t" or "%T" refers to current time <br/>
			"%x" or "%X" refers to object index <br/>
			"%o" or "%o" refers to object type <br/>
	*/
	virtual void replaceCommandArgument(CString &cmd);

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
	CriticalSectionEx m_baseObjLock;
	/// INI Filename
	CString m_iniFileName;
	/// Object Name in INI File (Internal use)
	CString m_objectString;

	/// Management Object Type
	ManagementObjectType m_objType;

	/// Deploy Object
	BaseDeployObject *m_deployObj;

};
#endif //__EP_BASE_MANAGEMENT_OBJECT_H__
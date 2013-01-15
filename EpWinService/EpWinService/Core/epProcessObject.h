#ifndef __EP_PROCESS_OBJECT_H__
#define __EP_PROCESS_OBJECT_H__

class ProcessObject{

public:
	ProcessObject(unsigned int procIndex);

	~ProcessObject();

	bool StartProcess();

	void EndProcess();

	void PostProcess();

	void CustomProcess();

	bool IsProcessStarted();

	void Reset();

	BOOL GetExitCodeProcess(DWORD *dwCode);


	CString GetCommandLine();
	void SetCommandLine(CString cmd);

	unsigned int GetDelayStartTime();
	void SetDelayStartTime(unsigned int timeInMilli);

	unsigned int GetDelayPauseEndTime();
	void SetDelayPauseEndTime(unsigned int timeInMilli);

	bool GetIsProcessRestart();
	void SetIsProcessRestart(bool isRestart);

	CString GetPreProcessCommandLine();
	void SetPreProcessCommandLine(CString cmd);
	
	CString GetPostProcessCommandLine();
	void SetPostProcessCommandLine(CString cmd);

	void SetCustomProcessCommandLine(CString cmd);
	CString GetCustomProcessCommandLine();

	bool GetIsImpersonate();
	void SetIsImpersonate(bool isImpersonate);

	bool GetIsUserInterface();
	void SetIsUserInterface(bool isUserInterface);

	CString GetDomainName();
	void SetDomainName(CString domainName);

	CString GetUserName();
	void SetUserName(CString userName);

	CString GetUserPassword();
	void SetUserPassword(CString userPassword);


private:

	void postProcess();
	
	void preProcess();

	unsigned int m_procIndex;
	
	PROCESS_INFORMATION	m_pProcInfo;

	CString m_commandLine;
	unsigned int m_delayStartTime;
	unsigned int m_delayPauseEndTime;
	bool m_isRestart;
	CString m_preProcessCommandLine;
	CString m_postProcessCommandLine;
	CString m_customProcessCommandLine;

	bool m_isImpersonate;
	bool m_isUserInterface;
	CString m_domainName;
	CString m_userName;
	CString m_userPassword;


	CriticalSectionEx m_lock;
	CString m_iniFileName;
	CString m_processString;

};
#endif //__EP_PROCESS_OBJECT_H__
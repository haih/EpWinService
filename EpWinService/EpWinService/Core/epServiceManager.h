#ifndef __EP_SERVICE_MANAGER_H__
#define __EP_SERVICE_MANAGER_H__
#include "epl.h"
#include "epProcessHandler.h"
#include "epAdminServer.h"
using namespace epl;
#define SERVICE_MANAGER_INSTANCE epl::SingletonHolder<ServiceManager>::Instance()


class ServiceManager{
public:

	friend SingletonHolder<ServiceManager>;

	void ExecuteSubProcess();

	bool CustomProcess(int idx);
	bool EndProcess(int idx);
	bool StartProcess(int idx);
	bool BounceProcess(int idx);

	bool RunService();
	bool KillService();
	void Install();
	void UnInstall();

	bool StartAdminServer();
	void StopAdminServer();

	SERVICE_STATUS &GetServiceStatus()
	{
		return m_serviceStatus;
	}

	SERVICE_STATUS_HANDLE &GetServiceStatusHandle()
	{
		return m_hServiceStatusHandle;
	}
private:

	ServiceManager(){
	}
	~ServiceManager(){}

	SERVICE_STATUS          m_serviceStatus; 
	SERVICE_STATUS_HANDLE   m_hServiceStatusHandle; 

	AdminServer m_adminServer;


};

#endif //__EP_SERVICE_MANAGER_H__
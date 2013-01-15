#ifndef __EP_SERVICE_PROPERTIES_H__
#define __EP_SERVICE_PROPERTIES_H__
#include "epl.h"
using namespace epl;

#define SERVICE_PROPERTIES_INSTANCE epl::SingletonHolder<ServiceProperties>::Instance()

class ServiceProperties 
{
public:
	friend SingletonHolder<ServiceProperties>;

	const TCHAR *GetServiceName();
	const TCHAR *GetDomainName();
	const TCHAR *GetUserName();
	const TCHAR *GetUserPassword();
	const TCHAR *GetDependency();
	CString GetOriginalDependency();

	const unsigned int GetCheckProcessInterval();
	bool GetUseAdminServer();
	const TCHAR *GetAdminServerPort();

	void SetCheckProcessInterval(unsigned int timeInMilli);
private:
	ServiceProperties();
	~ServiceProperties();

	CString m_serviceName;
	CString m_domainName;
	CString m_userName;
	CString m_userPassword;
	CString m_dependency;
	CString m_origDependency;

	unsigned int m_checkProcessInterval;


	bool m_useAdminServer;
	CString m_adminServerPort;

	CriticalSectionEx m_lock;
	CString m_iniFileName;

};
#endif //__EP_SERVICE_PROPERTIES_H__
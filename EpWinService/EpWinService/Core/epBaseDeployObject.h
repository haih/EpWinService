/*! 
@file epBaseDeployObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Base Deploy Object Interface
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

An Interface for Base Deploy Object.

*/
#ifndef __EP_BASE_DEPLOY_OBJECT_H__
#define __EP_BASE_DEPLOY_OBJECT_H__

/// Deploy Error Code
typedef enum _DeployErrCode{
	/// Success
	DEPLOY_ERR_CODE_SUCCESS=0,
	/// Deploy Command Error
	DEPLOY_ERR_CODE_FAIED_SVNCOMMAND,
	/// Deploy Username is NULL
	DEPLOY_ERR_CODE_FAIED_NULL_USERNAME,
	/// Deploy Password is NULL
	DEPLOY_ERR_CODE_FAIED_NULL_PASSWORD,
	/// No Deploy Repository Set
	DEPLOY_ERR_CODE_FAIED_NULL_REPOURL,
	/// No Deploy Local Path Set
	DEPLOY_ERR_CODE_FAIED_NULL_LOCALPATH,
	/// Deploy Cleanup failed
	DEPLOY_ERR_CODE_FAIED_CLEANUP,
}DeployErrCode;

/*!
@def REVISION_UNKNOWN
@brief Revision Unknown Declaration

Macro for the Revision Unknown Param.
*/
#define REVISION_UNKNOWN -1

/*! 
@class BaseDeployObject epBaseDeployObject.h
@brief A class for Base Deploy Object.
*/
class BaseDeployObject
{

public:
	/*!
	Default Constructor

	Initializes the Deploy Object
	*/
	BaseDeployObject(CString objectString, CString iniFileName);

	/*!
	Default Destructor

	Destroy the Deploy Object
	*/
	virtual ~BaseDeployObject();

	/*!
	Get the repository URL
	@return the repository URL
	*/
	const TCHAR *GetRepositoryURL();

	/*!
	Get the local path
	@return the local path
	*/
	const TCHAR *GetLocalPath();

	/*!
	Get the Username
	@return the Username
	*/
	const TCHAR *GetUserName();

	/*!
	Get the User Password
	@return the User Password
	*/
	const TCHAR *GetUserPassword();

	/*!
	Set Repository URL
	@param[in] reposURL Repository URL
	*/
	void SetRepositoryURL(CString reposURL);

	/*!
	Set Local Path
	@param[in] localPath Local Path
	*/
	void SetLocalPath(CString localPath);

	/*!
	Set User Name
	@param[in] userName User Name
	*/
	void SetUserName(CString userName);

	/*!
	Set User Password
	@param[in] userPass User Password
	*/
	void SetUserPassword(CString userPass);

	/*!
	Update the Local path as given revision
	@param[in] properties the properties
	@param[out] retRevNum the revision after the update
	@param[in] rev the revision to be updated to
	@return the Deploy Error Code
	@remark if rev is REVISION_UNKNOWN then Local path is updated to latest revision
	*/
	virtual DeployErrCode Update(unsigned int & retRevNum,int rev=REVISION_UNKNOWN)=0;

	/*!
	Return the current revision of the local path
	@param[out] retRevNum the current revision of the local path
	@return the Deploy Error Code
	*/
	virtual DeployErrCode GetCurrentRevision(unsigned int & retRevNum)=0;

	/*!
	Return the latest revision of the repository
	@param[out] retRevNum the latest revision of the repository
	@return the Deploy Error Code
	*/
	virtual DeployErrCode GetLatestRevision(unsigned int & retRevNum)=0;

	/*!
	Clean up the local path
	@param[in] properties the SVN properties
	@return the Deploy Error Code
	*/
	virtual DeployErrCode CleanUp()=0;
protected:
	/// Repository URL
	CString m_repoURL;
	/// SVN Local Path
	CString m_localPath;
	/// SVN Username
	CString m_userName;
	/// SVN User Password
	CString m_userPassword;


	/// Object String Name for Ini File
	CString m_objectString;
	/// Ini Filename
	CString m_iniFileName;

	/// Lock
	CriticalSectionEx m_deployLock;


};
#endif //__EP_BASE_DEPLOY_OBJECT_H__
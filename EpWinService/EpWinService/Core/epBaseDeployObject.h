/*! 
@file epBaseDeployObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Base Deploy Object Interface
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
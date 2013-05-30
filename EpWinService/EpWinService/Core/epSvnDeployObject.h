/*! 
@file epSvnDeployObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief SVN Deploy Object Interface
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

An Interface for SVN Deploy Object.

*/
#ifndef __EP_SVN_DEPLOY_OBJECT_H__
#define __EP_SVN_DEPLOY_OBJECT_H__
#include "epBaseDeployObject.h"

/*! 
@class SvnDeployObject epSvnDeployObject.h
@brief A class for SVN Deploy Object.
*/
class SvnDeployObject : public BaseDeployObject
{

public:
	/*!
	Default Constructor

	Initializes the Deploy Object
	@param[in] objectString the Object String for INI File
	@param[in] iniFileName the INI Filename
	*/
	SvnDeployObject(CString objectString, CString iniFileName);

	/*!
	Default Destructor

	Destroy the Deploy Object
	*/
	virtual ~SvnDeployObject();


	/*!
	Update the Local path as given revision
	@param[out] retRevNum the revision after the update
	@param[in] rev the revision to be updated to
	@return the Deploy Error Code
	@remark if rev is REVISION_UNKNOWN then Local path is updated to latest revision
	*/
	virtual DeployErrCode Update(unsigned int & retRevNum,int rev=REVISION_UNKNOWN);

	/*!
	Return the current revision of the local path
	@param[out] retRevNum the current revision of the local path
	@return the Deploy Error Code
	*/
	virtual DeployErrCode GetCurrentRevision(unsigned int & retRevNum);

	/*!
	Return the latest revision of the repository
	@param[out] retRevNum the latest revision of the repository
	@return the Deploy Error Code
	*/
	virtual DeployErrCode GetLatestRevision(unsigned int & retRevNum);

	/*!
	Clean up the local path
	@return the Deploy Error Code
	*/
	virtual DeployErrCode CleanUp();
private:
	/*!
	Clean up the local path
	@return the Deploy Error Code
	*/
	DeployErrCode cleanUp();


	/// last SVN Command output
	CString m_lastResult;
};
#endif //__EP_SVN_DEPLOY_OBJECT_H__
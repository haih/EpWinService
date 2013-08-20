/*! 
@file epSvnDeployObject.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief SVN Deploy Object Interface
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
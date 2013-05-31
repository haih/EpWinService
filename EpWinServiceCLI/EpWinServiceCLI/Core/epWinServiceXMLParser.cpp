/*! 
WinServiceXMLParser for the EpWinServiceCLI
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
*/

#include "stdafx.h"
#include "epWinServiceXMLParser.h"
#include "epWinServiceTypeInterpreter.h"


WinServiceXMLParserError WinServiceXMLParser::processMainServiceCommand(MainServiceCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	CString waitTimeString=_T("INFINITE");
	CString cmd=_T("");
	unsigned int waitTime=WAITTIME_INIFINITE;
	XNode * argNode=NULL;
	switch(subCommandType)
	{
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_RUN_COMMAND:
		argNode=root->GetChild(_T("waitTime"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());
		}
		argNode=root->GetChild(_T("runCommand"));
		if(argNode)
		{
			cmd=argNode->GetText();
		}	
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case MAIN_SERVICE_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		argNode=root->GetChild(_T("waitTime"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());
		}
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddCommandMainService(subCommandType,waitTime,cmd.GetString());
	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processMainServiceInfoGet(MainServiceInfoGetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	switch(subCommandType)
	{
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_SERVICE_NAME:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DOMAIN_NAME:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERNAME:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_USERPASSWORD:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_DEPENDENCY:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_PROCESSES:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_NUM_OF_SERVICES:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKPROCESSINTERVAL:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CHECKSERVICEINTERVAL:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
	case MAIN_SERVICE_INFO_GET_PACKET_TYPE_ALL:
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddGetMainServiceInfo(subCommandType);
	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processMainServiceInfoSet(MainServiceInfoSetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	XNode * argNode=NULL;
	MainServiceInfo mainServiceInfo;
	CString waitTimeString=_T("INFINITE");
	unsigned int waitTime=WAITTIME_INIFINITE;
	CString cmd=_T("");
	switch(subCommandType)
	{
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKPROCESSINTERVAL:
		argNode=root->GetChild(_T("interval"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());

		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CHECKSERVICESINTERVAL:
		argNode=root->GetChild(_T("interval"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());

		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case MAIN_SERVICE_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		break;
		argNode=root->GetChild(_T("customCommandLine"));
		if(argNode)
		{
			cmd=argNode->GetText();
		}		
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	mainServiceInfo.m_command=cmd.GetString();
	mainServiceInfo.m_interval=waitTime;
	retPacketGen.AddSetMainServiceInfo(subCommandType,mainServiceInfo);
	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processProcessObjectCommand(ProcessObjectCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	CString waitTimeString=_T("INFINITE");
	unsigned int waitTime=WAITTIME_INIFINITE;
	CString cmd=_T("");
	CString revisionNumString=_T("UNKNOWN");
	int revisionNum=REVISION_UNKNOWN;
	int objIdx=-1;
	XNode * argNode=NULL;

	argNode=root->GetChild(_T("objIndex"));
	if(argNode)
	{
		objIdx=_ttoi(argNode->GetText().GetString());
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
	
	switch(subCommandType)
	{
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_START:
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_END:
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		argNode=root->GetChild(_T("waitTime"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());

		}
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
		argNode=root->GetChild(_T("waitTime"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());

		}
		argNode=root->GetChild(_T("runCommand"));
		if(argNode)
		{
			cmd=argNode->GetText();
		}	
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
		argNode=root->GetChild(_T("revisionNum"));
		if(argNode)
		{
			revisionNumString=argNode->GetText();
			if(revisionNumString.Compare(_T("UNKNOWN"))!=0)
				revisionNum=(int)_ttoi(revisionNumString.GetString());
		}		
		retPacketGen.AddDeployCommandProcessObj(objIdx,revisionNum);
		return retErr;
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddCommandProcessObj(subCommandType,objIdx,waitTime,cmd.GetString());

	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processProcessObjectInfoGet(ProcessObjectInfoGetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	XNode * argNode=NULL;
	unsigned int objIdx=0;
	argNode=root->GetChild(_T("objIndex"));
	if(argNode)
	{
		objIdx=(unsigned int)_ttoi(argNode->GetText().GetString());
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

	switch(subCommandType)
	{
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_COMMANDLINE:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_STATUS:

	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:

	case PROCESS_OBJECT_INFO_GET_PACKET_TYPE_ALL:
		break;
	default:
		break;
	}
	retPacketGen.AddGetProcessInfo(subCommandType,objIdx);
	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processProcessObjectInfoSet(ProcessObjectInfoSetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	XNode * argNode=NULL;

	unsigned int objIdx=0;
	argNode=root->GetChild(_T("objIndex"));
	if(argNode)
	{
		objIdx=(unsigned int)_ttoi(argNode->GetText().GetString());
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

	CString argument;
	ProcessObjInfo procObjInfo;

	switch(subCommandType)
	{
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_COMMANDLINE:
		argNode=root->GetChild(_T("commandLine"));
		if(argNode)
			procObjInfo.m_commandLine=argNode->GetText();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		argNode=root->GetChild(_T("preProcessCommandLine"));
		if(argNode)
			procObjInfo.m_preProcessCommandLine=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		argNode=root->GetChild(_T("postProcessCommandLine"));
		if(argNode)
			procObjInfo.m_postProcessCommandLine=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		argNode=root->GetChild(_T("customProcessCommandLine"));
		if(argNode)
			procObjInfo.m_customProcessCommandLine=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		argNode=root->GetChild(_T("preProcessWaitTime"));
		if(argNode)
		{
			if(argNode->GetText().Compare(_T("INFINITE"))!=0)
				procObjInfo.m_preProcessWaitTime=_ttoi(argNode->GetText().GetString());
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		argNode=root->GetChild(_T("postProcessWaitTime"));
		if(argNode)
		{
			if(argNode->GetText().Compare(_T("INFINITE"))!=0)
				procObjInfo.m_postProcessWaitTime=_ttoi(argNode->GetText().GetString());
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME:
		argNode=root->GetChild(_T("domainName"));
		if(argNode)
			procObjInfo.m_domainName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERNAME:
		argNode=root->GetChild(_T("userName"));
		if(argNode)
			procObjInfo.m_userName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD:
		argNode=root->GetChild(_T("userPassword"));
		if(argNode)
			procObjInfo.m_userPassword=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME:
		argNode=root->GetChild(_T("delayStartTime"));
		if(argNode)
			procObjInfo.m_delayStartTime=(unsigned int)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		argNode=root->GetChild(_T("delayPauseEndTime"));
		if(argNode)
			procObjInfo.m_delayPauseEndTime=(unsigned int)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART:
		argNode=root->GetChild(_T("IsRestart"));
		if(argNode)
		{
			argument=argNode->GetText();
			argument=argument.MakeUpper();
			if(argument.Compare(_T("TRUE")))
				procObjInfo.m_isRestart=true;
			else
				procObjInfo.m_isRestart=false;
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE:
		argNode=root->GetChild(_T("IsImpersonate"));
		if(argNode)
		{
			argument=argNode->GetText();
			argument=argument.MakeUpper();
			if(argument.Compare(_T("TRUE")))
				procObjInfo.m_isImpersonate=true;
			else
				procObjInfo.m_isImpersonate=false;
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE:
		argNode=root->GetChild(_T("IsUserInterface"));
		if(argNode)
		{
			argument=argNode->GetText();
			argument=argument.MakeUpper();
			if(argument.Compare(_T("TRUE")))
				procObjInfo.m_isUserInterface=true;
			else
				procObjInfo.m_isUserInterface=false;
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;

	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL:
		argNode=root->GetChild(_T("deployRepositoryURL"));
		if(argNode)
			procObjInfo.m_deployRepositoryURL=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
		argNode=root->GetChild(_T("deployLocalPath"));
		if(argNode)
			procObjInfo.m_deployLocalPath=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME:
		argNode=root->GetChild(_T("deployUserName"));
		if(argNode)
			procObjInfo.m_deployUserName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD:
		argNode=root->GetChild(_T("deployUserPassword"));
		if(argNode)
			procObjInfo.m_deployUserName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;

	case PROCESS_OBJECT_INFO_SET_PACKET_TYPE_ALL:
		argNode=root->GetChild(_T("All"));
		if(argNode)
		{
			argNode=root->GetChild(_T("commandLine"));
			if(argNode)
				procObjInfo.m_commandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("preProcessCommandLine"));
			if(argNode)
				procObjInfo.m_preProcessCommandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("postProcessCommandLine"));
			if(argNode)
				procObjInfo.m_postProcessCommandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("customProcessCommandLine"));
			if(argNode)
				procObjInfo.m_customProcessCommandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("preProcessWaitTime"));
			if(argNode)
			{
				if(argNode->GetText().Compare(_T("INFINITE"))!=0)
					procObjInfo.m_preProcessWaitTime=_ttoi(argNode->GetText().GetString());
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("postProcessWaitTime"));
			if(argNode)
			{
				if(argNode->GetText().Compare(_T("INFINITE"))!=0)
					procObjInfo.m_postProcessWaitTime=_ttoi(argNode->GetText().GetString());
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("domainName"));
			if(argNode)
				procObjInfo.m_domainName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("userName"));
			if(argNode)
				procObjInfo.m_userName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("userPassword"));
			if(argNode)
				procObjInfo.m_userPassword=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("delayStartTime"));
			if(argNode)
				procObjInfo.m_delayStartTime=(unsigned int)_ttoi(argNode->GetText().GetString());
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("delayPauseEndTime"));
			if(argNode)
				procObjInfo.m_delayPauseEndTime=(unsigned int)_ttoi(argNode->GetText().GetString());
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("IsRestart"));
			if(argNode)
			{
				argument=argNode->GetText();
				argument=argument.MakeUpper();
				if(argument.Compare(_T("TRUE")))
					procObjInfo.m_isRestart=true;
				else
					procObjInfo.m_isRestart=false;
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("IsImpersonate"));
			if(argNode)
			{
				argument=argNode->GetText();
				argument=argument.MakeUpper();
				if(argument.Compare(_T("TRUE")))
					procObjInfo.m_isImpersonate=true;
				else
					procObjInfo.m_isImpersonate=false;
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("IsUserInterface"));
			if(argNode)
			{
				argument=argNode->GetText();
				argument=argument.MakeUpper();
				if(argument.Compare(_T("TRUE")))
					procObjInfo.m_isUserInterface=true;
				else
					procObjInfo.m_isUserInterface=false;
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("deployRepositoryURL"));
			if(argNode)
				procObjInfo.m_deployRepositoryURL=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("deployLocalPath"));
			if(argNode)
				procObjInfo.m_deployLocalPath=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("deployUserName"));
			if(argNode)
				procObjInfo.m_deployUserName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("deployUserPassword"));
			if(argNode)
				procObjInfo.m_deployUserName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddSetProcessInfo(subCommandType,objIdx,procObjInfo);

	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processServiceObjectCommand(ServiceObjectCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	CString waitTimeString=_T("INFINITE");
	unsigned int waitTime=WAITTIME_INIFINITE;
	CString cmd=_T("");
	CString revisionNumString=_T("UNKNOWN");
	int revisionNum=REVISION_UNKNOWN;
	int objIdx=-1;
	XNode * argNode=NULL;
	argNode=root->GetChild(_T("objIndex"));
	if(argNode)
	{
		objIdx=_ttoi(argNode->GetText().GetString());
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

	switch(subCommandType)
	{
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_START:
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_END:
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_PAUSE:
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CONTINUE:
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_BOUNCE:
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_CUSTOM_PROCESS:
		argNode=root->GetChild(_T("waitTime"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());

		}
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_RUN_COMMAND:
		argNode=root->GetChild(_T("waitTime"));
		if(argNode)
		{
			waitTimeString=argNode->GetText();
			if(waitTimeString.Compare(_T("INFINITE"))!=0)
				waitTime=(unsigned int)_ttoi(waitTimeString.GetString());

		}
		argNode=root->GetChild(_T("runCommand"));
		if(argNode)
		{
			cmd=argNode->GetText();
		}	
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_COMMAND_PACKET_TYPE_DEPLOY:
		argNode=root->GetChild(_T("revisionNum"));
		if(argNode)
		{
			revisionNumString=argNode->GetText();
			if(revisionNumString.Compare(_T("UNKNOWN"))!=0)
				revisionNum=(int)_ttoi(revisionNumString.GetString());
		}		
		retPacketGen.AddDeployCommandServiceObj(objIdx,revisionNum);
		return retErr;
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddCommandServiceObj(subCommandType,objIdx,waitTime,cmd.GetString());

	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processServiceObjectInfoGet(ServiceObjectInfoGetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	unsigned int objIdx=0;
	XNode * argNode=NULL;
	argNode=root->GetChild(_T("objIndex"));
	if(argNode)
	{
		objIdx=(unsigned int)_ttoi(argNode->GetText().GetString());
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

	switch(subCommandType)
	{
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_SERVICENAME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DOMAINNAME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERNAME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_USERPASSWORD:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_START_TIME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_RESTART:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_IMPERSONATE:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_IS_USER_INTERFACE:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_STATUS:

	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_REPOS_URL:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERNAME:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_USERPASSWORD:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_CURRENT_REVISION:
	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_DEPLOY_LATEST_REVISION:

	case SERVICE_OBJECT_INFO_GET_PACKET_TYPE_ALL:
		break;
	default:
		break;
	}
	retPacketGen.AddGetServiceInfo(subCommandType,objIdx);
	return retErr;
}

WinServiceXMLParserError WinServiceXMLParser::processServiceObjectInfoSet(ServiceObjectInfoSetPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	XNode * argNode=NULL;

	unsigned int objIdx=0;
	argNode=root->GetChild(_T("objIndex"));
	if(argNode)
	{
		objIdx=(unsigned int)_ttoi(argNode->GetText().GetString());
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

	CString argument;
	ServiceObjInfo serviceObjInfo;

	switch(subCommandType)
	{
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_SERVICENAME:
		argNode=root->GetChild(_T("serviceName"));
		if(argNode)
			serviceObjInfo.m_serviceName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_COMMANDLINE:
		argNode=root->GetChild(_T("preProcessCommandLine"));
		if(argNode)
			serviceObjInfo.m_preProcessCommandLine=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_COMMANDLINE:
		argNode=root->GetChild(_T("postProcessCommandLine"));
		if(argNode)
			serviceObjInfo.m_postProcessCommandLine=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_CUSTOMPROCESS_COMMANDLINE:
		argNode=root->GetChild(_T("customProcessCommandLine"));
		if(argNode)
			serviceObjInfo.m_customProcessCommandLine=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_PREPROCESS_WAIT_TIME:
		argNode=root->GetChild(_T("preProcessWaitTime"));
		if(argNode)
		{
			if(argNode->GetText().Compare(_T("INFINITE"))!=0)
				serviceObjInfo.m_preProcessWaitTime=_ttoi(argNode->GetText().GetString());
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_POSTPROCESS_WAIT_TIME:
		argNode=root->GetChild(_T("postProcessWaitTime"));
		if(argNode)
		{
			if(argNode->GetText().Compare(_T("INFINITE"))!=0)
				serviceObjInfo.m_postProcessWaitTime=_ttoi(argNode->GetText().GetString());
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DOMAINNAME:
		argNode=root->GetChild(_T("domainName"));
		if(argNode)
			serviceObjInfo.m_domainName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERNAME:
		argNode=root->GetChild(_T("userName"));
		if(argNode)
			serviceObjInfo.m_userName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_USERPASSWORD:
		argNode=root->GetChild(_T("userPassword"));
		if(argNode)
			serviceObjInfo.m_userPassword=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_START_TIME:
		argNode=root->GetChild(_T("delayStartTime"));
		if(argNode)
			serviceObjInfo.m_delayStartTime=(unsigned int)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DELAY_PAUSE_END_TIME:
		argNode=root->GetChild(_T("delayPauseEndTime"));
		if(argNode)
			serviceObjInfo.m_delayPauseEndTime=(unsigned int)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_RESTART:
		argNode=root->GetChild(_T("IsRestart"));
		if(argNode)
		{
			argument=argNode->GetText();
			argument=argument.MakeUpper();
			if(argument.Compare(_T("TRUE")))
				serviceObjInfo.m_isRestart=true;
			else
				serviceObjInfo.m_isRestart=false;
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_IMPERSONATE:
		argNode=root->GetChild(_T("IsImpersonate"));
		if(argNode)
		{
			argument=argNode->GetText();
			argument=argument.MakeUpper();
			if(argument.Compare(_T("TRUE")))
				serviceObjInfo.m_isImpersonate=true;
			else
				serviceObjInfo.m_isImpersonate=false;
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_IS_USER_INTERFACE:
		argNode=root->GetChild(_T("IsUserInterface"));
		if(argNode)
		{
			argument=argNode->GetText();
			argument=argument.MakeUpper();
			if(argument.Compare(_T("TRUE")))
				serviceObjInfo.m_isUserInterface=true;
			else
				serviceObjInfo.m_isUserInterface=false;
		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;

	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_REPOS_URL:
		argNode=root->GetChild(_T("deployRepositoryURL"));
		if(argNode)
			serviceObjInfo.m_deployRepositoryURL=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_LOCAL_PATH:
		argNode=root->GetChild(_T("deployLocalPath"));
		if(argNode)
			serviceObjInfo.m_deployLocalPath=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERNAME:
		argNode=root->GetChild(_T("deployUserName"));
		if(argNode)
			serviceObjInfo.m_deployUserName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_DEPLOY_USERPASSWORD:
		argNode=root->GetChild(_T("deployUserPassword"));
		if(argNode)
			serviceObjInfo.m_deployUserName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;

	case SERVICE_OBJECT_INFO_SET_PACKET_TYPE_ALL:
		argNode=root->GetChild(_T("All"));
		if(argNode)
		{
			argNode=root->GetChild(_T("serviceName"));
			if(argNode)
				serviceObjInfo.m_serviceName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("preProcessCommandLine"));
			if(argNode)
				serviceObjInfo.m_preProcessCommandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("postProcessCommandLine"));
			if(argNode)
				serviceObjInfo.m_postProcessCommandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("customProcessCommandLine"));
			if(argNode)
				serviceObjInfo.m_customProcessCommandLine=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("preProcessWaitTime"));
			if(argNode)
			{
				if(argNode->GetText().Compare(_T("INFINITE"))!=0)
					serviceObjInfo.m_preProcessWaitTime=_ttoi(argNode->GetText().GetString());
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("postProcessWaitTime"));
			if(argNode)
			{
				if(argNode->GetText().Compare(_T("INFINITE"))!=0)
					serviceObjInfo.m_postProcessWaitTime=_ttoi(argNode->GetText().GetString());
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("domainName"));
			if(argNode)
				serviceObjInfo.m_domainName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("userName"));
			if(argNode)
				serviceObjInfo.m_userName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("userPassword"));
			if(argNode)
				serviceObjInfo.m_userPassword=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("delayStartTime"));
			if(argNode)
				serviceObjInfo.m_delayStartTime=(unsigned int)_ttoi(argNode->GetText().GetString());
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("delayPauseEndTime"));
			if(argNode)
				serviceObjInfo.m_delayPauseEndTime=(unsigned int)_ttoi(argNode->GetText().GetString());
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("IsRestart"));
			if(argNode)
			{
				argument=argNode->GetText();
				argument=argument.MakeUpper();
				if(argument.Compare(_T("TRUE")))
					serviceObjInfo.m_isRestart=true;
				else
					serviceObjInfo.m_isRestart=false;
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("IsImpersonate"));
			if(argNode)
			{
				argument=argNode->GetText();
				argument=argument.MakeUpper();
				if(argument.Compare(_T("TRUE")))
					serviceObjInfo.m_isImpersonate=true;
				else
					serviceObjInfo.m_isImpersonate=false;
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("IsUserInterface"));
			if(argNode)
			{
				argument=argNode->GetText();
				argument=argument.MakeUpper();
				if(argument.Compare(_T("TRUE")))
					serviceObjInfo.m_isUserInterface=true;
				else
					serviceObjInfo.m_isUserInterface=false;
			}
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

			argNode=root->GetChild(_T("deployRepositoryURL"));
			if(argNode)
				serviceObjInfo.m_deployRepositoryURL=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("deployLocalPath"));
			if(argNode)
				serviceObjInfo.m_deployLocalPath=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			break;
			argNode=root->GetChild(_T("deployUserName"));
			if(argNode)
				serviceObjInfo.m_deployUserName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
			argNode=root->GetChild(_T("deployUserPassword"));
			if(argNode)
				serviceObjInfo.m_deployUserName=argNode->GetText().GetString();
			else
				return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;


		}
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddSetServiceInfo(subCommandType,objIdx,serviceObjInfo);

	return retErr;
}


WinServiceXMLParserError WinServiceXMLParser::processServiceCommand(ServiceCommandPacketType subCommandType, XNode *root,WinServicePacketGenerator &retPacketGen)
{
	WinServiceXMLParserError retErr=WINSERVICE_XML_PARSER_ERROR_SUCCESS;
	CString serviceName=_T("");
	CString waitTimeString=_T("INFINITE");
	unsigned int waitTime=WAITTIME_INIFINITE;
	int objIdx=-1;
	XNode * argNode=NULL;
	argNode=root->GetChild(_T("serviceName"));
	if(argNode)
	{
		serviceName=argNode->GetText();
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
	ServiceInfo serviceInfo;
	switch(subCommandType)
	{
	case SERVICE_COMMAND_PACKET_TYPE_START:
		break;
	case SERVICE_COMMAND_PACKET_TYPE_CONTINUE:
		break;
	case SERVICE_COMMAND_PACKET_TYPE_STOP:
		break;
	case SERVICE_COMMAND_PACKET_TYPE_PAUSE:
		break;
	case SERVICE_COMMAND_PACKET_TYPE_CONTROL:
		argNode=root->GetChild(_T("controlCode"));
		if(argNode)
			serviceInfo.m_code=(ServiceControlCode)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		break;
	case SERVICE_COMMAND_PACKET_TYPE_INSTALL:
		argNode=root->GetChild(_T("desiredAccess"));
		if(argNode)
			serviceInfo.m_desiredAccess=(ServiceDesiredAccess)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		argNode=root->GetChild(_T("serviceType"));
		if(argNode)
			serviceInfo.m_serviceType=(ServiceType)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		argNode=root->GetChild(_T("serviceStartType"));
		if(argNode)
			serviceInfo.m_serviceStartType=(ServiceStartType)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		argNode=root->GetChild(_T("serviceErrorControl"));
		if(argNode)
			serviceInfo.m_serviceErrorControl=(ServiceErrorControl)_ttoi(argNode->GetText().GetString());
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;

		argNode=root->GetChild(_T("binaryPathName"));
		if(argNode)
			serviceInfo.m_binaryPathName=argNode->GetText().GetString();
		else
			return WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT;
		argNode=root->GetChild(_T("loadOrderGroup"));
		if(argNode)
			serviceInfo.m_loadOrderGroup=argNode->GetText().GetString();
		argNode=root->GetChild(_T("dependencies"));
		if(argNode)
			serviceInfo.m_dependencies=argNode->GetText().GetString();
		argNode=root->GetChild(_T("domainName"));
		if(argNode)
			serviceInfo.m_domainName=argNode->GetText().GetString();
		argNode=root->GetChild(_T("userName"));
		if(argNode)
			serviceInfo.m_userName=argNode->GetText().GetString();
		argNode=root->GetChild(_T("userPassword"));
		if(argNode)
			serviceInfo.m_userPassword=argNode->GetText().GetString();
		break;
	case SERVICE_COMMAND_PACKET_TYPE_UNINSTALL:
		break;
	case SERVICE_COMMAND_PACKET_TYPE_EDIT:
		argNode=root->GetChild(_T("desiredAccess"));
		if(argNode)
			serviceInfo.m_desiredAccess=(ServiceDesiredAccess)_ttoi(argNode->GetText().GetString());
		argNode=root->GetChild(_T("serviceType"));
		if(argNode)
			serviceInfo.m_serviceType=(ServiceType)_ttoi(argNode->GetText().GetString());
		argNode=root->GetChild(_T("serviceStartType"));
		if(argNode)
			serviceInfo.m_serviceStartType=(ServiceStartType)_ttoi(argNode->GetText().GetString());
		argNode=root->GetChild(_T("serviceErrorControl"));
		if(argNode)
			serviceInfo.m_serviceErrorControl=(ServiceErrorControl)_ttoi(argNode->GetText().GetString());
		argNode=root->GetChild(_T("binaryPathName"));
		if(argNode)
			serviceInfo.m_binaryPathName=argNode->GetText().GetString();
		argNode=root->GetChild(_T("loadOrderGroup"));
		if(argNode)
			serviceInfo.m_loadOrderGroup=argNode->GetText().GetString();
		argNode=root->GetChild(_T("dependencies"));
		if(argNode)
			serviceInfo.m_dependencies=argNode->GetText().GetString();
		argNode=root->GetChild(_T("domainName"));
		if(argNode)
			serviceInfo.m_domainName=argNode->GetText().GetString();
		argNode=root->GetChild(_T("userName"));
		if(argNode)
			serviceInfo.m_userName=argNode->GetText().GetString();
		argNode=root->GetChild(_T("userPassword"));
		if(argNode)
			serviceInfo.m_userPassword=argNode->GetText().GetString();
		argNode=root->GetChild(_T("editControlBits"));
		if(argNode)
			serviceInfo.m_editControlBits=(unsigned int)_ttoi(argNode->GetText().GetString());
		break;
	case SERVICE_COMMAND_PACKET_TYPE_GET_STATUS:
		break;
	default:
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		break;
	}
	retPacketGen.AddCommandService(subCommandType,serviceName.GetString(),serviceInfo);

	return retErr;
}


WinServiceXMLParserError WinServiceXMLParser::processCommand(XNode * root,WinServicePacketGenerator &retPacketGen)
{
	if(!root)
		return WINSERVICE_XML_PARSER_ERROR_PARSE_FAIL;

	CString command,subCommand;
	XNode *nodePtr=root->GetChild(_T("command"));
	if(nodePtr)
	{
		command=nodePtr->GetText();
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_COMMAND;

	nodePtr=root->GetChild(_T("subcommand"));
	if(nodePtr)
	{
		subCommand=nodePtr->GetText();
	}
	else
		return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
    XNode *argsNodePtr=root->GetChild(_T("arguments"));

	PacketType commandType=PACKET_TYPE_NULL;
	if(command.Compare(_T("MainServiceCommand"))==0)
	{
		commandType= PACKET_TYPE_MAIN_SERVICE_COMMAND;
		MainServiceCommandPacketType subCommandType=WinServiceTypeInterpreter::GetMainServiceCommandPacketType(subCommand);
		if(subCommandType==MAIN_SERVICE_COMMAND_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processMainServiceCommand(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("MainServiceInfoGet"))==0)
	{
		commandType= PACKET_TYPE_MAIN_SERVICE_INFO_GET;
		MainServiceInfoGetPacketType subCommandType=WinServiceTypeInterpreter::GetMainServiceInfoGetPacketType(subCommand);
		if(subCommandType==MAIN_SERVICE_INFO_GET_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processMainServiceInfoGet(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("MainServiceInfoSet"))==0)
	{
		commandType= PACKET_TYPE_MAIN_SERVICE_INFO_SET;
		MainServiceInfoSetPacketType subCommandType=WinServiceTypeInterpreter::GetMainServiceInfoSetPacketType(subCommand);
		if(subCommandType==MAIN_SERVICE_INFO_SET_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processMainServiceInfoSet(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ProcessObjectCommand"))==0)
	{
		commandType= PACKET_TYPE_PROCESS_OBJECT_COMMAND;
		ProcessObjectCommandPacketType subCommandType=WinServiceTypeInterpreter::GetProcessObjectCommandPacketType(subCommand);
		if(subCommandType==PROCESS_OBJECT_COMMAND_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processProcessObjectCommand(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ProcessObjectInfoGet"))==0)
	{
		commandType= PACKET_TYPE_PROCESS_OBJECT_INFO_GET;
		ProcessObjectInfoGetPacketType subCommandType=WinServiceTypeInterpreter::GetProcessObjectInfoGetPacketType(subCommand);
		if(subCommandType==PROCESS_OBJECT_INFO_GET_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processProcessObjectInfoGet(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ProcessObjectInfoSet"))==0)
	{
		commandType= PACKET_TYPE_PROCESS_OBJECT_INFO_SET;
		ProcessObjectInfoSetPacketType subCommandType=WinServiceTypeInterpreter::GetProcessObjectInfoSetPacketType(subCommand);
		if(subCommandType==PROCESS_OBJECT_INFO_SET_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processProcessObjectInfoSet(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ServiceObjectCommand"))==0)
	{
		commandType= PACKET_TYPE_SERVICE_OBJECT_COMMAND;
		ServiceObjectCommandPacketType subCommandType=WinServiceTypeInterpreter::GetServiceObjectCommandPacketType(subCommand);
		if(subCommandType==SERVICE_OBJECT_COMMAND_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processServiceObjectCommand(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ServiceObjectInfoGet"))==0)
	{
		commandType= PACKET_TYPE_SERVICE_OBJECT_INFO_GET;
		ServiceObjectInfoGetPacketType subCommandType=WinServiceTypeInterpreter::GetServiceObjectInfoGetPacketType(subCommand);
		if(subCommandType==SERVICE_OBJECT_INFO_GET_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processServiceObjectInfoGet(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ServiceObjectInfoSet"))==0)
	{
		commandType= PACKET_TYPE_SERVICE_OBJECT_INFO_SET;
		ServiceObjectInfoSetPacketType subCommandType=WinServiceTypeInterpreter::GetServiceObjectInfoSetPacketType(subCommand);
		if(subCommandType==SERVICE_OBJECT_INFO_SET_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
		return processServiceObjectInfoSet(subCommandType,argsNodePtr,retPacketGen);
	}
	else if(command.Compare(_T("ServiceCommand"))==0)
	{
		commandType= PACKET_TYPE_SERVICE_COMMAND;
		ServiceCommandPacketType subCommandType=WinServiceTypeInterpreter::GetServiceCommandPacketType(subCommand);
		if(subCommandType==SERVICE_COMMAND_PACKET_TYPE_NULL)
			return WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND;
	}
	return WINSERVICE_XML_PARSER_ERROR_INVALID_COMMAND;
}


bool WinServiceXMLParser::parse(XNode *root,WinServicePacketGenerator &retPacketGen )
{
	vector<Pair<unsigned int,WinServiceXMLParserError> > errorList;
	if(!root)
		return false;

	for(int childIdx=0;childIdx<root->GetChildCount();childIdx++)
	{
		XNode * childNode=root->GetChild(childIdx);
		WinServiceXMLParserError err=processCommand(childNode,retPacketGen);
		Pair<unsigned int, WinServiceXMLParserError> errElement=Pair<unsigned int, WinServiceXMLParserError>(childIdx,err);
		errorList.push_back(errElement);
		switch(err)
		{
		case WINSERVICE_XML_PARSER_ERROR_SUCCESS:
			System::TPrintf(_T("Parsing Command(%d): Sucess\n"),childIdx);
			break;
		case WINSERVICE_XML_PARSER_ERROR_PARSE_FAIL:
			System::TPrintf(_T("Parsing Command(%d): Parse Fail\n"),childIdx);
			break;
		case WINSERVICE_XML_PARSER_ERROR_INVALID_COMMAND:
			System::TPrintf(_T("Parsing Command(%d): Invalid Command\n"),childIdx);
			break;
		case WINSERVICE_XML_PARSER_ERROR_INVALID_SUBCOMMAND:
			System::TPrintf(_T("Parsing Command(%d): Invalid Subcommand\n"),childIdx);
			break;
		case WINSERVICE_XML_PARSER_ERROR_INVALID_ARGUMENT:
			System::TPrintf(_T("Parsing Command(%d): Invalid Argument\n"),childIdx);
			break;
		}
		if(err!= WINSERVICE_XML_PARSER_ERROR_SUCCESS)
			return false;
	}

	return true;
}
bool WinServiceXMLParser::ProcessParse(XNode * root, WinServiceResult &retResult)
{
	if(!root)
		return false;
	if(!root->GetChild(_T("hostName")))
		return false;
	if(!root->GetChild(_T("port")))
		return false;

	CString hostName=root->GetChild(_T("hostName"))->GetText();
	CString port = root->GetChild(_T("port"))->GetText();



	WinServicePacketGenerator packetGenerator;

	XNode *commandList=root->GetChild(_T("commandList"));
	if(!parse(commandList,packetGenerator))
		return false;

	
	WinServiceCommunicator communicator=WinServiceCommunicator(hostName.GetString(),port.GetString());

	WinServiceCommunicatorSendError sendErr=communicator.Send(packetGenerator,retResult);
	if(sendErr!=WINSERVICE_COMMUNICATOR_SEND_ERROR_SUCCESS)
	{
		switch(sendErr)
		{
		case WINSERVICE_COMMUNICATOR_SEND_ERROR_CONNECTION_FAILED:
			System::TPrintf(_T("Send Error: Connection Failed\n"));
			return false;
			break;
		case WINSERVICE_COMMUNICATOR_SEND_ERROR_SEND_FAILED:
			System::TPrintf(_T("Send Error: Send Failed\n"));
			return false;
			break;
		case WINSERVICE_COMMUNICATOR_SEND_ERROR_RECEIVE_FAILED:
			System::TPrintf(_T("Send Error: Receive Failed\n"));
			return false;
			break;
		}
	}
	return true;
}


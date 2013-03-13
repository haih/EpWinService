// EpWinServiceCLI90.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "epWinServiceXMLParser.h"
#include "epWinServiceReturnXMLBuilder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CmdLineOptions options;
	if(options.Parse(argc,argv))
	{
		XMLFile m_xmlFile=XMLFile();
		WinServiceResult result;
		if(options.HasOption(_T("-xmlfile")))
		{
			EpTString fileName=options.GetArgument(_T("-xmlfile"),0);
			if(m_xmlFile.LoadFromFile(fileName.c_str()))
			{
				WinServiceXMLParser::ProcessParse(&m_xmlFile,result);
			}
			
			
		}
		else if(options.HasOption(_T("-xml")))
		{
			EpTString xmlString=options.GetArgument(_T("-xmlfile"),0);
			m_xmlFile.Load(xmlString.c_str());

			WinServiceXMLParser::ProcessParse(&m_xmlFile,result);
			
		}
		XMLFile m_outXmlFile=XMLFile();
		
		if(WinServiceReturnXMLBuilder::BuildResultXML(result, m_outXmlFile))
		{
			if(options.HasOption(_T("-output")))
			{
				m_outXmlFile.SaveToFile(options.GetArgument(_T("-output"),0).c_str());
			}
			else
			{
				System::TPrintf(_T("Building Result XML: Success\n"));
				System::TPrintf(_T("%s\n"),m_outXmlFile.GetXML().GetString());
			}
		}
		else
		{
			System::TPrintf(_T("Building Result XML: Failed\n"));
		}
		
	}
	return 0;
}


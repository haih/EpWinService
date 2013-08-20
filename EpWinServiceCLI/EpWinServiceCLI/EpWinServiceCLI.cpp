/*! 
EpWinServiceCLI for the EpWinServiceCLI

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
*/

// EpWinServiceCLI90.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "epWinServiceXMLParser.h"
#include "epWinServiceReturnXMLBuilder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(_T("\n"));
	_tprintf(_T("*********************************************************************\n"));
	_tprintf(_T("EpWinServiceCLI is a command line interface for EpWinService solution\n   under a MIT license.\n\n"));
	_tprintf(_T("Copyright (C) 2013  Woong Gyu La <juhgiyo@gmail.com>\n"));
	_tprintf(_T("            <http://github.com/juhgiyo/epWinService>\n\n"));
	_tprintf(_T("*********************************************************************\n"));
	_tprintf(_T("\n\n"));
	_tprintf(_T("EpWinServiceCLI: Started\n"));

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
				if(!WinServiceXMLParser::ProcessParse(&m_xmlFile,result))
				{
					return 0;
				}
			}
			
			
		}
		else if(options.HasOption(_T("-xml")))
		{
			EpTString xmlString=options.GetArgument(_T("-xml"),0);
			m_xmlFile.Load(xmlString.c_str());

			if(!WinServiceXMLParser::ProcessParse(&m_xmlFile,result))
			{
				return 0;
			}
			
		}
		XMLFile m_outXmlFile=XMLFile();
		m_outXmlFile.m_name=_T("EpWinServiceCLI_Result");
		
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
	else
	{
		System::TPrintf(_T("Usage: EpWinServiceCLI\n\
                 switch\n\
                 {\n\
                    -xmlfile <FileName>\n\
                    -xml <XMLString>\n\
                 }\n\
                 -output <Optional/FileName>\n"));
	}
	return 0;
}


/*! 
EpWinServiceCLI for the EpWinServiceCLI
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

// EpWinServiceCLI90.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "epWinServiceXMLParser.h"
#include "epWinServiceReturnXMLBuilder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(_T("\n"));
	_tprintf(_T("*********************************************************************\n"));
	_tprintf(_T("EpWinServiceCLI is a command line interface for EpWinService solution\n   under a GPL3.0 license.\n\n"));
	_tprintf(_T("Copyright (C) 2013  Woong Gyu La <juhgiyo@gmail.com>\n"));
	_tprintf(_T("            <http://github.com/juhgiyo/epWinService>\n\n"));
	_tprintf(_T("This program is free software: you can redistribute it and/or modify\n"));
	_tprintf(_T("it under the terms of the GNU General Public License as published by\n"));
	_tprintf(_T("the Free Software Foundation, either version 3 of the License, or\n"));
	_tprintf(_T("(at your option) any later version.\n\n"));
	_tprintf(_T("This program is distributed in the hope that it will be useful,\n"));
	_tprintf(_T("but WITHOUT ANY WARRANTY; without even the implied warranty of\n"));
	_tprintf(_T("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"));
	_tprintf(_T("GNU General Public License for more details.\n\n"));
	_tprintf(_T("You should have received a copy of the GNU General Public License\n"));
	_tprintf(_T("along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"));
	_tprintf(_T("*********************************************************************\n"));
	_tprintf(_T("\n\n"));

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
					return 0;
			}
			
			
		}
		else if(options.HasOption(_T("-xml")))
		{
			EpTString xmlString=options.GetArgument(_T("-xmlfile"),0);
			m_xmlFile.Load(xmlString.c_str());

			if(!WinServiceXMLParser::ProcessParse(&m_xmlFile,result))
				return 0;
			
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


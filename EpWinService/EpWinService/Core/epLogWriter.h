/*! 
@file epLogWriter.h
@author Woong Gyu La a.k.a Chris. <juhgiyo@gmail.com>
		<http://github.com/juhgiyo/epWinService>
@date January 16, 2013
@brief Log Writer Interface
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

An Interface for Log Writer.

*/
#ifndef __EP_LOG_WRITER_H__
#define __EP_LOG_WRITER_H__

#include "epl.h"

using namespace epl;

/*!
@def LOG_WRITER_INSTANCE
@brief Log Writer Singleton Instance

Macro for the Log Writer Singleton Instance.
*/
#define LOG_WRITER_INSTANCE epl::SingletonHolder<LogWriter>::Instance()

/*! 
@class LogWriter epLogWriter.h
@brief A class for Writing Log.
*/
class LogWriter{
public:
	friend SingletonHolder<LogWriter>;
	
	/*!
	Writer given message to the log with current time.
	@param[in] pMsg the message to print to the log file.
	*/
	void WriteLog(const TCHAR* pMsg);

private:
	/*!
	Default Constructor

	Initializes the Log Writer
	*/
	LogWriter();
	
	/*!
	Default Destructor

	Destroy the Log Writer
	*/
	~LogWriter();
	
	/// Mutex Lock
	Mutex *m_mux;
};
#endif //__EP_LOG_WRITER_H__
/*
 * SimpleLog.cpp
 *
 *  Created on: 26 янв. 2015 г.
 *      Author: orwell
 */

#include "SimpleLog.h"

namespace test_tasks
{

std::ostream& operator<<(std::ostream& os, LogLevels c)
{
    switch(c) {
         case LogLevels::debug	: os << "debug"; break;
         case LogLevels::error 	: os << "error"; break;
         case LogLevels::fatal 	: os << "fatal"; break;
         case LogLevels::info 	: os << "info"; break;
         case LogLevels::warn 	: os << "warn"; break;
         default : os.setstate(std::ios_base::failbit);
    }
    return os;
}

SimpleLog::SimpleLog():
		m_inited(false),
		m_current_log_level(LogLevels::warn), //default log level
		m_output_file(0),
		m_output_file_name("log.txt")
{
	InitSink();
}

SimpleLog::~SimpleLog()
{
}

void SimpleLog::Init()
{
	m_inited = false;
	InitSink();
	m_inited = true;
}

void SimpleLog::SetLogLevel(LogLevels log_level)
{
	m_current_log_level = log_level;
}

void SimpleLog::SetOutputFileName(std::string output_file_name)
{
	if (!output_file_name.compare(""))
	{
		throw std::runtime_error("SimpleLog::SetOutputFileName - wrong output file name.");
	}
	m_output_file_name = output_file_name;
}

void SimpleLog::AddMessage(std::string message,
						   LogLevels level,
						   std::map<AddInfo, std::string> add_info)
{
	if (level < m_current_log_level)
		return;
	std::stringstream ss;
	for (AddInfo iter = AddInfo::cur_time;
			iter <= AddInfo::log_level;
			iter = static_cast<AddInfo>(static_cast<int>(iter)+1))
	{
		if (add_info.find(iter) != add_info.end())
		{
			if (add_info.at(iter).compare(""))
			{
				ss << "["
						<< add_info.at(iter)
						<< "]";
			}
			else if (iter == AddInfo::log_level)
			{
				ss << "["
				   << level
				   << "]";
			}
			else if (iter == AddInfo::cur_time)
			{
				time_t cur_time;
				time(&cur_time);
				tm* ltime = localtime(&cur_time);
				ss << "["
				   << ltime->tm_hour << ":"
				   << ltime->tm_min << ":"
				   << ltime->tm_sec
				   << "]";
			}
		}
	}
	ss << message
	   << std::endl;
	WriteMessage(ss.str());
}

void SimpleLog::InitSink()
{
	m_output_file.open(m_output_file_name);
}

void SimpleLog::WriteMessage(std::string message)
{
	std::cout 		<< message;
	m_output_file 	<< message;
}

void SimpleLog::CloseSink()
{
	m_output_file.close();
}

} // end of namespace

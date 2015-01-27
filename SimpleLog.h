/*
 * SimpleLog.h
 *
 *  Created on: 26 янв. 2015 г.
 *      Author: orwell
 */

#ifndef SIMPLELOG_H_
#define SIMPLELOG_H_

#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <map>
#include <time.h>


namespace test_tasks
{
enum class AddInfo;
typedef std::map<AddInfo, std::string> MsgFormat;

enum class LogLevels
{
	debug,
	info,
	warn,
	error,
	fatal
};


enum class AddInfo : int
{
	cur_time		= 1,
	string_number	= 2,
	file_name		= 3,
	log_level		= 4
};

class SimpleLog
{
public:
	SimpleLog();
	virtual ~SimpleLog();
	void Init();
	void SetLogLevel(LogLevels log_level);
	void SetOutputFileName(std::string output_file_name);
	void AddMessage(std::string message,
					LogLevels level = LogLevels::warn,
					std::map<AddInfo, std::string> add_info = std::map<AddInfo, std::string>());
protected:
	virtual void InitSink();
	virtual void WriteMessage(std::string);
	virtual void CloseSink();
private:
	bool			m_inited;
	LogLevels		m_current_log_level;
	std::ofstream	m_output_file;
	std::string		m_output_file_name;
};

} // end of namespace

#endif /* SIMPLELOG_H_ */

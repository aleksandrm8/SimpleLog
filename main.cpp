/*
 * main.cpp
 *
 *  Created on: 26 янв. 2015 г.
 *      Author: orwell
 */

#include <stdio.h>
#include "SimpleLog.h"
int main()
{
	test_tasks::SimpleLog log;
	log.SetLogLevel(test_tasks::LogLevels::error);
	log.AddMessage("hello");
	log.AddMessage("sec_string");
	log.AddMessage("crit error",
				   test_tasks::LogLevels::fatal,
				   test_tasks::MsgFormat{std::make_pair(test_tasks::AddInfo::log_level, "lg_lev")} );


	log.AddMessage("crit error2",
				   test_tasks::LogLevels::fatal,
				   test_tasks::MsgFormat
				   {
						std::make_pair(test_tasks::AddInfo::log_level, ""),
						std::make_pair(test_tasks::AddInfo::cur_time, "")
				   }
	);
}




/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/log/log.h>

#include <string>
#include <chrono>
#include <ctime>

namespace basyx
{
	log::Level log::logLevel = log::Level::Trace;

	const char * log::printLevel(log::Level level)
	{
		switch (level)
		{
		case Level::Debug:
			return "debug";
		case Level::Trace:
			return "trace";
		case Level::Info:
			return "info";
		case Level::Warn:
			return "warn";
		case Level::Error:
			return "error";
		case Level::Critical:
			return "CRITICAL";
		};

		return "unknown";
	}

	std::string basyx::log::timestamp()
	{

		auto current_time = std::chrono::system_clock::now();

		std::time_t t = std::chrono::system_clock::to_time_t(current_time);
		std::string formatted_time = std::ctime(&t);

		//Remove trailing newline
		formatted_time.erase(formatted_time.end() - 1);

		return formatted_time;
	};

/*
	std::string basyx::log::buildMessage(const std::string & format, Level level)
	{
		return fmt::format("{}{}{}", "test", 1, 2.3f);

		//std::string message = "";
		//message += timestamp();
		//message += printLevel(level);
		//message += "[" + std::to_string(basyx::thread::currentThreadId()) + "] ";
		//message += sourceName;
		//message += format + "\r\n";
		//return message;
	};*/
};

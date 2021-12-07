/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_LOG_LOG_H
#define BASYX_LOG_LOG_H

#include <iostream>

#include <fmt/format.h>

namespace basyx {

class log {
public:
    enum class Level {
        Debug = 0,
        Trace = 1,
        Info = 2,
        Warn = 3,
        Error = 4,
        Critical = 5
    };

public:
    explicit log(const std::string& sourceName)
        : sourceName { sourceName }
    {
    }

    explicit log()
        : sourceName { "" } {};

private:
    const char* printLevel(Level level);

private:
    static Level logLevel;

public:
    static void setLogLevel(Level level)
    {
        logLevel = level;
    };

private:
    std::string sourceName;

    std::string timestamp();

    template <typename... Args>
    std::string buildMessage(const std::string& format, Level level, Args&&... args)
    {
        auto message = fmt::format("[{}] [{}] [{}] {}", timestamp(), printLevel(level), sourceName, format);
        return fmt::format(message, std::forward<Args>(args)...);
    };

    //template<typename T>
    //inline T && normalize(T && t)
    //{
    //	return std::forward<T>(t);
    //}

    //inline const char * normalize(const std::string & s)
    //{
    //	return s.c_str();
    //}

    template <typename... Args>
    inline void log_message(Level level, const std::string& msg, Args&&... args)
    {
        if (level >= logLevel)
            std::cout << buildMessage(msg, level, std::forward<Args>(args)...) << std::endl;
    };

public:
    template <typename... Args>
    inline void trace(const std::string& msg, Args&&... args)
    {
        log_message(Level::Trace, msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void debug(const std::string& msg, Args&&... args)
    {
        log_message(Level::Debug, msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void info(const std::string& msg, Args&&... args)
    {
        log_message(Level::Info, msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void warn(const std::string& msg, Args&&... args)
    {
        log_message(Level::Warn, msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void error(const std::string& msg, Args&&... args)
    {
        log_message(Level::Error, msg, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void crit(const std::string& msg, Args&&... args)
    {
        log_message(Level::Critical, msg, std::forward<Args>(args)...);
    }

    // static logging functions
public:
    inline static log topic(const std::string& topic)
    {
        return log(topic);
    };
};
};

#endif /* BASYX_LOG_LOG_H */

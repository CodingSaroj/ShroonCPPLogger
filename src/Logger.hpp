/* 
 * Copyright 2020 Saroj Kumar.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <chrono>

#include <csignal>

#include "CLIColors.hpp"
#include "StringFormat.hpp"
#include "LogLevels.hpp"

// Use the default log level if none is defined.
#ifndef PG_LOG_LEVEL
    // Default log level as Info.
    #define PG_LOG_LEVEL PG_LOG_LEVEL_INFO
#endif

#ifdef _MSC_VER
    #define PG_DEBUG_BREAK() __debugbreak();
#elif defined(SIGTRAP)
    #define PG_DEBUG_BREAK() raise(SIGTRAP);
#else
    #define PG_DEBUG_BREAK() raise(SIGABRT);
#endif

// Debug mode macros

#ifdef DEBUG
    // If log level is set at Info then define PG_INFO.
    #if PG_LOG_LEVEL == PG_LOG_LEVEL_INFO
        #define PG_INFO(section, ...) Peregrine::Logger::LogInfo(section, Peregrine::Logger::Format(__VA_ARGS__));
    #else
        #define PG_INFO(...)
    #endif

    // If log level is set above or at Warning then define PG_WARNING.
    #if PG_LOG_LEVEL >= PG_LOG_LEVEL_WARNING
        #define PG_WARNING(section, ...) Peregrine::Logger::LogWarning(section, Peregrine::Logger::Format(__VA_ARGS__));
    #else
        #define PG_WARNING(...)
    #endif

    // If log level is set above or at Error then define PG_ERROR and PG_ASSERT.
    #if PG_LOG_LEVEL == PG_LOG_LEVEL_ERROR
        #define PG_ERROR(section, ...) Peregrine::Logger::LogError(section, Peregrine::Logger::Format(__VA_ARGS__));

        #define PG_ASSERT(cond, section, ...) if (!(cond)) { Peregrine::Logger::LogFatalError(section, Peregrine::Logger::Format(__VA_ARGS__)); }
    #else
        #define PG_ERROR(...)

        #define PG_ASSERT(...) PG_DEBUG_BREAK();
    #endif
#else
    // Don't define non-release macros in Release mode.

    #define PG_INFO(...)
    #define PG_WARNING(...)
    #define PG_ERROR(...)

    #define PG_ASSERT(...) PG_DEBUG_BREAK();
#endif

// Release mode macros

// If log level is set above or at Info then define PG_REL_INFO.
#if PG_LOG_LEVEL == PG_LOG_LEVEL_INFO
    #define PG_REL_INFO(section, ...) Peregrine::Logger::LogInfo(section, Peregrine::Logger::Format(__VA_ARGS__))
#else
    #define PG_REL_INFO(...)
#endif

// If log level is set above or at Warning then define PG_REL_WARNING.
#if PG_LOG_LEVEL >= PG_LOG_LEVEL_WARNING
    #define PG_REL_WARNING(section, ...) Peregrine::Logger::LogWarning(section, Peregrine::Logger::Format(__VA_ARGS__))
#else
    #define PG_REL_WARNING(...)
#endif

// If log level is set to Error then define PG_REL_ERROR and PG_REL_ASSERT.
#if PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR
    #define PG_REL_ERROR(section, ...) Peregrine::Logger::LogError(section, Peregrine::Logger::Format(__VA_ARGS__))

    #define PG_REL_ASSERT(cond, section, ...) if (!(cond)) { Peregrine::Logger::LogFatalError(section, Peregrine::Logger::Format(__VA_ARGS__)); }
#else
    #define PG_REL_ERROR(...)

    #define PG_REL_ASSERT(...) PG_DEBUG_BREAK()
#endif

namespace Peregrine
{
    namespace Logger
    {
        /*
         * Set the std::ostream to log to. It is std::cout by default for
         * info, warnings and errors. Assertions are always written to std::cerr. 
         *
         * out - std::ostream & where all the logs will go.
         */
        void SetOStream(std::ostream & out);

        /*
         * Logs data to the output stream in the format:
         *      (Green)[<time_since_app_started_in_ms>](Bold|Cyan)Info(White)::<section>: <log>\n
         */
        void LogInfo(const std::string & section, const std::string & log);

        /*
         * Logs data to the output stream in the format:
         *      (Green)[<time_since_app_started_in_ms>](Bold|Yellow)Warning(White)::<section>: <log>\n
         */
        void LogWarning(const std::string & section, const std::string & log);

        /*
         * Logs data to the output stream in the format:
         *      (Green)[<time_since_app_started_in_ms>](Bold|Red)Error(White)::<section>: <log>\n
         */
        void LogError(const std::string & section, const std::string & log);

        /*
         * Logs data to the std::cerr in the format below and causes a debug break:
         *      (Green)[<time_since_app_started_in_ms>](Bold|Red)Error(White)::<section>: <log>\n
         */
        void LogFatalError(const std::string & section, const std::string & log);
    }
}

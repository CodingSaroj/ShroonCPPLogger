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
    /**
     * @brief Causes a debug break. Does \p __debugbreak() on MSVC, \p raise(SIGTRAP) on systems where \p SIGTRAP is defined and \p raise(SIGABRT) where it isn't.
     */
    #define PG_DEBUG_BREAK() raise(SIGABRT);
#endif

// Debug mode macros

/**
 * @defgroup LoggingMacros
 * This group consists of all the macros used for logging.
 * @{
 * @defgroup DebugLoggingMacros
 * This group consists of all the macros used for logging only in debug mode.
 * @{
 */
#ifdef DEBUG
    // If log level is set at Info then define PG_INFO.
    #if PG_LOG_LEVEL >= PG_LOG_LEVEL_INFO
        /**
         * @brief Calls \p Peregrine::Logger::LogInfo() when macro \p DEBUG is defined i.e. in debug mode and when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_INFO</tt>.
         */
        #define PG_INFO(section, ...) Peregrine::Logger::LogInfo(section, Peregrine::Logger::Format(__VA_ARGS__));
    #else
        #define PG_INFO(...)
    #endif

    // If log level is set above or at Warning then define PG_WARNING.
    #if PG_LOG_LEVEL >= PG_LOG_LEVEL_WARNING
        /**
         * @brief Calls \p Peregrine::Logger::LogWarning() when macro \p DEBUG is defined i.e. in debug mode and when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_WARNING</tt>.
         */
        #define PG_WARNING(section, ...) Peregrine::Logger::LogWarning(section, Peregrine::Logger::Format(__VA_ARGS__));
    #else
        #define PG_WARNING(...)
    #endif

    // If log level is set above or at Error then define PG_ERROR and PG_ASSERT.
    #if PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR
        /**
         * @brief Calls \p Peregrine::Logger::LogError() when macro \p DEBUG is defined i.e. in debug mode and when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR</tt>.
         */
        #define PG_ERROR(section, ...) Peregrine::Logger::LogError(section, Peregrine::Logger::Format(__VA_ARGS__));

        /**
         * @brief Calls \p Peregrine::Logger::LogFatalError() when macro \p DEBUG is defined i.e. in debug mode and when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR</tt>
         * otherwise calls \p PG_DEBUG_BREAK().
         */
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

/**
 * @}
 * @defgroup ReleaseLoggingMacros
 * This group consists of all the macros used for logging in both debug and release mode.
 * @{
 */

// If log level is set above or at Info then define PG_REL_INFO.
#if PG_LOG_LEVEL >= PG_LOG_LEVEL_INFO
    /**
     * @brief Calls \p Peregrine::Logger::LogInfo() when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_INFO</tt>.
     */
    #define PG_REL_INFO(section, ...) Peregrine::Logger::LogInfo(section, Peregrine::Logger::Format(__VA_ARGS__))
#else
    #define PG_REL_INFO(...)
#endif

// If log level is set above or at Warning then define PG_REL_WARNING.
#if PG_LOG_LEVEL >= PG_LOG_LEVEL_WARNING
    /**
     * @brief Calls \p Peregrine::Logger::LogWarning() when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_WARNING</tt>.
     */
    #define PG_REL_WARNING(section, ...) Peregrine::Logger::LogWarning(section, Peregrine::Logger::Format(__VA_ARGS__))
#else
    #define PG_REL_WARNING(...)
#endif

// If log level is set to Error then define PG_REL_ERROR and PG_REL_ASSERT.
#if PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR
    /**
     * @brief Calls \p Peregrine::Logger::LogError() when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR</tt>.
     */
    #define PG_REL_ERROR(section, ...) Peregrine::Logger::LogError(section, Peregrine::Logger::Format(__VA_ARGS__))

    /**
     * @brief Calls \p Peregrine::Logger::LogFatalError() when <tt>PG_LOG_LEVEL >= PG_LOG_LEVEL_ERROR</tt>
     * otherwise calls \p PG_DEBUG_BREAK().
     */
    #define PG_REL_ASSERT(cond, section, ...) if (!(cond)) { Peregrine::Logger::LogFatalError(section, Peregrine::Logger::Format(__VA_ARGS__)); }
#else
    #define PG_REL_ERROR(...)

    #define PG_REL_ASSERT(...) PG_DEBUG_BREAK()
#endif
/**
 * @}
 * @}
 */


/**
 * @brief The namespace in which all the projects under Peregrine exist.
 */
namespace Peregrine
{
    /**
     * @brief The namespace in which all the PeregrineCPPLogger API other than macros exists.
     */
    namespace Logger
    {
        /**
         * @brief Sets the \p std::ostream to log to. It is \p std::cout by default for
         * info, warnings and errors. Assertions are always written to \p std::cerr. 
         *
         * @param out  An <tt>std::ostream &</tt> to which, all the logs will be written.
         */
        void SetOStream(std::ostream & out);

        /**
         * @defgroup LoggingFunctions
         * This group consists of all the functions used for logging.
         * @{
         */

        /**
         * @brief Logs data with level \p Info to the output stream in the format:\n
         * > <tt>(Green)[\<time_since_app_started_in_ms\>](Bold|Cyan)Info(White)::\<section\>: \<log\>\\n</tt>.
         *
         * @param section The section from where the log is comming. Example - "Renderer::Rasterizer", "Parser" etc.
         * @param log The content of the log.
         */
        void LogInfo(const std::string & section, const std::string & log);

        /**
         * @brief Logs data with level \p Warning to the output stream in the format:\n
         * > <tt>(Green)[\<time_since_app_started_in_ms\>](Bold|Yellow)Warning(White)::\<section\>: \<log\>\\n</tt>.
         *
         * @param section The section from where the log is comming. Example - "Renderer::Rasterizer", "Parser" etc.
         * @param log The content of the log.
         */
        void LogWarning(const std::string & section, const std::string & log);

        /**
         * @brief Logs data with level \p Error to the output stream in the format:\n
         * > <tt>(Green)[\<time_since_app_started_in_ms\>](Bold|Red)Error(White)::\<section\>: \<log\>\\n</tt>.
         *
         * @param section The section from where the log is comming. Example - "Renderer::Rasterizer", "Parser" etc.
         * @param log The content of the log.
         */
        void LogError(const std::string & section, const std::string & log);

        /**
         * @brief Logs data with level \p Error to the output stream in the format:\n
         * > <tt>(Green)[\<time_since_app_started_in_ms\>](Bold|Red)Error(White)::\<section\>: \<log\>\\n</tt>\n
         * and performs a \p PG_DEBUG_BREAK().
         *
         * @param section The section from where the log is comming. Example - "Renderer::Rasterizer", "Parser" etc.
         * @param log The content of the log.
         */
        void LogFatalError(const std::string & section, const std::string & log);

        /**
         * @}
         */
    }
}

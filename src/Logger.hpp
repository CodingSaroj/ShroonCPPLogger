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

#include "StringFormat.hpp"
#include "LogLevels.hpp"

// Use the default log level if none is defined.
#ifndef SHRN_LOG_LEVEL
    // Default log level as Info.
    #define SHRN_LOG_LEVEL SHRN_LOG_LEVEL_INFO
#endif

#ifdef _MSC_VER
    #define SHRN_DEBUG_BREAK() __debugbreak();
#elif defined(SIGTRAP)
    #define SHRN_DEBUG_BREAK() raise(SIGTRAP);
#else
    /**
     * @brief Causes a debug break. Does \p __debugbreak() on MSVC, \p raise(SIGTRAP) on systems where \p SIGTRAP is defined and \p raise(SIGABRT) where it isn't.
     */
    #define SHRN_DEBUG_BREAK() raise(SIGABRT);
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
#ifndef NDEBUG
    // If log level is set at Info then define SHRN_INFO.
    #if SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_INFO
        /**
         * @brief Calls \p Shroon::Logger::LogInfo() when macro \p NDEBUG is not defined i.e. in debug mode and when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_INFO</tt>.
         */
        #define SHRN_INFO(section, ...) Shroon::Logger::LogInfo(section, Shroon::Logger::Format(__VA_ARGS__));
    #else
        #define SHRN_INFO(...)
    #endif

    // If log level is set above or at Warning then define SHRN_WARNING.
    #if SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_WARNING
        /**
         * @brief Calls \p Shroon::Logger::LogWarning() when macro \p NDEBUG is not defined i.e. in debug mode and when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_WARNING</tt>.
         */
        #define SHRN_WARNING(section, ...) Shroon::Logger::LogWarning(section, Shroon::Logger::Format(__VA_ARGS__));
    #else
        #define SHRN_WARNING(...)
    #endif

    // If log level is set above or at Error then define SHRN_ERROR and SHRN_ASSERT.
    #if SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_ERROR
        /**
         * @brief Calls \p Shroon::Logger::LogError() when macro \p NDEBUG is not defined i.e. in debug mode and when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_ERROR</tt>.
         */
        #define SHRN_ERROR(section, ...) Shroon::Logger::LogError(section, Shroon::Logger::Format(__VA_ARGS__));

        /**
         * @brief Calls \p Shroon::Logger::LogFatalError() when macro \p NDEBUG is not defined i.e. in debug mode and when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_ERROR</tt>
         * otherwise calls \p SHRN_DEBUG_BREAK().
         */
        #define SHRN_ASSERT(cond, section, ...) if (!(cond)) { Shroon::Logger::LogFatalError(section, Shroon::Logger::Format(__VA_ARGS__)); }
    #else
        #define SHRN_ERROR(...)

        #define SHRN_ASSERT(...) SHRN_DEBUG_BREAK();
    #endif
#else
    // Don't define non-release macros in Release mode.

    #define SHRN_INFO(...)
    #define SHRN_WARNING(...)
    #define SHRN_ERROR(...)

    #define SHRN_ASSERT(...) SHRN_DEBUG_BREAK();
#endif

// Release mode macros

/**
 * @}
 * @defgroup ReleaseLoggingMacros
 * This group consists of all the macros used for logging in both debug and release mode.
 * @{
 */

// If log level is set above or at Info then define SHRN_REL_INFO.
#if SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_INFO
    /**
     * @brief Calls \p Shroon::Logger::LogInfo() when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_INFO</tt>.
     */
    #define SHRN_REL_INFO(section, ...) Shroon::Logger::LogInfo(section, Shroon::Logger::Format(__VA_ARGS__))
#else
    #define SHRN_REL_INFO(...)
#endif

// If log level is set above or at Warning then define SHRN_REL_WARNING.
#if SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_WARNING
    /**
     * @brief Calls \p Shroon::Logger::LogWarning() when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_WARNING</tt>.
     */
    #define SHRN_REL_WARNING(section, ...) Shroon::Logger::LogWarning(section, Shroon::Logger::Format(__VA_ARGS__))
#else
    #define SHRN_REL_WARNING(...)
#endif

// If log level is set to Error then define SHRN_REL_ERROR and SHRN_REL_ASSERT.
#if SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_ERROR
    /**
     * @brief Calls \p Shroon::Logger::LogError() when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_ERROR</tt>.
     */
    #define SHRN_REL_ERROR(section, ...) Shroon::Logger::LogError(section, Shroon::Logger::Format(__VA_ARGS__))

    /**
     * @brief Calls \p Shroon::Logger::LogFatalError() when <tt>SHRN_LOG_LEVEL >= SHRN_LOG_LEVEL_ERROR</tt>
     * otherwise calls \p SHRN_DEBUG_BREAK().
     */
    #define SHRN_REL_ASSERT(cond, section, ...) if (!(cond)) { Shroon::Logger::LogFatalError(section, Shroon::Logger::Format(__VA_ARGS__)); }
#else
    #define SHRN_REL_ERROR(...)

    #define SHRN_REL_ASSERT(...) SHRN_DEBUG_BREAK()
#endif
/**
 * @}
 * @}
 */


/**
 * @brief The namespace in which all the projects under Shroon exist.
 */
namespace Shroon
{
    /**
     * @brief The namespace in which all the ShroonCPPLogger API other than macros exists.
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
         * and performs a \p SHRN_DEBUG_BREAK().
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

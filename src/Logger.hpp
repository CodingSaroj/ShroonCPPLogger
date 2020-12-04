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

#include "CLIColors.hpp"
#include "StringFormat.hpp"

#ifndef PG_LOG_LEVEL
    #define PG_LOG_LEVEL 3
#endif

#ifdef DEBUG
    #if PG_LOG_LEVEL >= 1
        #define PG_INFO(section, ...) Peregrine::Logger::LogInfo(section, Format(__VA_ARGS__))
    #endif

    #if PG_LOG_LEVEL >= 2
        #define PG_WARNING(section, ...) PeregrineLogger::LogWarning(section, Format(__VA_ARGS__))
    #endif

    #if PG_LOG_LEVEL == 3
        #define PG_ERROR(section, ...) Peregrine::Logger::LogError(section, Format(__VA_ARGS__))

        #define PG_ASSERT(cond, section, ...) if (!(cond)) { Peregrine::Logger::LogFatalError(section, Format(__VA_ARGS__)); exit(2); }
    #endif
#else
    #define PG_INFO(...)
    #define PG_WARNING(...)
    #define PG_ERROR(...)

    #define PG_ASSERT(cond, ...)
#endif

#define PG_REL_INFO(section, ...) Peregrine::Logger::LogInfo(section, Format(__VA_ARGS__))
#define PG_REL_WARNING(section, ...) Peregrine::Logger::LogWarning(section, Format(__VA_ARGS__))
#define PG_REL_ERROR(section, ...) Peregrine::Logger::LogError(section, Format(__VA_ARGS__))
#define PG_REL_ASSERT(cond, section, ...) if (!(cond)) { Peregrine::Logger::LogFatalError(section, Format(__VA_ARGS__)); exit(2); }

namespace Peregrine
{
    namespace Logger
    {
        static void SetOStream(std::ostream & out);

        static void LogInfo(const std::string & section, const std::string & log);
        static void LogWarning(const std::string & section, const std::string & log);
        static void LogError(const std::string & section, const std::string & log);
        static void LogFatalError(const std::string & section, const std::string & log);
    }
}

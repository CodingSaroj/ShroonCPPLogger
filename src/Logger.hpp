#pragma once

#include "CLIColors.hpp"
#include "StringFormat.hpp"

#ifndef PG_LOG_LEVEL
    #define PG_LOG_LEVEL 3
#endif

#ifdef DEBUG
    #if PG_LOG_LEVEL >= 1
        #define PG_INFO(section, ...) Logger::LogInfo(section, Format(__VA_ARGS__))
    #endif

    #if PG_LOG_LEVEL >= 2
        #define PG_WARNING(section, ...) Logger::LogWarning(section, Format(__VA_ARGS__))
    #endif

    #if PG_LOG_LEVEL == 3
        #define PG_ERROR(section, ...) Logger::LogError(section, Format(__VA_ARGS__))

        #define PG_ASSERT(cond, section, ...) if (!(cond)) { Logger::LogFatalError(section, Format(__VA_ARGS__)); exit(2); }
    #endif
#else
    #define PG_INFO(...)
    #define PG_WARNING(...)
    #define PG_ERROR(...)

    #define PG_ASSERT(cond, ...)
#endif

#define PG_REL_INFO(section, ...) Logger::LogInfo(section, Format(__VA_ARGS__))
#define PG_REL_WARNING(section, ...) Logger::LogWarning(section, Format(__VA_ARGS__))
#define PG_REL_ERROR(section, ...) Logger::LogError(section, Format(__VA_ARGS__))
#define PG_REL_ASSERT(cond, section, ...) if (!(cond)) { Logger::LogFatalError(section, Format(__VA_ARGS__)); exit(2); }

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

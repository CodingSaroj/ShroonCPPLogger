#include "Peregrine/Logger/LogLevels.hpp"

#define PG_LOG_LEVEL PG_LOG_LEVEL_INFO
#include "Peregrine/Logger/Logger.hpp"

int main()
{
#ifndef DEBUG
    PG_REL_INFO("Example", "In Release mode.");
#else
    PG_REL_INFO("Example", "In Debug mode.");
#endif

    // String formatting test.
    std::cout<<Peregrine::Logger::Format(
R"(String formatting is working.
|{wc10}|{wc10}|{wf6:wc10}|{x:wc10}|
)",                                     // Format string
        "String", 3456, 3.456, 0xbaba   // Format args
    );

    PG_INFO("Example", "{} is working.", "PG_INFO");
    PG_WARNING("Example", "{} is working.", "PG_WARNING");
    PG_ERROR("Example", "{} is working.", "PG_ERROR");

    PG_REL_INFO("Example", "{} is working.", "PG_REL_INFO");
    PG_REL_WARNING("Example", "{} is working.", "PG_REL_WARNING");
    PG_REL_ERROR("Example", "{} is working.", "PG_REL_ERROR");

    PG_REL_ASSERT(false, "{} is working", "PG_REL_ASSERT");
    PG_ASSERT(false, "{} is working", "PG_ASSERT");
}

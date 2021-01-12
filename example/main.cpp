#include "Peregrine/Logger/LogLevels.hpp"

#define PG_LOG_LEVEL PG_LOG_LEVEL_INFO
#include "Peregrine/Logger/Logger.hpp"

int main()
{
    // Debug/Release mode checks.
    std::cout<<"Debug/Release mode checks\n";
    std::cout<<"--------------------------------\n\n";

#ifdef NDEBUG
    PG_REL_INFO("Example", "In Release mode.");
#else
    PG_REL_INFO("Example", "In Debug mode.");
#endif

    // String formatting test.
    std::cout<<"\nString formatting test\n";
    std::cout<<"--------------------------------\n\n";

    std::cout<<Peregrine::Logger::Format(
        // Format string
        "|{wc10}|{wc10}|{wf6:wc10}|{x:wc10}|\n",

        // Format args
        "String", 3456, 3.456, 0xbaba
    );

    // Text color and style test
    std::cout<<"\nText color and style text\n";
    std::cout<<"--------------------------------\n\n";

    std::cout<<Peregrine::Logger::Format("{cwhtbx}It's bold on Non-Windows system!{cwhtxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{cwhtxi}It's italic on Non-Windows system!{cwhtxx}\n", "", "");

    std::cout<<Peregrine::Logger::Format("{cwhtxx}It's white!{cwhtxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{credxx}It's red!{credxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{cgrnxx}It's green!{cwhtxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{cbluxx}It's blue!{cwhtxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{cylwxx}It's yellow!{cwhtxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{ccynxx}It's cyan!{cwhtxx}\n", "", "");
    std::cout<<Peregrine::Logger::Format("{cpnkxx}It's pink!{cwhtxx}\n", "", "");

    std::cout<<"\nLogging functions test\n";
    std::cout<<"--------------------------------\n\n";

    PG_INFO("Example", "{} is working.", "PG_INFO");
    PG_WARNING("Example", "{} is working.", "PG_WARNING");
    PG_ERROR("Example", "{} is working.", "PG_ERROR");

    PG_REL_INFO("Example", "{} is working.", "PG_REL_INFO");
    PG_REL_WARNING("Example", "{} is working.", "PG_REL_WARNING");
    PG_REL_ERROR("Example", "{} is working.", "PG_REL_ERROR");

    PG_REL_ASSERT(false, "Example", "{} is working.", "PG_REL_ASSERT");
    PG_ASSERT(false, "Example", "{} is working.", "PG_ASSERT");
}

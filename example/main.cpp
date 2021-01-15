#include "Shroon/Logger/LogLevels.hpp"

#define SHRN_LOG_LEVEL SHRN_LOG_LEVEL_INFO
#include "Shroon/Logger/Logger.hpp"

int main()
{
    // Debug/Release mode checks.
    std::cout<<"Debug/Release mode checks\n";
    std::cout<<"--------------------------------\n\n";

#ifdef NDEBUG
    SHRN_REL_INFO("Example", "In Release mode.");
#else
    SHRN_REL_INFO("Example", "In Debug mode.");
#endif

    // String formatting test.
    std::cout<<"\nString formatting test\n";
    std::cout<<"--------------------------------\n\n";

    std::cout<<Shroon::Logger::Format(
        // Format string
        "|{wc10}|{wc10}|{wf6:wc10}|{x:wc10}|\n",

        // Format args
        "String", 3456, 3.456, 0xbaba
    );

    // Text color and style test
    std::cout<<"\nText color and style text\n";
    std::cout<<"--------------------------------\n\n";

    std::cout<<Shroon::Logger::Format("{cwhtbx}It's bold on Non-Windows system!{cwhtxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{cwhtxi}It's italic on Non-Windows system!{cwhtxx}\n", "", "");

    std::cout<<Shroon::Logger::Format("{cwhtxx}It's white!{cwhtxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{credxx}It's red!{credxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{cgrnxx}It's green!{cwhtxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{cbluxx}It's blue!{cwhtxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{cylwxx}It's yellow!{cwhtxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{ccynxx}It's cyan!{cwhtxx}\n", "", "");
    std::cout<<Shroon::Logger::Format("{cpnkxx}It's pink!{cwhtxx}\n", "", "");

    std::cout<<"\nLogging functions test\n";
    std::cout<<"--------------------------------\n\n";

    SHRN_INFO("Example", "{} is working.", "SHRN_INFO");
    SHRN_WARNING("Example", "{} is working.", "SHRN_WARNING");
    SHRN_ERROR("Example", "{} is working.", "SHRN_ERROR");

    SHRN_REL_INFO("Example", "{} is working.", "SHRN_REL_INFO");
    SHRN_REL_WARNING("Example", "{} is working.", "SHRN_REL_WARNING");
    SHRN_REL_ERROR("Example", "{} is working.", "SHRN_REL_ERROR");

    SHRN_REL_ASSERT(false, "Example", "{} is working.", "SHRN_REL_ASSERT");
    SHRN_ASSERT(false, "Example", "{} is working.", "SHRN_ASSERT");
}

#include "Logger.hpp"

namespace Peregrine
{
    namespace Logger
    {
        std::ostream * s_Out = &std::cout;
        
        void SetOStream(std::ostream & out)
        {
            s_Out = &out;
        }

        void LogInfo(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("{}Info{}::{}: {}\n", Colors::Blue | Colors::Bold, Colors::White, section, log);
        }

        void LogWarning(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("{}Warning{}::{}: {}\n", Colors::Yellow | Colors::Bold, Colors::White, section, log);
        }

        void LogError(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("{}Error{}::{}: {}\n", Colors::Red | Colors::Bold, Colors::White, section, log);
        }

        void LogFatalError(const std::string & section, const std::string & log)
        {
            std::cerr<<Format("{}Error{}::{}: {}\n", Colors::Red | Colors::Bold, Colors::White, section, log);
        }
    }
}

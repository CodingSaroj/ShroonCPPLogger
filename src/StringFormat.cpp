#include "StringFormat.hpp"

namespace Peregrine
{
    namespace Logger
    {
        std::string FormatBase(std::string && format, std::initializer_list<std::string> args)
        {
            size_t lastMatch = format.find('{', 0);
        
            for (auto & arg : args)
            {
                if (lastMatch == std::string::npos)
                {
                    break;
                }
        
                format.replace(lastMatch, 2, arg);
        
                lastMatch = format.find('{', lastMatch);
            }
        
            return std::move(format);
        }
    }
}

#pragma once

#include <iostream>

#include <sstream>
#include <string>

namespace Peregrine
{
    namespace Logger
    {
        std::string FormatBase(std::string && format, std::initializer_list<std::string> args);
   
        template <typename Type>
        std::string FormatArg(const Type & t)
        {
            std::stringstream out;
            out<<t;
            return std::move(out.str());
        }
        
        template <typename... Args>
        std::string Format(std::string && format, Args... args)
        {
            return FormatBase(std::move(format), {std::move(FormatArg(args))...});
        }
    }
}

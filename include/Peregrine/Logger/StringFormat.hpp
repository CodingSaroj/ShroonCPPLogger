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

#include <functional>
#include <iomanip>
#include <iostream>

#include <sstream>
#include <string>

namespace Peregrine
{
    namespace Logger
    {
        /*
         * Outputs a string with all the "{}" replaced with each element in `args` inside `format`.
         * Use Format instead.
         * 
         * format - std::string which needs to be formatted.
         * args - std::initializer_list containing format args.
         * returns - a std::string with all the "{}" replaced with each element in `args` inside `format`.
         */
        std::string FormatBase(const std::string & format, std::initializer_list<std::string> args);
        
        /*
         * Outputs a string with all the "{}" replaced with each element in `args` inside `format`.
         * Use Format instead.
         * 
         * format - std::string which needs to be formatted.
         * args - std::initializer_list containing format args.
         * returns - a std::string with all the "{}" replaced with each element in `args` inside `format`.
         */
        std::string FormatBase(std::string && format, std::initializer_list<std::string> args);
   
        /*
         * Coverts variable to std::string using operator<<.
         * 
         * t - variable to convert to string.
         * flags - flags to pass to stream before variable.
         * returns - std::string version of variable according to the operator<<.
         */
        template <typename Type, typename... IOSFlagTypes>
        inline std::string ToString(const Type & t, IOSFlagTypes... flags)
        {
            std::ostringstream out;
            ((out<<flags), ...);
            out<<t;
            return std::move(out.str());
        }
  
        /*
         * Outputs a string with all the "{}" replaced with positional `args` inside `format`.
         * 
         * format - std::string which needs to be formatted.
         * args - Argument pack of variables containing format args.
         * returns - a std::string with all the "{}" replaced with `args` inside `format`.
         */
        template <typename... Args>
        std::string Format(const std::string & format, Args... args)
        {
            return FormatBase(
                format,                         // Pass the format string as is
                {std::move(ToString(args))...}  // Expand argument pack to create an std::initializer_list of std::string returned by ToString.
            );
        }

        /*
         * Outputs a string with all the "{}" replaced with positional `args` inside `format`.
         * 
         * format - std::tring which needs to be formatted.
         * args - Argument pack of variables containing format args.
         * returns - a std::string with all the "{}" replaced with `args` inside `format`.
         */
        template <typename... Args>
        std::string Format(std::string && format, Args... args)
        {
            std::stringstream out;

            return FormatBase(
                std::move(format),              // Pass the format string as is
                {std::move(ToString(args))...}  // Expand argument pack to create an std::initializer_list of std::string returned by ToString.
            );
        }
    }
}

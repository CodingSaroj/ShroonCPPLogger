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

#include <iomanip>
#include <iostream>

#include <sstream>
#include <string>
#include <vector>

/**
 * @brief The namespace in which all the projects under Peregrine exist.
 */
namespace Peregrine
{
    /**
     * @brief The namespace in which all the PeregrineCPPLogger API other than macros exists.
     */
    namespace Logger
    {
        /**
         * @defgroup FormatFunctions
         * This group consists of all the functions used for formatting.
         * @{
         */

        /**
         * @brief Outputs a string with all the "{}" replaced with each element in \p args inside \p format.
         * 
         * @param format An <tt>const std::string &</tt> which needs to be formatted.
         * @param args An \p std::initializer_list containing format args.
         *
         * @return An \p std::string with all the "{}" replaced with each element in \p args inside \p format.
         */
        std::string FormatBase(const std::string & format, std::initializer_list<std::string> args);
        
        /**
         * @brief Outputs an \p std::string with all the "{}" replaced with each element in \p args inside \p format.
         * 
         * @param format An <tt>std::string &&</tt> which needs to be formatted.
         * @param args An \p std::initializer_list containing format args.
         *
         * @return An \p std::string with all the "{}" replaced with each element in \p args inside \p format.
         */
        std::string FormatBase(std::string && format, std::initializer_list<std::string> args);

        /**
         * @brief Converts variable of type \p Type to \p std::string using \p operator<<.
         * 
         * @tparam Type Type of variable which will be converted.
         * @tparam IOSFlagTypes A parameter pack of types of functors which will be passed to \p operator<<.
         *
         * @param t Variable to convert to string.
         * @param flags Flags to pass to stream before variable.
         * 
         * @return An \p std::string version of variable according to the \p operator<<.
         */
        template <typename Type, typename... IOSFlagTypes>
        inline std::string ToString(const Type & t, IOSFlagTypes... flags)
        {
            std::ostringstream out;
            ((out<<flags), ...);
            out<<t;
            return std::move(out.str());
        }
  
        /**
         * @brief Outputs a string with all the "{}" replaced with positional `args` inside `format`.
         * 
         * @param format - An `std::string` which needs to be formatted.
         * @param args - Argument pack of variables containing format args.
         * 
         * @return - An `std::string` with all the "{}" replaced with `args` inside `format`.
         */
        template <typename... Args>
        std::string Format(const std::string & format, Args... args)
        {
            return FormatBase(
                format,                         // Pass the format string as is
                {std::move(ToString(args))...}  // Expand argument pack to create an std::initializer_list of std::string returned by ToString.
            );
        }

        /**
         * @brief Outputs a string with all the "{}" replaced with positional `args` inside `format`.
         * 
         * @param format An \p std::tring which needs to be formatted.
         * @param args Argument pack of variables containing format args.
         * 
         * @return An \p std::string with all the "{}" replaced with \p args inside \p format.
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

        /**
         * @}
         */
    }
}

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
#include "StringFormat.hpp"

namespace Peregrine
{
    namespace Logger
    {
        std::string FormatBase(const std::string & format, std::initializer_list<std::string> args)
        {
            std::string formatted(format);

            // Find the first '{'
            size_t lastMatch = format.find('{', 0);
        
            for (auto & arg : args)
            {
                // If '{' isn't found in format
                if (lastMatch == std::string::npos)
                {
                    break;
                }

                // Replace "{}"
                formatted.replace(lastMatch, 2, arg);

                // Find the next '{'
                lastMatch = formatted.find('{', lastMatch);
            }
        
            return formatted;
        }

        std::string FormatBase(std::string && format, std::initializer_list<std::string> args)
        {
            // Find the first '{'
            size_t lastMatch = format.find('{', 0);
        
            for (auto & arg : args)
            {
                // If '{' isn't found in format
                if (lastMatch == std::string::npos)
                {
                    break;
                }

                // Replace "{}"
                format.replace(lastMatch, 2, arg);

                // Find the next '{'
                lastMatch = format.find('{', lastMatch);
            }
        
            return std::move(format);
        }
    }
}

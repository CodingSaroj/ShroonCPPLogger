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
            return FormatBase(std::string(format), args);
        }

        std::string FormatBase(std::string && format, std::initializer_list<std::string> args)
        {
            // Find the first '{'
            size_t lastMatch = format.find('{', 0);
        
            for (auto & arg : args)
            {
                std::string argStr(arg);

                // If '{' isn't found in format
                if (lastMatch == std::string::npos)
                {
                    break;
                }

                std::vector<std::string> flags;

                std::string currentFlag;

                size_t sizeToReplace = 2;

                // Collect flags
                for (size_t i = lastMatch + 1; format[i] != '}'; i++)
                {
                    // Flags are seperated by ':' e.g. {x:wi8} will set width to 8 and output in hex
                    if (format[i] == ':')
                    {
                        flags.emplace_back(currentFlag);
                        currentFlag.clear();
                    }
                    else
                    {
                        currentFlag += format[i];
                    }

                    // If next character is '}'
                    if (format[i + 1] == '}')
                    {
                        flags.emplace_back(currentFlag);
                        currentFlag.clear();

                        sizeToReplace = (i - lastMatch) + 2;
                    }
                }

                // Processing the flags
                for (auto & flag : flags)
                {
                    if (flag == "b")
                    {
                        bool argBool = strtoul(argStr.c_str(), nullptr, 10);
                        argStr = argBool ? "true" : "false";
                    }
                    else if (flag == "o")
                    {
                        uint64_t argDec = strtoul(argStr.c_str(), nullptr, 10);
                        argStr = ToString(argDec, std::oct);
                    }
                    else if (flag == "x")
                    {
                        uint64_t argDec = strtoul(argStr.c_str(), nullptr, 10);
                        argStr = ToString(argDec, std::hex);
                    }
                    else if (flag == "f")
                    {
                        double argFlt = strtod(argStr.c_str(), nullptr);
                        argStr = ToString(argFlt, std::fixed);
                    }
                    else if (flag[0] == 'w')
                    {
                        uint32_t width = strtoul(&flag[2], nullptr, 10);

                        if (flag[1] == 'l')
                        {
                            if (argStr.size() < width)
                            {
                                argStr.insert(argStr.begin(), width - argStr.size(), ' ');
                            }
                        }
                        else if (flag[1] == 't')
                        {
                            if (argStr.size() < width)
                            {
                                argStr.insert(argStr.end(), width - argStr.size(), ' ');
                            }
                        }
                        else if (flag[1] == 'c')
                        {
                            if (argStr.size() < width)
                            {
                                size_t numSpaces = width - argStr.size();
                                size_t numLeadingSpaces = 0, numTrailingSpaces = 0;
                                
                                if (numSpaces % 2)
                                {
                                    numLeadingSpaces = numSpaces - 1 / 2;
                                    numTrailingSpaces = (numSpaces + 1) / 2;
                                }
                                else
                                {
                                    numLeadingSpaces = numSpaces / 2;
                                    numTrailingSpaces = numLeadingSpaces;
                                }

                                argStr.insert(argStr.begin(), numLeadingSpaces, ' ');
                                argStr.insert(argStr.end(), numTrailingSpaces, ' ');
                            }
                        }
                        else if (flag[1] == 'i')
                        {
                            uint64_t argNum = strtoul(argStr.c_str(), nullptr, 10);
                            argStr = ToString(argNum, std::setw(width), std::setfill('0'));
                        }
                        else if (flag[1] == 'f')
                        {
                            double argNum = strtod(argStr.c_str(), nullptr);
                            argStr = ToString(argNum, std::setprecision(width), std::fixed);
                        }
                    }
                    else if (flag[0] == 'c')
                    {
                        if (flag.size() == 6)
                        {
                            std::string colorCode = flag.substr(1, 3);
                            char bold = flag[4];
                            char italic = flag[5];

                            argStr = "\033[";

                            if (colorCode == "wht")
                            {
                                argStr += '0';
                            }
                            else if (colorCode == "red")
                            {
                                argStr += "31";
                            }
                            else if (colorCode == "grn")
                            {
                                argStr += "32";
                            }
                            else if (colorCode == "blu")
                            {
                                argStr += "34";
                            }
                            else if (colorCode == "ylw")
                            {
                                argStr += "33";
                            }
                            else if (colorCode == "cyn")
                            {
                                argStr += "36";
                            }
                            else if (colorCode == "pnk")
                            {
                                argStr += "35";
                            }
                            else
                            {
                                argStr += '0';
                            }

                            if (bold == 'b')
                            {
                                argStr += ";1";
                            }
                            
                            if (italic == 'i')
                            {
                                argStr += ";3";
                            }

                            argStr += 'm';
                        }
                    }
                }

                // Replace "{...}"
                format.replace(lastMatch, sizeToReplace, argStr);

                // Find the next '{'
                lastMatch = format.find('{', lastMatch);
            }
        
            return std::move(format);
        }
    }
}

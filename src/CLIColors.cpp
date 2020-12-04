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
#include "CLIColors.hpp"

#ifdef _WIN32
    #include <Windows.h>
#endif

namespace Peregrine
{
    namespace Colors
    {
        std::ostream & operator<<(std::ostream & out, const Format & fmt)
        {
            #if defined(_WIN32)
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                // Win32 Console doesn't support bold/italic

                if (fmt.test(2))
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else if (fmt.test(3))
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
                }
                else if (fmt.test(4))
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
                }
                else if (fmt.test(5))
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                }
                else if (fmt.test(6))
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
                }
            #elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
                out.write("\033[0;", 4);

                if (fmt.test(0))
                {
                    out.write("1;", 2);
                }
                else if (fmt.test(1))
                {
                    out.write("3;", 2);
                }

                if (fmt.test(2))
                {
                    out.write("0", 1);
                }
                else if (fmt.test(3))
                {
                    out.write("31", 2);
                }
                else if (fmt.test(4))
                {
                    out.write("34", 2);
                }
                else if (fmt.test(5))
                {
                    out.write("32", 2);
                }
                else if (fmt.test(6))
                {
                    out.write("33", 2);
                }

                out.write("m", 1);
            #endif

            return out;
        }
    }
}

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
        std::ostream & operator<<(std::ostream & out, const ColorFmt & fmt)
        {
            // If on Windows use the Win32 library.
            #if defined(_WIN32)
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                // Win32 Console doesn't support bold/italic

                if (fmt & White)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else if (fmt & Red)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
                }
                else if (fmt & Green)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                }
                else if (fmt & Blue)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
                }
                else if (fmt & Yellow)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
                }
                else if (fmt & Cyan)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else if (fmt & Pink)
                {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
                }

            // If on Unix-style OS or MacOS then use ANSI escape sequences.
            #elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))

                // Acheives color and bold/italic using ANSI escape sequences.

                out.write("\033[0;", 4);

                if (fmt & Bold)
                {
                    out.write("1;", 2);
                }
                else if (fmt & Italic)
                {
                    out.write("3;", 2);
                }

                if (fmt & White)
                {
                    out.write("0", 1);
                }
                else if (fmt & Red)
                {
                    out.write("31", 2);
                }
                else if (fmt & Green)
                {
                    out.write("32", 2);
                }
                else if (fmt & Blue)
                {
                    out.write("34", 2);
                }
                else if (fmt & Yellow)
                {
                    out.write("33", 2);
                }
                else if (fmt & Cyan)
                {
                    out.write("36", 2);
                }
                else if (fmt & Pink)
                {
                    out.write("35", 2);
                }

                out.write("m", 1);
            #endif

            return out;
        }
    }
}

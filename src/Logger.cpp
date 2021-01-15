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
#include "Logger.hpp"

#ifdef _WIN32
    #include <windows.h>
#endif

namespace Shroon
{
    namespace Logger
    {
    #ifdef _WIN32
        static bool s_Win32ConsoleInitialized = false;
    #endif

        // Use std::cout as default output stream.
        static std::ostream * s_Out = &std::cout;

        static const double s_StartTime = std::chrono::system_clock::now().time_since_epoch().count() / 1000000.0;

    #ifdef _WIN32
        static void InitWin32Console()
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            DWORD consoleMode = 0;

            GetConsoleMode(hConsole, &consoleMode);
            
            if (!(consoleMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
            {
                consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hConsole, consoleMode);
            }

            s_Win32ConsoleInitialized = true;
        }
    #endif

        static std::string GetTimestamp()
        {
            double now = std::chrono::system_clock::now().time_since_epoch().count() / 1000000.0;

            return Format("{wf6}", now - s_StartTime);
        }
        
        void SetOStream(std::ostream & out)
        {
            s_Out = &out;
        }

        void LogInfo(const std::string & section, const std::string & log)
        {
        #ifdef _WIN32
            if (!s_Win32ConsoleInitialized)
            {
                InitWin32Console();
            }
        #endif

            std::ostream & out = *s_Out;

            out<<Format("{cgrnbx}[{}]{ccynbx}Info::{}: {}{cwhtxx}\n", "", GetTimestamp(), "", section, log, "");
        }

        void LogWarning(const std::string & section, const std::string & log)
        {
        #ifdef _WIN32
            if (!s_Win32ConsoleInitialized)
            {
                InitWin32Console();
            }
        #endif

            std::ostream & out = *s_Out;

            out<<Format("{cgrnbx}[{}]{cylwbx}Warning::{}: {}{cwhtxx}\n", "", GetTimestamp(), "", section, log, "");
        }

        void LogError(const std::string & section, const std::string & log)
        {
        #ifdef _WIN32
            if (!s_Win32ConsoleInitialized)
            {
                InitWin32Console();
            }
        #endif

            std::ostream & out = *s_Out;

            out<<Format("{cgrnbx}[{}]{credbx}Error::{}: {}{cwhtxx}\n", "", GetTimestamp(), "", section, log, "");
        }

        void LogFatalError(const std::string & section, const std::string & log)
        {
        #ifdef _WIN32
            if (!s_Win32ConsoleInitialized)
            {
                InitWin32Console();
            }
        #endif

            std::cerr<<Format("{cgrnbx}[{}]{credbx}Error::{}: {}{cwhtxx}\n", "", GetTimestamp(), "", section, log, "");

            SHRN_DEBUG_BREAK();
        }
    }
}

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

namespace Peregrine
{
    namespace Logger
    {
        // Use std::cout as default output stream.
        static std::ostream * s_Out = &std::cout;

        static double GetTimestamp()
        {
            auto now = std::chrono::system_clock::now();

            return now.time_since_epoch().count();
        }
        
        void SetOStream(std::ostream & out)
        {
            s_Out = &out;
        }

        void LogInfo(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("[{}]{}Info{}::{}: {}\n", GetTimestamp(), Colors::Cyan | Colors::Bold, Colors::White, section, log);
        }

        void LogWarning(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("[{}]{}Warning{}::{}: {}\n", GetTimestamp(), Colors::Yellow | Colors::Bold, Colors::White, section, log);
        }

        void LogError(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("[{}]{}Error{}::{}: {}\n", GetTimestamp(), Colors::Red | Colors::Bold, Colors::White, section, log);
        }

        void LogFatalError(const std::string & section, const std::string & log)
        {
            std::cerr<<Format("[{}]{}Error{}::{}: {}\n", GetTimestamp(), Colors::Red | Colors::Bold, Colors::White, section, log);
            PG_DEBUG_BREAK();
        }
    }
}

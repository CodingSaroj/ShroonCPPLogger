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
        std::ostream * s_Out = &std::cout;
        
        void SetOStream(std::ostream & out)
        {
            s_Out = &out;
        }

        void LogInfo(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("{}Info{}::{}: {}\n", Colors::Blue | Colors::Bold, Colors::White, section, log);
        }

        void LogWarning(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("{}Warning{}::{}: {}\n", Colors::Yellow | Colors::Bold, Colors::White, section, log);
        }

        void LogError(const std::string & section, const std::string & log)
        {
            std::ostream & out = *s_Out;

            out<<Format("{}Error{}::{}: {}\n", Colors::Red | Colors::Bold, Colors::White, section, log);
        }

        void LogFatalError(const std::string & section, const std::string & log)
        {
            std::cerr<<Format("{}Error{}::{}: {}\n", Colors::Red | Colors::Bold, Colors::White, section, log);
        }
    }
}

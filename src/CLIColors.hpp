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

#include <iostream>

#include <bitset>

namespace Peregrine
{
    namespace Colors
    {
        class Format 
        {
        public:
            inline Format(const std::bitset<7> & bitset)
                : m_Base(bitset)
            {
            }

            inline Format(const std::string & bitset)
                : m_Base(bitset)
            {
            }

            inline bool test(size_t index) const
            {
                return m_Base.test(index);
            }

            Format operator|(Format fmt) const
            {
                return m_Base | fmt.m_Base;
            }

        private:
            std::bitset<7> m_Base;
        };

        const Format Bold("0000001");
        const Format Italic("0000010");

        const Format White("0000100");
        const Format Red("0001000");
        const Format Blue("0010000");
        const Format Green("0100000");
        const Format Yellow("1000000");

        std::ostream & operator<<(std::ostream & out, const Format & fmt);
    }
}

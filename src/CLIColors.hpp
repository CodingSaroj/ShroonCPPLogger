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

#include <cstdint>

namespace Peregrine
{
    namespace Colors
    {
        /*
         * Wrapper for uint8_t, so operator<< doesn't override the
         * default operator<< for uint8_t.
         */
        class ColorFmt
        {
        public:
            explicit inline ColorFmt(uint16_t fmt)
                : m_Fmt(fmt)
            {
            }

            uint16_t operator&(uint16_t mask) const
            {
                return m_Fmt & mask;
            }

            ColorFmt operator&(ColorFmt mask) const
            {
                return ColorFmt(m_Fmt & mask.m_Fmt);
            }

            uint16_t operator|(uint16_t mask) const
            {
                return m_Fmt | mask;
            }

            ColorFmt operator|(ColorFmt mask) const
            {
                return ColorFmt(m_Fmt | mask.m_Fmt);
            }

            operator bool() const
            {
                return m_Fmt;
            }

        private:
            const uint16_t m_Fmt;
        };

        // Bold/Italic not available on Windows. Using it on Windows has no effects.
        const ColorFmt Bold(0x1);
        const ColorFmt Italic(0x2);

        /*
         * Bitmasks for common color codes.
         */
        const ColorFmt White(0x4);
        const ColorFmt Red(0x8);
        const ColorFmt Green(0x10);
        const ColorFmt Blue(0x20);
        const ColorFmt Yellow(0x40);
        const ColorFmt Cyan(0x80);
        const ColorFmt Pink(0x100);

        /*
         * operator<< so, you can pass it into an std::ostream to set text color.
         */
        std::ostream & operator<<(std::ostream & out, const ColorFmt & fmt);
    }
}

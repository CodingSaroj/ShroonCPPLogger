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

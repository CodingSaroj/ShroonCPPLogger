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

/**
 * @brief The namespace in which all the projects under Peregrine exist.
 */
namespace Peregrine
{
    /**
     * @brief The namespace in which all the PeregrineCPPLogger API other than macros exists.
     */
    namespace Logger
    {
        /**
         * @defgroup TextFormatting
         * This group consists of functions and classes used in the process of stylizing(color,bold & italic) text.
         * @{
         */

        /**
         * @brief Wrapper for \p uint8_t, so \p operator<< doesn't override the
         * default \p operator<< for \p uint8_t.
         */
        class TextFormat
        {
        public:
            /**
             * @defgroup TextFormatFlags
             * @ingroup TextFormatting
             * This group contains all possible values for \p TextFormat.
             * @{
             */

            /**
             * @brief Enum containing values for different text format flags.
             */
            enum FormatFlags : uint16_t
            {
                Bold    = 0x0001,   ///< @brief Changes the style of stream output to be bold. This doesn't work on Windows.
                Italic  = 0x0002,   ///< @brief Changes the style of stream output to be italic. This doesn't work on Windows.

                White   = 0x0004,   ///< @brief Changes the color of stream output to be white.
                Red     = 0x0008,   ///< @brief Changes the color of stream output to be red.
                Green   = 0x0010,   ///< @brief Changes the color of stream output to be green.
                Blue    = 0x0020,   ///< @brief Changes the color of stream output to be blue.
                Yellow  = 0x0040,   ///< @brief Changes the color of stream output to be yellow.
                Cyan    = 0x0080,   ///< @brief Changes the color of stream output to be cyan.
                Pink    = 0x0100    ///< @brief Changes the color of stream output to be pink.
            };
            /**
             * @}
             */

            /**
             * @brief Constructs a \p TextFormat with format as \p fmt.
             *
             * @param fmt The format this \p TextFormat will contain.
             */
            TextFormat(uint16_t fmt) : m_Fmt(fmt) {}

            /**
             * @brief "and"s the format with \p mask.
             *
             * @param mask The mask to use.
             *
             * @return The result of "and".
             */
            uint16_t operator&(uint16_t mask) const { return m_Fmt & mask; }

            /**
             * @brief "and"s the format with \p mask.
             *
             * @param mask The mask to use.
             *
             * @return The result of "and".
             */
            TextFormat operator&(TextFormat mask) const { return TextFormat(m_Fmt & mask.m_Fmt); }

            /**
             * @brief "or"s the format with \p mask.
             *
             * @param mask The mask to use.
             *
             * @return The result of "or".
             */
            uint16_t operator|(uint16_t mask) const { return m_Fmt | mask; }

            /**
             * @brief "or"s the format with \p mask.
             *
             * @param mask The mask to use.
             *
             * @return The result of "or".
             */
            TextFormat operator|(TextFormat mask) const { return TextFormat(m_Fmt | mask.m_Fmt); }

            /**
             * @brief Checks if the format is non-zero.
             *
             * @return A \p bool which is \p true when format is non-zero, \p false otherwise.
             */
            operator bool() const { return m_Fmt; }

        private:
            uint16_t m_Fmt;
        };

        /**
         * @brief \p operator<< so \p TextFormat can be passed into an \p std::ostream to set text color.
         *
         * @param out The \p std::ostream to which the \p fmt will be applied.
         * @param fmt The \p TextFormat to apply to \p out.
         *
         * @return \p out with \p fmt applied.
         */
        std::ostream & operator<<(std::ostream & out, const TextFormat & fmt);

        /**
         * @}
         */
    }
}

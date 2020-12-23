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

/**
 * @defgroup LogLevel
 * This group contains all possible values for \p PG_LOG_LEVEL. The default value
 * is PG_LOG_LEVEL_INFO i.e. 3.
 * @{
 */

#define PG_LOG_LEVEL_INFO 3     ///< @brief Allows logs of level Info, Warning and Error.
#define PG_LOG_LEVEL_WARNING 2  ///< @brief Allows logs of level Warning and Error.
#define PG_LOG_LEVEL_ERROR 1    ///< @brief Allows logs of level Error.
#define PG_LOG_LEVEL_NO_LOG 0   ///< @brief Doesn't allow any logs.

/**
 * @}
 */

/*
 * Copyright 2010-2013 DIMA Research Group, TU Berlin
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
 * 
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "myriad/core/types.h"

namespace Myriad {
/**
 * @addtogroup core
 * @{*/

/**
 * A holder for application specific constants.
 *
 * All constants are declared as static members and are defined in the
 * generator extension C++ sources (typically in core/main.cpp file).
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 */
struct Constant
{
    /**
     * The name of the data generator application.
     */
    static const String APP_NAME;
    /**
     * The version of the data generator application.
     */
    static const String APP_VERSION;
};

/** @}*/// add to core group
}  // namespace Myriad

#endif /* CONFIG_H_ */

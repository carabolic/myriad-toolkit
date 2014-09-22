/*
 * Copyright 2010-2014 DIMA Research Group, TU Berlin
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

#ifndef UTIL_H_
#define UTIL_H_

#include "core/exceptions.h"
#include "core/types.h"

#include <Poco/Format.h>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace Poco;
using namespace std;

namespace Myriad {
/**
 * @addtogroup math
 * @{*/

////////////////////////////////////////////////////////////////////////////////
/// @name Utility Function Declarations
////////////////////////////////////////////////////////////////////////////////
//@{

/**
 * Calculate x * y % N.
 *
 * @param x
 * @param y
 * @param N
 * @param InvN
 * @return
 */
I64 modmult(const I64 x, const I64 y, const I64 N, const Decimal InvN);

/**
 * Calculate (x ^ e % n) fast.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 *
 * @param x
 * @param e
 * @param N
 * @return
 */
I64u modexp(I64u x, I64u e, I64u N);

/**
 * Run a Miller-Rabin primality with loop length k on the input n.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 *
 * @param N
 * @param k
 * @return True, if N is found to be prime after k Miller-Rabin tests.
 */
bool isPrime(I64u N, const I16u k = 9);

/**
 * Return the smallest prime greater or equal to the lower bound l.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 *
 * @param l
 * @return The first prime greter or equal to \p l.
 */
I64u nextPrime(const I64u l);

/**
 * Compute the integer power x^e.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 *
 * @param x
 * @param e
 * @return x^e
 */
I64u power(I32u x, I16u e);

/**
 * Compute the nearest power of 2 of x.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 *
 * @param x
 * @return An integer \p y, such that <tt>abs(2^y - x)</tt> is minimal.
 */
I64u nearestPow2(I64u x);

/**
 * Compute the log2 of an exact power of 2.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 *
 * @param x
 * @return The logarithm of \p to the base of 2.
 */
I16u log2exact(I64u x);

//@}

/** @}*/// add to math group
} // namespace Myriad

#endif /* UTIL_H_ */

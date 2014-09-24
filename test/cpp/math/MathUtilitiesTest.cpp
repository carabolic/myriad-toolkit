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
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 * @author: Christoph Brücke <christoph.bruecke@campus.tu-berlin.de>
 */


#include "math/util.h"

#include "gtest/gtest.h"

namespace Myriad {

	TEST(MathUtilsTest, testModmult) {
		I64 N1 = 8832000017LL;
		Decimal InvN1 = 1.0/(Decimal) N1;

		I64 N2 = 2208000007LL;
		Decimal InvN2 = 1.0/(Decimal) N2;

		ASSERT_EQ(modmult(2717447886LL, 2717447886LL, N1, InvN1), 8832000016LL);
		ASSERT_EQ(modmult(550867102LL, 1010693226LL, N2, InvN2), 604567935LL);
	}

	TEST(MathUtilsTest, testModexp) {
		ASSERT_EQ(modexp(266905, 980448, 980449), 1);
		ASSERT_EQ(modexp(1804289385ULL, 0, 8832000017ULL), 1);
		ASSERT_EQ(modexp(1804289385ULL, 552000001ULL, 8832000017ULL), 7296544323ULL);
		ASSERT_EQ(modexp(1804289385ULL, 8832000016ULL, 8832000017ULL), 1);
		ASSERT_EQ(modexp(1804289385ULL, 1104000003ULL, 2208000007ULL), 1);
	}

    TEST(MathUtilsTest, testIsPrime) {
        ASSERT_TRUE(isPrime(251ULL));
        ASSERT_TRUE(isPrime(907ULL));
        ASSERT_TRUE(isPrime(271ULL));
        ASSERT_TRUE(isPrime(719ULL));
        ASSERT_TRUE(isPrime(137ULL));
        ASSERT_TRUE(isPrime(281ULL));
        ASSERT_TRUE(isPrime(487ULL));
        ASSERT_TRUE(isPrime(739ULL));
        ASSERT_TRUE(isPrime(887ULL));
        ASSERT_TRUE(isPrime(37));
        ASSERT_TRUE(isPrime(53));
        ASSERT_TRUE(isPrime(751ULL));
        ASSERT_TRUE(isPrime(503ULL));
        ASSERT_TRUE(isPrime(29ULL));
        ASSERT_TRUE(isPrime(980449ULL));
        ASSERT_TRUE(isPrime(88320007ULL));
        ASSERT_TRUE(isPrime(8832000017ULL));
        ASSERT_TRUE(isPrime(2208000007ULL));

		ASSERT_FALSE(isPrime(963ULL));
		ASSERT_FALSE(isPrime(574ULL));
		ASSERT_FALSE(isPrime(423ULL));
		ASSERT_FALSE(isPrime(388ULL));
		ASSERT_FALSE(isPrime(303ULL));
		ASSERT_FALSE(isPrime(471ULL));
		ASSERT_FALSE(isPrime(573ULL));
		ASSERT_FALSE(isPrime(626ULL));
		ASSERT_FALSE(isPrime(554ULL));
		ASSERT_FALSE(isPrime(196ULL));
		ASSERT_FALSE(isPrime(176ULL));
		ASSERT_FALSE(isPrime(316ULL));
		ASSERT_FALSE(isPrime(174ULL));
		ASSERT_FALSE(isPrime(968ULL));
		ASSERT_FALSE(isPrime(493ULL));
		ASSERT_FALSE(isPrime(890ULL));
		ASSERT_FALSE(isPrime(886ULL));
		ASSERT_FALSE(isPrime(973ULL));
		ASSERT_FALSE(isPrime(234ULL));
		ASSERT_FALSE(isPrime(414ULL));
		ASSERT_FALSE(isPrime(986ULL));
		ASSERT_FALSE(isPrime(688ULL));
		ASSERT_FALSE(isPrime(319ULL));
		ASSERT_FALSE(isPrime(482ULL));
		ASSERT_FALSE(isPrime(774ULL));
		ASSERT_FALSE(isPrime(714ULL));
		ASSERT_FALSE(isPrime(610ULL));
		ASSERT_FALSE(isPrime(657ULL));
		ASSERT_FALSE(isPrime(380ULL));
		ASSERT_FALSE(isPrime(159ULL));
		ASSERT_FALSE(isPrime(18));
		ASSERT_FALSE(isPrime(80));
		ASSERT_FALSE(isPrime(356ULL));
		ASSERT_FALSE(isPrime(1));
		ASSERT_FALSE(isPrime(88));
		ASSERT_FALSE(isPrime(391ULL));
		ASSERT_FALSE(isPrime(0ULL));
		ASSERT_FALSE(isPrime(88320001ULL));
		ASSERT_FALSE(isPrime(220800007ULL));
		ASSERT_FALSE(isPrime(8832000000ULL));
		ASSERT_FALSE(isPrime(2208000005ULL));
	}

    TEST(MathUtilsTest, testNextPrime) {
		ASSERT_EQ(nextPrime(1000ULL), 1009ULL);
		ASSERT_EQ(nextPrime(4322ULL), 4327ULL);
		ASSERT_EQ(nextPrime(53121ULL), 53129ULL);
		ASSERT_EQ(nextPrime(43224ULL), 43237ULL);
		ASSERT_EQ(nextPrime(10324ULL), 10331ULL);
		ASSERT_EQ(nextPrime(17000ULL), 17011ULL);
		ASSERT_EQ(nextPrime(18050ULL), 18059ULL);
		ASSERT_EQ(nextPrime(980432ULL), 980449ULL);
		ASSERT_EQ(nextPrime(980449ULL), 980449ULL);
		ASSERT_EQ(nextPrime(342891ULL), 342899ULL);
		ASSERT_EQ(nextPrime(342899ULL), 342899ULL);
		ASSERT_EQ(nextPrime(8832000000ULL), 8832000017ULL);
		ASSERT_EQ(nextPrime(2208000000ULL), 2208000007ULL);
	}

    TEST(MathUtilsTest, testPower) {
		ASSERT_EQ(power(0, 0), 0);
		ASSERT_EQ(power(0, 123), 0);
		ASSERT_EQ(power(1, 0), 1);
		ASSERT_EQ(power(1, 42), 1);
		ASSERT_EQ(power(2, 6), 64);
		ASSERT_EQ(power(2, 17), 131072);
		ASSERT_EQ(power(7, 7), 823543);
		ASSERT_EQ(power(11, 5), 161051);
	}

    TEST(MathUtilsTest, testNearestPow2) {
		ASSERT_EQ(nearestPow2(32), 32);
		ASSERT_EQ(nearestPow2(33), 32);
		ASSERT_EQ(nearestPow2(47), 32);
		ASSERT_EQ(nearestPow2(48), 64);
		ASSERT_EQ(nearestPow2(4294967296ULL), 4294967296ULL);
		ASSERT_EQ(nearestPow2(4294999437ULL), 4294967296ULL);
		ASSERT_EQ(nearestPow2(6442450947ULL), 8589934592ULL);
		ASSERT_EQ(nearestPow2(13510798882111487ULL), 9007199254740992ULL);
		ASSERT_EQ(nearestPow2(13510798882111489ULL), 18014398509481984ULL);
		ASSERT_EQ(nearestPow2(18446744073709551615ULL), 9223372036854775808ULL);
	}

} // namespace Myriad

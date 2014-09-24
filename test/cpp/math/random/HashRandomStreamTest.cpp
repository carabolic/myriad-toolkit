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

#include "math/random/HashRandomStream.h"

#include "gtest/gtest.h"

using namespace Poco;
using namespace std;

namespace Myriad {

    class HashRandomStreamTest: public ::testing::Test
    {
    protected:
        HashRandomStream _random;
    };

    TEST_F(HashRandomStreamTest, testHierarchicalInterface) {
        HashRandomStream random = _random;

        UInt64 s1[1] = { 0ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s1));

        random.nextSubstream();

        for (int i = 0; i < 3; i++)
        {
            random.next();
        }

        UInt64 s2[1] = { 281474976710659ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s2));

        random.nextSubstream();
        for (int i = 0; i < 5; i++)
        {
            random.next();
        }

        UInt64 s3[1] = { 562949953421317ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s3));

        for (int i = 0; i < 52; i++)
        {
            random.nextChunk();
        }
        for (int i = 0; i < 23; i++)
        {
            random.next();
        }

        UInt64 s4[1] = { 562949953434647ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s4));

        random.resetChunk();
        for (int i = 0; i < 180; i++)
        {
            random.next();
        }

        UInt64 s5[1] = { 562949953434804ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s5));

        for (int i = 0; i < 5321; i++)
        {
            random.nextSubstream();
        }
        for (int i = 0; i < 42; i++)
        {
            random.nextChunk();
        }
        for (int i = 0; i < 79; i++)
        {
            random.next();
        }

        UInt64 s6[1] = { 1498291301030832719ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s6));

        random.resetSubstream();
        for (int i = 0; i < 11; i++)
        {
            random.nextChunk();
        }

        UInt64 s7[1] = { 1498291301030824704ULL };
        ASSERT_EQ(random.seed(), HashRandomStream::Seed(s7));
    }

    TEST_F(HashRandomStreamTest, testRandomAccess) {
        srand(1985850524);

        HashRandomStream r1, r2;

        r1 = _random;
        r2 = _random;

        // test random access of chunks
        for (int j = 0; j < 100; j++)
        {
            int n = rand() % 10000;
            for (int i = 0; i < n; i++)
            {
                r1.nextChunk();
            }

            double x = r1.next();
            double y = r2.atChunk(n).next();

            ASSERT_EQ(x, y);

            r1.resetSubstream();
            r2.resetSubstream();
        }

        // test random access of elements
        for (int j = 0; j < 100; j++)
        {
            int n = rand() % 10000;
            for (int i = 0; i < n; i++)
            {
                r1.next();
            }

            double x = r1.next();
            double y = r2.at(n);

            ASSERT_EQ(x, y);

            r1.resetChunk();
            r2.resetChunk();
        }
    }

} // namespace Myriad

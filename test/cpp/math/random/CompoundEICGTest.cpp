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

#include "math/random/CompoundEICG.h"

#include <Poco/RunnableAdapter.h>
#include <Poco/ThreadPool.h>

#include "gtest/gtest.h"

using namespace Poco;
using namespace std;

namespace Myriad {

    class CompoundEICGTest: public ::testing::Test
    {
    protected:

        CompoundEICGTest() : _random("CompoundEICG under test") {
        }

        CompoundEICG _random;

        // Helper class for threading tests
        class CompoundEICGRunner : public Runnable {
        public:
            CompoundEICGRunner(CompoundEICG& _random) :
                    _random(_random)
            {
            }

            void run()
            {
                // a couple of first elements from the same chunk
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 50; j++)
                    {
                        _result.push_back(_random.next());
                    }
                }

                // a couple of first elements from subsequent chunks
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 50; j++)
                    {
                        _result.push_back(_random.next());
                    }

                    _random.nextChunk();
                }
            }

            const vector<double>& result()
            {
                return _result;
            }

        private:

            CompoundEICG _random;
            vector<double> _result;
        };
    };

    TEST_F(CompoundEICGTest, testHierarchicalInterface) {
        CompoundEICG random = _random;

        UInt32 s1[6] = { 0, 0, 0, 0, 0, 0 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s1));

        random.nextSubstream();

        for (int i = 0; i < 3; i++)
        {
            random.next();
        }

        UInt32 s2[6] = { 1073741827, 1073745247, 1073855287, 1073906047, 1074048847, 1074226927 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s2));

        random.nextSubstream();
        for (int i = 0; i < 5; i++)
        {
            random.next();
        }

        UInt32 s3[6] = { 6, 6864, 226986, 328514, 614130, 970304 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s3));

        for (int i = 0; i < 52; i++)
        {
            random.nextChunk();
        }
        for (int i = 0; i < 23; i++)
        {
            random.next();
        }

        UInt32 s4[6] = { 50, 7376, 228590, 330326, 616358, 972896 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s4));

        random.resetChunk();
        for (int i = 0; i < 180; i++)
        {
            random.next();
        }

        UInt32 s5[6] = { 207, 7533, 228747, 330483, 616515, 973053 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s5));

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

        UInt32 s6[6] = { 1073744585, 1091997521, 1677853085, 1948070021, 560753770, 1508711172 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s6));

        random.resetSubstream();
        for (int i = 0; i < 11; i++)
        {
            random.nextChunk();
        }

        UInt32 s7[6] = { 2667, 18255333, 604110267, 874327083, 1634494155, 434967784 };
        ASSERT_EQ(random.seed(), CompoundEICG::Seed(s7));
    }

    TEST_F(CompoundEICGTest, testRandomAccess) {
        srand(1985850524);

        CompoundEICG r1, r2;

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

    TEST_F(CompoundEICGTest, testThreads) {
        ThreadPool pool;

        CompoundEICGRunner t1(_random);
        CompoundEICGRunner t2(_random);

        pool.start(t1);
        pool.start(t2);

        pool.joinAll();

        const vector<double>& r1 = t1.result();
        const vector<double>& r2 = t2.result();


        ASSERT_EQ(r1.size(), r2.size());


        int x = r1.size();
        for (int i = 0; i < x; i++)
        {
            ASSERT_EQ(r1[i], r2[i]);
        }
    }

} // namespace Myriad

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

#include "core/types/MyriadDate.h"
#include "core/types.h"

#include "gtest/gtest.h"

using namespace std;

namespace Myriad {

    TEST(MyriadDateTest, testConstructorsAndSerDeMethods) {
        vector<string> dates;
        dates.push_back("2011-04-04 07:04:17");
        dates.push_back("2011-06-07 08:30:21");
        dates.push_back("2011-02-17 11:45:40");
        dates.push_back("2011-08-10 16:16:30");
        dates.push_back("2011-12-18 20:04:01");
        dates.push_back("2012-02-29 20:08:31");

        for(vector<string>::const_iterator it = dates.begin(); it != dates.end(); ++it) {
            MyriadDate myriadDate = fromString<MyriadDate>(*it);

            ASSERT_EQ((*it).substr(0, 10), toString<MyriadDate>(myriadDate));
        }
    }

    TEST(MyriadDateTest, testComparisonOperators) {
        MyriadDate d1("2011-02-03");
        MyriadDate d2("2011-02-04");
        MyriadDate d3("2011-02-12");
        MyriadDate d4("2012-02-12");
        MyriadDate d5("2012-03-12");
        MyriadDate d6("2012-04-02");
        MyriadDate d7("2012-03-29");
        MyriadDate d8("2011-02-12");

        ASSERT_LT(d1, d2);
        ASSERT_LT(d2, d3);
        ASSERT_GT(d6, d7);

        ASSERT_LE(d1, d2);
        ASSERT_LE(d2, d3);
        ASSERT_GE(d6, d7);

        ASSERT_LE(d8, d3);
        ASSERT_LE(d3, d8);

        ASSERT_NE(d2, d3);
        ASSERT_EQ(d8, d3);
    }

    TEST(MyriadDateTest, testArithmeticOperators) {
        MyriadDate d1("2011-02-03");
        MyriadDate d2("2011-02-04");
        MyriadDate d3("2011-02-12");
        MyriadDate d4("2012-02-12");
        MyriadDate d5("2012-03-12");
        MyriadDate d6("2012-04-02");
        MyriadDate d7("2012-03-29");


        MyriadDate t1 = d1 + 1;
        MyriadDate t2 = t1 + 8;
        MyriadDate t3 = t2 + 365;
        MyriadDate t4 = t3 + 29;
        MyriadDate t5 = t4 + 21;
        MyriadDate t6 = t5 - 4;

        int u1 = d2 - d1;
        int u2 = d3 - d2;
        int u3 = d4 - d3;
        int u6 = d7 - d6;

        ASSERT_TRUE(d1 + 1 == t1 && t1 == d2);
        ASSERT_TRUE(d1 + 9 == t2 && t2 == d3);
        ASSERT_TRUE(d1 + 374 == t3 && t3 == d4);
        ASSERT_TRUE(d1 + 403 == t4 && t4 == d5);
        ASSERT_TRUE(d1 + 424 == t5 && t5 == d6);
        ASSERT_TRUE(d1 + 420 == t6 && t6 == d7);

        ASSERT_TRUE(d2 - d1 == u1 && u1 == 1);
        ASSERT_TRUE(d3 - d2 == u2 && u2 == 8);
        ASSERT_TRUE(d4 - d3 == u3 && u3 == 365);
        ASSERT_TRUE(d4 - d3 == u3 && u3 == 365);
        ASSERT_TRUE(d7 - d6 == u6 && u6 == -4);
        ASSERT_TRUE(((t6++)--) == t6);
        ASSERT_TRUE((--(++t6)) == t6);

        t6 += 1;
        ASSERT_TRUE(d1 + 421 == t6);
        t6 -= 1;
        ASSERT_TRUE(d1 + 420 == t6);
    }
} // namespace Myriad

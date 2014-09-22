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

#include "math/probability/UniformPrFunction.h"
#include "gtest/gtest.h"

namespace {

    class UniformPrFunctionTest : public ::testing::Test {
    protected:

        UniformPrFunctionTest() :
                _uniformPr(1, 10000)
        {
        }

        // Distribution under test
        Myriad::UniformPrFunction<UInt64> _uniformPr;
    };

    TEST_F(UniformPrFunctionTest, IsPdfWellBehaved) {
        Decimal cumProb = 0.0;
        for (UInt64 i = 1; i < 10000; i++) {
            Decimal p = _uniformPr.pdf(i);
            cumProb += p;
            ASSERT_GE(p, 0.0);
            ASSERT_LE(p, 1.0);
        }
        ASSERT_LE((int) cumProb, 1);
    }

    TEST_F(UniformPrFunctionTest, IsCdfWellBehaved) {

    }

    TEST_F(UniformPrFunctionTest, Invcdf) {
        for (UInt64 i = 1; i < 10000; i++) {
            ASSERT_EQ(_uniformPr.invcdf(_uniformPr.cdf(i)), i);
        }
    }

}  // namespace

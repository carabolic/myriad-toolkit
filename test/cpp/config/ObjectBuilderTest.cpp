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

#include "core/types.h"
#include "config/ObjectBuilder.h"

#include "gtest/gtest.h"

using namespace Poco;
using namespace Myriad;

namespace {

    class ObjectBuilderTest: public ::testing::Test {
    protected:

        ObjectBuilderTest() {

        }

        class ConfigurableObject {
        public:
            ConfigurableObject(map<string, Any>& params)
            {
                x = AnyCast<Decimal>(params["x"]);
                y = AnyCast<I16u>(params["y"]);
                z = AnyCast<String>(params["z"]);
            }

            ConfigurableObject(const String& name, map<string, Any>& params) :
                    name(name)
            {
                x = AnyCast<Decimal>(params["x"]);
                y = AnyCast<I16u>(params["y"]);
                z = AnyCast<String>(params["z"]);
            }

            String name;
            Decimal x;
            I16u y;
            String z;
        };

        ObjectBuilder _builder;
    };

    TEST_F(ObjectBuilderTest, testBuilder) {
        _builder
                .clear()
                .addParameter("name", string("myConfigurable"))
                .addParameter("x", 3.1415926535)
                .addParameter("y", static_cast<I16u>(42))
                .addParameter("z", string("Hello, World!"));

        ConfigurableObject* o = _builder.createObject<ConfigurableObject>();

        ASSERT_EQ(o->name, "myConfigurable");
        ASSERT_EQ(o->x, 3.1415926535);
        ASSERT_EQ(o->y, 42);
        ASSERT_EQ(o->z, "Hello, World!");
    }

} // namespace Myriad

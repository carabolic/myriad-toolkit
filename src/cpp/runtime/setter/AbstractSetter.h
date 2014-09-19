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
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 */

#ifndef ABSTRACTSETTER_H_
#define ABSTRACTSETTER_H_

#include "core/types.h"
#include "math/random/RandomStream.h"

#include <Poco/AutoPtr.h>

namespace Myriad {

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// generic range provider template
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<class RecordType, I16u fid>
class AbstractSetter
{
public:

    typedef EqualityPredicate<RecordType> EqualityPredicateType;

    AbstractSetter(const I16u arity, bool invertible) :
        _arity(arity),
        _invertible(invertible)
    {
    }

    virtual ~AbstractSetter()
    {
    }

    I16u arity() const
    {
        return _arity;
    }

    bool invertible() const
    {
        return _invertible;
    }

    virtual Interval<I64u> valueRange(const AutoPtr<RecordType>& cxtRecordPtr)
    {
        if (_invertible)
        {
            throw RuntimeException("Trying to access missing valueRange method implementation in an invertible FieldSetter");
        }
        else
        {
            throw RuntimeException("Trying to access valueRange method of non-invertible FieldSetter");
        }
    }

    inline void filterRange(const EqualityPredicateType& predicate, Interval<I64u>& currentRange)
    {
        if (predicate.bound(fid))
        {
            currentRange.intersect(valueRange(predicate.valueHolder()));
        }
    }

    virtual const void operator()(AutoPtr<RecordType>& cxtRecordPtr, RandomStream& random) = 0;

private:

    const I16u _arity;

    const bool _invertible;
};

} // namespace Myriad

#endif /* ABSTRACTSETTER_H_ */

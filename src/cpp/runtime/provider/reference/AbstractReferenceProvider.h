/*
 * Copyright 2010-2011 DIMA Research Group, TU Berlin
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

#ifndef ABSTRACTREFERENCEPROVIDER_H_
#define ABSTRACTREFERENCEPROVIDER_H_

#include "core/types.h"
#include "math/random/RandomStream.h"

#include <Poco/AutoPtr.h>

namespace Myriad {

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// generic reference provider template
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<typename RefRecordType, class CxtRecordType>
class AbstractReferenceProvider
{
public:

    AbstractReferenceProvider(const I16u arity, bool invertible) :
    	_arity(arity),
    	_invertible(invertible)
    {
    }

    virtual ~AbstractReferenceProvider()
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

    virtual Interval<I64u> referenceRange(const I64u& refRecordID, const AutoPtr<CxtRecordType>& cxtRecordPtr)
	{
    	if (_invertible)
    	{
    		throw RuntimeException("Trying to access missing referenceRange method implementation in an invertible ReferenceProvider");
    	}
    	else
    	{
    		throw RuntimeException("Trying to access referenceRange method of non-invertible ReferenceProvider");
    	}
	}

    virtual const AutoPtr<RefRecordType>& operator()(AutoPtr<CxtRecordType>& cxtRecordPtr, RandomStream& random) = 0;

private:

    const I16u _arity;

    const bool _invertible;
};

} // namespace Myriad

#endif /* ABSTRACTREFERENCEPROVIDER_H_ */
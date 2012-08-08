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

#include "core/types.h"

#include <map>
#include <string>
#include <Poco/Any.h>
#include <Poco/AutoPtr.h>
#include <Poco/DynamicAny.h>
#include <Poco/RefCountedObject.h>

using namespace std;
using namespace Poco;

#ifndef RECORD_H_
#define RECORD_H_

namespace Myriad {

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// forward declarations
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

class RecordGenerator;
template<class RecordType>
class HydratorChain;
template<class RecordType>
class RecordFactory;
template<class RecordType>
class RecordMeta;
template<class RecordType>
class RecordRangePredicate;

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// record traits
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<class RecordType>
struct RecordTraits
{
	typedef RecordMeta<RecordType> MetaType;
	typedef RecordGenerator GeneratorType;
	typedef HydratorChain<RecordType> HydratorChainType;
	typedef RecordFactory<RecordType> FactoryType;
	typedef RecordRangePredicate<RecordType> RangePredicateType;

	enum Field { UNKNOWN, GEN_ID };
};

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// record type
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

class Record: public Poco::RefCountedObject
{
public:

	void genID(const I64u v);
	I64u genID() const;

    void genIDRef(const I64u& v);
	const I64u& genIDRef() const;

private:

	ID	_gen_id;
};

inline void Record::genID(const I64u v)
{
    _gen_id = v;
}

inline I64u Record::genID() const
{
	return _gen_id;
}

inline void Record::genIDRef(const I64u& v)
{
    _gen_id = v;
}

inline const I64u& Record::genIDRef() const
{
	return _gen_id;
}

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// record range predicate
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<class RecordType>
class RecordRangePredicate
{
public:

    RecordRangePredicate()
    {
    }

    virtual ~RecordRangePredicate()
    {
    }

    void genID(const I64u& min, I64u& max);
    void genID(I64u& v);
    const Interval<I64u>& genID() const;

private:

    Interval<I64u> _gen_id_range;
};

template<class RecordType>
inline void RecordRangePredicate<RecordType>::genID(const I64u& min, I64u& max)
{
    _gen_id_range.set(min, max);
}

template<class RecordType>
inline void RecordRangePredicate<RecordType>::genID(I64u& v)
{
    _gen_id_range.set(v, ++v);
}

template<class RecordType>
inline const Interval<I64u>& RecordRangePredicate<RecordType>::genID() const
{
    return _gen_id_range;
}

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// record factory
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<class RecordType>
class RecordFactory
{
public:

	typedef typename RecordTraits<RecordType>::MetaType RecordMetaType;

	RecordFactory(RecordMetaType meta)
		: _meta(meta)
	{
	}

	/**
	 * Object generating function.
	 */
	AutoPtr<RecordType> operator()() const;

private:

	const RecordMetaType _meta;
};

template<class RecordType>
inline AutoPtr<RecordType> RecordFactory<RecordType>::operator()() const
{
	return new RecordType(_meta);
}

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// record meta
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<class RecordType>
class RecordMeta
{
public:

	RecordMeta()
	{
	}

	RecordMeta(const map<string, vector<string> >& enumSets)
	{
	}
};

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// record field inspection structures
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

/**
 * Unspecialized traits object for introspection on record fields.
 */
template <I16u fid, class RecordType>
struct RecordFieldTraits
{
	typedef I64u FieldType;
	typedef typename MethodTraits<RecordType, FieldType>::Getter FieldGetterType;
	typedef typename MethodTraits<RecordType, FieldType>::Setter FieldSetterType;
    typedef typename MethodTraits<RecordType, FieldType>::Setter RangeSetterType;
    typedef typename MethodTraits<RecordType, FieldType>::Setter RangeGetterType;

	static FieldSetterType setter()
	{
		throw RuntimeException("Trying to access setter for unknown field");
	}

	static FieldGetterType getter()
	{
		throw RuntimeException("Trying to access getter for unknown field");
	}
};

/**
 * Unspecialized traits object for introspection on record fields.
 */
template <class RecordType>
struct RecordFieldTraits<1, RecordType>
{
	typedef I64u FieldType;
	typedef typename MethodTraits<Record, FieldType>::Getter FieldGetterType;
	typedef typename MethodTraits<Record, FieldType>::Setter FieldSetterType;

	static FieldSetterType setter()
	{
		return static_cast<FieldSetterType>(&Record::genIDRef);
	}

	static FieldGetterType getter()
	{
		return static_cast<FieldGetterType>(&Record::genIDRef);
	}
};

} // namespace Myriad

#endif /* RECORD_H_ */

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

#ifndef COMBINEDPRFUNCTION_H_
#define COMBINEDPRFUNCTION_H_

#include "core/exceptions.h"
#include "core/types.h"
#include "math/Function.h"

#include <Poco/Any.h>
#include <Poco/File.h>
#include <Poco/NumberParser.h>
#include <Poco/Path.h>
#include <Poco/String.h>
#include <Poco/RegularExpression.h>

#include <string>
#include <fstream>

using namespace std;
using namespace Poco;

namespace Myriad
{
/**
 * @addtogroup math_probability
 * @{*/

/**
 * A custom probability function consisting of a set of probabilities for
 * distinct values, a set of bucket probabilities, and a special probability for
 * the \p T domain NULL value.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 */
template<typename T>
class CombinedPrFunction: public UnivariatePrFunction<T>
{
public:

    /**
     * Default constructor.
     *
     * Merely creates a new function object, and does not execute any
     * initialization routines.
     */
    CombinedPrFunction() :
        UnivariatePrFunction<T>(""),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
    }

    /**
     * Anonymous file path initialization constructor.
     *
     * Loads the configuration for this probability function from the file
     * given by the \p path parameter.
     *
     * @param path The location of the function configuration file.
     */
    CombinedPrFunction(const string& path) :
        UnivariatePrFunction<T>(""),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
        initialize(path);
    }

    /**
     * Anonymous stream initialization constructor.
     *
     * Loads the configuration for this probability function from the input
     * stream given by the \p in parameter.
     *
     * @param in Input stream containing the function configuration.
     */
    CombinedPrFunction(istream& in) :
        UnivariatePrFunction<T>(""),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
        initialize(in);
    }

    /**
     * Named file path initialization constructor.
     *
     * Loads the configuration for this probability function from the file
     * given by the \p path parameter.
     *
     * @param name The name of this probability function instance.
     * @param path The location of the function configuration file.
     */
    CombinedPrFunction(const string& name, const string& path) :
        UnivariatePrFunction<T>(name),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
        initialize(path);
    }

    /**
     * Named stream initialization parameter.
     *
     * Loads the configuration for this probability function from the input
     * stream given by the \p in parameter.
     *
     * @param name The name of this probability function instance.
     * @param in Input stream containing the function configuration.
     */
    CombinedPrFunction(const string& name, istream& in) :
        UnivariatePrFunction<T>(name),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
        initialize(in);
    }

    /**
     * Anonymous ObjectBuilder constructor.
     *
     * Loads the configuration for this probability function from the input
     * stream given by the <tt>params['path']</tt> in parameter.
     *
     * @param params An array containing the required function parameters.
     */
    CombinedPrFunction(map<string, Any>& params) :
        UnivariatePrFunction<T>(""),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
        initialize(AnyCast<string>(params["path"]));
    }

    /**
     * Named ObjectBuilder constructor.
     *
     * Loads the configuration for this probability function from the input
     * stream given by the <tt>params['path']</tt> in parameter.
     *
     * @param name The name of this probability function instance.
     * @param params An array containing the required function parameters.
     */
    CombinedPrFunction(const string& name, map<string, Any>& params) :
        UnivariatePrFunction<T>(name),
        _notNullProbability(0),
        _activeDomain(nullValue<T>(), nullValue<T>()),
        _numberOfValues(0),
        _values(NULL),
        _valueProbability(0.0),
        _valueProbabilities(NULL),
        _numberOfBuckets(0),
        _buckets(NULL),
        _bucketProbability(0),
        _bucketProbabilities(NULL),
        _cumulativeProbabilites(NULL),
        _EPSILON(0.000000001)
    {
        initialize(AnyCast<string>(params["path"]));
    }

    /**
     * Destructor.
     */
    virtual ~CombinedPrFunction()
    {
        reset();
    }

    /**
     * Initialization routine.
     *
     * Initializes the function with the configuration stored in the file
     * located at the given \p path.
     *
     * @param path The location of the function configuration file.
     */
    void initialize(const string& path);

    /**
     * Initialization routine.
     *
     * Initializes the function with the configuration stored in the file
     * located at the given \p path.
     *
     * @param path The location of the function configuration file.
     */
    void initialize(const Path& path);

    /**
     * Initialization routine.
     *
     * Initializes the function with the configuration from the input stream
     * given by the \p in parameter.
     *
     * @param in Input stream containing the function configuration.
     */
    void initialize(istream& in);

    /**
     * Initialization routine.
     *
     * Initializes the function with the configuration from the input stream
     * given by the \p in parameter. When reading from the \p in stream, uses
     * the \p currentLineNumber parameter to track the current line number.
     *
     * @param in Input stream containing the function configuration.
     * @param currentLineNumber A reference to the current line number.
     */
    void initialize(istream& in, size_t& currentLineNumber);

    /**
     * Returns the number of buckets for this (configured) function.
     *
     * @return size_t The number of buckets configured for this function.
     */
    size_t numberOfBuckets() const;

    /**
     * Returns the left bound (inclusive) of the function active domain.
     *
     * @return size_t The left bound (inclusive) of the function active domain.
     */
    T min() const;

    /**
     * Returns the right bound (exclusive) of the function active domain.
     *
     * @return size_t The right bound (exclusive) of the function active domain.
     */
    T max() const;

    /**
     * @see UnivariatePrFunction::operator()
     */
    Decimal operator()(const T x) const;

    /**
     * @see UnivariatePrFunction::sample()
     */
    T sample(Decimal random) const;

    /**
     * @see UnivariatePrFunction::pdf()
     */
    Decimal pdf(T x) const;

    /**
     * @see UnivariatePrFunction::cdf()
     */
    Decimal cdf(T x) const;

    /**
     * @see UnivariatePrFunction::invcdf()
     */
    T invcdf(Decimal x) const;

private:

    void reset();

    void normalize();

    size_t findIndex(const Decimal y) const;

    size_t findValue(const T x, bool exact = true) const;

    size_t findBucket(const T x, bool exact = true) const;

    static RegularExpression headerLine1Format;
    static RegularExpression headerLine2Format;
    static RegularExpression headerLine3Format;
    static RegularExpression valueLineFormat;
    static RegularExpression bucketLineFormat;

    Decimal _notNullProbability;

    Interval<T> _activeDomain;

    size_t _numberOfValues;
    T* _values;
    Decimal _valueProbability;
    Decimal* _valueProbabilities;

    size_t _numberOfBuckets;
    Interval<T>* _buckets;
    Decimal _bucketProbability;
    Decimal* _bucketProbabilities;

    Decimal* _cumulativeProbabilites;

    Decimal _EPSILON;
};

////////////////////////////////////////////////////////////////////////////////
/// @name Static Template Members
////////////////////////////////////////////////////////////////////////////////
//@{

// general value and bucket line regular expressions
template<typename T>
inline String __valueLineFormat()
{
    return "\\s*p\\(X\\)\\s*=\\s*([+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s+for\\s+X\\s*=\\s*\\{\\s*(.+)\\s*\\}\\s*(#(.+))?";
}

template<typename T>
inline String __bucketLineFormat()
{
    return "\\s*p\\(X\\)\\s*=\\s*([+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s+for\\s+X\\s*=\\s*\\{\\s*x\\s+in\\s+\\[\\s*(.+)\\s*,\\s*(.+)\\s*\\)\\s*\\}\\s*(#(.+))?";
}

// specializations for 'Char' as 'Char' values must be quoted
template<>
inline String __valueLineFormat<Char>()
{
    return "\\s*p\\(X\\)\\s*=\\s*([+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s+for\\s+X\\s*=\\s*\\{\\s*'(.)'\\s*\\}\\s*(#(.+))?";
}

template<>
inline String __bucketLineFormat<Char>()
{
    return "\\s*p\\(X\\)\\s*=\\s*([+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s+for\\s+X\\s*=\\s*\\{\\s*x\\s+in\\s+\\[\\s*'(.)'\\s*,\\s*'(.+)'\\s*\\)\\s*\\}\\s*(#(.+))?";
}

template<typename T>
RegularExpression CombinedPrFunction<T>::headerLine1Format("\\s*@numberofexactvals\\s*=\\s*([+]?[0-9]+)\\s*(#(.+))?");
template<typename T>
RegularExpression CombinedPrFunction<T>::headerLine2Format("\\s*@numberofbins\\s*=\\s*([+]?[0-9]+)\\s*(#(.+))?");
template<typename T>
RegularExpression CombinedPrFunction<T>::headerLine3Format("\\s*@nullprobability\\s*=\\s*([+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?)\\s*(#(.+))?");
template<typename T>
RegularExpression CombinedPrFunction<T>::valueLineFormat(__valueLineFormat<T>());
template<typename T>
RegularExpression CombinedPrFunction<T>::bucketLineFormat(__bucketLineFormat<T>());

//@}

////////////////////////////////////////////////////////////////////////////////
/// @name Private Member Function Templates
////////////////////////////////////////////////////////////////////////////////
//@{

template<typename T>
void CombinedPrFunction<T>::reset()
{
    _notNullProbability = 0.0;
    _valueProbability = 0.0;
    _bucketProbability = 0.0;

    if (_numberOfValues > 0 || _numberOfBuckets > 0)
    {
        delete[] _cumulativeProbabilites;
    }

    if (_numberOfValues > 0)
    {
        _numberOfValues = 0;
        delete[] _values;
        delete[] _valueProbabilities;
    }

    if (_numberOfBuckets > 0)
    {
        _numberOfBuckets = 0;
        delete[] _buckets;
        delete[] _bucketProbabilities;
    }
}

template<typename T>
void CombinedPrFunction<T>::normalize()
{
    Decimal normalizationFactor = 1.0 / static_cast<Decimal>(_valueProbability + _bucketProbability + (1.0 - _notNullProbability));

    _valueProbability = 0;
    _bucketProbability = 0;

    for (size_t i = 0; i < _numberOfValues; i++)
    {
        Decimal probability = _valueProbabilities[i] * normalizationFactor;

        _valueProbabilities[i] = probability;
        _valueProbability += probability;
        _cumulativeProbabilites[i] = _valueProbability;
    }

    for (size_t i = 0; i < _numberOfBuckets; i++)
    {
        Decimal probability = _bucketProbabilities[i] * normalizationFactor;

        _bucketProbabilities[i] = probability;
        _bucketProbability += probability;
        _cumulativeProbabilites[i+_numberOfValues] = _valueProbability + _bucketProbability;
    }

    _notNullProbability = _valueProbability + _bucketProbability;
}

template<typename T>
inline size_t CombinedPrFunction<T>::findIndex(const Decimal y) const
{
    // we assert that the value x is in the active domain
    int min = 0;
    int max = _numberOfValues + _numberOfBuckets - 1;
    int mid = 0;

    // protect against invalid y
    if (y >= 1.0)
    {
        return max;
    }

    // continue searching while [min, max] is not empty
    while (max >= min)
    {
        // calculate the midpoint for roughly equal partition //
        mid = (min + max) / 2;

        // determine which subarray to search
        if (_cumulativeProbabilites[mid] <  y - _EPSILON)
        {
	        // change min index to search upper subarray
	        min = mid + 1;
        }
        else if (_cumulativeProbabilites[mid] > y + _EPSILON)
        {
	        // change max index to search lower subarray
	        max = mid - 1;
        }
        else
        {
	        // key found at index mid
	        // for all but the last position, increment the index by one to
	        // compensate for the fact that buckets are defined as Y < y rather than Y <= y
            return (static_cast<size_t>(mid) == _numberOfValues + _numberOfBuckets - 1) ? mid : mid+1;
        }
    }

    if (static_cast<size_t>(mid) < _numberOfValues + _numberOfBuckets - 1 && _cumulativeProbabilites[mid] < y)
    {
        return mid+1;
    }
    else
    {
        return mid;
    }
}

template<typename T>
inline size_t CombinedPrFunction<T>::findValue(const T x, bool exact) const
{
    // we assert that the value x is in the active domain
    int min = 0;
    int max = _numberOfValues - 1;
    int mid = 0;

    // continue searching while [min, max] is not empty
    while (max >= min)
    {
        // calculate the midpoint for roughly equal partition
        mid = (min + max) / 2;

        // determine which subarray to search
        if (_values[mid] <  x)
        {
	        // change min index to search upper subarray
	        min = mid + 1;
        }
        else if (_values[mid] > x)
        {
	        // change max index to search lower subarray
	        max = mid - 1;
        }
        else
        {
	        // key found at index mid
	        return mid;
        }
    }

    // at this point, mid is always equal to min and points to the first record higher than x
    // what we actually want the index of the first value less than or equal to x
    if (!exact && mid > 0)
    {
        if (static_cast<size_t>(mid) < _numberOfValues-2 && _values[mid+1] < x)
        {
	        return mid+1;
        }
        else if (_values[mid] < x)
        {
	        return mid;
        }
        else
        {
	        return mid-1;
        }
    }
    else
    {
        return nullValue<size_t>();
    }
}

template<typename T>
inline size_t CombinedPrFunction<T>::findBucket(const T x, bool exact) const
{
    // we assert that the value x is in the active domain
    int min = 0;
    int max = _numberOfBuckets - 1;
    int mid = 0;

    // continue searching while [min, max] is not empty
    while (max >= min)
    {
        // calculate the midpoint for roughly equal partition //
        mid = (min + max) / 2;

        // determine which subarray to search
        if (_buckets[mid].max() <=  x)
        {
	        // change min index to search upper subarray
	        min = mid + 1;
        }
        else if (_buckets[mid].min() > x)
        {
	        // change max index to search lower subarray
	        max = mid - 1;
        }
        else
        {
	        // key found at index mid
	        return mid;
        }
    }

    // at this point, mid is always equal to min and points to the first bucket where higher than x
    // what we actually want the index of the first bucket less than but not containing x
    if (!exact && mid > 0)
    {
        if (static_cast<size_t>(mid) < _numberOfBuckets-2 && _buckets[mid+1].max() <= x)
        {
	        return mid+1;
        }
        else if (_buckets[mid].max() <= x)
        {
	        return mid;
        }
        else
        {
	        return mid-1;
        }
    }
    else
    {
        return nullValue<size_t>();
    }
}

template<typename T>
inline Decimal CombinedPrFunction<T>::operator()(const T x) const
{
    return cdf(x);
}

template<typename T>
inline T CombinedPrFunction<T>::sample(Decimal random) const
{
    return invcdf(random);
}

template<typename T>
void CombinedPrFunction<T>::initialize(const string& path)
{
    initialize(Path(path));
}

template<typename T>
void CombinedPrFunction<T>::initialize(const Path& path)
{
    if (!path.isFile())
    {
        throw ConfigException(format("Cannot find file at `%s`", path.toString()));
    }

    File file(path);

    if (!file.canRead())
    {
        throw ConfigException(format("Cannot read from file at `%s`", path.toString()));
    }

    ifstream in(file.path().c_str());

    if (!in.is_open())
    {
        throw ConfigException(format("Cannot open file at `%s`", path.toString()));
    }

    try
    {
        initialize(in);
        in.close();
    }
    catch(Poco::Exception& e)
    {
        in.close();
        throw e;
    }
    catch(exception& e)
    {
        in.close();
        throw e;
    }
    catch(...)
    {
        in.close();
        throw;
    }
}

template<typename T>
void CombinedPrFunction<T>::initialize(istream& in)
{
    size_t currentLineNumber = 1;
    initialize(in, currentLineNumber);
}

template<typename T>
void CombinedPrFunction<T>::initialize(istream& in, size_t& currentLineNumber)
{
    enum READ_STATE { NOE, NOB, NPR, VLN, BLN, FIN, END };

    // reset old state
    reset();

    // reader variables
    READ_STATE currentState = NOE; // current reader machine state
    string currentLine; // the current line
    size_t currentItemIndex = 0; // current item index
    RegularExpression::MatchVec posVec; // a posVec for all regex matches

    // reader finite state machine
    while (currentState != END)
    {
        // the special FIN stage contains only final initialization constructs
        // and does not read the currentLine
        if (currentState == FIN)
        {
            T min, max;

            if (_numberOfValues == 0 && _numberOfBuckets == 0)
            {
                throw LogicException("Cannot specify a combined probability with zero values and zero buckets");
            }

            if (_numberOfValues == 0)
            {
                // no values - active domain determined only by buckets
                min = _buckets[0].min();
                max = _buckets[_numberOfBuckets-1].max();
            }
            else if (_numberOfBuckets == 0)
            {
                // no buckets - active domain determined only by values
                min = _values[0];
	            max = static_cast<T>(_values[_numberOfValues-1]+1);
            }
            else
            {
                // buckets and values - active domain determined by both
                min = std::min<T>(_buckets[0].min(), _values[0]);
                max = std::max<T>(_buckets[_numberOfBuckets-1].max(), static_cast<T>(_values[_numberOfValues-1]+1));
            }

            _activeDomain.set(min, max);

	        currentState = END;
	        continue;
        }

        // read next line
        currentLine = "";
        getline(in, currentLine);

        // trim whitespace
        trimInPlace(currentLine);

        // check if this line is empty or contains a single comment
        if (currentLine.empty() || currentLine.at(0) == '#')
        {
            if (!in.good()) // break on end of stream
            {
                if (currentState == VLN && currentItemIndex < _numberOfValues)
                {
                    throw DataException(format("line %z: Bad value probability line, should be: 'p(X) = $p_x for X = { $x }'", currentLineNumber));
                }
                else if (currentState == BLN && currentItemIndex < _numberOfBuckets)
                {
                    throw DataException(format("line %z: Bad bucket probability line, should be: 'p(X) = $p_x for X = { x \\in [$x_min, $x_max) }'", currentLineNumber));
                }
                else
                {
                    currentState = FIN;
                }
            }

	        currentLineNumber++;
	        continue; // skip this line
        }

        if (currentState == NOE)
        {
	        if (!headerLine1Format.match(currentLine, 0, posVec))
	        {
		        throw DataException(format("line %z: Bad header line, should be: '@numberofexactvals = $N'", currentLineNumber));
	        }

	        I64 numberOfValues = NumberParser::parse64(currentLine.substr(posVec[1].offset, posVec[1].length).c_str());

	        if (numberOfValues <= 0 && static_cast<size_t>(numberOfValues) > (numeric_limits<size_t>::max()/2U))
	        {
		        throw DataException("Invalid number of exact values " + toString(numberOfValues) +  ", should be in the (0, " + toString(numeric_limits<size_t>::max()/2U) + "] range");
	        }

	        _numberOfValues = numberOfValues;
	        if (_numberOfValues > 0)
	        {
                _values = new T[numberOfValues];
                _valueProbabilities = new Decimal[numberOfValues];
	        }

	        currentState = NOB;
        }
        else if (currentState == NOB)
        {
	        if (!headerLine2Format.match(currentLine, 0, posVec))
	        {
		        throw DataException(format("line %z: Bad header line, should be: '@numberofbins = $N'", currentLineNumber));
	        }

	        I64 numberOfBuckets = NumberParser::parse64(currentLine.substr(posVec[1].offset, posVec[1].length).c_str());

	        if (numberOfBuckets <= 0 && static_cast<size_t>(numberOfBuckets) > (numeric_limits<size_t>::max()/2U))
	        {
                throw DataException("Invalid number of buckets " + toString(numberOfBuckets) +  ", should be in the (0, " + toString(numeric_limits<size_t>::max()/2U) + "] range");
	        }

	        _numberOfBuckets = numberOfBuckets;
            if (_numberOfBuckets > 0)
            {
                _buckets = new Interval<T>[numberOfBuckets];
                _bucketProbabilities = new Decimal[numberOfBuckets];
            }

	        _cumulativeProbabilites = new Decimal[_numberOfValues+_numberOfBuckets];

	        currentState = NPR;
        }
        else if (currentState == NPR)
        {
	        if (!headerLine3Format.match(currentLine, 0, posVec))
	        {
		        throw DataException(format("line %z: Bad header line, should be: '@nullprobability = $N'", currentLineNumber));
	        }

	        _notNullProbability = 1.0 - NumberParser::parseFloat(currentLine.substr(posVec[1].offset, posVec[1].length).c_str());

	        currentItemIndex = 0;
	        currentState = (_numberOfValues > 0) ? VLN : BLN;
        }
        else if (currentState == VLN)
        {
	        if (!valueLineFormat.match(currentLine, 0, posVec))
	        {
		        throw DataException(format("line %z: Bad value probability line, should be: 'p(X) = $p_x for X = { $x }'", currentLineNumber));
	        }

	        Decimal probability = fromString<Decimal>(currentLine.substr(posVec[1].offset, posVec[1].length));
	        T value = fromString<T>(currentLine.substr(posVec[3].offset, posVec[3].length));

	        _values[currentItemIndex] = value;
	        _valueProbabilities[currentItemIndex] = probability;
	        _valueProbability += probability;
	        _cumulativeProbabilites[currentItemIndex] = _valueProbability;

	        currentItemIndex++;

	        if (currentItemIndex >= _numberOfValues)
	        {
		        currentItemIndex = 0;
		        currentState = (_numberOfBuckets > 0) ? BLN : FIN;
	        }
        }
        else if (currentState == BLN)
        {
	        if (!bucketLineFormat.match(currentLine, 0, posVec))
	        {
		        throw DataException(format("line %z: Bad bucket probability line, should be: 'p(X) = $p_x for X = { x \\in [$x_min, $x_max) }'", currentLineNumber));
	        }

	        Decimal probability = fromString<Decimal>(currentLine.substr(posVec[1].offset, posVec[1].length));
	        T min = fromString<T>(currentLine.substr(posVec[3].offset, posVec[3].length));
	        T max = fromString<T>(currentLine.substr(posVec[4].offset, posVec[4].length));

	        _buckets[currentItemIndex].set(min, max);
	        _bucketProbabilities[currentItemIndex] = probability;
	        _bucketProbability += probability;
	        _cumulativeProbabilites[currentItemIndex+_numberOfValues] = _valueProbability + _bucketProbability;

	        currentItemIndex++;

	        if (currentItemIndex >= _numberOfBuckets)
	        {
                currentItemIndex = 0;
		        currentState = FIN;
	        }
        }

        currentLineNumber++;
    }

    // protect against unexpected reader state
    if (currentState != END)
    {
        throw RuntimeException("Unexpected state in CombinedPrFunction reader at line " + currentLineNumber);
    }

    // check if extra normalization is required
    if (std::abs(_valueProbability + _bucketProbability - _notNullProbability) >= _EPSILON)
    {
        normalize();
    }
}

template<typename T>
inline size_t CombinedPrFunction<T>::numberOfBuckets() const
{
    return _numberOfBuckets;
}

template<typename T>
inline T CombinedPrFunction<T>::min()const
{
    return _activeDomain.min();
}

template<typename T>
inline T CombinedPrFunction<T>::max() const
{
    return _activeDomain.max();
}

template<typename T>
Decimal CombinedPrFunction<T>::pdf(T x) const
{
    if (x == nullValue<T>())
    {
        return 1.0-_notNullProbability;
    }
    else if (!_activeDomain.contains(x))
    {
        return 0.0;
    }
    else
    {
        size_t i;

        if (nullValue<size_t>() != (i = findValue(x)))
        {
	        return _valueProbabilities[i];
        }

        if (nullValue<size_t>() != (i = findBucket(x)))
        {
	        return _bucketProbabilities[i] * (1.0 / static_cast<Decimal>(_buckets[i].length()));
        }

        throw RuntimeException(AbstractFunction::name() + ": unknown pdf(x) for x = " + toString<T>(x));
    }
}

template<typename T>
Decimal CombinedPrFunction<T>::cdf(T x) const
{
    if (x < _activeDomain.min())
    {
        return 0.0;
    }
    else if (x >= _activeDomain.max())
    {
        return _notNullProbability;
    }
    else
    {
        Decimal cdf = 0.0;

        size_t i;

        if (nullValue<size_t>() != (i = findValue(x, false)))
        {
	        cdf += _cumulativeProbabilites[i];
        }

        if (nullValue<size_t>() != (i = findBucket(x, false)))
        {
	        const Interval<T>& b = _buckets[i];

	        if (!b.contains(x))
	        {
		        cdf += _cumulativeProbabilites[_numberOfValues + i] - _valueProbability;
	        }
	        else
	        {
		        if (i > 0)
		        {
			        cdf += _cumulativeProbabilites[_numberOfValues + i - 1] - _valueProbability;
		        }

		        cdf += _bucketProbabilities[i] * ((1 + (x - b.min()))/static_cast<Decimal>(b.length()));
	        }
        }

        return cdf;
    }
}

template<typename T>
T CombinedPrFunction<T>::invcdf(Decimal y) const
{
    if (y < _notNullProbability)
    {
        size_t i = findIndex(y);

        if (i < _numberOfValues)
        {
	        return _values[i];
        }
        else
        {
	        const Interval<T>& b = _buckets[i-_numberOfValues];
	        Decimal cdfBefore = i > 0 ? _cumulativeProbabilites[i-1] : 0;

	        Decimal z = ((y - cdfBefore) / _bucketProbabilities[i-_numberOfValues]) * b.length();

	        T x = static_cast<T>(b.min() + static_cast<I32u>(z));

	        if ((z - static_cast<I32u>(z) >= 0.999999))
	        {
		        x++;
	        }

	        // FIXME: a quick and dirty hack to protect against out of range behavior, needs rewrite
	        if (x >= b.max())
	        {
		        x--;
	        }

	        return x;
        }
    }
    else
    {
        return nullValue<T>();
    }
}

//@}

/** @}*/// add to math_probability group
} // namespace Myriad

#endif /* COMBINEDPRFUNCTION_H_ */

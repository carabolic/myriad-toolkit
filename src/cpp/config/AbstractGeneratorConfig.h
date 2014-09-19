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

#ifndef ABSTRACTGENERATORCONFIG_H_
#define ABSTRACTGENERATORCONFIG_H_

#include "core/types.h"
#include "config/EnumSetPool.h"
#include "config/FunctionPool.h"
#include "config/ObjectBuilder.h"
#include "math/probability/Probability.h"
#include "math/random/RandomStream.h"

#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/Channel.h>
#include <Poco/Exception.h>
#include <Poco/Formatter.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
#include <Poco/RegularExpression.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Poco/SAX/XMLReader.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Node.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

namespace Myriad {
/**
 * @addtogroup config
 * @{*/

class GeneratorPool;

/**
 * An abstract base for all application specific configurations.
 *
 * A layered configuration used by the RandomSequenceGenerator objects to access
 * application wide configuration parameters, probability distribution
 * functions, enumerated sets as well as all other registered generators.
 *
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 */
class AbstractGeneratorConfig: public LayeredConfiguration
{
public:

    /**
     * Constructor.
     *
     * @param generatorPool a reference to the application's generator pool.
     */
    AbstractGeneratorConfig(GeneratorPool& generatorPool) :
        _pattern_param_ref("\\$\\{(.+)\\}"),
        _masterPRNG("master_prng"),
        _generatorPool(generatorPool),
        _logger(Logger::get("generator.config"))
    {
    }

    /**
     * Initializes a layer of application-wide parameters on top of the
     * provided underlying \c AbstractConfiguration object. At the end the
     * initialization routine invokes the following private functions
     *
     * - configurePartitioning()
     * - configureFunctions()
     * - configureSets()
     *
     * These are implemented by the application-specific GeneratorConfig
     * specializations in order to compute proper partitioning parameters for
     * all registered generators and to add the required functions and enum
     * sets to the GeneratorConfig instance.
     */
    void initialize(AbstractConfiguration& appConfig);

    /**
     * Reads a parameter identified by the key 'generator.{\p key}' from tries
     * to convert it to a \p ParameterType instance using the fromString
     * conversion method.
     *
     * @return the \p ParameterType parameter identified by 'generator.{\p key}'
     */
    template<class ParameterType> ParameterType parameter(string key) const
    {
        return fromString<ParameterType>(getString("generator." + key));
    }

    /**
     * Wrapper around the FunctionPool::add() method of the private
     * FunctionPool member.
     *
     * @param functionPtr a pointer to the function to be added.
     */
    void function(AbstractFunction* functionPtr)
    {
        _functionPool.add(functionPtr);
    }

    /**
     * Wrapper around the FunctionPool::get() method of the private
     * FunctionPool member.
     *
     * @return a reference to a \p FunctionType function identified by the
     *         given \p name
     */
    template<class FunctionType> FunctionType& function(const string& name) const
    {
        return _functionPool.get<FunctionType>(name);
    }

    /**
     * Retrieves a reference to the global function pool.
     *
     * @return A reference to the global function pool.
     */
    FunctionPool& functions()
    {
        return _functionPool;
    }

    /**
     * Helper function - loads an enumerated set from a flat file to a vector.
     *
     * @param key
     * @param path
     *
     */
    void enumSet(MyriadEnumSet* enumSet)
    {
        _enumSetPool.add(enumSet);
    }

    /**
     * Retrieves the enum set identified by the given \p key.
     *
     * @return a const reference to the enumerated set identified by \p key
     */
    const vector<string>& enumSet(string key)
    {
        return _enumSetPool.get(key).values();
    }

    /**
     * Retrieves a reference to the global enum set pool.
     *
     * @return A reference to the global enum set pool.
     */
    EnumSetPool& enumSets()
    {
        return _enumSetPool;
    }

    /**
     * Reads the 'generator.{\p name}.sequence.cardinality' config parameter.
     *
     * @return the 'generator.{\p name}.sequence.cardinality' config parameter.
     */
    ID cardinality(const string name) const
    {
        return fromString<I64u>(getString("generator." + name + ".sequence.cardinality"));
    }

    /**
     * Reads the 'generator.{\p name}.partition.begin' config parameter.
     *
     * This value of this parameter identifies the starting position (inclusive)
     * of the subsequence identified by \p name generated by the current node.
     *
     * @return the 'generator.{\p name}.partition.begin' config parameter.
     */
    ID genIDBegin(const string name) const
    {
        return fromString<I64u>(getString("generator." + name + ".partition.begin"));
    }

    /**
     * Reads the 'generator.{\p name}.partition.begin' config parameter.
     *
     * This value of this parameter identifies the end position (exclusive)
     * of the subsequence identified by \p name generated by the current node.
     *
     * @return the 'generator.{\p name}.partition.begin' config parameter.
     */
    ID genIDEnd(const string name) const
    {
        return fromString<I64u>(getString("generator." + name + ".partition.end"));
    }

    /**
     * Computes the output path for this generator. The output path is defined
     * as the concatenation {application.output-dir} and the
     * {generator.GENERATOR-NAME.output-file} parameters. If the second config
     * parameter is not defined, the GENERATOR-NAME value itself is used as
     * default.
     *
     * @return The path for the output produced by the generator identified by
     *         the given \p name.
     */
    Path outputPath(const String& name) const
    {
        Path path(getString(format("generator.%s.output-file", name), name));
        path.makeAbsolute(getString("application.output-dir"));

        return path;
    }

    /**
     * Returns the application output type. The output type is bound to the
     * {application.output-type} config parameter and can be one of 'file',
     * 'socket', or 'void' (default is 'file').
     *
     * @return The \p AbstractOutputCollector type.
     */
    String outputType() const
    {
        return getString("application.output-type");
    }

    /**
     * Returns the application output port to be used by 'socket' collectors.
     * The port is bound to the {application.output-port} config parameter.
     *
     * @return The socket port for \p SocketStreamOutputCollector instances.
     */
    I16u outputPort() const
    {
        return static_cast<I16u>(getInt("application.output-port", 0));
    }

    /**
     * Returns the scaling factor for the data generator application.
     *
     * The retrieved value is stored in the underlying configuration under the
     * 'application.scaling-factor' key.
     *
     * @return the application scaling factor
     */
    Decimal scalingFactor() const
    {
        return getDouble("application.scaling-factor");
    }

    /**
     * Returns the number of chunks (nodes) for the data generator application.
     *
     * The retrieved value is stored in the underlying configuration under the
     * 'common.partitioning.number-of-chunks' key.
     *
     * @return the number of chunks
     */
    I16u numberOfChunks() const
    {
        return getInt("common.partitioning.number-of-chunks");
    }

    /**
     * Returns the index of the current chunk (node).
     *
     * The retrieved value is stored in the underlying configuration under the
     * 'common.partitioning.chunks-id' key.
     *
     * @return the number of chunks
     */
    I16u nodeID() const
    {
        return getInt("common.partitioning.chunks-id");
    }

    /**
     * Returns a reference to the application generator pool.
     *
     * @return a reference to the application generator pool
     */
    GeneratorPool& generatorPool() const
    {
        return _generatorPool;
    }

    /**
     * Returns a reference to the master PRNG stream for this application.
     *
     * @return a reference to the master PRNG
     */
    RandomStream& masterPRNG()
    {
        return _masterPRNG;
    }

protected:

    /**
     * Helper function - configures the logging subsystem.
     */
    void configureLogging();

    /**
     * Helper function - loads functions.
     */
    virtual void configureFunctions()
    {
    }

    /**
     * Helper function - computes the PRDG subsequences assigned to the current
     * node for each data type.
     */
    virtual void configurePartitioning()
    {
    }

    /**
     * Helper function - binds record and string sets to local variables.
     */
    virtual void configureSets()
    {
    }

    /**
     * Helper partitioning function for fixed size subsequences.
     *
     * @param key
     */
    void computeFixedPartitioning(const string& key);

    /**
     * Helper partitioning function for equi-partitioned subsequences.
     *
     * @param key
     */
    void computeLinearScalePartitioning(const string& key);

    /**
     * Resolves values of the form ${param_name} to the corresponding parameter name.
     *
     * @param value
     */
    const string resolveValue(const string& value);

    /**
     * A regular expression that matches parameter references (i.e. "${...}" strings).
     */
    RegularExpression _pattern_param_ref;

    /**
     * The master PRNG instance.
     */
    RandomStream _masterPRNG;

    /**
     * A pool for the registered generators.
     */
    GeneratorPool& _generatorPool;

    /**
     * A global function pool.
     */
    FunctionPool _functionPool;

    /**
     * The global enum sets pool.
     */
    EnumSetPool _enumSetPool;

    /**
     * An auto-release pool for the registered logger channel(s).
     */
    AutoReleasePool<Channel> _loggerChannelsPool;

    /**
     * An auto-release pool for the registered logger formatter(s).
     */
    AutoReleasePool<Formatter> _loggerFormattersPool;

    /**
     * A 'generator.config' logger instance.
     */
    Logger& _logger;
};

} // namespace Myriad

#endif /* ABSTRACTGENERATORCONFIG_H_ */

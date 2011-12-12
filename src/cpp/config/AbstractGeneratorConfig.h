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

#ifndef ABSTRACTGENERATORCONFIG_H_
#define ABSTRACTGENERATORCONFIG_H_

#include "core/types.h"
#include "config/ObjectBuilder.h"
#include "config/FunctionPool.h"
#include "math/probability/Probability.h"
#include "math/random/RandomStream.h"

#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/Exception.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
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
 * A layered configuration used by the generator objects both as storage
 * v as well as an access point to some relevant sections from the
 * common application configuration.
 */
class AbstractGeneratorConfig: public LayeredConfiguration
{
public:

	AbstractGeneratorConfig() :
		_masterPRNG("master_prng"),
		_logger(Logger::get("generator.config"))
	{
	}

	void initialize(AbstractConfiguration& appConfig);

	void addFunction(AbstractFunction* functionPtr)
	{
		_functionPool.addFunction(functionPtr);
	}

	template<class C> C& func(const string& name) const
	{
		return _functionPool.func<C>(name);
	}

	ID cardinality(string name)
	{
		return fromString<I64u>(getString("generator." + name + ".sequence.cardinality"));
	}

	ID genIDBegin(string name)
	{
		return fromString<I64u>(getString("generator." + name + ".partition.begin"));
	}

	ID genIDEnd(string name)
	{
		return fromString<I64u>(getString("generator." + name + ".partition.end"));
	}

	Decimal scalingFactor()
	{
		return getDouble("application.scaling-factor");
	}

	I16u numberOfChunks()
	{
		return getInt("common.partitioning.number-of-chunks");
	}

	I16u chunkID()
	{
		return getInt("common.partitioning.chunks-id");
	}

	RandomStream& masterPRNG()
	{
		return _masterPRNG;
	}

protected:
	/**
	 * Loads the configuration from the given XML configuration file and the
	 * current api configuration.
	 *
	 * @param path
	 */
	void loadXMLConfig(const Path& path);

	/**
	 * Helper function - loads properties from XML.
	 *
	 * @param doc
	 */
	void configureProperties(const AutoPtr<XML::Document>& doc);

	/**
	 * Helper function - loads functions from XML.
	 *
	 * @param doc
	 */
	void configureFunctions(const AutoPtr<XML::Document>& doc);

	/**
	 * Helper function - computes the PRDG subsequences assigned to the current
	 * node for each data type.
	 *
	 * @param doc
	 */
	void configurePartitioning(const AutoPtr<XML::Document>& doc);

	/**
	 * Binds XML configured record and string sets to local variables. This
	 * function is extension specific and must be provided by the user in the
	 * GeneratorConfig subclass.
	 *
	 * @param doc
	 */
	virtual void configureSets(const AutoPtr<XML::Document>& doc) = 0;

	/**
	 * Helper function - binds a XML configured string set to a vector.
	 *
	 * @param doc
	 * @param id
	 * @param set
	 */
	void bindStringSet(const AutoPtr<XML::Document>& doc, const string& id, vector<string>& set);

	/**
	 * Helper function - binds a XML configured record set to a vector.
	 *
	 * @param doc
	 * @param id
	 * @param set
	 */
	template<class T> void bindRecordSet(const AutoPtr<XML::Document>& doc, const string& id, vector<AutoPtr<T> >& set);

	/**
	 * Helper function - defines a probability point in a custom probability.
	 *
	 * @param genID
	 * @param probability
	 */
	void setProbability(const ID genID, const XML::Element* probability);

	/**
	 * Helper partitioning function for equi-partitioned subsequences.
	 *
	 * @param key
	 */
	void computeSimplePartitioning(const string& key);

	/**
	 * Helper partitioning function for fixed size subsequences.
	 *
	 * @param key
	 */
	void computeFixedPartitioning(const string& key);

	/**
	 * Helper partitioning function for mirror-partitioned subsequences.
	 *
	 * @param key
	 */
	void computeMirroredPartitioning(const string& key);

	/**
	 * Helper partitioning function for nested block partitioned subsequences.
	 *
	 * @param key
	 */
	void computeNestedBlockPartitioning(const string& key);

	/**
	 * The master PRNG instance.
	 */
	RandomStream _masterPRNG;

	/**
	 * A global function pool.
	 */
	FunctionPool _functionPool;

	/**
	 * A 'generator.config' logger instance.
	 */
	Logger& _logger;
};

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
// template methods
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

template<class T> void AbstractGeneratorConfig::bindRecordSet(const AutoPtr<XML::Document>& doc, const string& id, vector<AutoPtr<T> >& set)
{
	XML::Element* containerEl = doc->getElementById(id, "id");
	if (containerEl == NULL || containerEl->tagName() != "object-set")
	{
		throw ConfigException(format("No <object-set> element found for `%s`", id));
	}

	ObjectBuilder objectBuilder;
	AutoPtr<XML::NodeList> strings = containerEl->getElementsByTagName("object");

	set.resize(strings->length());
	for (ID i = 0; i < strings->length(); i++)
	{
		objectBuilder.addParameter("gen_id", i);

		XML::Element* o = static_cast<XML::Element*> (strings->item(i));

		// read object properties
		AutoPtr<XML::NodeList> properties = o->getElementsByTagName("property");
		for (unsigned long int j = 0; j < properties->length(); j++)
		{
			XML::Element* p = static_cast<XML::Element*> (properties->item(j));
			objectBuilder.addParameter(p->getAttribute("name"), p->innerText());
		}

		// read object functions
		ObjectBuilder functionBuilder;
		AutoPtr<XML::NodeList> functions = o->getElementsByTagName("function");
		for (unsigned long int j = 0; j < functions->length(); j++)
		{
			XML::Element* f = static_cast<XML::Element*> (functions->item(j));
			// read name and type
			String name = f->getAttribute("name");
			String type = f->getAttribute("type");
			String functionName = format("%s-%Lu", name, i);

			// read function parameters
			AutoPtr<XML::NodeList> parameters = f->getElementsByTagName("param");
			for (unsigned long int j = 0; j < parameters->length(); j++)
			{
				XML::Element* p = static_cast<XML::Element*> (parameters->item(j));
				functionBuilder.addParameter(p->getAttribute("name"), fromString<Decimal>(p->innerText()));
			}

			// create function of the specified type
			if (type == "custom-discrete-probability")
			{
				// read function parameters
				AutoPtr<XML::NodeList> probabilities = f->getElementsByTagName("probability");
				for (unsigned long int j = 0; j < probabilities->length(); j++)
				{
					XML::Element* p = static_cast<XML::Element*> (probabilities->item(j));
					functionBuilder.addParameter(p->getAttribute("argument"), fromString<Decimal>(p->getAttribute("value")));
				}

				CustomDiscreteProbability* f = functionBuilder.create<CustomDiscreteProbability> (functionName);
				addFunction(f);
				objectBuilder.addParameter(name, f);
			}
			else if (type == "interval-map")
			{
				IntervalMap<ID, ID>* f = functionBuilder.create<IntervalMap<ID, ID> > (functionName);
				addFunction(f);
				objectBuilder.addParameter(name, f);
			}
			else if (type == "id-range-map")
			{
				DiscreteMap<ID, Interval<ID> >* f = functionBuilder.create<DiscreteMap<ID, Interval<ID> > > (functionName);
				addFunction(f);
				objectBuilder.addParameter(name, f);
			}
			else if (type == "pareto")
			{
				ParetoPrFunction* f = functionBuilder.create<ParetoPrFunction> (functionName);
				addFunction(f);
				objectBuilder.addParameter(name, f);
			}
			else if (type == "normal")
			{
				NormalPrFunction* f = functionBuilder.create<NormalPrFunction> (functionName);
				addFunction(f);
				objectBuilder.addParameter(name, f);
			}
			else if (type == "bounded-normal")
			{
				BoundedNormalPrFunction* f = functionBuilder.create<BoundedNormalPrFunction> (name);
				addFunction(f);
				objectBuilder.addParameter(name, f);
			}
			else
			{
				throw FeatureConfigurationException(format("Unsupported function type '%s' for function", type, name));
			}

			functionBuilder.clear();
		}

		set[i] = objectBuilder.create<T>();
		objectBuilder.clear();

		AutoPtr<XML::NodeList> probabilities = o->getElementsByTagName("probability");
		for (unsigned long int j = 0; j < probabilities->length(); j++)
		{
			setProbability(i, static_cast<XML::Element*> (probabilities->item(j)));
		}
	}
}

} // namespace Myriad

#endif /* ABSTRACTGENERATORCONFIG_H_ */

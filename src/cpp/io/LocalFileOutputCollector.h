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

#ifndef LOCALFILEOUTPUTCOLLECTOR_H_
#define LOCALFILEOUTPUTCOLLECTOR_H_

#include "io/AbstractOutputCollector.h"

#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/Logger.h>

using namespace Poco;

namespace Myriad {

class LocalFileOutputCollector : public AbstractOutputCollector
{
public:

	typedef FileOutputStream StreamType;

	LocalFileOutputCollector(const String& generatorName, const GeneratorConfig& config) :
		AbstractOutputCollector(generatorName, config),
		_isOpen(false),
		_logger(Logger::get("collector."+generatorName))
	{
		// make sure that the output-dir exists
		File outputDir(config.getString("application.output-dir"));
		outputDir.createDirectories();

		// compute the output path
		Path path(config.getString(format("generator.%s.output-file", generatorName)));
		path.makeAbsolute(config.getString("application.output-dir"));

		_path = path.toString();
	}

	LocalFileOutputCollector(const LocalFileOutputCollector& o) :
		AbstractOutputCollector(o),
		_path(o._path),
		_isOpen(false),
		_logger(Logger::get(o._logger.name()))
	{
		if (o._isOpen)
		{
			open();
		}
	}

	virtual ~LocalFileOutputCollector()
	{
		close();
	}

	void open()
	{
		if (!_isOpen)
		{
			_out.open(_path, std::ios::trunc | std::ios::binary);
			_isOpen = true;
		}
		else
		{
			throw LogicException(format("Can't open already opened FileOutputStream %s", _path));
		}
	}

	void close()
	{
		if (_isOpen)
		{
			_logger.debug(format("Closing output file %s", _path));
			_out.close();
		}
	}

	/**
	 * Output collection method.
	 */
	template<typename RecordType> void collect(const RecordType& record);

private:

	/**
	 * The path of the underlying OutputStream.
	 */
	std::string _path;

	/**
	 * The underlying output stream.
	 */
	StreamType _out;

	/**
	 * A boolean flag indicating that the underlying output stream is open.
	 */
	bool _isOpen;

	/**
	 * Logger instance.
	 */
	Logger& _logger;
};

template<typename RecordType> inline void LocalFileOutputCollector::collect(const RecordType& record)
{
	_out << record;
}

} // namespace Myriad

#endif /* LOCALFILEOUTPUTCOLLECTOR_H_ */

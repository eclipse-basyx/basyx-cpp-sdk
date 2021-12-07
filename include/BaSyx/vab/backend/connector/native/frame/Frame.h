/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_VAB_BACKEND_CONNECTOR_NATIVE_FRAME_FRAME_H
#define VAB_VAB_BACKEND_CONNECTOR_NATIVE_FRAME_FRAME_H

#include <BaSyx/abstraction/net/Buffer.h>

#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>

#include <BaSyx/util/tools/StringTools.h>

namespace basyx {
namespace vab {
namespace connector {
namespace native {

class Frame
{
private:
	uint8_t flag;
	std::string value_1;
	std::string value_2;
public:
	struct Builder {
		static Frame Get(const std::string & path);
		static Frame Set(const std::string & path, const basyx::object & value);
		static Frame Create(const std::string & path, const basyx::object & value);
		static Frame Delete(const std::string & path);
		static Frame Delete(const std::string & path, const basyx::object & value);
		static Frame Invoke(const std::string & path, const basyx::object & value);
	};
public:
	Frame();
	Frame(uint8_t flag, const std::string & value_1);
	Frame(uint8_t flag, const std::string & value_1, const std::string & value_2);

	Frame(const Frame & other) = default;
	Frame(Frame && other) noexcept = default;

	Frame & operator=(const Frame & other) = default;
	Frame & operator=(Frame && other) noexcept = default;

	~Frame() = default;
public:
	const std::string & getFirstValue() const;
	void setFirstValue(const std::string & value);

	const std::string & getSecondValue() const;
	void setSecondValue(const std::string & path);

	uint8_t getFlag() const;
	void setFlag(uint8_t flag);
	void setFlag(BaSyxCommand flag);

	std::size_t size() const;
public:
	template<typename Buffer>
	static bool write_to_buffer(Buffer & buffer, const Frame & frame)
	{
		// bail out if buffer to small
		if (frame.size() > buffer.size())
			return false;

		std::size_t pos = 0;
		char * data = reinterpret_cast<char*>(buffer.data());

		// write command field
		data[pos] = static_cast<uint8_t>(frame.getFlag());
		pos += 1;

		// write first value field
		pos += StringTools::toArray(frame.getFirstValue(), &data[pos]);

		// write second value field
		if (!frame.getSecondValue().empty()) {
			pos += StringTools::toArray(frame.getSecondValue(), &data[pos]);
		};

		return true;
	};

	template<typename Buffer>
	static Frame read_from_buffer(const Buffer & buffer)
	{
		Frame frame;

		std::size_t pos = 0;
		auto data = reinterpret_cast<const char*>(buffer.data());

		auto flag = static_cast<const uint8_t>(data[pos]);
		frame.setFlag(flag);
		pos += 1;

		frame.setFirstValue(StringTools::fromArray(&data[pos]));
		pos += frame.getFirstValue().size() + sizeof(uint32_t);

		if (pos < buffer.size())
		{
			frame.setSecondValue(StringTools::fromArray(&data[pos]));
			pos += frame.getSecondValue().size() + sizeof(uint32_t);
		};

		return frame;
	};
};

}
}
}
}

#endif /* VAB_VAB_BACKEND_CONNECTOR_NATIVE_FRAME_FRAME_H */
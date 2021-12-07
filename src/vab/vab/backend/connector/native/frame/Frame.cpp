/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/backend/connector/native/frame/Frame.h>

#include <BaSyx/util/tools/StringTools.h>

using namespace basyx::vab::connector::native;

Frame::Frame()
	: flag(0xFF)
	, value_1()
	, value_2()
{
};

Frame::Frame(uint8_t flag, const std::string & value_1) 
	: flag(flag)
	, value_1(value_1)
	, value_2()
{
};

Frame::Frame(uint8_t flag, const std::string & value_1, const std::string & value_2)
	: flag(flag)
	, value_1(value_1)
	, value_2(value_2)
{
};

uint8_t Frame::getFlag() const
{
	return this->flag;
};

void Frame::setFlag(uint8_t flag)
{
	this->flag = flag;
};

void Frame::setFlag(BaSyxCommand flag)
{
	this->flag = static_cast<decltype(this->flag)>(flag);
};

const std::string & Frame::getFirstValue() const
{
	return this->value_1;
};

void Frame::setFirstValue(const std::string & value)
{
	this->value_1 = value;
};

const std::string & Frame::getSecondValue() const
{
	return this->value_2;
};

void Frame::setSecondValue(const std::string & value)
{
	this->value_2 = value;
};

//bool Frame::write_to_buffer(const basyx::net::Buffer & buffer, const Frame & frame)
//{
//	// bail out if buffer to small
//	if (frame.size() > buffer.size())
//		return false;
//
//	std::size_t pos = 0;
//	char * data = reinterpret_cast<char*>(buffer.data());
//
//	// write command field
//	data[pos] = static_cast<uint8_t>(frame.getFlag());
//	pos += 1;
//	
//	// write first value field
//	pos += StringTools::toArray(frame.getFirstValue(), &data[pos]);
//
//	// write second value field
//	if (!frame.getSecondValue().empty())
//	{
//		pos += StringTools::toArray(frame.getSecondValue(), &data[pos]);
//	};
//
//	return true;
//};

//Frame Frame::read_from_buffer(const basyx::net::Buffer & buffer)
//{
//	Frame frame;
//
//	std::size_t pos = 0;
//	char * data = reinterpret_cast<char*>(buffer.data());
//	
//	uint8_t flag = static_cast<uint8_t>(data[pos]);
//	frame.setFlag(flag);
//	pos += 1;
//
//	frame.setFirstValue(StringTools::fromArray(&data[pos]));
//	pos += frame.getFirstValue().size() + sizeof(uint32_t);
//
//	if (pos < buffer.size())
//	{
//		frame.setSecondValue(StringTools::fromArray(&data[pos]));
//		pos += frame.getSecondValue().size() + sizeof(uint32_t);
//	};
//
//	return frame;
//};

std::size_t Frame::size() const
{
	std::size_t size = 1; // size of flag field
	size += sizeof(uint32_t) + this->getFirstValue().size(); // size of first value + length

	if(!this->getSecondValue().empty())
		size += sizeof(uint32_t) + this->getSecondValue().size(); // size of second value + length

	return size;
};

Frame Frame::Builder::Get(const std::string & path)
{
	return Frame{ static_cast<uint8_t>(BaSyxCommand::Get), path };
};

Frame Frame::Builder::Set(const std::string & path, const basyx::object & value)
{
	return Frame{
		static_cast<uint8_t>(BaSyxCommand::Set),
		path,
		basyx::serialization::json::serialize(value).dump(4)
	};
};

Frame Frame::Builder::Create(const std::string & path, const basyx::object & value)
{
	return Frame{
		static_cast<uint8_t>(BaSyxCommand::Create),
		path,
		basyx::serialization::json::serialize(value).dump(4)
	};
};

Frame Frame::Builder::Delete(const std::string & path)
{
	return Frame{ static_cast<uint8_t>(BaSyxCommand::Delete), path };
}; 

Frame Frame::Builder::Delete(const std::string & path, const basyx::object & value)
{
	return Frame{
		static_cast<uint8_t>(BaSyxCommand::Delete),
		path,
		basyx::serialization::json::serialize(value).dump(4)
	};
};

Frame Frame::Builder::Invoke(const std::string & path, const basyx::object & value)
{
	return Frame{
		static_cast<uint8_t>(BaSyxCommand::Invoke),
		path,
		basyx::serialization::json::serialize(value).dump(4)
	};
};
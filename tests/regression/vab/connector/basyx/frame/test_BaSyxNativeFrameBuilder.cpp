/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
 * test_BaSyxNativeFrameBuilder.cpp
 *
 *  Created on: 14.08.2018
 *      Author: schnicke
 */

#include <memory>

#include <gtest/gtest.h>

#include <BaSyx/vab/backend/connector/native/frame/BaSyxNativeFrameBuilder.h>

#include <BaSyx/shared/types.h>
#include <BaSyx/shared/object.h>

#include <BaSyx/util/util.h>
#include <BaSyx/util/tools/StringTools.h>


TEST(BaSyxNativeFrameBuilder, buildGetFrame) {
	auto builder = util::make_unique<basyx::vab::connector::native::frame::BaSyxNativeFrameBuilder>();

	std::unique_ptr<char> buffer(new char[1000]);
	std::string path = "TestPath";
	size_t size = builder->buildGetFrame(path, buffer.get());
	
	ASSERT_EQ(buffer.get()[0], static_cast<uint8_t>(BaSyxCommand::Get));
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1), path);
	
	// 1 byte command, 4 byte string size, n byte string
	ASSERT_EQ(size, 1 + 4 + path.size());
}

TEST(BaSyxNativeFrameBuilder, buildSetFrame) {
	auto builder = util::make_unique<basyx::vab::connector::native::frame::BaSyxNativeFrameBuilder>();

	std::unique_ptr<char> buffer(new char[1000]);
	std::string path = "TestPath";
	basyx::object val = 10;
	std::string valSerialize = basyx::serialization::json::serialize(val).dump(4);

	size_t size = builder->buildSetFrame(path, val, buffer.get());
	ASSERT_EQ(buffer.get()[0], static_cast<uint8_t>(BaSyxCommand::Set));
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1), path);
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1 + 4 + path.length()), valSerialize);
	
	// 1 byte command, 4 byte string size, n byte string
	ASSERT_EQ(size, 1 + 4 + path.size() + 4 + valSerialize.length());
}

TEST(BaSyxNativeFrameBuilder, buildCreateFrame) {
	auto builder = util::make_unique<basyx::vab::connector::native::frame::BaSyxNativeFrameBuilder>();

	std::unique_ptr<char> buffer(new char[1000]);
	std::string path = "TestPath";
	basyx::object val = 10;
	std::string valSerialize = basyx::serialization::json::serialize(val).dump(4);

	size_t size = builder->buildCreateFrame(path, val, buffer.get());
	ASSERT_EQ(buffer.get()[0], static_cast<uint8_t>(BaSyxCommand::Create));
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1), path);
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1 + 4 + path.length()), valSerialize);
	
	// 1 byte command, 4 byte string size, n byte string
	ASSERT_EQ(size, 1 + 4 + path.size() + 4 + valSerialize.length());
}

TEST(BaSyxNativeFrameBuilder, buildSimpleDeleteFrame) {
	auto builder = util::make_unique<basyx::vab::connector::native::frame::BaSyxNativeFrameBuilder>();

	std::unique_ptr<char> buffer(new char[1000]);
	std::string path = "TestPath";
	size_t size = builder->buildDeleteFrame(path, buffer.get());
	
	ASSERT_EQ(buffer.get()[0], static_cast<uint8_t>(BaSyxCommand::Delete));
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1), path);
	
	// 1 byte command, 4 byte string size, n byte string
	ASSERT_EQ(size, 1 + 4 + path.size());
}

TEST(BaSyxNativeFrameBuilder, buildComplexDeleteFrame) {
	auto builder = util::make_unique<basyx::vab::connector::native::frame::BaSyxNativeFrameBuilder>();

	std::unique_ptr<char> buffer(new char[1000]);
	std::string path = "TestPath";
	basyx::object val = 10;
	std::string valSerialize = basyx::serialization::json::serialize(val).dump(4);

	size_t size = builder->buildDeleteFrame(path, val, buffer.get());
	ASSERT_EQ(buffer.get()[0], static_cast<uint8_t>(BaSyxCommand::Delete));
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1), path);
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1 + 4 + path.length()), valSerialize);
	
	// 1 byte command, 4 byte string size, n byte string
	ASSERT_EQ(size, 1 + 4 + path.size() + 4 + valSerialize.length());
}

TEST(BaSyxNativeFrameBuilder, buildInvokeFrame) {
	auto builder = util::make_unique<basyx::vab::connector::native::frame::BaSyxNativeFrameBuilder>();

	std::unique_ptr<char> buffer(new char[1000]);
	std::string path = "TestPath";
	basyx::object val = 10;
	std::string valSerialize = basyx::serialization::json::serialize(val).dump(4);

	size_t size = builder->buildInvokeFrame(path, val, buffer.get());
	ASSERT_EQ(buffer.get()[0], static_cast<uint8_t>(BaSyxCommand::Invoke));
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1), path);
	ASSERT_EQ(StringTools::fromArray(buffer.get() + 1 + 4 + path.length()), valSerialize);
	
	// 1 byte command, 4 byte string size, n byte string
	ASSERT_EQ(size, 1 + 4 + path.size() + 4 + valSerialize.length());
}

/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <gtest/gtest.h>

#include <BaSyx/aas/simple/submodelelement/file/File.h>
#include <BaSyx/aas/map_v2/submodelelement/file/File.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::File,
	map::File
>;

template<class Impl>
class FileTest :public ::testing::Test {
protected:
	using impl_t = Impl;
protected:
	const std::string idShort = "id_test";
	const std::string mimeType = "bytes";

	std::unique_ptr<api::IFile> file;
protected:
	void SetUp() override
	{
		this->file = util::make_unique<Impl>(idShort, mimeType);
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(FileTest, ImplTypes);

TYPED_TEST(FileTest, TestConstructor)
{
	ASSERT_EQ(this->file->getIdShort(), this->idShort);
	ASSERT_EQ(this->file->getMimeType(), this->mimeType);
}

TYPED_TEST(FileTest, TestMimeType)
{
	this->file->setMimeType("test");
	ASSERT_EQ(this->file->getMimeType(), "test");
}

TYPED_TEST(FileTest, TestPath)
{
	this->file->setPath("url://test");
	ASSERT_EQ(this->file->getPath(), "url://test");
}


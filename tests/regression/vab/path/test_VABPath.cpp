/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include "gtest/gtest.h"
#include <BaSyx/vab/core/util/VABPath.h>

#include <memory>


using namespace basyx::vab::core;

TEST(TestBaSyxVABPath, TestConstructionWithSingleSubPath)
{
	std::string path = "basyx://127.0.0.1:6998/somepath";
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	auto elements = vabpath->getElements();
	ASSERT_EQ(path, vabpath->toString());
	// should be 4 elements, because the empty element between basyx and ip address
	ASSERT_EQ(4, elements.size());
	// no operations at the end, therefore no operation path
	ASSERT_FALSE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestConstructionWithTwoSubPathsAndOperation)
{
	const char path[] = "basyx://127.0.0.1:6998/somepath//https://localhost/test/operations";
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	auto elements = vabpath->getElements();

	ASSERT_EQ(10, elements.size());
	ASSERT_TRUE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestConstructionWithElementsListOperations)
{
	std::vector<std::string> in_elements;
	in_elements.push_back("basyx:");
	in_elements.push_back("");
	in_elements.push_back("127.0.0.1:6998");
	in_elements.push_back("operations");

	std::unique_ptr<VABPath> vabpath(new VABPath(in_elements));

	auto elements = vabpath->getElements();

	std::string path = "basyx://127.0.0.1:6998/operations";

	//the construction of a path should not change anything
	ASSERT_EQ(4, elements.size());
	ASSERT_EQ(path, vabpath->toString());
	// the last element is operations -> path is operation
	ASSERT_TRUE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestConstructionWithElementsListNoOperations)
{
	std::vector<std::string> in_elements;
	in_elements.push_back("basyx:");
	in_elements.push_back("");
	in_elements.push_back("127.0.0.1:6998");
	in_elements.push_back("test");

	std::unique_ptr<VABPath> vabpath(new VABPath(in_elements));

	auto elements = vabpath->getElements();

	std::string path = "basyx://127.0.0.1:6998/test";

	ASSERT_EQ(4, elements.size());
	ASSERT_EQ(path, vabpath->toString());
	// the last element is no operations -> no operations path
	ASSERT_FALSE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestGetLastElement)
{
	std::unique_ptr<VABPath> vabpath(new VABPath("basyx://127.0.0.1:6998/operations"));
	ASSERT_EQ("operations", vabpath->getLastElement());

	// last element should be element without delimiter /
	std::unique_ptr<VABPath> vabpath2(new VABPath("basyx://127.0.0.1:6998/test/"));
	ASSERT_EQ("test", vabpath2->getLastElement());
}

TEST(TestBaSyxVABPath, TestGetParentPath)
{
	std::unique_ptr<VABPath> vabpath(new VABPath("basyx://127.0.0.1:6998/test/"));

	ASSERT_EQ("basyx://127.0.0.1:6998", vabpath->getParentPath().toString());
}

TEST(TestBaSyxVABPath, TestGetParentPathIsEmpty)
{
	std::unique_ptr<VABPath> vabpath(new VABPath("basyx:"));

	// The parent path of a single path-element is an empty path
	ASSERT_EQ("", vabpath->getParentPath().toString());
}

TEST(TestBaSyxVABPath, TestGetParentPathIsCompleteEmpty)
{
	std::unique_ptr<VABPath> vabpath(new VABPath(""));

	// The parent path of an empty path is an empty path
	ASSERT_EQ("", vabpath->getParentPath().toString());
}

TEST(TestBaSyxVABPath, TestRemovePrefix)
{
	std::string path = "basyx://127.0.0.1:6998/test";
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	vabpath->removePrefix("basyx:");

	ASSERT_EQ("127.0.0.1:6998/test", vabpath->toString());
	// old length was 4 and new one must be 2, 
	// because an empty element at the begin makes no sense
	ASSERT_EQ(2, vabpath->getElements().size());
}

TEST(TestBaSyxVABPath, TestRemoveNotExistingPrefix)
{
	std::string path = "basyx://127.0.0.1:6998/test";
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	//Should not change anything
	vabpath->removePrefix("asy:");

	ASSERT_EQ(4, vabpath->getElements().size());
	ASSERT_EQ(path, vabpath->toString());
}

TEST(TestBaSyxVABPath, TestToStringWithoutPrefix)
{
	std::string path = "basyx://127.0.0.1:6998/test";
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	auto new_path = vabpath->toStringWithoutPrefix("basyx:");
	ASSERT_EQ("127.0.0.1:6998/test", new_path);

	// operation should not change anything at the path
	ASSERT_EQ(path, vabpath->toString());
}

TEST(TestBaSyxVABPath, TestAppend)
{
	std::string path = "basyx://127.0.0.1:6998/test";
	std::string path2 = "https://localhost/path/";

	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	vabpath->append(path2);

	// new path should contain "//" between both paths
	ASSERT_EQ(9, vabpath->getElements().size());
	ASSERT_EQ(path + "//https://localhost/path", vabpath->toString());
	// should not be operations path
	ASSERT_FALSE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestAppendOperation)
{
	std::string path = "basyx://127.0.0.1:6998/test";
	std::string path2 = "https://localhost/operations";

	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	vabpath->append(path2);

	ASSERT_EQ(9, vabpath->getElements().size());
	ASSERT_EQ(path + "//" + path2, vabpath->toString());
	// should be operations path
	ASSERT_TRUE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestAppendWasOperation)
{
	std::string path = "basyx://127.0.0.1:6998/operations";
	std::string path2 = "https://localhost/path/anotherPath";

	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	//is operations now
	ASSERT_TRUE(vabpath->isOperationPath());

	vabpath->append(path2);

	ASSERT_EQ(10, vabpath->getElements().size());
	ASSERT_EQ(path + "//" + path2, vabpath->toString());
	//no operation anymore
	ASSERT_FALSE(vabpath->isOperationPath());
}

TEST(TestBaSyxVABPath, TestGetAddressEntry)
{
	std::string entry = "basyx://127.0.0.1:6998/operations";
	std::string second_path = "https://localhost/path/anotherPath";
	std::string third_path = "http://192.168.0.0/example/";

	std::string path = entry + "//" + second_path + "//" + third_path;
	std::unique_ptr<VABPath> vabpath(new VABPath(path));


	// Address entry is only the first address part
	ASSERT_EQ(entry, vabpath->getAddressEntry());
}

TEST(TestBaSyxVABPath, TestGetAddressEntryIsOnlyEntry)
{
	std::string entry = "basyx://127.0.0.1:6998/operations";
	std::unique_ptr<VABPath> vabpath(new VABPath(entry));

	ASSERT_EQ(entry, vabpath->getAddressEntry());
}

TEST(TestBaSyxVABPath, TestGetEntryPath)
{
	std::string entry = "basyx://127.0.0.1:6998/operations";
	std::string second_path = "https://localhost/path/anotherPath";
	std::string third_path = "http://192.168.0.0/example";

	std::unique_ptr<VABPath> vabpath(new VABPath(entry));
	vabpath->append(second_path);
	vabpath->append(third_path);

	// constructs a new VABpath object
	auto entryPath = vabpath->getAddressEntryPath();
	ASSERT_EQ(entry, entryPath.toString());

	// the original should not be affected
	std::string new_path = entry + "//" + second_path + "//" + third_path;
	ASSERT_EQ(new_path, vabpath->toString());
}

TEST(TestBaSyxVABPath, TestRemoveEntry)
{
	std::string entry = "basyx://127.0.0.1:6998/operations";
	std::string second_path = "https://localhost/path/anotherPath/";
	std::string third_path = "http://192.168.0.0/example";

	std::string path = entry + "//" + second_path + "//" + third_path;
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	vabpath->removeEntry();

	// the remaining path should only consist of the second and third path
	std::string path_without_entry = second_path + "//" + third_path;

	ASSERT_EQ(path_without_entry, vabpath->toString());
}

TEST(TestBaSyxVABPath, TestRemoveEntryIsPath)
{
	std::string path = "http://192.168.0.0/example";

	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	vabpath->removeEntry();

	// path should be empty now
	ASSERT_EQ("", vabpath->toString());
	ASSERT_TRUE(vabpath->isEmpty());
}

TEST(TestBaSyxVABPath, TestToStringWithoutEntry)
{
	std::string entry = "basyx://127.0.0.1:6998/operations";
	std::string second_path = "https://localhost/path/anotherPath/";
	std::string third_path = "http://192.168.0.0/example";

	std::string path = entry + "//" + second_path + "//" + third_path;
	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	std::string path_without_entry = second_path + "//" + third_path;

	// string should be without empty
	ASSERT_EQ(path_without_entry, vabpath->toStringWithoutEntry());
	// but path should be further complete
	ASSERT_EQ(entry + "//" + path_without_entry, vabpath->toString());
}

TEST(TestBaSyxVABPath, TestToStringWithoutEntryIsPath)
{
	std::string path = "basyx://127.0.0.1:6998/operations";

	std::unique_ptr<VABPath> vabpath(new VABPath(path));

	// string should be emtpy
	ASSERT_EQ("", vabpath->toStringWithoutEntry());
	// but path should be the same anymore
	ASSERT_EQ(path, vabpath->toString());
}

TEST(TestBaSyxVABPath, TestAdditionOfPaths)
{
	std::string path = "basyx://127.0.0.1:6998/operations";
	std::string second_path = "http://192.168.0.0/example";

	std::shared_ptr<VABPath> vabpath1(new VABPath(path));
	std::shared_ptr<VABPath> vabpath2(new VABPath(second_path));

	auto vabpath = *vabpath1.get() + *vabpath2.get();

	// string should be the same
	ASSERT_EQ(path + "//" + second_path, vabpath.toString());
	// but path 1 and 2 should be the same anymore
	ASSERT_EQ(path, vabpath1->toString());
	ASSERT_EQ(second_path, vabpath2->toString());
}

TEST(TestBaSyxVABPath, ImplicitConversionToString)
{
	std::string path = "basyx://127.0.0.1:6998/operations";

	std::shared_ptr<VABPath> vabpath(new VABPath(path));

	// string should be the same
	std::string path_string = *vabpath;
	ASSERT_EQ(path, path_string);
}

TEST(TestBaSyxVABPath, TestEmptyPath)
{
	std::unique_ptr<VABPath> vabpath(new VABPath(""));

	ASSERT_TRUE(vabpath->isEmpty());
}

TEST(TestBaSyxVABPath, TestPathNotEmpty)
{
	std::unique_ptr<VABPath> vabpath(new VABPath("basyx://127.0.0.1:6998/"));

	ASSERT_FALSE(vabpath->isEmpty());
}

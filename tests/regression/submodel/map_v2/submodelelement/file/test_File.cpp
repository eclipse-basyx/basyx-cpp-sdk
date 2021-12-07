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

#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/file/File.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class FileTest : public ::testing::Test {};

TEST_F(FileTest, TestObjectConstructor)
{
  // compose parent classes
  object object = TestingObjects::map::testingReferable_1().getMap();
  object.insert(TestingObjects::map::testingHasDataSpecification().getMap());
  object.insert(TestingObjects::map::testingQualifiable().getMap());
  object.insertKey(SubmodelElement::Path::Kind, ModelingKind_::to_string(ModelingKind::Instance));

  object.insertKey(File::Path::MimeType, "Mime type");
  object.insertKey(File::Path::Value, "Value");

  // build from object
  File file{object};

  ASSERT_TRUE(TestingObjects::map::testingReferable_1(file));
  ASSERT_TRUE(TestingObjects::map::testingHasDataSpecification(file));
  ASSERT_TRUE(TestingObjects::map::testingQualifiable(file));
  ASSERT_EQ(file.getMimeType(), "Mime type");
  ASSERT_EQ(file.getPath(), "Value");
}

TEST_F(FileTest, TestObjectCopy)
{
  File file{"id short", "Mime type"};
  file.setSemanticId(util::make_unique<Reference>(TestingObjects::map::testingReference_1()));

  file.setPath("test path");

  auto map = file.getMap();
  File copied{map};

  ASSERT_EQ( "id short", copied.getIdShort());
  ASSERT_EQ("Mime type", copied.getMimeType());
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *file.getSemanticId());
  ASSERT_EQ("test path", file.getPath());
}
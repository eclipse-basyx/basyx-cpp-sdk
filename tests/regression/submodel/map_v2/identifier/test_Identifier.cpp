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

#include "BaSyx/aas/map_v2/dataspecification/DataSpecification.h"

using namespace basyx::aas::map;
using namespace basyx::aas;

class IdentifierTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}
};

TEST_F(IdentifierTest, TestEqualityOperator_same)
{
  simple::Identifier id1(IdentifierType::IRDI, "id");
  simple::Identifier id2(IdentifierType::IRDI, "id");

  ASSERT_TRUE(id1 == id2);
}



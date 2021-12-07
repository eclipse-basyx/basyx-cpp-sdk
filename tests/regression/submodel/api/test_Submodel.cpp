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

#include <BaSyx/aas/map_v2/Submodel.h>
#include <BaSyx/aas/map_v2/aas/Asset.h>
#include <BaSyx/aas/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/aas/simple/Submodel.h>
#include <BaSyx/aas/simple/aas/Asset.h>
#include <BaSyx/aas/simple/aas/AssetAdministrationShell.h>

using namespace basyx::aas;
using namespace basyx::aas::map;
using namespace basyx::aas::simple;

// Implementations to run tests for
struct map_types {
	using submodel_t = map::Submodel;
	using asset_t = map::Asset;
	using reference_t = map::Reference;
	using aas_t = map::AssetAdministrationShell;
};

struct simple_types {
	using submodel_t = simple::Submodel;
	using asset_t = simple::Asset;
  using reference_t = simple::Reference;
  using aas_t = simple::AssetAdministrationShell;
};

using TestTypes = ::testing::Types<
	map_types,
	simple_types>;

template <class Types>
class SubmodelTest : public ::testing::Test {
public:
	using types = Types;

protected:
	std::unique_ptr<typename Types::submodel_t> subModel;
};

TYPED_TEST_CASE(SubmodelTest, TestTypes);

TYPED_TEST(SubmodelTest, TestSubmodelConstructor)
{
	using namespace basyx::aas;

  simple::Identifier identifier( IdentifierType::Custom, "testId");
	typename TypeParam::submodel_t submodel("test", identifier);

	ASSERT_EQ(submodel.getIdShort(), "test");
	ASSERT_EQ(submodel.getIdentification(), identifier);
};

TYPED_TEST(SubmodelTest, TestSubmodelReferences)
{
	using aas_t = typename TypeParam::aas_t;
	using asset_t = typename TypeParam::asset_t;
	using submodel_t = typename TypeParam::submodel_t;

	// Create asset
	asset_t asset{
		"asset", /* idShort */
		simple::Identifier::Custom("asset") /* identifier */
	};

	// Create the asset administration shell and assign asset
	aas_t aas{
		"aas", /* idShort */
		simple::Identifier::Custom("aas"), /* identifier */
		asset
	};


	auto & submodels = aas.getSubmodels();
	submodels.template createElement<submodel_t>("submodel", simple::Identifier::Custom("submodel"));

	ASSERT_EQ(submodels.size(), 1);

	auto sm = submodels.getElement("submodel");
	ASSERT_TRUE(sm != nullptr);

	ASSERT_EQ(sm->getIdShort(), "submodel");
}

TYPED_TEST(SubmodelTest, TestSubmodelSemanticId)
{
  simple::Identifier identifier( IdentifierType::Custom, "testId");
  typename TypeParam::submodel_t submodel("test", identifier);

  using reference_t = typename TypeParam::reference_t;
  simple::Key key(KeyElements::DataElement, false, KeyType::IdShort, "key");
  std::unique_ptr<reference_t> semanticId = util::make_unique<reference_t>(key);
  submodel.setSemanticId(std::move(semanticId));

  ASSERT_EQ(submodel.getSemanticId()->getKeys().at(0), key);
}
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

#include <BaSyx/aas/api_v2/aas/IAssetAdministrationShell.h>
#include <BaSyx/aas/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/aas/simple/aas/AssetAdministrationShell.h>

#include <BaSyx/aas/map_v2/Submodel.h>

#include <BaSyx/util/util.h>

using namespace basyx::aas;

using ImplTypes = ::testing::Types<
    std::tuple<map::AssetAdministrationShell, map::Asset>,
    std::tuple<simple::AssetAdministrationShell, simple::Asset>>;

template<class Impl>
class AssetAdministrationShellTest :public ::testing::Test {
protected:
  using impl_t = typename std::tuple_element<0, Impl>::type;
  using asset_t = typename std::tuple_element<1, Impl>::type;

	std::unique_ptr<api::IAssetAdministrationShell> aas;
protected:
	void SetUp() override
	{
		aas = util::make_unique<impl_t>("testAas",
			simple::Identifier::Custom("testAas"), 
			asset_t{ "testAsset", simple::Identifier::Custom("testAsset") }
			);
	}

	void TearDown() override
	{	}
};

TYPED_TEST_CASE(AssetAdministrationShellTest, ImplTypes);

TYPED_TEST(AssetAdministrationShellTest, TestModelType)
{
	ASSERT_EQ(this->aas->GetModelType(), basyx::aas::ModelTypes::AssetAdministrationShell);
};

TYPED_TEST(AssetAdministrationShellTest, TestAddSubmodel)
{
	auto submodel = this->aas->getSubmodels().template createElement<basyx::aas::map::Submodel>("testSubmodel", simple::Identifier::Custom("testSubmodel"));

	ASSERT_EQ(this->aas->getSubmodels().size(), 1);

	return;
};

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

#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/simple/qualifier/Identifiable.h>
#include <BaSyx/aas/map_v2/qualifier/Identifiable.h>

using namespace basyx::aas;

// Constants
static const char * idShort = "testId";

// Implementations to run tests for
using ImplTypes = ::testing::Types<
  std::tuple<simple::Identifiable, simple::AdministrativeInformation>,
  std::tuple<map::Identifiable, map::AdministrativeInformation>
>;

template<class Impl>
class IdentifiableTest :public ::testing::Test {
protected:
  using impl_t = typename std::tuple_element<0, Impl>::type;
  using impl_admin_info_t = typename std::tuple_element<1, Impl>::type;

	std::unique_ptr<impl_t> identifiable;

	impl_admin_info_t administrative_information;

protected:
	void SetUp() override
	{
		this->identifiable = util::make_unique<impl_t>(idShort, simple::Identifier{ IdentifierType::Custom, "Test" });
		this->administrative_information = impl_admin_info_t("test version", "test revision");
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(IdentifiableTest, ImplTypes);

TYPED_TEST(IdentifiableTest, TestConstructor)
{
	ASSERT_EQ(this->identifiable->getIdShort(), idShort);
	ASSERT_EQ(this->identifiable->getCategory(), nullptr);
	ASSERT_EQ(this->identifiable->getParent(), nullptr);

	auto ident = this->identifiable->getIdentification();
	ASSERT_EQ(ident.getId(), "Test" );
	ASSERT_EQ(ident.getIdType(), IdentifierType::Custom );
}

TYPED_TEST(IdentifiableTest, TestSetAdministrativeInformation)
{
  ASSERT_FALSE(this->identifiable->hasAdministrativeInformation());

  this->identifiable->setAdministrativeInformation(this->administrative_information);

  ASSERT_TRUE(this->identifiable->hasAdministrativeInformation());
  ASSERT_EQ(*this->identifiable->getAdministrativeInformation().getVersion(), std::string("test version"));
}
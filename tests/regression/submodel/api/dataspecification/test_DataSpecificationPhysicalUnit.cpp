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

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationPhysicalUnit.h>
#include <BaSyx/aas/simple/dataspecification/DataSpecificationPhysicalUnit.h>
#include <BaSyx/aas/map_v2/dataspecification/DataSpecificationPhysicalUnit.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::DataSpecificationPhysicalUnit,
	map::DataSpecificationPhysicalUnit
>;

template<class Impl>
class DataSpecificationPhysicalUnitTest :public ::testing::Test {
protected:
	using impl_t = Impl;
protected:
  simple::LangStringSet lang_string;
	std::unique_ptr<api::IDataSpecificationPhysicalUnit> data_spec;
protected:
	void SetUp() override
	{
	  this->lang_string = simple::LangStringSet("EN", "test");
		this->data_spec = util::make_unique<Impl>("Test data specification", "Test symbol", this->lang_string);
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(DataSpecificationPhysicalUnitTest, ImplTypes);

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestConstructor)
{
	ASSERT_EQ(this->data_spec->getUnitName(), std::string("Test data specification"));
  ASSERT_EQ(this->data_spec->getUnitSymbol(), std::string("Test symbol"));
  ASSERT_EQ(this->data_spec->getDefinition(), this->lang_string);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetDefinition)
{
  api::ILangStringSet * other_lang_string = new simple::LangStringSet("DE", "test2");

  this->data_spec->setDefinition(*other_lang_string);

  api::ILangStringSet * definition = &this->data_spec->getDefinition();

  ASSERT_EQ(this->data_spec->getDefinition(), *other_lang_string);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetUnitName)
{
  std::string unit_name("test");

  this->data_spec->setUnitName(unit_name);

  ASSERT_EQ(this->data_spec->getUnitName(), unit_name);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetUnitSymbol)
{
  std::string unit_symbol("test");

  this->data_spec->setUnitSymbol(unit_symbol);

  ASSERT_EQ(this->data_spec->getUnitSymbol(), unit_symbol);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetSINotation)
{
  ASSERT_EQ(this->data_spec->getSiNotation(), nullptr);

  std::string si_notation("test");

  this->data_spec->setSiNotation(si_notation);

  ASSERT_EQ(*this->data_spec->getSiNotation(), si_notation);
}


TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetSiName)
{
  ASSERT_EQ(this->data_spec->getSiName(), nullptr);

  std::string new_SiName("test");

  this->data_spec->setSiName(new_SiName);

  ASSERT_EQ(*this->data_spec->getSiName(), new_SiName);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetDinNotation)
{
  ASSERT_EQ(this->data_spec->getDinNotation(), nullptr);

  std::string new_DinNotation("test");

  this->data_spec->setDinNotation(new_DinNotation);

  ASSERT_EQ(*this->data_spec->getDinNotation(), new_DinNotation);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetEceName)
{
  ASSERT_EQ(this->data_spec->getEceName(), nullptr);

  std::string new_EceName("test");

  this->data_spec->setEceName(new_EceName);

  ASSERT_EQ(*this->data_spec->getEceName(), new_EceName);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetEceCode)
{
  ASSERT_EQ(this->data_spec->getEceCode(), nullptr);

  std::string new_EceCode("test");

  this->data_spec->setEceCode(new_EceCode);

  ASSERT_EQ(*this->data_spec->getEceCode(), new_EceCode);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetNistName)
{
  ASSERT_EQ(this->data_spec->getNistName(), nullptr);

  std::string new_NistName("test");

  this->data_spec->setNistName(new_NistName);

  ASSERT_EQ(*this->data_spec->getNistName(), new_NistName);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetSourceOfDefinition)
{
  ASSERT_EQ(this->data_spec->getSourceOfDefinition(), nullptr);

  std::string new_SourceOfDefinition("test");

  this->data_spec->setSourceOfDefinition(new_SourceOfDefinition);

  ASSERT_EQ(*this->data_spec->getSourceOfDefinition(), new_SourceOfDefinition);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetConversionFactor)
{
  ASSERT_EQ(this->data_spec->getConversionFactor(), nullptr);

  std::string new_ConversionFactor("test");

  this->data_spec->setConversionFactor(new_ConversionFactor);

  ASSERT_EQ(*this->data_spec->getConversionFactor(), new_ConversionFactor);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetRegistrationAuthorityId)
{
  ASSERT_EQ(this->data_spec->getRegistrationAuthorityId(), nullptr);

  std::string new_RegistrationAuthorityId("test");

  this->data_spec->setRegistrationAuthorityId(new_RegistrationAuthorityId);

  ASSERT_EQ(*this->data_spec->getRegistrationAuthorityId(), new_RegistrationAuthorityId);
}

TYPED_TEST(DataSpecificationPhysicalUnitTest, TestGetSetSupplier)
{
  ASSERT_EQ(this->data_spec->getSupplier(), nullptr);

  std::string new_Supplier("test");

  this->data_spec->setSupplier(new_Supplier);

  ASSERT_EQ(*this->data_spec->getSupplier(), new_Supplier);
}
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
#include <BaSyx/aas/simple/submodelelement/property/Property.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>
#include <BaSyx/aas/simple/common/xsd_types/AnyURI.h>
#include <BaSyx/aas/enumerations/XsdTypes.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::Property<int>,
	map::Property<int>
>;

template<class Impl>
class PropertyTest :public ::testing::Test {
protected:
	using impl_t = Impl;
protected:
	std::unique_ptr<api::IProperty> property;
protected:
	void SetUp() override
	{
		std::string idShort("id test");
		this->property = util::make_unique<Impl>(idShort);
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(PropertyTest, ImplTypes);

TYPED_TEST(PropertyTest, TestConstructor)
{
  ASSERT_EQ(this->property->getIdShort(), std::string("id test"));
}

TYPED_TEST(PropertyTest, TestValueType)
{
  this->property->setValueType("valueType test");
  ASSERT_EQ(this->property->getValueType(), std::string("valueType test"));
}

TYPED_TEST(PropertyTest, TestObject)
{
  basyx::object o(123);
  this->property->setObject(o);
  ASSERT_EQ(this->property->getObject(), basyx::object(123));
}

TYPED_TEST(PropertyTest, TestValueID)
{
  simple::Key key(KeyElements::ConceptDictionary, false, KeyType::Custom, "test key");
  std::unique_ptr<api::IReference> ref = util::make_unique<simple::Reference>(key);
  this->property->setValueId(*ref);
  ASSERT_EQ(this->property->getValueId()->getKeys().at(0), key);
}

TYPED_TEST(PropertyTest, TestGetKeyElementType)
{
  ASSERT_EQ(this->property->getKeyElementType(), KeyElements::Property);
}

TYPED_TEST(PropertyTest, TestAnyURI)
{
  map::Property<simple::AnyURI> map_uri_prop("id");
  ASSERT_EQ(map_uri_prop.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_anyuri));
}

TYPED_TEST(PropertyTest, TestSafeDateTime)
{
  map::Property<simple::DateTime> dateTime_property("test id");
  std::string valueType = dateTime_property.getValueType();
  ASSERT_EQ(valueType, XsdTypes_::to_string(XsdTypes::xsd_dateTime));

  //Try to add a DateTime
  time_t t = 1563002200;
  tm time = *gmtime(&t);
  simple::DateTime test_time(time);
  dateTime_property.setValue(test_time);

  auto dateTime_string = dateTime_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
  ASSERT_EQ(dateTime_string, std::string("2019-07-13T07:16:40Z"));
  tm saved_time = dateTime_property.getValue().getTime();
  ASSERT_EQ(mktime(&saved_time), mktime(&time));
}

TYPED_TEST(PropertyTest, TestSafeDate)
{
  map::Property<simple::Date> date_property("test id");
  std::string valueType = date_property.getValueType();
  ASSERT_EQ(valueType, XsdTypes_::to_string(XsdTypes::xsd_date));

  //Try to add a Date
  tm date;
  //epoche starts at 1900
  date.tm_year = 1986 - 1900;
  //month count starts at 0
  date.tm_mon = 5 - 1;
  date.tm_mday = 6;
  simple::Date test_date(date);
  date_property.setValue(test_date);

  auto dateTime_string = date_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
  ASSERT_EQ(dateTime_string, std::string("1986-05-06Z"));
  tm saved_date = date_property.getValue().getDate();
  ASSERT_EQ(saved_date.tm_year, date.tm_year);
  ASSERT_EQ(saved_date.tm_mon, date.tm_mon);
  ASSERT_EQ(saved_date.tm_mday, date.tm_mday);
}

TYPED_TEST(PropertyTest, TestSafeDayTimeDuration)
{
  map::Property<simple::DayTimeDuration> duration_property("test id");
  ASSERT_EQ(duration_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_dayTimeDuration));

  std::vector<std::pair<long, std::string>> test_cases = {
      {0, "P"},
      {12312123, "P142D12H2M3S"},
      {12268923, "P142D2M3S"},
      {12312120, "P142D12H2M"},
      {59, "P59S"},
      {60, "P1M"},
      {-1, "-P1S"},
      {-12312123, "-P142D12H2M3S"}
  };

  for (auto pair : test_cases)
  {
    std::chrono::duration<long> test_duration{pair.first};
    simple::DayTimeDuration duration{test_duration};
    duration_property.setValue(duration);

    auto dateTime_string = duration_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(dateTime_string, std::string(pair.second));
    ASSERT_EQ(duration_property.getValue().getDuration().count(), test_duration.count());
  }
}



TYPED_TEST(PropertyTest, TestSafeYearMonthDuration)
{
  map::Property<simple::YearMonthDuration> duration_property("test id");
  ASSERT_EQ(duration_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_yearMonthDuration));

  std::vector<std::tuple<int, int, int, int, std::string>> test_cases = {
      {0, 0, 0, 0, "P"},
      {99, 0, 99, 0, "P99Y"},
      {0, 11, 0, 11, "P11M"},
      {50, 100, 58, 4, "P58Y4M"},
      {50, -100, 41, 8, "P41Y8M"},
      {-50, 100, -42, 4, "-P42Y4M"}
  };

  for (auto tuple : test_cases)
  {
    simple::YearMonthDuration duration{std::get<0>(tuple), std::get<1>(tuple)};
    duration_property.setValue(duration);

    auto duration_string = duration_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(duration_string, std::string(std::get<4>(tuple)));
    ASSERT_EQ(duration_property.getValue().getYears(), std::get<2>(tuple));
    ASSERT_EQ(duration_property.getValue().getMonths(), std::get<3>(tuple));
  }
}

TYPED_TEST(PropertyTest, TestTime)
{
  map::Property<simple::Time> time_property("test id");
  ASSERT_EQ(time_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_time));

  std::vector<std::tuple<uint8_t, uint8_t, float, std::string, std::string>> test_cases = {
      {0, 0, 0, "Z", "00:00:00Z"},
      {11, 12, 3, "+01:00", "11:12:03+01:00"},
      {12, 34, 56.789, "-12:00", "12:34:56.789-12:00"},
      {1, 2, 3.04, "Z", "01:02:03.04Z"}
  };

  for (auto tuple : test_cases)
  {
    simple::Time time{std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple), std::get<3>(tuple)};
    time_property.setValue(time);

    auto xsd_str = time_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(xsd_str, std::string(std::get<4>(tuple)));
    ASSERT_EQ(time_property.getValue().getHours(), std::get<0>(tuple));
    ASSERT_EQ(time_property.getValue().getMinutes(), std::get<1>(tuple));
    ASSERT_EQ(time_property.getValue().getSeconds(), std::get<2>(tuple));
    ASSERT_EQ(std::string{time_property.getValue().getTimezone()}, std::string(std::get<3>(tuple)));
  }
}

TYPED_TEST(PropertyTest, TestGregorianYearMonth)
{
  map::Property<simple::GYearMonth> gregorianYearMonth_property("test id");
  ASSERT_EQ(gregorianYearMonth_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_gYearMonth));

  std::vector<std::tuple<int, uint8_t, std::string, std::string>> test_cases = {
      {0, 01, "Z", "0000-01Z"},
      {11, 12, "+01:00", "0011-12+01:00"},
      {2016, 1, "-12:00", "2016-01-12:00"},
      {-1, 10, "Z", "-0001-10Z"},
      {20202, 10, "Z", "20202-10Z"}
  };

  for (auto tuple : test_cases)
  {
    simple::GYearMonth yearMonth{std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple)};
    gregorianYearMonth_property.setValue(yearMonth);

    auto xsd_str = gregorianYearMonth_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(xsd_str, std::string(std::get<3>(tuple)));
    ASSERT_EQ(gregorianYearMonth_property.getValue().getYear(), std::get<0>(tuple));
    ASSERT_EQ(gregorianYearMonth_property.getValue().getMonth(), std::get<1>(tuple));
    ASSERT_EQ(std::string{gregorianYearMonth_property.getValue().getTimezone()}, std::string(std::get<2>(tuple)));
  }
}

TYPED_TEST(PropertyTest, TestGregorianYear)
{
  map::Property<simple::GYear> gregorianYear_property("test id");
  ASSERT_EQ(gregorianYear_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_gYear));

  std::vector<std::tuple<int, std::string, std::string>> test_cases = {
      {0, "Z", "0000Z"},
      {11, "+01:00", "0011+01:00"},
      {2016, "-12:00", "2016-12:00"},
      {-1, "Z", "-0001Z"},
      {-15445, "Z", "-15445Z"},
      {20202, "Z", "20202Z"}
  };

  for (auto tuple : test_cases)
  {
    simple::GYear year{std::get<0>(tuple), std::get<1>(tuple)};
    gregorianYear_property.setValue(year);

    auto xsd_str = gregorianYear_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(xsd_str, std::string(std::get<2>(tuple)));
    ASSERT_EQ(gregorianYear_property.getValue().getYear(), std::get<0>(tuple));
    ASSERT_EQ(std::string{gregorianYear_property.getValue().getTimezone()}, std::string(std::get<1>(tuple)));
  }
}

TYPED_TEST(PropertyTest, TestGregorianMonthDay)
{
  map::Property<simple::GMonthDay> gregorianMonthDay_property("test id");
  ASSERT_EQ(gregorianMonthDay_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_gMonthDay));

  std::vector<std::tuple<uint8_t, uint8_t, std::string, std::string, uint8_t, uint8_t>> test_cases = {
      {1, 1, "Z", "--01-01Z", 1, 1},
      {10, 31, "+01:00", "--10-31+01:00", 10, 31},
      {13, 32,  "-12:00", "--01-31-12:00", 1, 31},
  };

  for (auto tuple : test_cases)
  {
    simple::GMonthDay monthDay{std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple)};
    gregorianMonthDay_property.setValue(monthDay);

    auto xsd_str = gregorianMonthDay_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(xsd_str, std::string(std::get<3>(tuple)));
    ASSERT_EQ(gregorianMonthDay_property.getValue().getMonth(), std::get<4>(tuple));
    ASSERT_EQ(gregorianMonthDay_property.getValue().getDay(), std::get<5>(tuple));
    ASSERT_EQ(std::string{gregorianMonthDay_property.getValue().getTimezone()}, std::string(std::get<2>(tuple)));
  }
}

TYPED_TEST(PropertyTest, TestGregorianDay)
{
  map::Property<simple::GDay> gregorianDay_property("test id");
  ASSERT_EQ(gregorianDay_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_gDay));

  std::vector<std::tuple<uint8_t, std::string, std::string, uint8_t>> test_cases = {
      {1, "Z", "---01Z", 1},
      {10, "+01:00", "---10+01:00", 10},
      {32,  "-12:00", "---01-12:00", 1},
  };

  for (auto tuple : test_cases)
  {
    simple::GDay day{std::get<0>(tuple), std::get<1>(tuple)};
    gregorianDay_property.setValue(day);

    auto xsd_str = gregorianDay_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(xsd_str, std::string(std::get<2>(tuple)));
    ASSERT_EQ(gregorianDay_property.getValue().getDay(), std::get<3>(tuple));
    ASSERT_EQ(std::string{gregorianDay_property.getValue().getTimezone()}, std::string(std::get<1>(tuple)));
  }
}

TYPED_TEST(PropertyTest, TestGregorianMonth)
{
  map::Property<simple::GMonth> gregorianMonth_property("test id");
  ASSERT_EQ(gregorianMonth_property.getValueType(), XsdTypes_::to_string(XsdTypes::xsd_gMonth));

  std::vector<std::tuple<uint8_t, std::string, std::string, uint8_t>> test_cases = {
      {1, "Z", "--01Z", 1},
      {10, "+01:00", "--10+01:00", 10},
      {13,  "-12:00", "--01-12:00", 1},
  };

  for (auto tuple : test_cases)
  {
    simple::GMonth month{std::get<0>(tuple), std::get<1>(tuple)};
    gregorianMonth_property.setValue(month);

    auto xsd_str = gregorianMonth_property.getMap().getProperty(map::PropertyPath::Value).GetStringContent();
    ASSERT_EQ(xsd_str, std::string(std::get<2>(tuple)));
    ASSERT_EQ(gregorianMonth_property.getValue().getMonth(), std::get<3>(tuple));
    ASSERT_EQ(std::string{gregorianMonth_property.getValue().getTimezone()}, std::string(std::get<1>(tuple)));
  }
}

/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_C_SDK_XSDANYSIMPLETYPE_H
#define BASYX_C_SDK_XSDANYSIMPLETYPE_H

#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <regex>
#include <sstream>

#include <BaSyx/aas/simple/common/xsd_types/AnyURI.h>
#include <BaSyx/aas/simple/common/xsd_types/DateTime.h>
#include <BaSyx/aas/simple/common/xsd_types/Date.h>
#include <BaSyx/aas/simple/common/xsd_types/DayTimeDuration.h>
#include <BaSyx/aas/simple/common/xsd_types/YearMonthDuration.h>
#include <BaSyx/aas/simple/common/xsd_types/Time.h>
#include <BaSyx/aas/simple/common/xsd_types/GYearMonth.h>
#include <BaSyx/aas/simple/common/xsd_types/GYear.h>
#include <BaSyx/aas/simple/common/xsd_types/GMonthDay.h>
#include <BaSyx/aas/simple/common/xsd_types/GDay.h>
#include <BaSyx/aas/simple/common/xsd_types/GMonth.h>

#include <BaSyx/aas/enumerations/XsdTypes.h>

namespace basyx {
namespace xsd_types {
using namespace aas;

  static const std::string getPrimitiveXSDType(type::valueType type)
  {
    switch(type)
    {
      case type::valueType::Bool:
        return "boolean";
      case type::valueType::Int:
        return "integer";
      case type::valueType::Float:
        return "float";
      case type::valueType::String:
        return "string";
      default:
        return "Type not supported!";
    }
  }

  template<typename T, typename Enable = void>
  struct xsd_type
  {
    static constexpr int fail_vab_type_not_supported() { static_assert("Type not supported by VAB!"); return 0; };
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_NotSupported);
    };
  };

  template<>
  struct xsd_type<bool>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_boolean);
    }

    static const inline bool getXSDRepresentation(const bool & bool_value)
    {
      return bool_value;
    }

    static const inline bool fromXSDRepresentation(basyx::object value)
    {
      return value.Get<bool>();
    }

    static inline std::unique_ptr<bool> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<bool>(value.Get<bool>());
    }
  };

  template<>
  struct xsd_type<int8_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_byte);
    }

    static const inline int8_t getXSDRepresentation(const int8_t & int_value)
    {
      return int_value;
    }

    static const inline int8_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<int8_t>();
    }

    static inline std::unique_ptr<int8_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<int8_t>(value.Get<int8_t>());
    }
  };

  template<>
  struct xsd_type<int16_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_short);
    }

    static const inline int16_t getXSDRepresentation(const int16_t & short_value)
    {
      return short_value;
    }

    static const inline int16_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<int16_t>();
    }

    static inline std::unique_ptr<int16_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<int16_t>(value.Get<int16_t>());
    }
  };

  template<>
  struct xsd_type<int32_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_int);
    }

    static const inline int32_t getXSDRepresentation(const int32_t & int_value)
    {
      return int_value;
    }

    static const inline int32_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<int32_t>();
    }

    static inline std::unique_ptr<int32_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<int32_t>(value.Get<int32_t>());
    }
  };

  template<>
  struct xsd_type<int64_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_long);
    }

    static const inline int64_t getXSDRepresentation(const int64_t & long_value)
    {
      return long_value;
    }

    static const inline int64_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<int64_t>();
    }

    static inline std::unique_ptr<int64_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<int64_t>(value.Get<int64_t>());
    }
  };

  template<>
  struct xsd_type<uint8_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_unsignedByte);
    }

    static const inline uint8_t getXSDRepresentation(const uint8_t & int_value)
    {
      return int_value;
    }

    static const inline uint8_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<uint8_t>();
    }

    static inline std::unique_ptr<uint8_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<uint8_t>(value.Get<uint8_t>());
    }
  };

  template<>
  struct xsd_type<uint16_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_unsignedShort);
    }

    static const inline uint16_t getXSDRepresentation(const uint16_t & ushort_value)
    {
      return ushort_value;
    }

    static const inline uint16_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<uint16_t>();
    }

    static inline std::unique_ptr<uint16_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<uint16_t>(value.Get<uint16_t>());
    }
  };

#ifdef _MSC_VER 
  template<>
  struct xsd_type<long>
  {
	  static const std::string getDataTypeDef()
	  {
		  return XsdTypes_::to_string(XsdTypes::xsd_long);
	  }

	  static const inline long getXSDRepresentation(const long & uint_value)
	  {
		  return uint_value;
	  }

	  static const inline long fromXSDRepresentation(basyx::object value)
	  {
		  return value.Get<long>();
	  }

	  static inline std::unique_ptr<long> ptrFromXSDRepresentation(basyx::object value)
	  {
		  return util::make_unique<long>(value.Get<long>());
	  }
  };
#endif

  template<>
  struct xsd_type<uint32_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_unsignedInt);
    }

    static const inline uint32_t getXSDRepresentation(const uint32_t & uint_value)
    {
      return uint_value;
    }

    static const inline uint32_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<uint32_t>();
    }

    static inline std::unique_ptr<uint32_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<uint32_t>(value.Get<uint32_t>());
    }
  };

  template<>
  struct xsd_type<uint64_t>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_unsignedLong);
    }

    static const inline uint64_t getXSDRepresentation(const uint64_t & ulong_value)
    {
      return ulong_value;
    }

    static const inline uint64_t fromXSDRepresentation(basyx::object value)
    {
      return value.Get<uint64_t>();
    }

    static inline std::unique_ptr<uint64_t> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<uint64_t>(value.Get<uint64_t>());
    }
  };

  template<>
  struct xsd_type<double>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_double);
    }

    static const inline double getXSDRepresentation(const double & double_value)
    {
      return double_value;
    }

    static const inline double fromXSDRepresentation(basyx::object value)
    {
      return value.Get<double>();
    }

    static inline std::unique_ptr<double> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<double>(value.Get<double>());
    }
  };

  template<>
  struct xsd_type<float>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_float);
    }

    static const inline float getXSDRepresentation(const float & float_value)
    {
      return float_value;
    }

    static const inline float fromXSDRepresentation(basyx::object value)
    {
      return value.Get<float>();
    }

    static inline std::unique_ptr<float> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<float>(value.Get<float>());
    }
  };

  template<>
  struct xsd_type<std::string>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_string);
    }

    static const inline std::string getXSDRepresentation(const std::string & string)
    {
      return string;
    }

    static const inline std::string fromXSDRepresentation(basyx::object value)
    {
      return value.GetStringContent();
    }

    static inline std::unique_ptr<std::string> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<std::string>(value.GetStringContent());
    }
  };

  template<>
  struct xsd_type<simple::AnyURI>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_anyuri);
    }

    static const inline std::string getXSDRepresentation(const simple::AnyURI & uri)
    {
      return uri.getUri();
    }

    static const inline simple::AnyURI fromXSDRepresentation(const std::string & value)
    {
      return simple::AnyURI(value);
    }

    static const inline simple::AnyURI fromXSDRepresentation(basyx::object value)
    {
        return simple::AnyURI(value.Get<std::string>());
    }

    static inline std::unique_ptr<simple::AnyURI> ptrFromXSDRepresentation(basyx::object value)
    {
      return util::make_unique<simple::AnyURI>(value.Get<std::string>());
    }
  };

  template<>
  struct xsd_type<simple::Date>
  {
    static constexpr char format[] = "%Y-%m-%dZ";

    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_date);
    }

    static const inline std::string getXSDRepresentation(const simple::Date & date)
    {
      std::stringstream formatted;
      formatted << std::put_time(&date.getDate(), format);

      return formatted.str();
    }

    static const inline simple::Date fromXSDRepresentation(basyx::object value)
    {
      tm date;
      // Daylight Saving  is not in effect
      date.tm_isdst = 0;

      std::stringstream sstream;
      sstream << value.GetStringContent();
      sstream >> std::get_time(&date, format);

      return simple::Date{date};
    }

    static inline std::unique_ptr<simple::Date> ptrFromXSDRepresentation(basyx::object value)
    {
      tm date;
      // Daylight Saving  is not in effect
      date.tm_isdst = 0;

      std::stringstream sstream;
      sstream << value.GetStringContent();
      sstream >> std::get_time(&date, format);

      return util::make_unique<simple::Date>(date);
    }
  };

  template<>
  struct xsd_type<simple::DateTime>
  {
    static constexpr char format[] = "%Y-%m-%dT%TZ";

    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_dateTime);
    }

    static const inline std::string getXSDRepresentation(const simple::DateTime & dateTime)
    {
      std::stringstream formatted;
      formatted << std::put_time(&dateTime.getTime(), format);

      return formatted.str();
    }

    static const inline simple::DateTime fromXSDRepresentation(basyx::object value)
    {
      tm time;
      // Daylight Saving Time is not in effect
      time.tm_isdst = 0;

      std::stringstream sstream;
      sstream << value.GetStringContent();
      sstream >> std::get_time(&time, format);

      return simple::DateTime{time};
    }

    static inline std::unique_ptr<simple::DateTime> ptrFromXSDRepresentation(basyx::object value)
    {
      tm time;
      // Daylight Saving Time is not in effect
      time.tm_isdst = 0;

      std::stringstream sstream;
      sstream << value.GetStringContent();
      sstream >> std::get_time(&time, format);

      return util::make_unique<simple::DateTime>(time);
    }
  };

  template<>
  struct xsd_type<simple::DayTimeDuration>
  {
    static constexpr int seconds_per_day = 86400; //60*60*24
    static constexpr int seconds_per_hour = 3600; //60*60
    static constexpr int seconds_per_minute = 60;

    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_dayTimeDuration);
    }

    static const inline std::string getXSDRepresentation(const simple::DayTimeDuration & dayTimeDuration)
    {
      std::string xsd_str;
      long duration = dayTimeDuration.getDuration().count();
      if (duration < 0)
      {
        xsd_str = "-";
        duration *= -1;
      }

      xsd_str += "P";
      if (duration / seconds_per_day)
      {
        xsd_str += std::to_string(duration / seconds_per_day) + "D";
        duration = duration % seconds_per_day;
      }
      if (duration / seconds_per_hour)
      {
        xsd_str += std::to_string(duration / seconds_per_hour) + "H";
        duration = duration % seconds_per_hour;
      }
      if (duration / seconds_per_minute)
      {
        xsd_str += std::to_string(duration / seconds_per_minute) + "M";
        duration = duration % seconds_per_minute;
      }
      if (duration)
        xsd_str += std::to_string(duration) + "S";

      return xsd_str;
    }

    static const inline simple::DayTimeDuration fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      long seconds = 0;

      std::smatch match;
      std::regex regex("\\d+D");
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str()) * seconds_per_day;
      regex = "\\d+H";
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str()) * seconds_per_hour;
      regex = "\\d+M";
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str()) * seconds_per_minute;
      regex = "\\d+S";
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str());

      if (xsd_str.find('-') == 0)
        seconds *= -1;

      return simple::DayTimeDuration{std::chrono::duration<long>(seconds)};
    }

    static inline std::unique_ptr<simple::DayTimeDuration> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      long seconds = 0;

      std::smatch match;
      std::regex regex("\\d+D");
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str()) * seconds_per_day;
      regex = "\\d+H";
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str()) * seconds_per_hour;
      regex = "\\d+M";
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str()) * seconds_per_minute;
      regex = "\\d+S";
      if (std::regex_search(xsd_str, match, regex))
        seconds += std::stol(match.str());

      if (xsd_str.find('-') == 0)
        seconds *= -1;

      return util::make_unique<simple::DayTimeDuration>(std::chrono::duration<long>(seconds));
    }
  };


  template<>
  struct xsd_type<simple::YearMonthDuration>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_yearMonthDuration);
    }

    static const inline std::string getXSDRepresentation(const simple::YearMonthDuration & yearMonthDuration)
    {
      std::string xsd_str;
      int years = yearMonthDuration.getYears();
      int months = yearMonthDuration.getMonths();
      if (years < 0)
      {
        xsd_str += "-";
        years *= -1;
      }
	  else if (months < 0 && years == 0)
      {
        xsd_str += "-";
        months *= -1;
      }

      xsd_str +=  "P";
      xsd_str += (years > 0) ? std::to_string(years) + "Y" : "";
      xsd_str += (months > 0) ? std::to_string(months) + "M" : "";

      return xsd_str;
    }

    static const inline simple::YearMonthDuration fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      int years = 0, months = 0;

      std::smatch match;
      std::regex regex("\\d+Y");
      if (std::regex_search(xsd_str, match, regex))
        years = std::stoi(match.str());
      regex = "\\d+M";
      if (std::regex_search(xsd_str, match, regex))
        months = std::stoi(match.str());

      if (xsd_str.find('-') == 0)
        (years == 0) ? months *= -1 : years *= -1;

      simple::YearMonthDuration yearMonthDuration{years,months};

      return yearMonthDuration;
    }

    static inline std::unique_ptr<simple::YearMonthDuration> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      int years = 0, months = 0;

      std::smatch match;
      std::regex regex("\\d+Y");
      if (std::regex_search(xsd_str, match, regex))
        years = std::stoi(match.str());
      regex = "\\d+M";
      if (std::regex_search(xsd_str, match, regex))
        months = std::stoi(match.str());

      if (xsd_str.find('-') == 0)
        (years == 0) ? months *= -1 : years *= -1;

      return util::make_unique<simple::YearMonthDuration>(years,months);
    }
  };

  template<>
  struct xsd_type<simple::Time>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_time);
    }

    static const inline std::string getXSDRepresentation(const simple::Time & time)
    {
      char buffer[9];
      snprintf(buffer, 9, "%02d:%02d:%02d", time.getHours(), time.getMinutes(), int(time.getSeconds()));
      std::string xsd_str{buffer};

      // check if number has decimal places
      if (std::fmod(time.getSeconds(), 1.0) != 0)
      {
        snprintf(buffer, 9, "%.05f", time.getSeconds());

        std::string decimal = buffer;
        // find trailing zeros and erase them
        decimal = decimal.erase(decimal.find_last_not_of('0') + 1, std::string::npos).substr(decimal.find("."));
        xsd_str += decimal;
      }

      return xsd_str + std::string{time.getTimezone()};
    }

    static const inline simple::Time fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"(\\d\\d):(\\d\\d):(\\d\\d(\\.\\d+)?)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      float second = 0;
      uint8_t hour = std::stoi(match.str(1)); // first (\\d\\d)
      uint8_t minute = std::stoi(match.str(2)); // second (\\d\\d)
      second = std::stof(match.str(3)); // (\\d\\d(\\.\\d+)?) Two digits plus optional decimal point and arbitrary number of digits
      std::string timezone = match.str(5); // ([Z|\+|\-]) "Z" or + or - and arbitrary characters

      return simple::Time{hour, minute, second, timezone};
    }

    static inline std::unique_ptr<simple::Time> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"(\\d\\d):(\\d\\d):(\\d\\d(\\.\\d+)?)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      float second = 0;
      uint8_t hour = std::stoi(match.str(1)); // first (\\d\\d)
      uint8_t minute = std::stoi(match.str(2)); // second (\\d\\d)
      second = std::stof(match.str(3)); // (\\d\\d(\\.\\d+)?) Two digits plus optional decimal point and arbitrary number of digits
      std::string timezone = match.str(5); // ([Z|\+|\-]) "Z" or + or - and arbitrary characters

      return util::make_unique<simple::Time>(hour, minute, second, timezone);
    }
  };

  template<>
  struct xsd_type<simple::GYearMonth>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_gYearMonth);
    }

    static const inline std::string getXSDRepresentation(const simple::GYearMonth & date)
    {
      char buffer[15];
      if (date.getYear() < 0)
        snprintf(buffer, 15, "%05d-%02d", date.getYear(), date.getMonth());
      else
        snprintf(buffer, 15, "%04d-%02d", date.getYear(), date.getMonth());

      return buffer + std::string{date.getTimezone()};
    }

    static const inline simple::GYearMonth fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"(-?\\d+)-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      int year = std::stoi(match.str(1)); // first (\\d+)
      uint8_t month = std::stoi(match.str(2)); // second (\\d\\d)
      std::string timezone = match.str(3);

      return simple::GYearMonth{year, month, timezone};
    }

    static inline std::unique_ptr<simple::GYearMonth> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"(-?\\d+)-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      int year = std::stoi(match.str(1)); // first (\\d+)
      uint8_t month = std::stoi(match.str(2)); // second (\\d\\d)
      std::string timezone = match.str(3);

      return util::make_unique<simple::GYearMonth>(year, month, timezone);
    }
  };

  template<>
  struct xsd_type<simple::GYear>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_gYear);
    }

    static const inline std::string getXSDRepresentation(const simple::GYear & year)
    {
      char buffer[15];
      if (year.getYear() < 0)
        snprintf(buffer, 15, "%05d", year.getYear());
      else
        snprintf(buffer, 15, "%04d", year.getYear());

      return buffer + std::string{year.getTimezone()};
    }

    static const inline simple::GYear fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"(-?\\d+)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      int year = std::stoi(match.str(1)); // first (\\d+)
      std::string timezone = match.str(2);

      return simple::GYear{year, timezone};
    }

    static inline std::unique_ptr<simple::GYear> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"(-?\\d+)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      int year = std::stoi(match.str(1)); // first (\\d+)
      std::string timezone = match.str(2);

      return util::make_unique<simple::GYear>(year, timezone);
    }
  };

  template<>
  struct xsd_type<simple::GMonthDay>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_gMonthDay);
    }

    static const inline std::string getXSDRepresentation(const simple::GMonthDay & monthDay)
    {
      char buffer[10];
      snprintf(buffer, 8, "--%02d-%02d", monthDay.getMonth(), monthDay.getDay());

      return buffer + std::string{monthDay.getTimezone()};
    }

    static const inline simple::GMonthDay fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"\\-\\-(\\d\\d)\\-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      uint8_t month = std::stoi(match.str(1)); // first (\\d\\d)
      uint8_t day = std::stoi(match.str(2)); // second (\\d\\d)
      std::string timezone = match.str(3);

      return simple::GMonthDay{month, day, timezone};
    }

    static inline std::unique_ptr<simple::GMonthDay> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"\\-\\-(\\d\\d)\\-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      uint8_t month = std::stoi(match.str(1)); // first (\\d\\d)
      uint8_t day = std::stoi(match.str(2)); // second (\\d\\d)
      std::string timezone = match.str(3);

      return util::make_unique<simple::GMonthDay>(month, day, timezone);
    }
  };

  template<>
  struct xsd_type<simple::GDay>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_gDay);
    }

    static const inline std::string getXSDRepresentation(const simple::GDay & day)
    {
      char buffer[7];
      snprintf(buffer, 7, "---%02d", day.getDay());

      return buffer + std::string{day.getTimezone()};
    }

    static const inline simple::GDay fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"\\-\\-\\-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      uint8_t day = std::stoi(match.str(1)); // first (\\d\\d)
      std::string timezone = match.str(2);

      return simple::GDay{day, timezone};
    }

    static inline std::unique_ptr<simple::GDay> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"\\-\\-\\-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      uint8_t day = std::stoi(match.str(1)); // first (\\d\\d)
      std::string timezone = match.str(2);

      return util::make_unique<simple::GDay>(day, timezone);
    }
  };

  template<>
  struct xsd_type<simple::GMonth>
  {
    static const std::string getDataTypeDef()
    {
      return XsdTypes_::to_string(XsdTypes::xsd_gMonth);
    }

    static const inline std::string getXSDRepresentation(const simple::GMonth & month)
    {
      char buffer[6];
      snprintf(buffer, 6, "--%02d", month.getMonth());

      return buffer + std::string{month.getTimezone()};
    }

    static const inline simple::GMonth fromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"\\-\\-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      uint8_t month = std::stoi(match.str(1)); // first (\\d\\d)
      std::string timezone = match.str(2);

      return simple::GMonth{month, timezone};
    }

    static inline std::unique_ptr<simple::GMonth> ptrFromXSDRepresentation(basyx::object value)
    {
      std::string xsd_str = value.GetStringContent();

      std::smatch match;
      std::regex regex{"\\-\\-(\\d\\d)([Z|\\+|\\-].*)"};
      std::regex_search(xsd_str, match, regex);

      uint8_t month = std::stoi(match.str(1)); // first (\\d\\d)
      std::string timezone = match.str(2);

      return util::make_unique<simple::GMonth>(month, timezone);
    }
  };

}
}


#endif //BASYX_C_SDK_XSDANYSIMPLETYPE_H

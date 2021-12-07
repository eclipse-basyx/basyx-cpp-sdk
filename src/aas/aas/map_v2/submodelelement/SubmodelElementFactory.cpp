/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>
#include <BaSyx/util/util.h>

#include <BaSyx/aas/map_v2/submodelelement/AnnotatedRelationshipElement.h>
#include <BaSyx/aas/map_v2/submodelelement/BasicEvent.h>
#include <BaSyx/aas/map_v2/submodelelement/Capability.h>
#include <BaSyx/aas/map_v2/submodelelement/Entity.h>
#include <BaSyx/aas/map_v2/submodelelement/Range.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementCollection.h>
#include <BaSyx/aas/map_v2/submodelelement/file/Blob.h>
#include <BaSyx/aas/map_v2/submodelelement/file/File.h>
#include <BaSyx/aas/map_v2/submodelelement/operation/Operation.h>
#include <BaSyx/aas/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/aas/map_v2/submodelelement/property/MultiLanguageProperty.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>
#include <BaSyx/aas/map_v2/submodelelement/property/ReferenceElement.h>

#include <BaSyx/aas/enumerations/XsdTypes.h>

using namespace basyx;
using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

constexpr char SubmodelElementFactory::Path::Value[];

std::unique_ptr<map::DataElement> SubmodelElementFactory::CreateProperty(const vab::ElementMap & elementMap)
{
	auto object = elementMap.getMap();
	auto value = object.getProperty(Path::Value);
	auto type = value.GetValueType();

	switch (type)
	{
    case basyx::type::valueType::Int:
      return util::make_unique<Property<int>>(elementMap);
    case basyx::type::valueType::Bool:
      return util::make_unique<Property<bool>>(elementMap);
    case basyx::type::valueType::Float:
      return util::make_unique<Property<float>>(elementMap);
    case basyx::type::valueType::String:
      return util::make_unique<Property<std::string>>(elementMap);
    case basyx::type::valueType::Object:
    case basyx::type::valueType::Null:
    default:
      return nullptr;
	}

	return nullptr;
}

std::unique_ptr<map::DataElement> SubmodelElementFactory::CreateRange(const vab::ElementMap & elementMap)
{
  auto object = elementMap.getMap();
  auto & type_string = object.getProperty("dataTypeDef").GetStringContent();
  XsdTypes xsdType = XsdTypes_::from_string(type_string);

  switch (xsdType)
  {
    case XsdTypes::xsd_boolean:
      return util::make_unique<Range<bool>>(object);
    case XsdTypes::xsd_byte:
      return util::make_unique<Range<int8_t>>(object);
    case XsdTypes::xsd_short:
      return util::make_unique<Range<short>>(object);
    case XsdTypes::xsd_int:
      return util::make_unique<Range<int>>(object);
    case XsdTypes::xsd_long:
      return util::make_unique<Range<long>>(object);
    case XsdTypes::xsd_unsignedByte:
      return util::make_unique<Range<uint8_t>>(object);
    case XsdTypes::xsd_unsignedShort:
      return util::make_unique<Range<uint16_t>>(object);
    case XsdTypes::xsd_unsignedInt:
      return util::make_unique<Range<uint32_t>>(object);
    case XsdTypes::xsd_unsignedLong:
      return util::make_unique<Range<uint64_t>>(object);
    case XsdTypes::xsd_double:
      return util::make_unique<Range<double>>(object);
    case XsdTypes::xsd_float:
      return util::make_unique<Range<float>>(object);
    case XsdTypes::xsd_string:
      return util::make_unique<Range<std::string>>(object);
    case XsdTypes::xsd_anyuri:
      return util::make_unique<Range<simple::AnyURI>>(object);
    case XsdTypes::xsd_date:
      return util::make_unique<Range<simple::Date>>(object);
    case XsdTypes::xsd_dateTime:
      return util::make_unique<Range<simple::DateTime>>(object);
    case XsdTypes::xsd_dayTimeDuration:
      return util::make_unique<Range<simple::DayTimeDuration>>(object);
    case XsdTypes::xsd_yearMonthDuration:
      return util::make_unique<Range<simple::YearMonthDuration>>(object);
    case XsdTypes::xsd_time:
      return util::make_unique<Range<simple::Time>>(object);
    case XsdTypes::xsd_gYearMonth:
      return util::make_unique<Range<simple::GYearMonth>>(object);
    case XsdTypes::xsd_gYear:
      return util::make_unique<Range<simple::GYear>>(object);
    case XsdTypes::xsd_gMonthDay:
      return util::make_unique<Range<simple::GMonthDay>>(object);
    case XsdTypes::xsd_gDay:
      return util::make_unique<Range<simple::GDay>>(object);
    case XsdTypes::xsd_gMonth:
      return util::make_unique<Range<simple::GMonth>>(object);
    case XsdTypes::xsd_NotSupported:
    default:
      return nullptr;
  }
  return nullptr;
}

std::unique_ptr<map::SubmodelElement> SubmodelElementFactory::Create(const vab::ElementMap & elementMap)
{
	ModelTypes modelType = ModelType<ModelTypes::SubmodelElement>(elementMap.getMap()).GetModelType();

	switch (modelType)
	{
    case ModelTypes::AnnotatedRelationshipElement:
      return util::make_unique<AnnotatedRelationshipElement>(elementMap.getMap());
    case ModelTypes::BasicEvent:
      return util::make_unique<BasicEvent>(elementMap.getMap());
    case ModelTypes::Capability:
      return util::make_unique<Capability>(elementMap.getMap());
    case ModelTypes::Entity:
      return util::make_unique<Entity>(elementMap.getMap());
    case ModelTypes::Operation:
      return util::make_unique<Operation>(elementMap.getMap());
    case ModelTypes::OperationVariable:
      return util::make_unique<OperationVariable>(elementMap.getMap());
    case ModelTypes::RelationshipElement:
      return util::make_unique<RelationshipElement>(elementMap.getMap());
    case ModelTypes::SubmodelElementCollection:
      return util::make_unique<SubmodelElementCollection>(elementMap.getMap());

    //DataElements
    case ModelTypes::File:
    case ModelTypes::Blob:
    case ModelTypes::MultiLanguageProperty:
    case ModelTypes::Property:
    case ModelTypes::Range:
    case ModelTypes::ReferenceElement:
      return CreateDataElement(elementMap);

  	default:
	  	return nullptr;
	};
	
	return nullptr;
}

std::unique_ptr<map::DataElement> SubmodelElementFactory::CreateDataElement(const vab::ElementMap & elementMap)
{
  ModelTypes modelType = ModelType<ModelTypes::SubmodelElement>(elementMap.getMap()).GetModelType();

  switch (modelType)
  {
    case ModelTypes::Property:
      return SubmodelElementFactory::CreateProperty(elementMap);
    case ModelTypes::Range:
      return SubmodelElementFactory::CreateRange(elementMap);
    case ModelTypes::ReferenceElement:
      return util::make_unique<ReferenceElement>(elementMap.getMap());
    case ModelTypes::MultiLanguageProperty:
      return util::make_unique<MultiLanguageProperty>(elementMap.getMap());
    case ModelTypes::Blob:
      return util::make_unique<Blob>(elementMap.getMap());
    case ModelTypes::File:
      return util::make_unique<File>(elementMap.getMap());
      
    default:
      return nullptr;
  }
  return nullptr;
}

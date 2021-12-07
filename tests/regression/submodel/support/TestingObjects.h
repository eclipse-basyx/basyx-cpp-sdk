/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_TEST_SUPPORT_H
#define BASYX_SUBMODEL_TEST_SUPPORT_H

#include <BaSyx/shared/object.h>
#include <BaSyx/aas/map_v2/common/LangStringSet.h>
#include <BaSyx/aas/map_v2/constraint/Formula.h>
#include <BaSyx/aas/map_v2/constraint/Qualifier.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>
#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/map_v2/qualifier/Qualifiable.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/file/File.h>
#include <BaSyx/aas/map_v2/submodelelement/operation/OperationVariable.h>

#include <BaSyx/aas/simple/identifier/Identifier.h>

using namespace basyx;
using namespace basyx::aas;
using namespace basyx::aas::map;

namespace TestingObjects{

namespace map {

static LangStringSet testingLangString()
{
  LangStringSet langStringSet;

  langStringSet.add("DE", "Deutscher Text");
  langStringSet.add("EN", "English text");

  return langStringSet;
}

static aas::map::Reference testingReference_1()
{
  aas::map::Reference reference;

  simple::Key key_1(KeyElements::Unknown, false, KeyType::Unknown, "value 1");
  reference.addKey(key_1);
  simple::Key key_2(KeyElements::DataElement, true, KeyType::URI, "value 2");
  reference.addKey(key_2);

  return reference;
}

static aas::map::Reference testingReference_2()
{
  aas::map::Reference reference;

  simple::Key key_1(KeyElements::SubmodelElement, false, KeyType::FragementId, "value 12");
  reference.addKey(key_1);
  simple::Key key_2(KeyElements::SubmodelElementCollection, true, KeyType::IRDI, "value 21");
  reference.addKey(key_2);

  return reference;
}

static Referable testingReferable_1()
{
  Referable referable {std::string("test id 1")};

  referable.setCategory("testing category 1");
  referable.setDescription(testingLangString());

  return referable;
}

static bool testingReferable_1(api::IReferable & ref)
{
  return *ref.getCategory() == "testing category 1" and ref.getIdShort() == "test id 1" and ref.getDescription() == testingLangString();
}

static Referable testingReferable_2()
{
  Referable referable {std::string("test id 2")};

  referable.setCategory("testing category 2");
  referable.setDescription(testingLangString());

  return referable;
}

static bool testingReferable_2(api::IReferable & ref)
{
  return *ref.getCategory() == "testing category 2" and ref.getIdShort() == "test id 2" and ref.getDescription() == testingLangString();
}

static HasDataSpecification testingHasDataSpecification()
{
  HasDataSpecification hasDataSpecification;
  hasDataSpecification.addDataSpecification(simple::Reference {testingReference_2()});
  hasDataSpecification.addDataSpecification(simple::Reference {testingReference_1()});

  return hasDataSpecification;
}

static bool testingHasDataSpecification(HasDataSpecification & hasDataSpecification)
{
  auto references = hasDataSpecification.getDataSpecificationReference();
  return references.at(0) == testingReference_2() and references.at(1) == testingReference_1();
}

static Formula testingFormula()
{
  Formula formula;

  formula.addDependency(TestingObjects::map::testingReference_1());
  formula.addDependency(TestingObjects::map::testingReference_2());

  return formula;
}

static bool testingFormula(api::IFormula & formula)
{
  auto deps = formula.getDependencies();
  return deps.at(0) == testingReference_1() and deps.at(1) == testingReference_2();
}

static Qualifier testingQualifier(int c = 1)
{
  return {"Qualifier type " + std::to_string(c), "Value type " + std::to_string(c)};
}

static bool testingQualifier(api::IQualifier & qualifier, int c = 1)
{
  return qualifier.getQualifierType() == ("Qualifier type " + std::to_string(c)) and qualifier.getValueType() == ("Value type " + std::to_string(c));
}

static Qualifiable testingQualifiable()
{
  Qualifiable qualifiable;

  qualifiable.addFormula(testingFormula());
  qualifiable.addQualifier(testingQualifier(3));
  qualifiable.addQualifier(testingQualifier(1));

  return qualifiable;
}

static bool testingQualifiable(api::IQualifiable & qualifiable)
{
  auto qualifiers = qualifiable.getQualifiers();
  auto formulas = qualifiable.getFormulas();

  return testingQualifier(qualifiers.at(0), 3) and testingQualifier(qualifiers.at(1), 1) and testingFormula(formulas.at(0));
}

static File testingFile(int i=0)
{
  File file{"testing file " + std::to_string(i), "testing mime type"};
  file.setPath("some testing path");
  return file;
}

static bool testingFile(api::ISubmodelElement & submodelElement, int i=0)
{
  api::IFile & file = dynamic_cast<api::IFile&>(submodelElement);
  return (file.getIdShort() == ("testing file " + std::to_string(i)))
          and (file.getPath() == "some testing path")
          and (file.getMimeType() == "testing mime type");
}

static OperationVariable testingOperationVariable(int i=0)
{
  OperationVariable ov{"testing id " + std::to_string(i), util::make_unique<File>(testingFile(2))};

  return ov;
}

static bool testingOperationVariable(api::IOperationVariable & ov, int i=0)
{
  return (ov.getIdShort() == "testing id " + std::to_string(i))
          and testingFile(ov.getValue(), 2);
}

}
namespace object {

static basyx::object testingSubmodelElement()
{
  basyx::object object = map::testingReferable_1().getMap();
  object.insert(map::testingHasDataSpecification().getMap());
  object.insert(map::testingQualifiable().getMap());
  object.insertKey(SubmodelElement::Path::Kind, ModelingKind_::to_string(ModelingKind::Instance));

  return object;
}

static bool testingSubmodelElement(SubmodelElement & submodelElement)
{
  return TestingObjects::map::testingReferable_1(submodelElement)
          and TestingObjects::map::testingHasDataSpecification(submodelElement)
          and TestingObjects::map::testingQualifiable(submodelElement);
}

}

namespace simple
{

static basyx::aas::simple::Identifier testingIdentifier()
{
  basyx::aas::simple::Identifier identifier{IdentifierType::FragementId, "testing id"};

  return identifier;
}

}
}

#endif
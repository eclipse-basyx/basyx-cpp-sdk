/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/Submodel.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

using IdPath = Identifiable::Path;

constexpr char Submodel::Path::SubmodelElements[];
constexpr char Submodel::Path::SemanticId[];
constexpr char Submodel::Path::Kind[];

Submodel::Submodel(const std::string & idShort, const simple::Identifier & identifier, ModelingKind kind)
	: Identifiable(idShort, identifier)
{
	this->map.insertKey(Path::SubmodelElements, this->elementContainer.getMap());
  this->map.insertKey(Path::Kind, ModelingKind_::to_string(kind));
}

Submodel::Submodel(basyx::object object)
  : ElementMap{}
  , Identifiable{
  object.getProperty(Referable::Path::IdShort).GetStringContent(),
  simple::Identifier(IdentifierType_::from_string(object.getProperty(IdPath::Identifier).getProperty(IdPath::IdType).GetStringContent()),
                     object.getProperty(IdPath::Identifier).getProperty(IdPath::Id).GetStringContent())}
  , HasDataSpecification{object}
  , Qualifiable{object}
{
  if ( not object.getProperty(Path::SubmodelElements).IsNull() )
  {
    auto elements = object.getProperty(Path::SubmodelElements).Get<object::object_map_t>();
    for ( auto element : elements )
    {
      auto submodelElement = SubmodelElementFactory::Create(element.second);
      this->elementContainer.addElement(std::move(submodelElement));
    }
  }

  if ( not object.getProperty(Path::SemanticId).IsNull() )
    this->semanticId = util::make_unique<Reference>(object.getProperty(Path::SemanticId));

  if ( not object.getProperty(IdPath::AdministrativeInformation).IsNull() )
  {
    AdministrativeInformation administrativeInformation(object.getProperty(IdPath::AdministrativeInformation));
    this->setAdministrativeInformation(administrativeInformation);
  }

  this->setCategory(object.getProperty(Referable::Path::Category).GetStringContent());
  this->setDescription(LangStringSet::from_object(object.getProperty(Referable::Path::Description)));
}

IElementContainer<ISubmodelElement> & Submodel::submodelElements()
{
	return this->elementContainer;
}

const IElementContainer<ISubmodelElement> & Submodel::submodelElements() const
{
	return this->elementContainer;
}

ModelingKind Submodel::getKind() const
{
	return ModelingKind_::from_string(this->map.getProperty(Path::Kind).GetStringContent());
}

const IReference * Submodel::getSemanticId() const
{
	return this->semanticId.get();
}

void Submodel::setSemanticId(std::unique_ptr<Reference> semanticId)
{
	this->semanticId = std::move(semanticId);
  this->map.insertKey(Path::SemanticId, this->semanticId->getMap());
}

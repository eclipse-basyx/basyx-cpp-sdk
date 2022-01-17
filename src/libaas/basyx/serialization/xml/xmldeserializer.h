#ifndef XMLDESERIALIZER_H
#define XMLDESERIALIZER_H

#include <string>
#include <functional>

#include <basyx/util/string_view/string_view.hpp>

#include <basyx/serialization/base/serialization.h>

#include <basyx/environment.h>

#include <basyx/base/elementvector.h>

#include <pugixml.hpp>

namespace basyx::serialization::xml
{

using namespace basyx::serialization::priv;

class XMLDeSerializer {
   pugi::xml_document doc;
   //util::string_view xml;
private:
   Deserializer *ds;
public:
   XMLDeSerializer();
   ~XMLDeSerializer();
   Environment deSerializeEnv(util::string_view node);
   Environment deSerializeEnvNode(pugi::xml_node node);

   ElementVector<Asset> deSerializeAssets(
         pugi::xml_node node);

   ElementVector<AssetInformation> convertAssetToAssetInformation(
         ElementVector<Asset> assets);
   Asset deSerializeAssetMetamodel_V2(pugi::xml_node node);
   AssetKind deSerializeAssetKind(pugi::xml_node node);

   ElementContainer<AssetAdministrationShell> deSerializeAASs(
         pugi::xml_node node);
   AssetAdministrationShell deSerializeAAS(pugi::xml_node node);
   void deSerializeDerivedFrom(pugi::xml_node node,
                               AssetAdministrationShell & a);

   ElementVector<Submodel> deSerializeSubmodels(pugi::xml_node node);
   Submodel deSerializeSubmodel(pugi::xml_node node);

   template <typename X>
   void deSerializeIdentifiable(pugi::xml_node node, X & metamodelElement);
   AdministrativeInformation deSerializeAdministrativeInformation(
         pugi::xml_node node);
   Identifier deSerializeIdentifier(pugi::xml_node node);

   template <typename X>
   void deSerializeReferable(pugi::xml_node node, X & metamodelElement);

   template <typename X>
   void deSerializeHasKind(pugi::xml_node node, X & metamodelElement);

   template <typename X>
   void deSerializeHasSemantics(pugi::xml_node node, X & metamodelElement);

   template <typename X>
   void deSerializeQualifiable(pugi::xml_node node, X & metamodelElement);

   template <typename X>
   void deSerializeHasDataSpecification(pugi::xml_node node,
                                        X & metamodelElement);

   util::optional<Reference> deSerializeReferenceFromParent(pugi::xml_node node);
   util::optional<Reference> deSerializeReference(pugi::xml_node node);
   Key deSerializeKey(pugi::xml_node node);

   std::string deSerializeString(pugi::xml_node node);
   langstringset_t deSerializeLangStringSet(pugi::xml_node node);
   langstring_t deSerializeLangString(pugi::xml_node node);

   template<class T, class X>
   T iterateChildren(pugi::xml_node node,
                     std::string element_name,
                     std::function<X(pugi::xml_node)> callback,
                     T & container);

   pugi::xml_node findChildByName(pugi::xml_node node, std::string name);
   pugi::xml_attribute findAttributeByName(pugi::xml_node node,
                                           std::string name);
};
}

#endif // XMLDESERIALIZER_H

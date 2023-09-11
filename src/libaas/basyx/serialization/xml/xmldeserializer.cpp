#include "xmldeserializer.h"

#include <iostream>
#include <type_traits>

#include <basyx/serialization/private/deserializer_priv.h>

using namespace basyx;
using namespace basyx::serialization::xml;

using namespace pugi;

// Environment
#define XML_ENV "aas:aasenv"
// Asset
#define XML_assets "aas:assets"
#define XML_asset "aas:asset"
#define XML_assetKind "aas:kind"
#define XML_billOfMaterialRef "aas:billOfMaterialRef"
#define XML_assetIdentificationModelRef "aas:assetIdentificationModelRef"
// Asset Administration Shell
#define XML_AASS "aas:assetAdministrationShells"
#define XML_AAS "aas:assetAdministrationShell"
#define XML_derivedFrom "aas:derivedFrom"
// Submodel
#define XML_submodels "aas:submodels"
#define XML_submodel "aas:submodel"
// Identifiable
#define XML_adminstration "aas:administration"
#define XML_adminstration_Ver "aas:version"
#define XML_adminstration_Rev "aas:revision"
#define XML_identification "aas:identification"
// Referable
#define XML_idShort "aas:idShort"
#define XML_displayName "aas:displayName"
#define XML_category "aas:category"
#define XML_description "aas:description"
// LangString
#define XML_langStr "aas:langString"
// DataSpecification
#define XML_dataSpecification "aas:dataSpecification"

// Reference
#define XML_keys "aas:keys"
#define XML_key "aas:key"

// HasKind
#define XML_modelingKind "aas:kind"

// HasSemantics
#define XML_semanticID "aas:semanticId"

// Qualifiable
#define XML_qualifier "aas:qualifier"

// Attributes
#define XML_ATTR_lang "lang"
#define XML_ATTR_idType "idType"
#define XML_ATTR_type "type"

XMLDeSerializer::XMLDeSerializer() {
   ds = new Deserializer();
}

XMLDeSerializer::~XMLDeSerializer() {
   delete ds;
}

Environment XMLDeSerializer::deSerializeEnv(util::string_view node) {
   this->doc.load_buffer_inplace((void*)node.data(), node.length());
   xml_node env_node = findChildByName(doc.root(), XML_ENV);
   if (env_node.empty())
      return Environment();
   return deSerializeEnvNode(env_node);
}

Environment XMLDeSerializer::deSerializeEnvNode(xml_node node) {
   Environment env;

   // Legacy AAS Part 1 - V2
   xml_node asset_container_node = findChildByName(node, XML_assets);
   ElementVector<Asset> assets;
   if (asset_container_node.root()) {
      assets = deSerializeAssets(asset_container_node);
      env.setAssets(assets);
   }

   xml_node submodel_container_node = findChildByName(node, XML_submodels);
   ElementVector<Submodel> submodels;
   if (submodel_container_node.root()) {
      submodels = deSerializeSubmodels(submodel_container_node);
      //env.setSubmodels(submodels);
   }

   xml_node aas_container_node = findChildByName(node, XML_AASS);
   ElementContainer<AssetAdministrationShell> aas_container;
   if (aas_container_node.root()) {
         aas_container = deSerializeAASs(aas_container_node);
         env.setAssetAdministrationShells(aas_container);
      }

   return env;
}

/* TODO: Convert legacy V2 -> V3 (asset -> assetInformation)
/*
ElementVector<AssetInformation> XMLDeSerializer::convertAssetToAssetInformation(
      ElementVector<Asset> assets) {
   ElementVector<AssetInformation> aiC;
   ElementVector<Asset>::iterator it = assets.begin();
   while (it != assets.end()) {
      if (it->getAssetKind().has_value()) {
         AssetInformation ai(it->getAssetKind().value());
         ai.setAsset(*it);

         ai.setGlobalAssetId(
                  Reference(
                     Key(KeyElements::Asset,
                         it->getIdentification().getId(),
                         it->getIdentification().getIdType()
                         )
                     )
                  );

         if (it->getBillOfMaterialModelRef().has_value())
            ai.addBillOfMaterial(it->getBillOfMaterialModelRef().value());

         aiC.add(ai);
      }
      it++;
   }
   return aiC;
}
*/

ElementVector<Asset> XMLDeSerializer::deSerializeAssets(
      xml_node node) {

   std::function<Asset(xml_node)> asset_callback =
         std::bind(&XMLDeSerializer::deSerializeAssetMetamodel_V2,
                   this,
                   std::placeholders::_1);

   ElementVector<Asset> asset_container;
         iterateChildren<ElementVector<Asset>>(
            node,
            XML_asset,
            asset_callback,
            asset_container);
   return asset_container;
}

Asset XMLDeSerializer::deSerializeAssetMetamodel_V2(xml_node node) {

   Asset a("", Identifier(""));

   deSerializeIdentifiable(node, a);
   deSerializeHasDataSpecification(node, a);

   // AssetKind [1]
   xml_node ak_node = findChildByName(node, XML_assetKind);
   if (ak_node.root()) {
      AssetKind ak = deSerializeAssetKind(ak_node);
      a.setAssetKind(ak);
   }

   xml_node bom_node = findChildByName(node, XML_billOfMaterialRef);
   if (bom_node.root()) {
      util::optional<Reference> bomRef = deSerializeReferenceFromParent(bom_node);
      if (bomRef.has_value())
         a.setBillOfMaterialModelRef(bomRef.value());
   }

   xml_node asset_ident_node = findChildByName(node,
                                               XML_assetIdentificationModelRef);
   if (asset_ident_node.root()) {
      util::optional<Reference> assetIdentRef = deSerializeReferenceFromParent(
               asset_ident_node);
      if (assetIdentRef.has_value())
         a.setAssetIdentificationModelRef(assetIdentRef.value());
   }
   return a;
}

AssetKind XMLDeSerializer::deSerializeAssetKind(xml_node node) {
   std::string kind = deSerializeString(node);
   return AssetKind_::from_string(kind);
}

ElementContainer<AssetAdministrationShell> XMLDeSerializer::deSerializeAASs(
      xml_node node) {
   std::function<AssetAdministrationShell(xml_node)> aas_callback =
         std::bind(&XMLDeSerializer::deSerializeAAS,
                   this,
                   std::placeholders::_1);

   ElementContainer<AssetAdministrationShell> aas_container;
         iterateChildren<ElementContainer<AssetAdministrationShell>>(
            node,
            XML_AAS,
            aas_callback,
            aas_container);
   return aas_container;
}

AssetAdministrationShell XMLDeSerializer::deSerializeAAS(xml_node node) {
      AssetAdministrationShell a("",
                                 Identifier(""),
                                 AssetInformation(AssetKind::Type));

      deSerializeIdentifiable(node, a);
      deSerializeHasDataSpecification(node, a);
      deSerializeDerivedFrom(node, a);

      return a;
}

void XMLDeSerializer::deSerializeDerivedFrom(xml_node node,
                                             AssetAdministrationShell & a) {
   xml_node derivedFrom_node = findChildByName(node, XML_derivedFrom);
   if (derivedFrom_node.root()) {
      util::optional<Reference> r =
            deSerializeReferenceFromParent(derivedFrom_node);
      if (r.has_value()) {
         Reference dr = r.value();
         a.setDerivedFrom(dr);
      }
   }
}

ElementVector<Submodel> XMLDeSerializer::deSerializeSubmodels(
      pugi::xml_node node) {
   std::cout << "deSerializeSubmodels " << node.name() << std::endl;

   std::function<Submodel(xml_node)> submodel_callback =
         std::bind(&XMLDeSerializer::deSerializeSubmodel,
                   this,
                   std::placeholders::_1);

   ElementVector<Submodel> submodel_container;
         iterateChildren<ElementVector<Submodel>>(
            node,
            XML_submodel,
            submodel_callback,
            submodel_container);
   return submodel_container;
}

Submodel XMLDeSerializer::deSerializeSubmodel(pugi::xml_node node) {
   Submodel sm("", Identifier(""));

   deSerializeIdentifiable(node, sm);
   deSerializeHasKind(node, sm);
   deSerializeHasSemantics(node, sm);
   deSerializeQualifiable(node, sm);
   deSerializeHasDataSpecification(node, sm);


   return sm;
}

template <typename X>
void XMLDeSerializer::deSerializeIdentifiable(xml_node node,
                                              X & metamodelElement) {

   deSerializeReferable(node, metamodelElement);

   // administration - AdministrativeInformation [0..1]
   xml_node admin_node = findChildByName(node, XML_adminstration);
   if (admin_node.root()) {
      AdministrativeInformation ai =
            deSerializeAdministrativeInformation(admin_node);
      metamodelElement.setAdministration(ai);
   }
   // identification - Identifier [1]
   xml_node ident_node = findChildByName(node, XML_identification);
   if (ident_node.root()) {
      Identifier ident = deSerializeIdentifier(ident_node);
      metamodelElement.setIdentification(ds->getToken(), ident);
   }
}

AdministrativeInformation XMLDeSerializer::deSerializeAdministrativeInformation(
      xml_node node) {
   std::string version;
   std::string revision;

   xml_node ver_node = findChildByName(node, XML_adminstration_Ver);
   if (ver_node.root())
      version = deSerializeString(ver_node);

    xml_node rev_node = findChildByName(node, XML_adminstration_Rev);
    if (rev_node.root())
       revision = deSerializeString(rev_node);

   AdministrativeInformation ai(version, revision);
   return ai;
}

Identifier XMLDeSerializer::deSerializeIdentifier(xml_node node) {
   xml_attribute idType_attr = findAttributeByName(node, XML_ATTR_idType);
   Identifier ident(deSerializeString(node));
   return ident;
}

template <typename X>
void XMLDeSerializer::deSerializeReferable(xml_node node,
                                           X & metamodelElement) {
   // idShort - String [1]
   xml_node idShort_node = findChildByName(node, XML_idShort);
   if (idShort_node.root()) {
      std::string idShort = deSerializeString(idShort_node);
      metamodelElement.setIdShort(idShort);
   }
   // displayName - LangStringSet [0..1]
   xml_node dn_node = findChildByName(node, XML_displayName);
   if (dn_node.root()) {
      langstringset_t ls = deSerializeLangStringSet(dn_node);
      metamodelElement.setDisplayname(ls);
   }
   // category - String [0..1]
   xml_node cat_node = findChildByName(node, XML_category);
   if (cat_node.root()) {
      std::string category = deSerializeString(cat_node);
      metamodelElement.setCategory(category);
   }
   // description - LangStringSet [0..1]
   xml_node desc_node = findChildByName(node, XML_description);
   if (desc_node.root()) {
      langstringset_t ls = deSerializeLangStringSet(desc_node);
      metamodelElement.setDescription(ls);
   }
}

template <typename X>
void XMLDeSerializer::deSerializeHasKind(pugi::xml_node node,
                                                 X & metamodelElement) {
   xml_node mk_node = findChildByName(node, XML_modelingKind);
   if (mk_node.root()) {
      std::string mk_str = deSerializeString(mk_node);
      metamodelElement.kind = ModelingKind_::from_string(mk_str);
   }
   /* As per spec:
    * "Default for an element is that it is representing an instance."
    */
   else
      metamodelElement.kind = ModelingKind::Instance;
}

template <typename X>
void XMLDeSerializer::deSerializeHasSemantics(pugi::xml_node node,
                                                      X & metamodelElement) {
   xml_node semanticsId_node = findChildByName(node, XML_semanticID);
   if (semanticsId_node.root()) {
      util::optional<Reference> r =
            deSerializeReferenceFromParent(semanticsId_node);
      if (r.has_value())
         metamodelElement.setSemanticId(r.value());
   }
}

template<typename X>
void XMLDeSerializer::deSerializeQualifiable(pugi::xml_node node,
                                             X &metamodelElement) {
   xml_node qf_node = findChildByName(node, XML_qualifier);
   if (qf_node.root()) {
      std::cout << "TODO: deSerializeQualifiable(): No interface to set Constraint (Qualifier/Formula)" << std::endl;
      // FIXME: No interface to set Constraint (Qualifier/Formula)
   }
}

template <typename X>
void XMLDeSerializer::deSerializeHasDataSpecification(xml_node node,
                                                      X & metamodelElement) {
   xml_node ds_node = findChildByName(node, XML_dataSpecification);
   if (ds_node.root()) {
      util::optional<Reference> r = deSerializeReferenceFromParent(ds_node);
      if (r.has_value())
         std::cout << "TODO: deSerializeHasDataSpecification(): No interface to set dataSpecifcation" << std::endl;
      // FIXME: No interface to set dataSpecifcation
   }
}

util::optional<Reference> XMLDeSerializer::deSerializeReferenceFromParent(xml_node node) {
   xml_node keys_node = findChildByName(node, XML_keys);
   if (keys_node.root()) {
      return deSerializeReference(keys_node);
   }
   return util::optional<Reference>();
}

util::optional<Reference> XMLDeSerializer::deSerializeReference(xml_node node) {
   std::function<Key(xml_node)> key_callback =
         std::bind(&XMLDeSerializer::deSerializeKey,
             this,
             std::placeholders::_1);

   Reference r(ds->getToken());

   iterateChildren<Reference>(
      node,
      XML_key,
      key_callback,
      r);

   if (r.size() > 0)
     return r;
   return util::optional<Reference>();
}

Key XMLDeSerializer::deSerializeKey(xml_node node) {
   std::string content = deSerializeString(node);

   Key k(content);

   xml_attribute type_attr = findAttributeByName(node, XML_ATTR_type);
   KeyElements ke = KeyElements_::from_string(type_attr.as_string());
   k.set_type(ke);

   // Legacy version 2.0 metamodel
   xml_attribute idType_attr = findAttributeByName(node, XML_ATTR_idType);
   if (!idType_attr.empty()) {
      KeyType kt = KeyType_::from_string(idType_attr.as_string());
      k.set_id_type(kt);
   }

   return k;
}


std::string XMLDeSerializer::deSerializeString(xml_node node) {
   std::string str = node.first_child().value();
   return str;
}

langstringset_t XMLDeSerializer::deSerializeLangStringSet(xml_node node) {
   std::function<langstring_t(xml_node)> langstring_callback =
         std::bind(&XMLDeSerializer::deSerializeLangString,
                   this,
                   std::placeholders::_1);

   langstringset_t set;
         iterateChildren<langstringset_t>(
            node,
            XML_langStr,
            langstring_callback,
            set);
   return set;
}

langstring_t XMLDeSerializer::deSerializeLangString(xml_node node) {
   xml_attribute lang_attr = findAttributeByName(node, XML_ATTR_lang);
   std::string lang = lang_attr.as_string();
   std::string text = deSerializeString(node);
   langstring_t ls(lang, text);
   return ls;
}

template<typename Elem>
void add(std::vector<Elem> & vector, Elem & elem) {
   vector.emplace_back(std::forward<Elem>(elem));
}

template<typename Elem>
void add(ElementContainer<Elem> & cont, Elem & elem) {
   cont.add(std::forward<Elem>(elem));
}

template<typename Elem>
void add(ElementVector<Elem> & cont, Elem & elem) {
   cont.emplace_back(std::forward<Elem>(elem));
}

template<typename Elem>
void add(langstringset_t & cont, Elem & elem) {
   cont.add(elem);
}

template<typename Elem>
void add(Reference & cont, Elem & elem) {
   cont.add(elem);
}


template<class T, class X>
T XMLDeSerializer::iterateChildren(xml_node node,
                                   std::string element_name,
                                   std::function<X(xml_node)> callback,
                                   T & container) {
   for (xml_node_iterator iter = node.begin(); iter != node.end(); iter++) {
      std::string name = iter->name();
      if (element_name.compare(name) != 0)
         continue;
      X x = callback(*iter);
      add(container, x);
   }
   return container;
}

xml_node XMLDeSerializer::findChildByName(xml_node node, std::string name) {
   xml_node ret_node = node.find_child([name](xml_node node) {
        return std::string(name).compare(node.name()) == 0 ? true : false;
   });
   return ret_node;
}

xml_attribute XMLDeSerializer::findAttributeByName(xml_node node, std::string name) {
   xml_attribute ret_attribute = node.find_attribute([name](xml_attribute attr) {
        return std::string(name).compare(attr.name()) == 0 ? true : false;
   });
   return ret_attribute;
}

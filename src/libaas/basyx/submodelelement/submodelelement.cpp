#include "submodelelement.h"

#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>

namespace basyx
{

	bool SubmodelElementHelper::IsProperty(const SubmodelElement& ele) {
		return SubmodelElement::is_element_type<property_base>(&ele);
	};

	bool SubmodelElementHelper::IsMultiLanguageProperty(const SubmodelElement& ele) {
		return SubmodelElement::is_element_type<MultiLanguageProperty>(&ele);
	};
	
	bool SubmodelElementHelper::IsSubmodelElementCollection(const SubmodelElement& ele)  {
		return SubmodelElement::is_element_type<SubmodelElementCollection>(&ele);
	};


};
#include "submodelelementcollection.h"

namespace basyx
{

SubmodelElement * SubmodelElementCollection::find_element_internal(util::string_view idShort) const noexcept
{
	for (const auto & item : this->valueList) {
		if (item->get_id_short() == idShort)
			return item.get();
	};

	return nullptr;
};

};
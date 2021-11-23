#ifndef BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H

#include <basyx/base/basyx_enum_base.h>

namespace basyx {

enum class IdentifiableElements {
    Asset,
    AssetAdministrationShell,
    ConceptDescription,
    Submodel
};

using IdentifiableElements_ = basyx::basyx_enum_base<IdentifiableElements, 4>;

}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H */

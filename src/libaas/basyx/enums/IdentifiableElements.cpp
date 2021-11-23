#include <basyx/enums/IdentifiableElements.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

template<>
const IdentifiableElements_::enum_array_t IdentifiableElements_::string_to_enum =
{
    std::make_pair("Asset",  IdentifiableElements::Asset),
    std::make_pair("AssetAdministrationShell", IdentifiableElements::AssetAdministrationShell),
    std::make_pair("ConceptDescription",  IdentifiableElements::ConceptDescription),
    std::make_pair("Submodel", IdentifiableElements::Submodel),
};
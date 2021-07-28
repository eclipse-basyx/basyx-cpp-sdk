#ifndef BASYX_SUBMODEL_ENUMERATIONS_ASSETKIND_H
#define BASYX_SUBMODEL_ENUMERATIONS_ASSETKIND_H

#include <string>

namespace basyx {
namespace submodel {

enum class AssetKind {
    Type,
    Instance,
    Unknown,
};

class AssetKind_
{
public:
    static AssetKind from_string(const std::string & name);
    static const char * to_string(AssetKind value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_ASSETKIND_H */

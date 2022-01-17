#ifndef BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {

enum class LevelType {
    Max,
    Min,
    Nom,
    Typ,
};

class LevelType_
{
public:
    static LevelType from_string(util::string_view name);
    static const char * to_string(LevelType value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H */

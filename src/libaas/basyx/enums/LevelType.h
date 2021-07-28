#ifndef BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H

#include <string>

namespace basyx {
namespace submodel {

enum class LevelType {
    Max,
    Min,
    Nom,
    Typ,
    Undefined,
};

class LevelType_
{
public:
    static LevelType from_string(const std::string & name);
    static const char * to_string(LevelType value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H */

#ifndef BASYX_SUBMODEL_ENUMERATIONS_LOCALKEYTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_LOCALKEYTYPE_H

#include <string>

namespace basyx {
namespace submodel {

enum class LocalKeyType {
    IdShort,
    FragmentId,
};

class LocalKeyType_
{
public:
    static LocalKeyType from_string(const std::string & name);
    static const char * to_string(LocalKeyType value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_LOCALKEYTYPE_H */

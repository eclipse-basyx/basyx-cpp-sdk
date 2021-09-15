#ifdef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUELIST_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUELIST_H

#include <BaSyx/submodel/api_v2/dataspecification/IValueList.h>

namespace basyx {
namespace submodel {
namespace simple {

class ValueList
    : public api::IValueList {
public:
    ValueList() = default;
    explicit ValueList(const std::vector<simple::ValueReferencePair>& list);

    void addValueReferencePair(const simple::ValueReferencePair& valueRefPair) override;
    std::vector<simple::ValueReferencePair> getValueReferencePairs() override;

private:
    std::vector<simple::ValueReferencePair> list;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUELIST_H */

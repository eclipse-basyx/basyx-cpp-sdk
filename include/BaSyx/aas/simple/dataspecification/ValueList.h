/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUELIST_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUELIST_H

#include <BaSyx/aas/api_v2/dataspecification/IValueList.h>

namespace basyx {
namespace aas {
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

/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef API_METAMODEL_UTILITIES_H
#define API_METAMODEL_UTILITIES_H

#include <BaSyx/opcua/aas/node/MetamodelTypes.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            struct ApiMetamodelUtilities
            {
                static bool isPropertyType(const ISubmodelElement_t * t_submodelElement);
                
                template<typename TYPE>
                static std::unique_ptr<IProperty_t> makeXsdPropertyWithValue(basyx::object t_value,
                    const std::string & t_idShort, const std::string& t_category, LangStringSet_t t_descriptions);
            };

            template<typename TYPE>
            inline std::unique_ptr<IProperty_t> ApiMetamodelUtilities::makeXsdPropertyWithValue(basyx::object t_value,
                const std::string & t_idShort, const std::string & t_category, LangStringSet_t t_descriptions)
            {
                using namespace basyx::xsd_types;

                auto prop{ util::make_unique<Property_t<TYPE>>(t_idShort) };
                prop->setValue(xsd_type<TYPE>::fromXSDRepresentation(t_value));
                prop->setCategory(t_category);
                for (const std::string& code : t_descriptions.getLanguageCodes())
                {
                    prop->getDescription().add(code, t_descriptions.get(code));
                }
                
                return prop;
            }

        }
    }
}
#endif
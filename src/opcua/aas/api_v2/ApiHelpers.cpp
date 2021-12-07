/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/api_v2/ApiHelpers.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            BrowsePath ApiHelpers::getAdminVerBrowsePath(int32_t nsIdx)
            {
                using namespace metamodel;

                return BrowsePath(BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Administration),
                    BrowseName(nsIdx, AASAdministrativeInformationType::AttrNames::BrowseText_Version));
            }

            BrowsePath ApiHelpers::getAdminRevBrowsePath(int32_t nsIdx)
            {
                using namespace metamodel;

                return BrowsePath(BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Administration),
                    BrowseName(nsIdx, AASAdministrativeInformationType::AttrNames::BrowseText_Revision));
            }

            BrowsePath ApiHelpers::getIdentIdBrowsePath(int32_t nsIdx)
            {
                using namespace metamodel;

                return BrowsePath(BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Identification),
                    BrowseName(nsIdx, AASIdentifierType::AttrNames::BrowseText_ID));
            }

            BrowsePath ApiHelpers::getIdentIdTypeBrowsePath(int32_t nsIdx)
            {
                using namespace metamodel;

                return BrowsePath(BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Identification),
                    BrowseName(nsIdx, AASIdentifierType::AttrNames::BrowseText_IdType));
            }

            // Converts the metamodel description to node description (Node standard format)
            // (en-US) Foo (de-DE) Foe => <en-Us; de-DE , Foo; Foe>
            LocalizedText ApiHelpers::getNodeDescription(const basyx::aas::map::LangStringSet & t_descriptions)
            {
                std::string langCodes, descriptions;

                for (const std::string& code : t_descriptions.getLanguageCodes())
                {
                    langCodes += code + ";";
                    descriptions += t_descriptions.get(code) + ";";
                }

                shared::string::chop(langCodes);
                shared::string::chop(descriptions);

                return LocalizedText(langCodes, descriptions);
            }

            basyx::aas::map::LangStringSet ApiHelpers::getMetamodelDescription(const LocalizedText & t_text)
            {
                basyx::aas::map::LangStringSet set;

                auto locales = shared::string::split(t_text.getLocale(), ';');
                auto texts = shared::string::split(t_text.getText(), ';');

                // Return empty set if inconsistent
                if ((locales.size() != texts.size()) || locales.empty() || texts.empty())
                    return set;

                size_t idx(0);
                for (const std::string& locale : locales)
                {
                    set.add(locale, texts[idx]);
                    idx++;
                }

                return set;
            }


        }
    }
}
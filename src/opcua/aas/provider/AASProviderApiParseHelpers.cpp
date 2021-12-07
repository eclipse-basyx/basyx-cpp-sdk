/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/provider/AASProviderApiParseHelpers.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			/* API : shells/{aasID}/aas*/
			bool AASProviderApiParseHelpers::isApiShellsAASIdAAS(const vab::core::VABPath& t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(!(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end())) &&
					(!(std::find(elements.begin(), elements.end(), Element::submodelElements) != elements.end())) &&
					(elements.back() == Element::aas)
					);
			}

			/* API : shells/{aasID}*/
			bool AASProviderApiParseHelpers::isApiShellsAASId(const vab::core::VABPath& t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(!(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end())) &&
					(!(std::find(elements.begin(), elements.end(), Element::submodelElements) != elements.end())) &&
					(elements.back() != Element::aas)
					);
			}

			/* API : shells/{aasID}/aas/submodels/{submodelIdshort} */
			bool AASProviderApiParseHelpers::isAPISubmodelsIdShort(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(elements.back() != Element::submodels)
					);
			}

			/* API : shells/{aasID}/aas/submodels */
			bool AASProviderApiParseHelpers::isAPISubmodels(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(elements.back() == Element::submodels)
					);
			}

			/* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel */
			bool AASProviderApiParseHelpers::isAPISubmodelsSubmodel(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(elements.back() == Element::submodel_)
					);
			}


			/* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/values */
			bool AASProviderApiParseHelpers::isAPISubmodelValues(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodel_) != elements.end()) &&
					(elements.back() == Element::values)
					);

			}

			/* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements*/
			bool AASProviderApiParseHelpers::isAPISubmodelElements(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodel_) != elements.end()) &&
					(elements.back() == Element::submodelElements)
					);
			}

			/* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort} */
			bool AASProviderApiParseHelpers::isAPISubmodelElementsIdShort(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodel_) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodelElements) != elements.end()) &&
					(elements.back() != Element::submodelElements)
					);
			}

			/* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort}/value */
			bool AASProviderApiParseHelpers::isAPISubmodelElementsValue(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodel_) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodelElements) != elements.end()) &&
					(elements.back() == Element::value)
					);
			}

			/* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShortOperation}/invoke */
			bool AASProviderApiParseHelpers::isAPISubmodelElementsInvoke(const vab::core::VABPath & t_path)
			{
				auto& elements{ t_path.getElements() };

				return ((elements.front() == Element::shells) &&
					(std::find(elements.begin(), elements.end(), Element::aas) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodels) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodel_) != elements.end()) &&
					(std::find(elements.begin(), elements.end(), Element::submodelElements) != elements.end()) &&
					(elements.back() == Element::invoke)
					);
			}

			/* Returns a tuple <aasId, smId, smEleId> */
			std::tuple<std::string, std::string, std::string> AASProviderApiParseHelpers::parseIdentifiers(const vab::core::VABPath & t_path)
			{
				std::string aasId, smId, propIdShort;

				bool tokaasList(false), tokaas(false), toksubmodels(false), toksubmodelElements(false);

				for (const std::string& element : t_path.getElements())
				{
					tokaasList = tokaasList || (element == Element::shells);
					toksubmodels = toksubmodels || (element == Element::submodels);
					tokaas = tokaas || (element == Element::aas);
					toksubmodelElements = toksubmodelElements ||
						((element == Element::properties) ||
						(element == Element::operations) ||
							(element == Element::submodelElements));

					if (tokaasList && !toksubmodels && !tokaas && !toksubmodelElements)
					{
						if ((element != Element::shells) && (element != Element::aas))
						{
							aasId += element + "/";
						}
					}
					else if (tokaasList && toksubmodels && !toksubmodelElements)
					{
						if (element != Element::submodels)
						{
							smId += element + "/";
						}
					}
					else if (tokaasList && toksubmodels && tokaas && toksubmodelElements)
					{
						if ((element != Element::properties) &&
							(element != Element::operations) &&
							(element != Element::submodelElements) &&
							(element != Element::value)
							)
						{
							propIdShort += element;
						}
					}
				}

				// TODO: This is temperory fix to remove the "submodel" postfix from the 
				// submodel Identifier. Incorporate that part in the automaton above.
				shared::string::replaceAllWithWhiteSpace(smId, std::string(Element::submodel_)+"/");
				shared::string::replaceAllWithWhiteSpace(smId, std::string(Element::values) + "/");

				if (!aasId.empty())
					basyx::opcua::shared::string::chop(aasId);

				if (!smId.empty())
					basyx::opcua::shared::string::chop(smId);		

				return std::make_tuple(aasId, smId, propIdShort);
			}
        }
    }
}
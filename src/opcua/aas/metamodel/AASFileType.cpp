/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/metamodel/AASFileType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            namespace metamodel
            {
                constexpr char AASFileType::AttrNames::BrowseText[];
                constexpr char AASFileType::AttrNames::DisplayName[];
                constexpr char AASFileType::AttrNames::Description[];
                constexpr char AASFileType::AttrNames::NodeHandle[];
                constexpr char AASFileType::AttrNames::BrowseName_PropertyFileReference[];
                constexpr char AASFileType::AttrNames::DisplayName_PropertyFileReference[];
                constexpr char AASFileType::AttrNames::Description_PropertyFileReference[];
                constexpr char AASFileType::AttrNames::NodeHandle_PropertyFileReference[];
                constexpr char AASFileType::AttrNames::BrowseName_PropertyMimeType[];
                constexpr char AASFileType::AttrNames::DisplayName_PropertyMimeType[];
                constexpr char AASFileType::AttrNames::Description_PropertyMimeType[];
                constexpr char AASFileType::AttrNames::NodeHandle_PropertyMimeType[];
                constexpr char AASFileType::AttrNames::BrowseName_FileType[];
                constexpr char AASFileType::AttrNames::DisplayName_FileType[];
                constexpr char AASFileType::AttrNames::Description_FileType[];
                constexpr char AASFileType::AttrNames::NodeHandle_FileType[];
            }
        }
    }
}
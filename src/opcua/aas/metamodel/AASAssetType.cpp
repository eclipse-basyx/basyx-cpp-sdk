/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/metamodel/AASAssetType.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            namespace metamodel
            {
                constexpr char AASAssetType::AttrNames::InstanceName[];
                constexpr char AASAssetType::AttrNames::BrowseText[];
                constexpr char AASAssetType::AttrNames::DisplayName[];
                constexpr char AASAssetType::AttrNames::Description[];
                constexpr char AASAssetType::AttrNames::NodeHandle[];

                constexpr char AASAssetType::AttrNames::BrowseText_PropertyAssetKind[];
                constexpr char AASAssetType::AttrNames::DisplayName_PropertyAssetKind[];
                constexpr char AASAssetType::AttrNames::Description_PropertyAssetKind[];
                constexpr char AASAssetType::AttrNames::NodeHandle_PropertyAssetKind[];

                constexpr char AASAssetType::AttrNames::BrowseText_AASRefIdentSubmodel[];
                constexpr char AASAssetType::AttrNames::DisplayName_AASRefIdentSubmodel[];
                constexpr char AASAssetType::AttrNames::Description_AASRefIdentSubmodel[];
                constexpr char AASAssetType::AttrNames::NodeHandle_AASRefIdentSubmodel[];

                constexpr char AASAssetType::AttrNames::BrowseText_IdentSubmodel[];
                constexpr char AASAssetType::AttrNames::DisplayName_IdentSubmodel[];
                constexpr char AASAssetType::AttrNames::Description_IdentSubmodel[];
                constexpr char AASAssetType::AttrNames::NodeHandle_IdentSubmodel[];

                constexpr char AASAssetType::AttrNames::BrowseText_AASRefBomSubmodel[];
                constexpr char AASAssetType::AttrNames::DisplayName_AASRefBomSubmodel[];
                constexpr char AASAssetType::AttrNames::Description_AASRefBomSubmodel[];
                constexpr char AASAssetType::AttrNames::NodeHandle_AASRefBomSubmodel[];

                constexpr char AASAssetType::AttrNames::BrowseText_BomSubmodel[];
                constexpr char AASAssetType::AttrNames::DisplayName_BomSubmodel[];
                constexpr char AASAssetType::AttrNames::Description_BomSubmodel[];
                constexpr char AASAssetType::AttrNames::NodeHandle_BomSubmodel[];
            }
        }
    }
}
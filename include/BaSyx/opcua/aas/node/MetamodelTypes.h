/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef METAMODEL_TYPES_H
#define METAMODEL_TYPES_H

#include <BaSyx/shared/object.h>
#include <BaSyx/aas/api_v2/aas/IAsset.h>
#include <BaSyx/aas/map_v2/aas/Asset.h>
#include <BaSyx/aas/api_v2/aas/IAssetAdministrationShell.h>
#include <BaSyx/aas/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/aas/api_v2/ISubmodel.h>
#include <BaSyx/aas/map_v2/Submodel.h>
#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/api_v2/submodelelement/property/IProperty.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>
#include <BaSyx/aas/enumerations/IdentifierType.h>
#include <BaSyx/aas/simple/identifier/Identifier.h>
#include <BaSyx/aas/api_v2/submodelelement/property/XSDAnySimpleType.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            // AAS and SM data types aliases
            using IAsset_t = basyx::aas::api::IAsset;
            using Asset_t  = basyx::aas::map::Asset;
            using IAssetAdministrationShell_t = basyx::aas::api::IAssetAdministrationShell;
            using AssetAdministrationShell_t  = basyx::aas::map::AssetAdministrationShell;
            using ISubmodel_t = basyx::aas::api::ISubmodel;
            using Submodel_t  = basyx::aas::map::Submodel;
            using ISubmodelElement_t = basyx::aas::api::ISubmodelElement;
            using SubmodelElement_t  = basyx::aas::map::SubmodelElement;
            using IProperty_t = basyx::aas::api::IProperty;
            template<typename TYPE>
            using Property_t    = basyx::aas::map::Property<TYPE>;
            using Identifier_t     = basyx::aas::simple::Identifier;
            using IdentifierType_t = basyx::aas::IdentifierType;
            using Key_t = basyx::aas::simple::Key;;
            using LangStringSet_t = basyx::aas::simple::LangStringSet;
            //XSD Data type aliases
            using AnyURI_t   = basyx::aas::simple::AnyURI;
            using DateTime_t = basyx::aas::simple::DateTime;
            using Date_t     = basyx::aas::simple::Date;
            using DayTimeDuration_t   = basyx::aas::simple::DayTimeDuration;
            using YearMonthDuration_t = basyx::aas::simple::YearMonthDuration;
            using Time_t = basyx::aas::simple::Time;
            using GYearMonth_t = basyx::aas::simple::GYearMonth;
            using GYear_t     = basyx::aas::simple::GYear;
            using GMonthDay_t = basyx::aas::simple::GMonthDay;
            using GDay_t   = basyx::aas::simple::GDay;
            using GMonth_t = basyx::aas::simple::GMonth;
        }
    }
}
#endif
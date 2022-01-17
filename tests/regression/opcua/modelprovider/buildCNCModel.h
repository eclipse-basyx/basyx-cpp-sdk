/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BUILD_CNC_MODEL_H
#define BUILD_CNC_MODEL_H

#include <BaSyx/shared/object.h>
#include <string>
#include <cstdint>
#include <thread>
#include <BaSyx/shared/object.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/common/VariableAttributes.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/provider/OPCUAModelProvider.h>
#include <BaSyx/opcua/provider/OPCUAModelProviderHelpers.h>
#include <BaSyx/opcua/provider/VAB2OPCUAHandlers.h>
#include <BaSyx/opcua/provider/OPCUA2VabHandlers.h>

#include <iostream>

/* The below information model will be build

	0:Objects
		2:basyx
			2:EmcoCNC
				2:CuttingTool
					2:Force_X
						2:Engineering_Unit (Property :String)
					2:Force_Y
						2:Engineering_Unit (Property :String)
					2:Force_Z
						2:Engineering_Unit (Property :String)
				2:Tool_ID
				2:Tool_Size
				2:Tool_Type
				2:Vibratiion
					2:Amplitude
						2:Engineering_Unit (Property :String)

*/
namespace tests_opcua_model_provider_leg
{
    using namespace basyx::opcua;

    class EmcoCNC
    {
    public:
        static void createEmoCNCInstance(basyx::opcua::Client* client, const NodeId& rootNode)
        {
            Services<basyx::opcua::Client> services(*client);

            auto t_ns = client->getNamespaceIndexDefault();

            NodeId nodeIdEmcoCNC;
            NodeId nodeIdCuttingTool;
            NodeId nodeIdVibration;
            NodeId nodeIdCuttingForces;

            /* Create the instance of CNCType */
            services.addObjectNode(
                rootNode,
                NodeId::numeric(5000),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "EmcoCNC"),
                ObjectAttributes("EmcoCNC", "EmcoCNC", "en-US"),
                nodeIdEmcoCNC
            );

            services.addObjectNode(
                nodeIdEmcoCNC,
                NodeId::numeric(5001),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "CuttingTool"),
                ObjectAttributes("CuttingTool", "CuttingTool", "en-US"),
                nodeIdCuttingTool
            );

            services.addObjectNode(
                nodeIdCuttingTool,
                NodeId::numeric(5005),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Vibration"),
                ObjectAttributes("Vibration", "Vibration", "en-US"),
                nodeIdVibration
            );

            services.addObjectNode(
                nodeIdCuttingTool,
                NodeId::numeric(5008),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "CuttingForces"),
                ObjectAttributes("CuttingForces", "CuttingForces", "en-US"),
                nodeIdCuttingForces
            );
        }

        static void defineMachineToolType(basyx::opcua::Client * client)
        {
            Services<basyx::opcua::Client> services(*client);

            auto t_ns = client->getNamespaceIndexDefault();

            /* MachineToolType */
            auto nodeIdToolType = NodeId::numeric(5000);

            ObjectTypeAttributes toolTypeAttrs("MachineToolType", "MachineToolType", "en-US");

            services.addObjectTypeNode(
                nodeIdToolType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASSUBTYPE),
                QualifiedName(t_ns, "MachineToolType"),
                toolTypeAttrs
            );
        }

        static void defineCuttingToolType(basyx::opcua::Client * client)
        {
            Services<basyx::opcua::Client> services(*client);

            auto t_ns = client->getNamespaceIndexDefault();

            /* CuttingToolType */
            auto nodeIdCuttingToolType = NodeId::numeric(5001);
            auto nodeIdCuttingToolToolID = NodeId::numeric(5002);
            auto nodeIdCuttingToolToolType = NodeId::numeric(5003);
            auto nodeIdCuttingToolToolSize = NodeId::numeric(5004);

            ObjectTypeAttributes cuttingtoolTypeAttrs("CuttingToolType", "CuttingToolType", "en-US");

            services.addObjectTypeNode(
                nodeIdCuttingToolType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASSUBTYPE),
                QualifiedName(t_ns, "CuttingToolType"),
                cuttingtoolTypeAttrs
            );

            /* CuttingToolType.CuttingTool.Tool_ID */
            services.addObjectNode(
                nodeIdCuttingToolToolID,
                nodeIdCuttingToolType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Tool_ID"),
                ObjectAttributes("Tool_ID", "Tool_ID", "en-US")
            );

            /* CuttingToolType.CuttingTool.Tool_Type */
            services.addObjectNode(
                nodeIdCuttingToolToolType,
                nodeIdCuttingToolType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Tool_Type"),
                ObjectAttributes("Tool_Type", "Tool_Type", "en-US")
            );

            /* CuttingToolType.CuttingTool.Tool_Size */
            services.addObjectNode(
                nodeIdCuttingToolToolSize,
                nodeIdCuttingToolType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Tool_Size"),
                ObjectAttributes("Tool_Size", "Tool_Size", "en-US")
            );

            /* Add Mandatory forward References */
            services.addForwardReferenceModellingRuleMandatory(nodeIdCuttingToolToolID, UA_NODECLASS_OBJECT);
            services.addForwardReferenceModellingRuleMandatory(nodeIdCuttingToolToolType, UA_NODECLASS_OBJECT);
            services.addForwardReferenceModellingRuleMandatory(nodeIdCuttingToolToolSize, UA_NODECLASS_OBJECT);
        }

        static void defineToolVibrationType(basyx::opcua::Client * client)
        {
            Services<basyx::opcua::Client> services(*client);

            auto t_ns = client->getNamespaceIndexDefault();

            /* ToolVibrationType */
            auto nodeIdToolVibrationType = NodeId::numeric(5005);
            auto nodeIdAmplitude = NodeId::numeric(5006);
            auto nodeIdEngineering_Unit = NodeId::numeric(5007);

            VariableAttributes attrEngUnit(UA_TYPES_STRING, "Engineering_Unit", "Engineering_Unit", "en-US");

            services.addObjectTypeNode(
                nodeIdToolVibrationType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASSUBTYPE),
                QualifiedName(t_ns, "ToolVibrationType"),
                ObjectTypeAttributes("ToolVibrationType", "ToolVibrationType", "en-US")
            );

            services.addObjectNode(
                nodeIdAmplitude,
                nodeIdToolVibrationType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Amplitude"),
                ObjectAttributes("Amplitude", "Amplitude", "en-US")
            );

            services.addVariableNode(
                nodeIdEngineering_Unit,
                nodeIdAmplitude,
                NodeId::numeric(UA_NS0ID_HASPROPERTY),
                NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                QualifiedName(t_ns, "Engineering_Unit"),
                attrEngUnit
            );

            /* Add Mandatory forward References */
            services.addForwardReferenceModellingRuleMandatory(nodeIdAmplitude, UA_NODECLASS_OBJECT);
            services.addForwardReferenceModellingRuleMandatory(nodeIdEngineering_Unit, UA_NODECLASS_VARIABLE);
        }

        static void defineCuttingForceType(basyx::opcua::Client * client)
        {
            Services<basyx::opcua::Client> services(*client);

            auto t_ns = client->getNamespaceIndexDefault();

            /* CuttingForceType */
            auto nodeIdCuttingForcesType = NodeId::numeric(5008);
            auto nodeIdForce_X = NodeId::numeric(5009);
            auto nodeIdForce_Y = NodeId::numeric(5010);
            auto nodeIdForce_Z = NodeId::numeric(5011);
            auto nodeIdForce_X_EngUnit = NodeId::numeric(5012);
            auto nodeIdForce_Y_EngUnit = NodeId::numeric(5013);
            auto nodeIdForce_Z_EngUnit = NodeId::numeric(5014);

            VariableAttributes attrEngUnit(UA_TYPES_STRING, "Engineering_Unit", "Engineering_Unit", "en-US");

            services.addObjectTypeNode(
                nodeIdCuttingForcesType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASSUBTYPE),
                QualifiedName(t_ns, "CuttingForceType"),
                ObjectTypeAttributes("CuttingForceType", "CuttingForceType", "en-US")
            );

            services.addObjectNode(
                nodeIdForce_X,
                nodeIdCuttingForcesType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Force_X"),
                ObjectAttributes("Force_X", "Force_X", "en-US")
            );


            services.addVariableNode(
                nodeIdForce_X_EngUnit,
                nodeIdForce_X,
                NodeId::numeric(UA_NS0ID_HASPROPERTY),
                NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                QualifiedName(t_ns, "Engineering_Unit"),
                attrEngUnit
            );

            services.addObjectNode(
                nodeIdForce_Y,
                nodeIdCuttingForcesType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Force_Y"),
                ObjectAttributes("Force_Y", "Force_Y", "en-US")
            );

            services.addVariableNode(
                nodeIdForce_Y_EngUnit,
                nodeIdForce_Y,
                NodeId::numeric(UA_NS0ID_HASPROPERTY),
                NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                QualifiedName(t_ns, "Engineering_Unit"),
                attrEngUnit
            );

            services.addObjectNode(
                nodeIdForce_Z,
                nodeIdCuttingForcesType,
                NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                QualifiedName(t_ns, "Force_Z"),
                ObjectAttributes("Force_Z", "Force_Z", "en-US")
            );

            services.addVariableNode(
                nodeIdForce_Z_EngUnit,
                nodeIdForce_Z,
                NodeId::numeric(UA_NS0ID_HASPROPERTY),
                NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                QualifiedName(t_ns, "Engineering_Unit"),
                attrEngUnit
            );

            services.addForwardReferenceModellingRuleMandatory(nodeIdForce_X, UA_NODECLASS_OBJECT);
            services.addForwardReferenceModellingRuleMandatory(nodeIdForce_X_EngUnit, UA_NODECLASS_VARIABLE);
            services.addForwardReferenceModellingRuleMandatory(nodeIdForce_Y, UA_NODECLASS_OBJECT);
            services.addForwardReferenceModellingRuleMandatory(nodeIdForce_Y_EngUnit, UA_NODECLASS_VARIABLE);
            services.addForwardReferenceModellingRuleMandatory(nodeIdForce_Z, UA_NODECLASS_OBJECT);
            services.addForwardReferenceModellingRuleMandatory(nodeIdForce_Z_EngUnit, UA_NODECLASS_VARIABLE);
        }
    };
}

#endif
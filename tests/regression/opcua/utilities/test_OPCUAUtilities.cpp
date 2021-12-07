/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include "gtest/gtest.h"
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/LocalizedText.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/common/VariableAttributes.h>
#include <BaSyx/opcua/common/MethodAttributes.h>
#include <BaSyx/opcua/common/Variant.h>

namespace basyx
{
    namespace tests
    {
        namespace opcua
        {
            class OPCUAUtilitiesTest : public ::testing::Test
            {
            };

            TEST_F(OPCUAUtilitiesTest, diag_getErrorString)
            {
                auto str = basyx::opcua::shared::diag::getErrorString(UA_STATUSCODE_GOOD);

                ASSERT_EQ(str, "Good");
            }

            TEST_F(OPCUAUtilitiesTest, diag_isStatusBad)
            {
                auto b = basyx::opcua::shared::diag::isStatusBad(UA_STATUSCODE_BADAGGREGATELISTMISMATCH);

                ASSERT_TRUE(b);
            }

            TEST_F(OPCUAUtilitiesTest, NodeId)
            {
                using namespace basyx::opcua;

                NodeId n(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 0, 4);

                NodeId n1(UA_NodeIdType::UA_NODEIDTYPE_STRING, 0, "asdf");

                NodeId n2(UA_NodeIdType::UA_NODEIDTYPE_STRING, 0, "asdf__2");

                NodeId n3;

                ASSERT_TRUE(n3 == NodeId(UA_NODEID_NULL));

                n3 = n1;

                ASSERT_TRUE(n3 == n1);
                ASSERT_FALSE(n1 != n3);

                ASSERT_EQ(n1.toString(), "ns:0;s=asdf");
                ASSERT_EQ(n.toString(), "ns:0;i=4");

                std::vector<NodeId> nv;

                nv.push_back(NodeId::numeric(0));
                nv.push_back(NodeId::numeric(1));
                nv.push_back(NodeId::numeric(2));

                ASSERT_EQ(nv.size(), 3);

                ASSERT_TRUE(nv[0] == NodeId::numeric(0));


            }

            TEST_F(OPCUAUtilitiesTest, QualifiedName)
            {
                using namespace basyx::opcua;

                QualifiedName q1(0, "test1");
                QualifiedName q2(0, "test1");

                ASSERT_TRUE(q1 == q2);
                ASSERT_FALSE(q1 != q2);

                QualifiedName q3;

                q3 = q1;

                ASSERT_TRUE(q3 == q1);

                ASSERT_EQ(q3.toString(), "0:test1");
            }


            TEST_F(OPCUAUtilitiesTest, ObjectAttributes)
            {
                using namespace basyx::opcua;

                ObjectAttributes o("abc", "description abc", "en-US");

                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectAttributes().displayName.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectAttributes().displayName.text), "abc");
                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectAttributes().description.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectAttributes().description.text), "description abc");
            }

            TEST_F(OPCUAUtilitiesTest, ObjectTypeAttributes)
            {
                using namespace basyx::opcua;

                ObjectTypeAttributes o("abc", "description abc", "en-US");

                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectTypeAttributes().displayName.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectTypeAttributes().displayName.text), "abc");
                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectTypeAttributes().description.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(o.getUA_ObjectTypeAttributes().description.text), "description abc");
            }

            TEST_F(OPCUAUtilitiesTest, VariableAttributes)
            {
                using namespace basyx::opcua;

                VariableAttributes v(UA_TYPES_INT32, "rpm", "description rpm", "en-US");

                ASSERT_EQ(shared::string::UAStringToStdString(v.getUA_VariableAttributes().displayName.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(v.getUA_VariableAttributes().displayName.text), "rpm");
                ASSERT_EQ(shared::string::UAStringToStdString(v.getUA_VariableAttributes().description.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(v.getUA_VariableAttributes().description.text), "description rpm");
                ASSERT_TRUE(NodeId(v.getUA_VariableAttributes().dataType) == NodeId(UA_TYPES[UA_TYPES_INT32].typeId));
            }

            TEST_F(OPCUAUtilitiesTest, MethodAttributes)
            {
                using namespace basyx::opcua;

                MethodAttributes m("operation", "description operation", "en-US");

                ASSERT_EQ(shared::string::UAStringToStdString(m.getUA_MethodAttributes().displayName.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(m.getUA_MethodAttributes().displayName.text), "operation");
                ASSERT_EQ(shared::string::UAStringToStdString(m.getUA_MethodAttributes().description.locale), "en-US");
                ASSERT_EQ(shared::string::UAStringToStdString(m.getUA_MethodAttributes().description.text), "description operation");
                ASSERT_EQ(m.getUA_MethodAttributes().executable, true);
                ASSERT_EQ(m.getUA_MethodAttributes().userExecutable, true);
            }

            TEST_F(OPCUAUtilitiesTest, VaraintScalar)
            {
                using namespace basyx::opcua;

                Variant<bool> varBool(true);

                ASSERT_FALSE(varBool.isVector());
                ASSERT_TRUE(varBool.isScalar());
                ASSERT_EQ(true, *(bool*)varBool.get_UAVariant()->data);

                uint16_t valU16(65535);

                Variant<uint16_t> varU16(valU16);

                ASSERT_FALSE(varU16.isVector());
                ASSERT_TRUE(varU16.isScalar());
                ASSERT_EQ(65535, *(uint16_t*)varU16.get_UAVariant()->data);

                std::vector<int32_t> vectInt32{ -4, 3234244, 23 };

                Variant<int32_t> variantInt32(vectInt32);

                auto ptrI32 = (int32_t*)variantInt32.get_UAVariant()->data;

                ASSERT_EQ(3, variantInt32.getArrayLength());
                ASSERT_TRUE(variantInt32.isVector());
                ASSERT_FALSE(variantInt32.isScalar());
                ASSERT_EQ(-4, *ptrI32);
                ptrI32++;
                ASSERT_EQ(3234244, *(ptrI32));
                ptrI32++;
                ASSERT_EQ(23, *(ptrI32));

                Variant<bool> varVecBool({ true, false });
                ASSERT_TRUE(varVecBool.isVector());
                ASSERT_FALSE(varVecBool.isScalar());
                ASSERT_EQ(2, varVecBool.getArrayLength());

                auto ptrIBool = (bool*)varVecBool.get_UAVariant()->data;

                ASSERT_TRUE(*ptrIBool);
                ptrIBool++;
                ASSERT_FALSE(*ptrIBool);

                auto scalar = basyx::opcua::Variant<uint16_t>::scalar(*varU16.get_UAVariant());

                ASSERT_EQ(scalar, 65535);

                Variant<std::string> vStrVec({ "basyx", "opcua","i4.0" });

                auto vector = basyx::opcua::Variant<std::string>::array(*vStrVec.get_UAVariant());

                ASSERT_EQ(vector[0], "basyx");
                ASSERT_EQ(vector[1], "opcua");
                ASSERT_EQ(vector[2], "i4.0");

                Variant <std::string> vStr("test string");

                auto scalar_ = Variant<std::string>::scalar(*vStr.get_UAVariant());

                ASSERT_EQ(scalar_, "test string");
            }

            TEST_F(OPCUAUtilitiesTest, LocalizedText)
            {
                using namespace basyx::opcua;

                LocalizedText l0;
                ASSERT_EQ(l0.getLocale(), std::string());
                ASSERT_EQ(l0.getText(), std::string());

                LocalizedText l1("en-US", "foo");
                ASSERT_EQ(l1.getLocale(), "en-US");
                ASSERT_EQ(l1.getText(), "foo");

                LocalizedText l2("de-DE", "foö");
                ASSERT_EQ(l2.getLocale(), "de-DE");
                ASSERT_EQ(l2.getText(), "foö");

                LocalizedText l3("en-US;de-DE", "foo;foö");
                ASSERT_EQ(l3.getLocale(), "en-US;de-DE");
                ASSERT_EQ(l3.getText(), "foo;foö");

                ASSERT_EQ(l1.toString(), "(en-US)foo");

                LocalizedText l4;
                l4 = l1;
                ASSERT_TRUE(l4 == l1);

            }
        }
    }
}

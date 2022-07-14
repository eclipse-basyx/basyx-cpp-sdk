#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/environment.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/asset.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/submodel.h>

#include <basyx/enums/IdentifiableElements.h>

#include <basyx/qualifiable/qualifier.h>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class QualifierTest : public ::testing::Test {
protected:
    // Test settings

    // Test variables

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};


TEST_F(QualifierTest, QualifierType)
{
    ASSERT_EQ(Qualifier<uint8_t> { "id" }.getValueType(), "unsignedByte");
    ASSERT_EQ(Qualifier<int8_t> { "id" }.getValueType(), "byte");
    ASSERT_EQ(Qualifier<std::string> { "id" }.getValueType(), "string");
    ASSERT_EQ(Qualifier<double> { "id" }.getValueType(), "double");
    ASSERT_EQ(Qualifier<float> { "id" }.getValueType(), "float");
    ASSERT_EQ(Qualifier<char> { "id" }.getValueType(), "byte");
};

TEST_F(QualifierTest, QualifierTest1)
{
    Qualifier<int> q1{ "int_qual" };
    q1.setValue(5);

    ASSERT_EQ(*q1.getValue(), 5);
    ASSERT_EQ(q1.getValueType(), "int");

    Qualifier<float> p2{ "float_qualifier" };
    ASSERT_EQ(p2.getValueType(), "float");
    ASSERT_FALSE(p2.getValue());

    p2.setValue(5.0f);
    ASSERT_TRUE(p2.getValue());
    ASSERT_EQ(*p2.getValue(), 5.0f);
};

TEST_F(QualifierTest, QualifierTest2)
{
    Qualifier<int> q1{ "int_qualifier", 5 };
    ASSERT_EQ(*q1.getValue(), 5);
    ASSERT_EQ(q1.getValueType(), "int");

    Qualifier<float> q2{ "float_qualifier", 5.0f };
    ASSERT_TRUE(q2.getValue());
    ASSERT_EQ(*q2.getValue(), 5.0f);

    Qualifier<std::string> q3{ "string_qualifier", "test" };
    ASSERT_TRUE(q3.getValue());
    ASSERT_EQ(*q3.getValue(), "test");
};


TEST_F(QualifierTest, IntQualifierCopy)
{
    Qualifier<int> i{ "i", 1 };
    auto i2 = i;

    i2.~Qualifier();
    i.~Qualifier();
}

TEST_F(QualifierTest, StringQualifierCopy)
{
    Qualifier<std::string> s("stringType");
    s.setValue("testStart");
    auto s2 = s;

    s.setValue("test");

    s.~Qualifier();
    s2.~Qualifier();
}

TEST_F(QualifierTest, QualifierTypeTest)
{
    std::string s = "string_qualifier";

    Qualifier<std::string> qs{ "string_qualifier", "test" };
    ASSERT_EQ(qs.getQualifierType(), s);

    auto qs2 = qs;

    ASSERT_EQ(qs2.getQualifierType(), s);
}

TEST_F(QualifierTest, StringQualifierInitializerListCopy)
{
    Qualifier<std::string> s{ "string_qualifier", "testStart" };
    auto s2 = s;

    s.setValue("test");
}

TEST_F(QualifierTest, QualifierCast)
{
    Qualifier<int> i{ "i", 1 };
    QualifierBase* baseQual = &i;

    auto casted_ok = baseQual->cast<int>();
    ASSERT_NE(casted_ok, nullptr);
    ASSERT_EQ(casted_ok->getValue(), i.getValue());

    auto casted_bad = baseQual->cast<std::string>();
    ASSERT_EQ(casted_bad, nullptr);
}

TEST_F(QualifierTest, QualifierTypeInfo)
{
    int intVal = 1;
    Qualifier<int> i{ "i", intVal };
    QualifierBase* baseQual = &i;

    ASSERT_EQ(baseQual->getValueType(), "int");

    switch (baseQual->getValueTypeEnum()) {
    case basyx::detail::Integer: {
       Qualifier<int> *i2= baseQual->cast<int>();
       ASSERT_EQ(i2->getValue(), intVal);
       break;
    }
    default:
       break;
    }
}

TEST_F(QualifierTest, QualifiableVectorTest)
{
   Qualifier<float> q("floatQ", float(1.43));
   Qualifier<int> int_q("intQ", 5);
   Qualifier<std::string> str_q("strQ", "testStr");

   Qualifier<int> *qp  = q.addQualifier(int_q);
   ASSERT_EQ(qp->getValueType(), "int");
   ASSERT_EQ(qp->getValue(), 5);

   Qualifier<std::string> *qp2  = q.addQualifier(str_q);
   ASSERT_EQ(qp2->getValueType(), "string");
   ASSERT_EQ(qp2->getValue(), "testStr");

   auto qi = q.getQualifiers().begin();
   // Counter to check if elements are actually found
   int counter = 0;
   while (qi != q.getQualifiers().end()) {
      switch (qi->get()->getValueTypeEnum()) {
      case basyx::detail::Integer: {
         counter++;
         Qualifier<int> *iq = qi->get()->cast<int>();
         ASSERT_EQ(iq->getValue(), 5);
         break;
      }
      case basyx::detail::String: {
         counter++;
         Qualifier<std::string> *sq = qi->get()->cast<std::string>();
         ASSERT_EQ(sq->getValue(), "testStr");
         break;
      }
      default:
         break;
      }
      qi++;
   }
   ASSERT_EQ(counter, 2);
}



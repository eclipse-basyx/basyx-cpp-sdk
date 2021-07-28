#include <gtest/gtest.h>

#include <spdlog/spdlog.h>

#include <basyx/langstringset.h>
#include <basyx/key.h>
#include <basyx/reference.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class MiscTest : public ::testing::Test
{
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

class base;
class derived;

template<typename T>
void serialize_helper(int & x, const T & t)
{
	spdlog::info("Serializing base!");
};

template<>
void serialize_helper(int & x, const derived & d)
{
	spdlog::info("Serializing derived!");
	x = 5;
};

struct zinghy
{
	std::string s = "AHA!";
	~zinghy() { 
		s = "NULL"; 
	};
};

class serializable_base
{
public:
	virtual void serialize_json(int & x) = 0;
};

template<typename T>
class Serializable : public virtual serializable_base
{
public:
	void serialize_json(int & x) override { serialize_helper<T>(x, *static_cast<T*>(this)); };
};

class base : public virtual serializable_base
{
public:
	virtual ~base() = default;
};

class derived : public base, public Serializable<derived>
{
public:
	int x;
public:
	zinghy z;
	~derived()
	{
		int j = 2;
	};
};

TEST_F(MiscTest, Stuff_1)
{
	std::unique_ptr<base> b = std::make_unique<derived>();

	derived * d = (derived*)b.get();

	auto * ch = d->z.s.data();

	b.reset();
	b.reset();
};

TEST_F(MiscTest, Serialize_1)
{
	std::unique_ptr<base> b = std::make_unique<derived>();

	int x;

	b->serialize_json(x);

	int j = 2;
};



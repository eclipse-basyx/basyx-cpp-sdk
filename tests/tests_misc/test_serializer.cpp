#include <gtest/gtest.h>

#include <spdlog/spdlog.h>

#include <type_traits>

namespace ser
{

class SerializerTest : public ::testing::Test
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
class derived2;
struct zinghy
{
	std::string s = "AHA!";
	~zinghy() { 
		s = "NULL"; 
	};
};

class Serializer
{
public:
	virtual void serialize(const base & based) { spdlog::info("[XXX] base"); };
	virtual void serialize(const derived & deriveded) { spdlog::info("[XXX] derived"); };
};

class serializable_base
{
public:
	virtual void serialize(Serializer & serializer) = 0;
};

template<typename T>
class Serializable : public virtual serializable_base
{
public:
	void serialize(Serializer & serializer) override
	{ 
		serializer.serialize(*static_cast<T*>(this)); 
	};
};

class base : public virtual serializable_base
{
public:
	virtual ~base() = default;
};

class derived2 : public base, private Serializable<derived2>
{
};

class derived : public base, private Serializable<derived>
{
public:
	int x;
public:
	zinghy z;
	~derived()
	{
		
	};
};

class JSON : public Serializer
{
public:
	int buffer;
public:
	void serialize(const base & based) { buffer = 0; spdlog::info("[JSON] base"); };
	void serialize(const derived & deriveded) { buffer = deriveded.x; spdlog::info("[JSON] derived"); };
};

class XML : public Serializer
{
public:
	float buffer;
public:
	void serialize(const base & based) { buffer = 0.0f; spdlog::info("[XML] base"); };
	void serialize(const derived & deriveded) { buffer = deriveded.x; spdlog::info("[XML] derived"); };
};


TEST_F(SerializerTest, Stuff_1)
{
	std::unique_ptr<base> b = std::make_unique<derived>();

	derived * d = (derived*)b.get();

	auto * ch = d->z.s.data();

	b.reset();
	b.reset();
};

TEST_F(SerializerTest, Serialize_1)
{
	std::unique_ptr<base> b = std::make_unique<derived>();
	std::unique_ptr<base> b2 = std::make_unique<derived2>();

	int x;

	JSON js;
	XML xml;

	b->serialize(js);
	b2->serialize(xml);

	
};

}


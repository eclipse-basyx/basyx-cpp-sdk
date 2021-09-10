#include <gtest/gtest.h>

#include <spdlog/spdlog.h>

#include <type_traits>

namespace ser2
{

class SerializerTest2 : public ::testing::Test
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

template<typename T>
class Serializable
{
public:
	template<typename Serializer>
	void serialize(Serializer & serializer) override
	{ 
		serializer.serialize(*static_cast<T*>(this)); 
	};
};

class base
{
public:
	virtual ~base() = default;
};

class derived2 : public base
{
};

class derived : public base
{
public:
	int x;
public:
	zinghy z;
	~derived()
	{
		
	};
};

class JSON
{
public:
	int buffer;
public:
	void serialize(const base & based) { buffer = 0; spdlog::info("[JSON] base"); };
	void serialize(const derived & deriveded) { buffer = deriveded.x; spdlog::info("[JSON] derived"); };
};

class XML
{
public:
	float buffer;
public:
	void serialize(const base & based) { buffer = 0.0f; spdlog::info("[XML] base"); };
	void serialize(const derived & deriveded) { buffer = deriveded.x; spdlog::info("[XML] derived"); };
};


TEST_F(SerializerTest2, Stuff_1)
{
	std::unique_ptr<base> b = std::make_unique<derived>();

	derived * d = (derived*)b.get();

	auto * ch = d->z.s.data();

	b.reset();
	b.reset();
};

TEST_F(SerializerTest2, Serialize_1)
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


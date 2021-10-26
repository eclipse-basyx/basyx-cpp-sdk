#include <gtest/gtest.h>

#include <basyx/submodelelement/operation.h>
#include <basyx/submodelelement/operationvariable.h>
#include <basyx/submodelelement/multilanguageproperty.h>

#include <type_traits>


using namespace basyx;

class OperationTest : public ::testing::Test {
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

TEST_F(OperationTest, OperationVariable)
{
	//auto var = OperationVariable::create<MultiLanguageProperty>("op_var", "mlp");
};

int mult(int a, int b)
{
	return a * b;
};

TEST_F(OperationTest, Operation)
{
	Operation op{ "test" };

	auto mlp = std::make_unique<MultiLanguageProperty>("mlp");

	op.inputVariables() = {
		Property<int>("a"),
		Property<int>("b")
	};

	/*
	SubmodelElement>(
		const ElementContainer<SubmodelElement>&,
		ElementContainer<SubmodelElement>&
	)
	*/

	ASSERT_EQ(op.inputVariables().size(), 2);

	op.setInvokable([] (
		const ElementContainer<SubmodelElement>& input, 
		ElementContainer<SubmodelElement>& inout,
		ElementContainer<SubmodelElement> & output) -> bool {
			// Extract input variables from input list
			int a = *input.get<Property<int>>("a")->get_value();
			int b = *input.get<Property<int>>("b")->get_value();

			// Call the actual function
			auto c = mult(a, b);

			// Set output variables
			output.get<Property<int>>("umdrehungszahl")->set_value(c);
			output.get<Property<int>>("winkel")->set_value(100);

			// Return invokation result
			return true;
	});

	auto input = ElementContainer<SubmodelElement>{
		Property<int>("a", 4), 
		Property<int>("b", 2)
	};

	auto inout = ElementContainer<SubmodelElement>{};

	auto output = ElementContainer<SubmodelElement>{
		Property<int>("umdrehungszahl"), 
		Property<int>("winkel") 
	};

	auto invoke_result = op.invoke(
		input,
		inout,
		output
	);

	ASSERT_EQ(invoke_result, true);

	ASSERT_EQ(*output.get<Property<int>>("umdrehungszahl")->get_value(), 4*2);
	ASSERT_EQ(*output.get<Property<int>>("winkel")->get_value(), 100);


	//bool op.invoke(const input&, inout&, output&)
	//{
	//	auto output = op.outputVariables.copy();

	//	auto ret = invokable(input, inout, outputs);
	//};

	//LambdaOperation l([](const int & a, const int & b, int & c) -> int {});
	//typename ReturnType -> int
	//typename... Inputs  -> int , int

	//auto a = input.get<Property<int>>(Is<Inputs...>...)->get_value().value();

	//ElementContainer<SubmodelElement> output;
	//output.create<Property<int>>("result", mult(a, b));
	//return output;
};

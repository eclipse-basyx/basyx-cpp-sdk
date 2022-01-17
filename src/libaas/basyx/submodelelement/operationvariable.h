#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>

#include <basyx/submodelelement/property.h>

#include <basyx/modeltype.h>

#include <basyx/util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class OperationVariable : private ModelType<ModelTypes::OperationVariable>
{
private:
	std::unique_ptr<SubmodelElement> value;
public:
	OperationVariable(std::unique_ptr<SubmodelElement> value)
		: value(std::move(value)) 
	{
	};

	OperationVariable(const SubmodelElement & value)
		: value(value.copy<SubmodelElement>())
	{
	};

	OperationVariable(OperationVariable& rhs) = default;
	OperationVariable& operator=(OperationVariable&) = default;

	OperationVariable(OperationVariable&& rhs) noexcept = default;
	OperationVariable& operator=(OperationVariable&&) noexcept = default;

	~OperationVariable() = default;
public:
	const SubmodelElement & get_value() const { return *this->value; };
	SubmodelElement & get_value() { return *this->value; };
public:
	template<typename SubmodelElementType, typename... Args>
	static OperationVariable create(util::string_view idShort, Args&&... args)
	{
		auto value = std::make_unique<SubmodelElementType>(idShort, std::forward<Args>(args)...);
		return { std::move(value) };
	};

	template<typename SubmodelElementType>
	static SubmodelElementType Create(util::string_view idShort, basyx::langstringset_t description)
	{
		auto var = SubmodelElementType{ idShort };
		var.setCategory("VARIABLE");
		var.setDescription(std::move(description));
		return var;
	};
};

}
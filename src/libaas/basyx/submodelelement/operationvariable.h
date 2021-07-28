#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>

#include <basyx/submodelelement/property.h>

#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class OperationVariable : public DataElement, private ModelType<ModelTypes::OperationVariable>
{
private:
	std::unique_ptr<SubmodelElement> value;
public:
	OperationVariable(util::string_view idShort, std::unique_ptr<SubmodelElement> value)
		: DataElement(idShort), value(std::move(value)) 
	{
	};

	OperationVariable(OperationVariable& rhs) = delete;
	OperationVariable& operator=(OperationVariable&) = delete;

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
		auto value = std::make_unique<SubmodelElementType>(std::forward<Args>(args)...);
		value->kind = ModelingKind::Template;
		return { idShort, std::move(value) };
	};
};

}
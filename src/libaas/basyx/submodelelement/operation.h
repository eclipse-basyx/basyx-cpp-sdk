#pragma once

#include <basyx/submodelelement/operationvariable.h>
#include <basyx/langstringset.h>

#include <basyx/base/elementcontainer.h>
#include <basyx/submodelelement/property.h>

#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>
#include <util/container/container.hpp>

#include <functional>
#include <string>
#include <deque>
#include <list>

namespace basyx
{

class Operation : public DataElement, private ModelType<ModelTypes::Operation>
{
public:
	using opVarList_t = basyx::ElementContainer<SubmodelElement>;
	using invokable_t = std::function<bool( // Function success
		const opVarList_t&,  // inputVars
		opVarList_t&,        // inOutVars
		opVarList_t& )>;     // outputVars
private:
	opVarList_t inputVars;
	opVarList_t outputVars;
	opVarList_t inOutVars;

	invokable_t invokable;
public:
	Operation(util::string_view idShort) : DataElement(idShort) {
		inputVars.setOwner(this);
		outputVars.setOwner(this);
		inOutVars.setOwner(this);
	};

	Operation(util::string_view idShort,
		opVarList_t inputVars,
		opVarList_t outputVars,
		opVarList_t inOutVars)
	: DataElement(idShort)
	, inputVars(std::move(inputVars))
	, outputVars(std::move(outputVars))
	, inOutVars(std::move(inOutVars)) {
		inputVars.setOwner(this);
		outputVars.setOwner(this);
		inOutVars.setOwner(this);
	};

	Operation(const Operation&) = default;
	Operation& operator=(const Operation&) = default;

	Operation(Operation&&) = default;
	Operation& operator=(Operation&&) = default;

	~Operation() = default;
private:
	template<typename... Vars>
	inline void _set_opvarlist(opVarList_t & list, Vars&&... vars) {
		util::vector_helper::emplace_variadic(list, std::forward<Vars>(vars)...);
	};
public:
	opVarList_t & inputVariables() { return inputVars; };
	const opVarList_t & inputVariables() const { return inputVars; };

	opVarList_t & outputVariables() { return outputVars; };
	const opVarList_t & outputVariables() const { return outputVars; };

	opVarList_t & inOutVariables() { return inOutVars; };
	const opVarList_t & inOutVariables() const { return inOutVars; };
public:
	void setInvokable(invokable_t invokable) { this->invokable = invokable; }
	bool invoke(const opVarList_t& inputVars, 
		opVarList_t& inoutVars,        
		opVarList_t& outputVars);
};

}
#pragma once

#include <basyx/submodelelement/operationvariable.h>
#include <basyx/langstringset.h>

#include <basyx/submodelelement/property.h>

#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>
#include <util/container/container.hpp>

#include <string>
#include <deque>
#include <list>

namespace basyx
{

class Operation : public DataElement, private ModelType<ModelTypes::Operation>
{
public:
	using opvarList_t = std::vector<OperationVariable>;
private:
	opvarList_t inputVars;
	opvarList_t outputVars;
	opvarList_t inoutputVars;
public:
	Operation(util::string_view idShort) : DataElement(idShort) {};
	Operation(util::string_view idShort,
		opvarList_t inputVars,
		opvarList_t outputVars,
		opvarList_t inoutVars)
	: DataElement(idShort)
	, inputVars(std::move(inputVars))
	, outputVars(std::move(outputVars))
	, inoutputVars(std::move(inoutputVars)) {};

	Operation(const Operation&) = default;
	Operation& operator=(const Operation&) = default;

	Operation(Operation&&) = default;
	Operation& operator=(Operation&&) = default;

	~Operation() = default;
private:
	template<typename... Vars>
	inline void _set_opvarlist(opvarList_t & list, Vars&&... vars) {
		list.clear();
		list.reserve(sizeof...(Vars));
		util::vector_helper::emplace_variadic(list, std::forward<Vars>(vars)...);
		//list.emplace_back(std::forward<Vars>(vars)...);
	};
public:
	const opvarList_t & get_input_variables() const { return this->inputVars; };
	opvarList_t & get_input_variables() { return this->inputVars; };
	void set_input_variables(opvarList_t vars) { this->inputVars = std::move(vars); }
	
	template<typename... Vars>
	void set_input_variables(Vars&&... vars) {
		this->_set_opvarlist(inputVars, std::forward<Vars>(vars)...);
	};

	const opvarList_t & get_output_variables() const { return this->outputVars; };
	opvarList_t & get_output_variables() { return this->outputVars; };
	void set_output_variables(opvarList_t vars) { this->outputVars = std::move(vars); }
	
	template<typename... Vars>
	void set_output_variables(Vars&&... vars) {
		this->_set_opvarlist(outputVars, std::forward<Vars>(vars)...);
	};

	const opvarList_t & get_inoutput_variables() const { return this->inoutputVars; };
	opvarList_t & get_inoutput_variables() { return this->inoutputVars; };
	void set_inoutput_variables(opvarList_t vars) { this->inoutputVars = std::move(vars); }
	
	template<typename... Vars>
	void set_inoutput_variables(Vars&&... vars) {
		this->_set_opvarlist(inoutputVars, std::forward<Vars>(vars)...);
	};
};

}
/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJ_FUNCTION_H
#define BASYX_SHARED_OBJECT_OBJ_FUNCTION_H

#include <functional>

#include <BaSyx/shared/object/object_header.h>

#include <nlohmann/json.hpp>

namespace basyx {
namespace detail {

class functionWrapper
{
private:
	std::function<basyx::object(basyx::object*)> func;

	template <typename R, typename... Args, std::size_t... Is>
	static R invoke_helper(std::function<R(Args...)> f, basyx::object::object_list_t & params, util::index_sequence<Is...>)
	{
		return f(params[Is].Get<Args&>()...);
	};
public:
	// Invoke wrapped function with no arguments
	basyx::object invoke() const
	{
		return func(nullptr);
	};

	// Invoke wrapped function with argument
	// Has to be primitive object or object list
	basyx::object invoke(basyx::object & obj) const
	{
		return func(&obj);
	};

	// Wrap void function with no arguments
	static functionWrapper wrap_func(std::function<void(void)> f)
	{
		functionWrapper fw;
		fw.func = [f](basyx::object*)
		{
			f();
			return basyx::object::make_null();
		};
		return fw;
	};

	// Wrap function with no arguments
	template<typename RetType>
	static functionWrapper wrap_func(std::function<RetType(void)> f)
	{
		functionWrapper fw;
		fw.func = [f](basyx::object*)
		{
			return basyx::object{ f() };
		};
		return fw;
	};

	// Wrap function with single argument
	template<typename RetType, typename Arg>
	static functionWrapper wrap_func(std::function<RetType(Arg)> f)
	{
		functionWrapper fw;
		fw.func = [f](basyx::object * obj)
		{
			// Only allow primitive object types
			if (obj != nullptr && obj->GetObjectType() == basyx::type::objectType::Primitive && obj->GetValueType() == basyx::type::basyx_type<Arg>::value_type)
			{
				// Cast object to argument type and invoke
				auto & i = obj->Get<Arg&>();
				return basyx::object{ f(i) };
			};

			return basyx::object::make_null();
		};
		return fw;
	};

	// Wrap function with argument list
	template<typename RetType, typename... Args>
	static functionWrapper wrap_func(std::function<RetType(Args...)> f)
	{
		functionWrapper fw;
		fw.func = [f](basyx::object * obj)
		{
			// Only allow object lists
			if (obj != nullptr && obj->GetObjectType() == basyx::type::objectType::List && obj->GetValueType() == basyx::type::valueType::Object)
			{
				auto & list = obj->Get<basyx::object::object_list_t&>();

				// if size of argument list differs from the functions parameter list, return null
				if (list.size() != sizeof...(Args))
					return basyx::object::make_null();

				// TODO: type check arguments

				// Invoke, using an integer sequence to pass the values from the list as single parameters to the function
				return basyx::object{ invoke_helper<RetType, Args...>(f, list, util::make_index_sequence<sizeof...(Args)>{}) };
			};

			return basyx::object::make_null();
		};
		return fw;
	};

	template<typename T>
	bool operator==(const T &) const
	{
		return false;
	};
};

static void to_json(nlohmann::json & json, const functionWrapper &)
{
	return;
};

}
}


#endif /* BASYX_SHARED_OBJECT_OBJ_FUNCTION_H */

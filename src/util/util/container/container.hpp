#pragma once

#include <vector>

namespace basyx::util {

struct vector_helper
{
public:
	template <typename T>
	static void emplace_variadic(std::vector<T>&) {};

	template <typename T, typename Head, typename... Tail>
	static void emplace_variadic(std::vector<T>& v, Head&& head, Tail&&... tail) 
	{
		v.emplace_back(std::forward<Head>(head));
		emplace_variadic(v, std::forward<Tail>(tail)...);
	}
};

}
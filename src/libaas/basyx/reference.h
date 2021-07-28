#pragma once

#include <basyx/key.h>

#include <util/optional/optional.hpp>

#include <basyx/referable.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class Reference
{
private:
	std::vector<Key> keys;
public:
	Reference(const Key & key) : keys{ key } {};
	Reference(Key && key) : keys{ std::move(key) } {};
	Reference(util::string_view str);
	Reference(const Referable & referable);
	Reference(std::initializer_list<Key> init_list) : keys{ std::move(init_list) } {};
public:
	Reference(const Reference &) = default;
	Reference& operator=(const Reference &) = default;

	Reference(Reference &&) = default;
	Reference& operator=(Reference &&) = default;
public:
	const Key & get_key(std::size_t index) const { return keys[index]; };
	const std::size_t size() const { return keys.size(); };
};

};

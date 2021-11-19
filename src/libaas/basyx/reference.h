#pragma once

#include <basyx/key.h>

#include <util/optional/optional.hpp>

#include <basyx/referable.h>

#include <basyx/base/token.h>
#include <basyx/serialization/base/serialization.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class Reference
{
public:
	using keyList_t = std::vector<Key>;
private:
	keyList_t keys;
public:
	Reference(basyx::base::Token<basyx::serialization::priv::Deserializer> t);
	Reference(const Key & key) : keys{ key } {};
	Reference(Key && key) : keys{ std::move(key) } {};
	Reference(util::string_view from_string);
	Reference(const Referable & referable);
	Reference(const keyList_t & keyList) : keys(keyList) {};
	Reference(keyList_t && keyList) : keys(std::move(keyList)) {};
	Reference(std::initializer_list<Key> init_list) : keys{ std::move(init_list) } {};
public:
	Reference(const Reference &) = default;
	Reference& operator=(const Reference &) = default;

	Reference(Reference &&) noexcept = default;
	Reference& operator=(Reference &&) noexcept = default;
public:
   void add(Key & k) { keys.emplace_back(std::move(k)); }
public:
	const Key & get_key(std::size_t index) const { return keys[index]; };
	const std::size_t size() const { return keys.size(); };
};

};

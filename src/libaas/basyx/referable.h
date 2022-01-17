#pragma once

#include <string>

#include <basyx/util/optional/optional.hpp>

#include <basyx/base/copyable.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>

namespace basyx
{

class Referable : public virtual modeltype_base, 
				  public virtual copyable_base<Referable>
{
public:
	template<typename T>
	using Copyable = Copyable<T, Referable>;
	using parent_t = const Referable *;
private:
	parent_t parent;
	std::string idShort;
	util::optional<std::string> category;
	util::optional<langstringset_t> displayName;
	util::optional<langstringset_t> description;
public:
	Referable(util::string_view idShort);

	Referable(const Referable&) = default;
	Referable(Referable&&) = default;

	Referable & operator=(const Referable&) noexcept = default;
	Referable & operator=(Referable&&) noexcept = default;

	virtual ~Referable() = default;
public:
	util::string_view getIdShort() const;
   void setIdShort(util::string_view idShort);
	
	const util::optional<std::string> & getCategory() const;
	void setCategory(util::string_view category);

	const util::optional<langstringset_t> & getDisplayname() const;
	util::optional<langstringset_t> & getDisplayname();
	void setDisplayname(langstringset_t displayname);

	const util::optional<langstringset_t> & getDescription() const;
	util::optional<langstringset_t> & getDescription();
	void setDescription(langstringset_t displayname);

	parent_t getParent() const { return this->parent; };
	void setParent(const Referable * parent) { this->parent = parent; };
};

};

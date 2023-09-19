#ifndef SPECIFICASSETID_H
#define SPECIFICASSETID_H

#include <basyx/reference.h>
#include <basyx/hassemantics.h>

#include <basyx/util/optional/optional.hpp>
#include <basyx/util/string_view/string_view.hpp>

#include <basyx/identifier.h>
#include <basyx/labelType.h>

#include <string>

namespace basyx
{

class SpecificAssetId : public HasSemantics
{
private:
   LabelType name;
   Identifier value;
	util::optional<Reference> externalSubjectId;
public:
   SpecificAssetId(util::string_view name) : name(name.to_string()) {};

   SpecificAssetId(const SpecificAssetId&) = default;
   SpecificAssetId(SpecificAssetId&&) = default;

   SpecificAssetId & operator=(const SpecificAssetId&) noexcept = default;
   SpecificAssetId & operator=(SpecificAssetId&&) noexcept = default;

   ~SpecificAssetId() = default;
public:
   const std::string getName() const { return name.getLabel(); };
   void setName(util::string_view name) { this->name = name.to_string(); };

   const Identifier & getValue() const { return this->value; };
   void setValue(Identifier value) { this->value = value; }

	const util::optional<Reference> & getExternalSubjectId() const { return this->externalSubjectId; };
	template<typename Ref> void setExternalSubjectId(Ref && ref) { this->externalSubjectId = std::forward<Ref>(ref); };
};
};

#endif /* SPECIFICASSETID_H */

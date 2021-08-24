#pragma once

#include <basyx/submodelelement/submodelelement.h>
#include <basyx/modeltype.h>
#include <basyx/serialization/serializable.h>

namespace basyx
{

class Capability : 
	public SubmodelElement, 
	private ModelType<ModelTypes::Capability>,
	private serialization::Serializable<Capability>
{
public:
	Capability(util::string_view idShort) : SubmodelElement(idShort) {};

	Capability(const Capability&) = default;
	Capability& operator=(const Capability&) = default;

	Capability(Capability&&) = default;
	Capability& operator=(Capability&&) = default;

	~Capability() = default;
};

}
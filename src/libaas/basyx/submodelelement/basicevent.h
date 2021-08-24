#pragma once

#include <basyx/submodelelement/event.h>

#include <basyx/serialization/serializable.h>

namespace basyx
{

class BasicEvent : 
	public Event, 
	private ModelType<ModelTypes::BasicEvent>,
	private serialization::Serializable<BasicEvent>
{
private:
	Reference observed;
public:
	BasicEvent(util::string_view idShort, Reference observed) : Event(idShort), observed(std::move(observed)) {};

	BasicEvent(const BasicEvent&) = default;
	BasicEvent& operator=(const BasicEvent&) = default;

	BasicEvent(BasicEvent&&) = default;
	BasicEvent& operator=(BasicEvent&&) = default;

	~BasicEvent() = default;
public:
	const Reference & getObserved() const { return this->observed; };

	//template<typename T>
	//void setObserved(T && t) { this->observed.emplace(std::forward<T>(t)); };
};

}
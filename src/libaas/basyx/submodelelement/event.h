#pragma once

#include <basyx/submodelelement/submodelelement.h>

#include <util/string_view/string_view.hpp>

namespace basyx
{

	class Event : public SubmodelElement
	{
	public:
		Event(util::string_view idShort) : SubmodelElement(idShort) {};

		Event(const Event&) = default;
		Event& operator=(const Event&) = default;

		Event(Event&&) noexcept = default;
		Event& operator=(Event&&) noexcept = default;

		virtual ~Event() = default;
	};

}
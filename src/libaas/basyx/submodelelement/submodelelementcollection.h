#pragma once

#include <basyx/base/elementcontainer.h>

#include <basyx/submodelelement/submodelelement.h>
#include <basyx/serialization/serializable.h>

#include <basyx/modeltype.h>

#include <basyx/util/string_view/string_view.hpp>
#include <basyx/util/container/container.hpp>

#include <string>

namespace basyx
{

	class SubmodelElementCollection :
		public SubmodelElement,
		private ModelType<ModelTypes::SubmodelElementCollection>,
		private serialization::Serializable<SubmodelElementCollection>
	{
	public:
		using valueList_t = ElementContainer<SubmodelElement>;
		using valueIterator_t = valueList_t::elementIterator_t;
		using constValueIterator_t = valueList_t::elementConstIterator_t;
		using constValuePtr_t = const std::unique_ptr<SubmodelElement>;
	private:
		valueList_t valueList;
		bool ordered;
		bool allowDuplicates;
	public:
		SubmodelElementCollection(util::string_view idShort) : SubmodelElement(idShort) {};

		SubmodelElementCollection(const SubmodelElementCollection&) = default;
		SubmodelElementCollection& operator=(const SubmodelElementCollection&) = default;

		SubmodelElementCollection(SubmodelElementCollection&&) noexcept = default;
		SubmodelElementCollection& operator=(SubmodelElementCollection&&) noexcept = default;

		virtual ~SubmodelElementCollection() = default;

		template<typename... Args>
		SubmodelElementCollection(util::string_view idShort, Args&&... args)
			: SubmodelElement(idShort), valueList(std::forward<Args>(args)...) 
		{};
	public:
		const valueList_t & getSubmodelElements() const { return this->valueList; };
		valueList_t & getSubmodelElements() { return this->valueList; };
		void setSubmodelElements(valueList_t submodelElements) { this->valueList = std::move(valueList); };
	public:
		std::size_t size() const { return this->valueList.size(); };
	};
}

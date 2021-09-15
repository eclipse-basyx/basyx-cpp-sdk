#pragma once

#include <basyx/identifiable.h>

namespace basyx {

class IDataSpecification : public Identifiable
{
public:
	IDataSpecification(util::string_view idShort, util::string_view id) : Identifiable(idShort, id) {};
	IDataSpecification(util::string_view idShort, Identifier identifier) : Identifiable(idShort, std::move(identifier)) {};
	virtual ~IDataSpecification() = default;
};

template<typename DataSpecificationContent>
class DataSpecification : public IDataSpecification
{
public:
	using dataSpecificationContent_t = DataSpecificationContent;
public:
	DataSpecificationContent content;
public:
	DataSpecification(util::string_view idShort, util::string_view id, DataSpecificationContent content)
		: IDataSpecification(idShort, id), content(std::move(content)) {};

	DataSpecification(util::string_view idShort, Identifier identifier, DataSpecificationContent content)
		: IDataSpecification(idShort, std::move(identifier)), content(std::move(content)) {};
private:
	void setContent(DataSpecificationContent content) { this->content = std::move(content); }
public:
	const DataSpecificationContent & getContent() const { return this->content; };
};

}


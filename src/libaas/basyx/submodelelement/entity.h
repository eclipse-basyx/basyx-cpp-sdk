#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/enums/EntityType.h>
#include <basyx/submodelelement/submodelelement.h>
#include <basyx/serialization/serializable.h>
#include <basyx/identifierkeyvaluepair.h>
#include <basyx/modeltype.h>

namespace basyx
{

class Entity : 
	public DataElement, 
	private ModelType<ModelTypes::Entity>,
	private serialization::Serializable<Entity>
{
public:
	using statementList_t = ElementContainer<SubmodelElement>;
private:
	statementList_t statement;
	EntityType entityType;
	util::optional<Reference> globalAssetId;
	util::optional<IdentifierKeyValuePair> specificAssetId;
public:
	Entity(util::string_view idShort) : DataElement(idShort) {};

	Entity(const Entity&) = default;
	Entity& operator=(const Entity&) = default;

	Entity(Entity&&) noexcept = default;
	Entity& operator=(Entity&&) noexcept = default;

	~Entity() = default;
public:
	const util::optional<Reference> & getGlobalAssetId() const { return this->globalAssetId; };
	template<typename Ref> void setGlobalAssetId(Ref && ref) { this->globalAssetId.emplace(std::forward<Ref>(ref); };

	EntityType getEntityType() const { return this->entityType; };
	void setEntityType(EntityType entityType) { this->entityType = entityType; };

	const statementList_t & getStatement() const { return this->statement; };
	statementList_t & getStatement() { return this->statement; };
	void setStatement(statementList_t statement) { this->statement = std::move(statement); };

	const util::optional<IdentifierKeyValuePair> & getSpecificAssetId() const { return this->getSpecificAssetId; };
	void setSpecificAssetId(IdentifierKeyValuePair specificAssetId) { this->specificAssetId = std::move(specificAssetId); };
};

}
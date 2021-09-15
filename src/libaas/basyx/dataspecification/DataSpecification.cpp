//#include <BaSyx/submodel/simple/dataspecification/DataSpecification.h>
//
//namespace basyx {
//namespace submodel {
//namespace simple {
//
//using namespace basyx::submodel::api;
//
//DataSpecification::DataSpecification(const std::string & idShort, const Identifier & identifier)
//	: ident(idShort, identifier)
//	, content(nullptr)
//{}
//
//void DataSpecification::setContent(std::unique_ptr<IDataSpecificationContent> content)
//{
//	this->content = std::move(content);
//};
//
//const std::string & DataSpecification::getIdShort() const
//{
//	return this->ident.getIdShort();
//}
//
//const std::string * const DataSpecification::getCategory() const
//{
//	return this->ident.getCategory();
//}
//
//simple::LangStringSet & DataSpecification::getDescription()
//{
//	return this->ident.getDescription();
//}
//
//const simple::LangStringSet & DataSpecification::getDescription() const
//{
//	return this->ident.getDescription();
//}
//
//IReferable * DataSpecification::getParent() const
//{
//	return this->ident.getParent();
//}
//
//void DataSpecification::setParent(IReferable * parent)
//{
//	this->setParent(parent);
//}
//
//const AdministrativeInformation & DataSpecification::getAdministrativeInformation() const
//{
//	return this->ident.getAdministrativeInformation();
//}
//
//AdministrativeInformation & DataSpecification::getAdministrativeInformation()
//{
//	return this->ident.getAdministrativeInformation();
//}
//
//Identifier DataSpecification::getIdentification() const
//{
//	return this->ident.getIdentification();
//}
//
//bool DataSpecification::hasAdministrativeInformation() const
//{
//	return this->ident.hasAdministrativeInformation();
//}
//
//IDataSpecificationContent & DataSpecification::getContent()
//{
//	return *this->content;
//}
//
//void DataSpecification::setCategory(const std::string &category)
//{
//  this->ident.setCategory(category);
//}
//
//simple::Reference DataSpecification::getReference() const
//{
//	return this->ident.getReference();
//};
//
//
//}
//}
//}

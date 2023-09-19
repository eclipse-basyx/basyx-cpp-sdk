#ifndef ADMINISTRATIVEINFORMATION_H
#define ADMINISTRATIVEINFORMATION_H

#include <string>

#include <basyx/util/optional/optional.hpp>
#include <basyx/langstringset.h>
#include <basyx/key.h>
#include <basyx/versionRevisionType.h>
#include <basyx/reference.h>
#include <basyx/identifier.h>
#include <basyx/semantics/hasDataSpecification.h>

namespace basyx
{

class AdministrativeInformation: public HasDataSpecification
{
public:
   using VersionType = basyx::VersionRevisionType;
   using RevisionType = basyx::VersionRevisionType;
private:
   util::optional<VersionType> version;
   util::optional<RevisionType> revision;
   util::optional<Reference> creator;
   util::optional<Identifier> templateId;
public:
	AdministrativeInformation() = default;
	AdministrativeInformation(util::string_view version);
	AdministrativeInformation(util::string_view version, util::string_view revision);

	AdministrativeInformation(const AdministrativeInformation&) = default;
	AdministrativeInformation(AdministrativeInformation&&) = default;

	AdministrativeInformation & operator=(const AdministrativeInformation&) = default;
	AdministrativeInformation & operator=(AdministrativeInformation&&) = default;

	~AdministrativeInformation() = default;
public:
   const util::optional<VersionType> getVersion() const { return version; };
   void setVersion(util::string_view version) { this->version = version; };

   const util::optional<RevisionType> getRevision() const { return revision; };
   void setRevision(util::string_view revision) { this->revision = revision; };

   const util::optional<Reference> & getCreator() const { return creator; };
   void setCreator(Reference & creator) { this->creator = std::move(creator); };

   const util::optional<Identifier> & getTemplateId() const { return templateId; };
   void setTemplateId(Identifier templateId) {
      this->templateId = std::move(templateId);
   };
};

};

#endif /* ADMINISTRATIVEINFORMATION_H */

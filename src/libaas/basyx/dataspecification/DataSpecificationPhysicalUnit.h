#ifdef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATIONPHYSICALUNIT_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATIONPHYSICALUNIT_H

#include <BaSyx/submodel/api_v2/dataspecification/IDataSpecificationPhysicalUnit.h>
#include <BaSyx/submodel/simple/common/LangStringSet.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace submodel {
namespace simple {

class DataSpecificationPhysicalUnit
    : public api::IDataSpecificationPhysicalUnit
{
private:
  LangStringSet definition;
  std::string unitName;
  std::string unitSymbol;
  std::string siNotation;
  std::string siName;
  std::string dinNotation;
  std::string eceName;
  std::string eceCode;
  std::string nistName;
  std::string sourceOfDefinition;
  std::string conversionFactor;
  std::string registrationAuthorityId;
  std::string supplier;

public:
  DataSpecificationPhysicalUnit(const std::string & unitName, const std::string & unitSymbol, const api::ILangStringSet & definition);

  const std::string & getUnitName() const override;
  void setUnitName(const std::string & unitName) override;

  const std::string & getUnitSymbol() const override;
  void setUnitSymbol(const std::string & unitSymbol) override;

  LangStringSet & getDefinition() override;
  void setDefinition(const api::ILangStringSet & definition) override;

  const std::string * getSiNotation() const override;
  void setSiNotation(const std::string & siNotation) override;

  const std::string * getSiName() const override;
  void setSiName(const std::string & siName) override;

  const std::string * getDinNotation() const override;
  void setDinNotation(const std::string & dinNotation) override;

  const std::string * getEceName() const override;
  void setEceName(const std::string & eceName) override;

  const std::string * getEceCode() const override;
  void setEceCode(const std::string & eceCode) override;

  const std::string * getNistName() const override;
  void setNistName(const std::string & nistName) override;

  const std::string * getSourceOfDefinition() const override;
  void setSourceOfDefinition(const std::string & sourceOfDefinition) override;

  const std::string * getConversionFactor() const override;
  void setConversionFactor(const std::string & conversionFactor) override;

  const std::string * getRegistrationAuthorityId() const override;
  void setRegistrationAuthorityId(const std::string & registrationAuthorityId) override;

  const std::string * getSupplier() const override;
  void setSupplier(const std::string & supplier) override;

};

}
}
}
#endif /* BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATIONPHYSICALUNIT_H */

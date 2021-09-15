#ifdef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUEREFERENCEPAIR_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUEREFERENCEPAIR_H

#include <BaSyx/submodel/simple/reference/Reference.h>
#include <BaSyx/shared/object/object_type.h>
#include <BaSyx/shared/object.h>

#include <string>
#include <BaSyx/submodel/map_v2/reference/Reference.h>

namespace basyx {
namespace submodel {
namespace simple {

class ValueReferencePair
{
private:
	std::string value;
	Reference valueId;

public:
	ValueReferencePair() = default;
	ValueReferencePair(const ValueReferencePair & other) = default;
	ValueReferencePair(ValueReferencePair && other) noexcept = default;

	ValueReferencePair & operator=(const ValueReferencePair & other) = default;
	ValueReferencePair & operator=(ValueReferencePair && other) noexcept = default;

	ValueReferencePair(const std::string & value, const api::IReference & valueId)
		: value(value), valueId(valueId)
	{};

	~ValueReferencePair() = default;
public:
	const std::string & getValue() const { return this->value; };
	const api::IReference & getValueId() const { return this->valueId; };
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUEREFERENCEPAIR_H */

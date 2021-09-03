#pragma once

#include <basyx/enums/ModelTypes.h>

#ifdef _MSC_VER
#pragma warning(disable : 4250)
#endif

namespace basyx
{

class modeltype_base
{
public:
	virtual ModelTypes get_model_type() const = 0;
	virtual ~modeltype_base() = default;
};

template<ModelTypes modelType>
class ModelType : public virtual modeltype_base
{
public:
	constexpr ModelTypes get_model_type() const override { return modelType; };
};

};

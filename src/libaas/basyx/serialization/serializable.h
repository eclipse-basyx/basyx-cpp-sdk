#pragma once


#include <basyx/serialization/serializable_base.h>
#include <basyx/serialization/json/serializer.h>

namespace basyx::serialization
{

template<typename T>
class Serializable : public virtual serializable_base
{
public:
	void serialize_json(nlohmann::json & json) const override
	{
		json::serialize_helper<T>(json, *static_cast<const T*>(this));
	};
};

};
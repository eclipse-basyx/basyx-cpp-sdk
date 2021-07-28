#pragma once


#include <basyx/serialization/json/serializer.h>

namespace basyx::serialization
{
class serializable_base
{
public:
	virtual void serialize_json(json::json_t & json) = 0;

	virtual ~serializable_base() = default;
};

template<typename T>
class Serializable : public virtual serializable_base
{
public:
	virtual void serialize_json(json::json_t & json)
	{
		json::serialize_helper<T>(*static_cast<T*>(this));
	};
};

};
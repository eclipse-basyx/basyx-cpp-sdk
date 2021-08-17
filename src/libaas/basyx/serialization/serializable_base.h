#pragma once

#include <nlohmann/json.hpp>

namespace basyx::serialization
{

class serializable_base
{
public:
	virtual void serialize_json(nlohmann::json & json) const {};

	virtual ~serializable_base() = default;
};

};
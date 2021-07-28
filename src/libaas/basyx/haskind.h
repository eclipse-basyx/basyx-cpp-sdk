#pragma once


namespace basyx
{
enum class ModelingKind
{
	Template,
	Instance
};

class HasKind
{
public:
	ModelingKind kind = ModelingKind::Instance;
};

};

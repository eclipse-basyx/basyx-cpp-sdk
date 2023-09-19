#pragma once

#include <basyx/enums/ModelingKind.h>

namespace basyx
{
class HasKind
{
private:
   ModelingKind kind = ModelingKind::Instance;
public:
   void setKind(ModelingKind kind) { this->kind = kind; }
   const ModelingKind getKind() const { return kind; }
};

};

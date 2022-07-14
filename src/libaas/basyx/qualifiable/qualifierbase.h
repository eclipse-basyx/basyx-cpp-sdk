#ifndef QUALIFIERBASE_H
#define QUALIFIERBASE_H

#include <basyx/modeltype.h>
#include <basyx/base/valuetypedefs.h>

#include <basyx/qualifiable/qualifiable_fwd.h>

namespace basyx {

class qualifier_base : public virtual modeltype_base {
public:
   qualifier_base() = default;
   virtual ~qualifier_base() = default;
public:
   virtual util::string_view getValueType() const = 0;
};

class QualifierBase: public ModelType<ModelTypes::Qualifier>, public qualifier_base {
   basyx::detail::datatypes type;
public:
   QualifierBase(basyx::detail::datatypes type): type(type) {}
   ~QualifierBase() = default;

   util::string_view getValueType() const override { return basyx::detail::toString(type); }
   basyx::detail::datatypes getValueTypeEnum() { return type; }

   template <typename DataType>
   Qualifier<DataType>* cast() { return dynamic_cast<Qualifier<DataType>*>(this); };
};
}

#endif // QUALIFIERBASE_H

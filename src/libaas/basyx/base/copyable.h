#pragma once

#include <basyx/base/copyable_base.h>

#include <memory>

namespace basyx {

template <typename T, typename CopyBase>
class Copyable : public virtual copyable_base<CopyBase> 
{
//static_assert(std::is_convertible<T*, CopyBase*>::value, "Type 'T' is not based on 'CopyBase'!");
public:
    using copyable_base_t = copyable_base<CopyBase>;
public:
    typename copyable_base_t::copy_base_ptr_t copy_base() const override { 
		return std::make_unique<T>(*(const T*)(this)); 
	};
};

}

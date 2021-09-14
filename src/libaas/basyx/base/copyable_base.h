#pragma once

#include <memory>

#include <exception>

namespace basyx
{

template<typename T>
class copyable_base
{
public:
	using copy_base_t = T;
	using copy_base_ptr_t = std::unique_ptr<T>;
protected:
	virtual ~copyable_base() {};
private:
	virtual std::unique_ptr<T> copy_base() const { throw std::exception{}; /* ToDo: make pure virtual */};
public:
	template<typename U = T>
	std::unique_ptr<U> copy() const;
};

template<typename T>
template<typename U>
inline std::unique_ptr<U> copyable_base<T>::copy() const 
{
	// create a copy of this object, creating a pointer to base type
	auto copy_ptr = this->copy_base();
	
	// check if base type can be upcasted to requested type,
	// return nullptr if not compatible
	auto casted_ptr = dynamic_cast<U*>(copy_ptr.get());
	if (casted_ptr == nullptr)
		return nullptr;

	// At this point we are safe to upcast the unique_ptr
	// create a new unique_ptr to the requested type, by releasing control from base unique_ptr
	return std::unique_ptr<U>((U*)(copy_ptr.release()));
};


};
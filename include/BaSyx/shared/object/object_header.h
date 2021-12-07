/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJECT_HEADER_H
#define BASYX_SHARED_OBJECT_OBJECT_HEADER_H

#include <cstddef>
#include <memory>
#include <string>
#include <typeinfo>

#include <nlohmann/json.hpp>

#include <BaSyx/shared/object/obj_error.h>
#include <BaSyx/shared/object/obj_placeholder.h>

#include <vector>
#include <unordered_map>

namespace basyx {
// basyx::object
// Type-safe wrapper class for holding vab primitives
// The actual value is passed at construction time and stored inside a templated placeholder
// Stores its held value inside its own unique_ptr, thus resource will be freed automatically at destruction time
// Values can be retrieved type-safely using the basyx::object_cast function

	class object 
	{
	public:
		using error = basyx::detail::error;
	public: // Type definitions
		template<typename T>
		using list_t = std::vector<T>;

		template<typename T>
		using hash_map_t = std::unordered_map<std::string, T>;

		using object_list_t = list_t<basyx::object>;
		using object_map_t = object::hash_map_t<basyx::object>;

		using function_t = std::function<basyx::object(basyx::object*)>;	
	public:	// Constructors
		object();
		object(const char *);

		template <typename T>
		object(const T& t);

		//template<typename T>
		//object(T && t)
		//	: content{ std::make_shared< Holder< typename std::remove_cv< typename std::decay<const T>::type>::type>>(std::forward<T>(t)) }
		//{};

		object(const object& other) = default;
		object& operator=(const object& other) = default;

		object(object&& other) = default;
		object& operator=(object&& other) = default;
	
	public: // Generic functions
		const std::type_info& type() const
		{
			return content->type();
		}

		std::string Typename() const
		{
			return std::string{ content->type().name() };
		}

		basyx::type::objectType GetObjectType() const { return this->content->object_type(); };
		basyx::type::valueType GetValueType() const { return this->content->value_type(); };

		template <typename T>
		bool InstanceOf() const noexcept
		{
			if (this->content == nullptr)
				return false;

			if (this->IsError())
				return false;

			return this->content->object_type() == basyx::type::basyx_type<T>::object_type
				&& this->content->value_type() == basyx::type::basyx_type<T>::value_type;
		};

		template <typename T>
		T Get()
		{
			return object_cast<T>(*this);
		};

		std::string & GetStringContent()
		{
		  return this->Get<std::string&>();
		}

		template <typename T>
		T* GetPtr()
		{
			// using non_ptr_t = std::remove_pointer<T>::type;
			return object_cast_ptr<T>(this);
		};

		bool IsInvokable() const noexcept
		{
			return this->GetObjectType() == basyx::type::objectType::Function;
		};

		bool IsNull() const noexcept
		{
			return this->content == nullptr || this->InstanceOf<std::nullptr_t>() || this->IsError();
		}

		bool IsError() const noexcept
		{
			return this->GetObjectType() == basyx::type::objectType::Error;
		};

		error getError() const;
		const std::string & getErrorMessage() const;
	private: // Private type definitions
		// PlaceHolder:
		// Interface class for the actual value to be stored by the object object
		// Allows introspection of type
		using PlaceHolder = basyx::detail::objPlaceHolder;
	private:
		// The actual object holding the value
		//	std::unique_ptr<PlaceHolder> content;
		std::shared_ptr<PlaceHolder> content;		
	public:
		bool insert(basyx::object obj);

		template<typename T>
		bool insert(const T & t);

		template<typename T>
		bool insertKey(const std::string & key, const T & t, bool override = true);

		std::size_t size();

		template<typename T>
		bool remove(const T & t);
		bool remove(basyx::object & obj);
		bool removeProperty(const std::string & propertyName);

		bool hasProperty(const std::string & propertyName);
		basyx::object getProperty(const std::string & propertyName);

		basyx::object invoke();
		basyx::object invoke(basyx::object & object);

		bool empty();
	public: // Object casting functions
		// object_cast:
		// Cast a basyx::object object to the desired type
		// If the cast itself is not allowed on the held object, basyx::bad_object_cast exception will be thrown
		template <typename T>
		static T object_cast(object& operand);

		template <typename T>
		static T* object_cast_ptr(object * operand);

		template <typename T>
		static T* object_cast(object* operand) noexcept;

		template <typename T>
		static inline const T* object_cast(const object* operand);
	public: // Factories
		static object make_null();

		static object make_error(error error_code);
		static object make_error(error error_code, const std::string & message);

		template<typename T>
		static object make_object_ref(T* t);

		template<typename T, typename... Args>
		static object make_list(Args && ... args);

		template<typename... Args>
		static object make_object_list(Args && ... args);

		template<typename T>
		static object make_list(std::initializer_list<T>);

		template<typename... Args>
		static object make_map(Args && ... args);

		template<typename... Args>
		static object make_function(Args && ... args);
    public: // operator overloads
		template <typename T>
		bool operator!=(const T& rhs) const;

        template <typename T>
		bool operator==(const T& rhs) const;

		bool operator==(const basyx::object& rhs) const;
	public:
		friend void to_json(nlohmann::json& json, const basyx::object& object);
		friend struct std::hash<basyx::object>;
	};

	void to_json(nlohmann::json& json, const basyx::object& object);
};

#include <functional>

namespace std
{
	template<>
	struct hash<basyx::object>
	{
		std::size_t operator()(basyx::object const & o) const noexcept
		{
			return reinterpret_cast<std::size_t>(o.content->get_address());
		};
	};
};

#endif /* BASYX_SHARED_OBJECT_OBJECT_HEADER_H */

#ifndef UTIL_OPTIONAL_HPP_
#define UTIL_OPTIONAL_HPP_

#include <array>
#include <exception>

namespace basyx::util {

// C++11 backported version of std::optional
// See: https://en.cppreference.com/w/cpp/utility/optional for further details

class bad_optional_access : public std::exception {};

struct nullopt_t {
	explicit constexpr nullopt_t(int) {};
};

inline constexpr nullopt_t nullopt{0};

template<typename T>
class optional
{
private:
	struct _internals_t {
		std::array<uint8_t, sizeof(T)> _data;
		bool _empty = true;
#if defined(DEBUG) || defined(_DEBUG)
		T* _val_view;
		constexpr _internals_t() noexcept : _data() {
			_val_view = reinterpret_cast<T*>(&_data[0]);
			int j = 2;
		};
		constexpr _internals_t(const _internals_t& rhs) noexcept
			: _empty(rhs._empty), _data(rhs._data) {
			_val_view = reinterpret_cast<T*>(&_data[0]);
			int j = 2;
		};
		constexpr _internals_t& operator=(const _internals_t& rhs) noexcept { 
			_empty = rhs._empty; _data = rhs._data;
			_val_view = reinterpret_cast<T*>(&_data[0]);
			return *this;
		};
		constexpr _internals_t(_internals_t&& rhs) noexcept
			: _empty(rhs._empty), _data(std::move(rhs._data)) {
			rhs._empty = true;
			_val_view = reinterpret_cast<T*>(&_data[0]);
			int j = 2;
		};
		constexpr _internals_t& operator=(_internals_t&& rhs) noexcept {
			_empty = rhs._empty; _data = std::move(rhs._data);
			rhs._empty = true;
			_val_view = reinterpret_cast<T*>(&_data[0]);
			return *this;
		};
#endif
	} _internals;
private:
	constexpr void _copy_internal(const optional& rhs) {
		this->_internals._empty = rhs._internals._empty;
		if (rhs.has_value()) {
			this->emplace(rhs.value());
		}
	};
public:
	constexpr optional() noexcept = default;

	constexpr optional(const optional& rhs) { this->_copy_internal(rhs); };
	constexpr optional& operator=(const optional& rhs) { this->_copy_internal(rhs); return *this; };

	constexpr optional(optional&&) noexcept = default;
	constexpr optional& operator=(optional&&) noexcept = default;

	~optional() {
		if constexpr (!std::is_trivially_destructible<T>::value) {
			if (this->has_value()) {
				(*this)->~T();
			}
		};
		this->_internals._empty = true;
	};
public:
	template <class U = T>
	constexpr optional& operator=(U&& value) {
		this->emplace(std::forward<U>(value));
		return *this;
		//T * t = new (_internals._data.data()) T(std::forward<U>(value));
		//this->_internals._empty = false;
	};

	template <class U = T>
	constexpr optional(U&& value) {
		this->emplace(std::forward<U>(value));
		//T * t = new (_internals._data.data()) T(std::forward<U>(value));
		//this->_internals._empty = false;
	};
public:
	// constructs the contained value in-place
	template<typename... Args>
	void emplace(Args&&... args) {
		this->reset();
		T * t = new (_internals._data.data()) T(std::forward<Args...>(args...));
		this->_internals._empty = false;
	};

	// destroys any contained value
	constexpr void reset() noexcept {
		if constexpr (!std::is_trivially_destructible<T>::value) {
			if (this->has_value()) {
				(*this)->~T();
			}
		};

		this->_internals._empty = true;
	};
public:
	// returns the contained value
	constexpr T& value() & 
	{ 
		if (!this->has_value())
			throw new bad_optional_access();

		return reinterpret_cast<T&>(*_internals._data.data());
	}
	// returns the contained value
	constexpr const T& value() const & 
	{
		if (!this->has_value())
			throw new bad_optional_access();

		return reinterpret_cast<const T&>(*_internals._data.data());
	}
	// returns the contained value
	constexpr T&& value() && 
	{
		if (!this->has_value())
			throw new bad_optional_access();

		return reinterpret_cast<T&&>(*_internals._data.data());
	};
	// returns the contained value
	constexpr const T&& value() const && 
	{
		if (!this->has_value())
			throw new bad_optional_access();

		return reinterpret_cast<const T&&>(*_internals._data.data());
	};
public:
	// checks whether the object contains a value
	constexpr explicit operator bool() const noexcept { return !_internals._empty; }

	// checks whether the object contains a value
	constexpr bool has_value() const noexcept { return !_internals._empty; }
public:
	// accesses the contained value
	constexpr const T* operator->() const { return reinterpret_cast<const T*>(_internals._data.data()); }
	// accesses the contained value
	constexpr T* operator->() { return reinterpret_cast<T*>(_internals._data.data()); }
	// accesses the contained value
	constexpr const T& operator*() const& { return reinterpret_cast<const T&>(*_internals._data.data()); }
	// accesses the contained value
	constexpr T& operator*() & { return reinterpret_cast<T&>(*_internals._data.data()); }
	// accesses the contained value
	constexpr const T&& operator*() const&& { return reinterpret_cast<const T&&>(*_internals._data.data()); }
	// accesses the contained value
	constexpr T&& operator*() && { return reinterpret_cast<T&&>(*_internals._data.data()); }
};

template<class T>
constexpr bool operator==(const optional<T>& opt, util::nullopt_t) noexcept {
	return !opt.has_value();
};

template<class T>
constexpr bool operator==(util::nullopt_t, const optional<T>& opt) noexcept {
	return !opt.has_value();
};

template<class T>
constexpr bool operator!=(const optional<T>& opt, util::nullopt_t) noexcept {
	return opt.has_value();
};

template<class T>
constexpr bool operator!=(util::nullopt_t, const optional<T>& opt) noexcept {
	return opt.has_value();
};


}

#endif
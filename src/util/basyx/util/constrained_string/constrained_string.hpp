#ifndef BASYX_UTIL_CONSTRAINED_STRING_H
#define BASYX_UTIL_CONSTRAINED_STRING_H

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {
namespace util {

class NullConstraint
{
public:
	bool operator()(basyx::util::string_view sv) { return true; };
};

template<std::size_t Min = 1, std::size_t Max = 2048, typename ConstraintT = NullConstraint, char FillChar = '-'>
class constrained_string
{
public:
	using constraint_t = ConstraintT;

public:
	using iterator = std::string::iterator;
	using reverse_iterator = std::string::reverse_iterator;
	using const_iterator = std::string::const_iterator;
	using const_reverse_iterator = std::string::const_reverse_iterator;

public:
	static constexpr char fill_char = FillChar;

private:
	constraint_t constraint;
	std::string content;

public:
	static constexpr std::size_t min = Min;
	static constexpr std::size_t max = Max;

public:
	// Constructors
	explicit constrained_string() noexcept {};
	constrained_string(const char* c_str) noexcept { this->assign(c_str); }
	constrained_string(const std::string& string) noexcept { this->assign(string); };
	constrained_string(util::string_view sv) noexcept { this->assign(sv); }

	// Copy constructors
	template<std::size_t Min_ = Min, std::size_t Max_ = Max, typename ConstraintT_ = ConstraintT, char FillChar_ = FillChar>
	constrained_string(const constrained_string<Min_, Max_, ConstraintT_, FillChar_>& rhs) noexcept {
		this->assign(rhs.str());
	};

	template<std::size_t Min_ = Min, std::size_t Max_ = Max, typename ConstraintT_ = ConstraintT, char FillChar_ = FillChar>
	constrained_string& operator=(const constrained_string<Min_, Max_, ConstraintT_, FillChar_>& rhs) noexcept {
		this->assign(rhs.str());
		return *this;
	};

	// Move constructors
	template<std::size_t Min_ = Min, std::size_t Max_ = Max, typename ConstraintT_ = ConstraintT, char FillChar_ = FillChar>
	constrained_string(constrained_string<Min_, Max_, ConstraintT_, FillChar_> && rhs) noexcept {
		this->assign(std::move(rhs.content));
	};

	template<std::size_t Min_ = Min, std::size_t Max_ = Max, typename ConstraintT_ = ConstraintT, char FillChar_ = FillChar>
	constrained_string& operator=(constrained_string<Min_, Max_, ConstraintT_, FillChar_>&& rhs) noexcept {
		this->assign(std::move(rhs.content));
		return *this;
	};

	// Assignment operators
	constrained_string& operator=(const char* c_str) noexcept { this->assign(c_str); return *this; }
	constrained_string& operator=(const std::string& string) noexcept { this->assign(string); return *this; };
	constrained_string& operator=(util::string_view sv) noexcept { this->assign(sv); return *this; }

public:
	bool check_constraint(util::string_view sv) {
		//if (sv.size() < Min || sv.size() > Max)
		//	return false;
		
		return constraint(sv);
	};

private:
	void assign_fill(util::string_view sv) {
		this->content = sv.to_string();

		if (sv.size() > Max) {
			this->content.resize(max, fill_char);
		} 
		else if (sv.size() < Min) {
			this->content.resize(min, fill_char);
		};
	};

public:
	void assign(util::string_view sv) {
		if (check_constraint(sv)) {
			this->assign_fill(sv);
		};
	};

public:
	inline std::size_t size() const { return this->content.size(); };
	inline const char* data() const { return this->content.data(); };
	inline bool empty() const { return this->content.empty(); };

public:
	inline const std::string& str() const { return this->content; };
	inline operator const std::string& () const { return this->str(); };

public:
	inline iterator begin() noexcept { return this->content.begin(); };
	inline const_iterator begin() const noexcept { return this->content.cbegin(); };

	inline iterator end() noexcept { return this->content.end(); };
	inline const_iterator cend() const noexcept { return this->content.end(); };

public:
	inline reverse_iterator rbegin() noexcept { return this->content.rbegin(); };
	inline const_reverse_iterator crbegin() const noexcept { return this->content.crbegin(); };

	inline reverse_iterator rend() noexcept { return this->content.rend(); };
	inline const_reverse_iterator crend() const noexcept { return this->content.crend(); };
};


// Comparison operators
template<std::size_t Min, std::size_t Max, typename ConstraintT, char FillChar>
inline bool operator==(const constrained_string<Min, Max, ConstraintT, FillChar>& lhs, util::string_view sv) {
	return lhs.str().compare(0, sv.size(), sv.data()) == 0;
};

template<std::size_t Min, std::size_t Max, typename ConstraintT, char FillChar>
inline bool operator!=(const constrained_string<Min, Max, ConstraintT, FillChar>& rhs, util::string_view sv) {
	return !(rhs == sv);
};

// Stream operator
template<std::size_t Min, std::size_t Max, typename ConstraintT, char FillChar>
std::ostream& operator <<(std::ostream& os, const constrained_string<Min, Max, ConstraintT, FillChar>& constr_str) {
	os << constr_str.str();
	return os;
}

}
}

#endif
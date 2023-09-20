#ifndef BASYX_UTIL_CONSTRAINED_STRING_REGEX_CHECKER_H
#define BASYX_UTIL_CONSTRAINED_STRING_REGEX_CHECKER_H

#include <regex>

namespace basyx {
namespace util {

template<typename Holder>
class RegExChecker
{
public:
	bool check(basyx::util::string_view sv) {
		std::cmatch matches;

		return std::regex_match(sv.begin(), sv.end(), matches, Holder::regex);
	};

	bool operator()(basyx::util::string_view sv) { return check(sv); };
};

}
}

#endif
#ifndef QUALIFIERKIND_CPP
#define QUALIFIERKIND_CPP

#include <algorithm>
#include <memory>
#include <string>
#include <array>

#include <basyx/enums/QualifierKind.h>

namespace basyx {

using enum_pair_t = std::pair<const char*, QualifierKind>;

static const std::array<enum_pair_t, 3> string_to_enum = {
    std::make_pair("ValueQualifier",  QualifierKind::ValueQualifier),
    std::make_pair("ConceptQualifier", QualifierKind::ConceptQualifier),
    std::make_pair("TemplateQualifier", QualifierKind::TemplateQualifier),
};

QualifierKind QualifierKind_::from_string(const std::string &name) {
   auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(),
                            [&name](const enum_pair_t & pair) {
        return !name.compare(pair.first);
  });
   return pair->second;
}

const char * QualifierKind_::to_string(QualifierKind value) {
   auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(),
                            [value](const enum_pair_t & pair) {
      return value == pair.second;
   });
   return pair->first;
}

}



#endif // QUALIFIERKIND_CPP



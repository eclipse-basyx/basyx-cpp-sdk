#ifndef QUALIFIERKIND_H
#define QUALIFIERKIND_H

#include <string>

namespace basyx {

enum class QualifierKind {
   ValueQualifier,
   ConceptQualifier,
   TemplateQualifier,
};

class QualifierKind_
{
public:
    static QualifierKind from_string(const std::string & name);
    static const char * to_string(QualifierKind value);
};
}

#endif // QUALIFIERKIND_H

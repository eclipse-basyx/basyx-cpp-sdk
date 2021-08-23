#ifndef BASYX_SUBMODEL_ENUMERATIONS_KEYTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_KEYTYPE_H

#include <basyx/base/basyx_enum_base.h>

#include <string>

namespace basyx {

struct IdentifierType : public basyx_enum_base
{
private:
	using basyx_enum_base::basyx_enum_base;
public:
	static const IdentifierType Custom;
	static const IdentifierType IRDI;
	static const IdentifierType IRI;
};

struct LocalKeyType : public basyx_enum_base
{
private:
	using basyx_enum_base::basyx_enum_base;
public:
	static const LocalKeyType IdShort;
	static const LocalKeyType FragmentId;
};

struct KeyType : public basyx_enum_base
{
public:
	using IdentifierType = basyx::IdentifierType;
	using LocalKeyType = basyx::LocalKeyType;
private:
	using basyx_enum_base::basyx_enum_base;
public:
	KeyType(LocalKeyType rhs) : basyx_enum_base{ rhs } {};
	KeyType(IdentifierType rhs) : basyx_enum_base{ rhs } {};
};

class KeyType_
{
public:
    static KeyType from_string(const std::string & name);
    static const char * to_string(KeyType value);
};

class IdentifierType_
{
public:
	static IdentifierType from_string(const std::string & name);
	static const char * to_string(IdentifierType value);
};

class LocalKeyType_
{
public:
	static LocalKeyType from_string(const std::string & name);
	static const char * to_string(LocalKeyType value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_KEYTYPE_H */

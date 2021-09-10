#ifndef BASYX_SUBMODEL_ENUMERATIONS_KEYTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_KEYTYPE_H

#include <util/string_view/string_view.hpp>

namespace basyx {

	enum class KeyType {
		Custom,
		IRI,
		IRDI,
		IdShort,
		FragmentId
	};

	class KeyType_
	{
	public:
		static KeyType from_string(util::string_view str_v);
		static const char * to_string(KeyType id);
	public:
		static constexpr KeyType from_id(util::string_view id)
		{
			// If begins with an URI schema, assume it's an IRDI
			if ((id.substr(0, 7) == "http://") || (id.substr(0, 8) == "https://") || (id.substr(0, 6) == "urn://"))
				return KeyType::IRI;

			// check if it is an ISO/IEC 11179-6 eClass identifier, see: https://wiki.eclass.eu/wiki/IRDI
			// e.g. 0173-1#02-AAR972#002
			else if (id.length() == 20 && id[4] == '-' && id[6] == '#' && id[9] == '-' && id[16] == '#')
				return KeyType::IRDI;

			// otherwise, assume it's a Custom identifier
			return KeyType::Custom;
		};
	};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_KEYTYPE_H */

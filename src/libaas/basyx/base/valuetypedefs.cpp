#include <basyx/base/valuetypedefs.h>

namespace basyx::detail {

util::string_view toString(const datatypes valuetype) {
   switch (valuetype) {
   case Boolean:
      return "boolean";
   case Byte:
      return "byte";
   case UnsignedByte:
      return "unsignedByte";
   case Short:
      return "short";
   case UnsignedShort:
      return "unsignedShort";
   case Integer:
      return "int";
   case UnsignedInteger:
      return "unsignedInt";
   case Long:
      return "long";
   case UnsignedLong:
      return "unsignedLong";
   case Float:
      return "float";
   case Double:
      return "double";
   case String:
      return "string";
   default:
      /* unreachable */
      return "string";
   }
}
}

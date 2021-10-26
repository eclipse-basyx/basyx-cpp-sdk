#ifndef DESERIALIZER_PRIV_H
#define DESERIALIZER_PRIV_H

#include <basyx/base/token.h>

namespace basyx::serialization::priv {

using namespace basyx::base;

class Deserializer {
public:
   Deserializer() {};
public:
   Token<Deserializer> getToken() { return Token<Deserializer>(); }
};
}

#endif // DESERIALIZER_PRIV_H

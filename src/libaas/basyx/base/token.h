#ifndef TOKEN_H
#define TOKEN_H

namespace basyx::base {

template<typename T>
class Token {
private:
   friend T;
   Token() {};
};
}

#endif // TOKEN_H

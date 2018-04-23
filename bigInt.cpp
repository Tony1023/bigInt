#include "bigInt.h"
#include <cstdlib>
#include <iostream>

BigInt::BigInt() 
  : neg_(false) { }

BigInt::BigInt(const BigInt &i)
  : P_Int(i), neg_(i.neg_) { }

BigInt::BigInt(int i) 
  : P_Int(abs(i)) {
  neg_ = i > 0? false: true;
}

BigInt& BigInt::operator=(const BigInt& rhs) {
  neg_ = rhs.neg_;
  P_Int::operator=(rhs);
  return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt &rhs) {
  if (rhs.neg_)
    os << '-';
  size_t len = rhs.size();
	for (size_t j = 0; j < len; ++j)
		os << (int) rhs.at(len - j - 1);
	return os;
}


#include "bigInt.h"
#include <cstdlib>
#include <iostream>

BigInt::BigInt() 
  : neg_(false) { }

BigInt::BigInt(const BigInt &i)
  : P_Int(i), neg_(i.neg_) { }

BigInt::BigInt(int i) 
  : P_Int(static_cast<unsigned>(abs(i))) {
  neg_ = i < 0? true: false;
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

BigInt& BigInt::operator++() {
  if (neg_)
    P_Int::operator--();
  else
    P_Int::operator++();
  if (P_Int::operator==(0))
    neg_ = false;
  return *this;
}

BigInt BigInt::operator++(int o) {
  BigInt copy(*this);
  this->operator++();
  return copy;
}

BigInt& BigInt::operator--() {
  // if non-positive, then add to the abs value and set to negative
  if (neg_ || P_Int::operator==(0)) {
    P_Int::operator++();
    neg_ = false;
  }
  else {
    P_Int::operator--();
  }
  return *this;
}

BigInt BigInt::operator--(int o) {
  BigInt copy(*this);
  this->operator--();
  return copy;
}

/**
 * Comparisons
 */
bool BigInt::operator==(const BigInt &rhs) const {
  if (neg_ != rhs.neg_) return false;
  if (!P_Int::operator==(rhs)) return false;
  return true;
}

bool BigInt::operator!=(const BigInt &rhs) const {
  return !operator==(rhs);
}

bool BigInt::operator<(const BigInt &rhs) const {
  // Different signs
  if (neg_ && !rhs.neg_) return true;
  else if (!neg_ && rhs.neg_) return false;
  if (!neg_)
    return P_Int::operator<(rhs);
  else
    return P_Int::operator>(rhs);
}

bool BigInt::operator>(const BigInt &rhs) const {
  return !(operator<(rhs) || operator==(rhs));
}

bool BigInt::operator<=(const BigInt &rhs) const {
  return (operator<(rhs) || operator==(rhs));
}

bool BigInt::operator>=(const BigInt &rhs) const {
  return !operator<(rhs);
}

// below are friend functions
bool operator>(int lhs, const BigInt &rhs) {
  return rhs.operator<(lhs);
}

bool operator<(int lhs, const BigInt &rhs) {
  return rhs.operator>(lhs);
}

bool operator>=(int lhs, const BigInt &rhs) {
  return rhs.operator<=(lhs);
}

bool operator<=(int lhs, const BigInt &rhs) {
  return rhs.operator>=(lhs);
}

bool operator==(int lhs, const BigInt &rhs) {
  return rhs.operator==(lhs);
}

bool operator!=(int lhs, const BigInt &rhs) {
  return rhs.operator!=(lhs);
}
/**
 * Comparisons end
 */


#include "p_int.h"
#include "negativeExcept.h"
#include <string>
#include <iostream>
#include <cctype>
#include <limits>


/**
 * Public functions
 */

P_Int::P_Int() :std::vector<char> ({0}) {};

P_Int::P_Int(const P_Int &i) :std::vector<char>(i) {};

P_Int::P_Int(unsigned int i) 
	:std::vector<char>(0) {
	if (i == 0) {
		push_back(0);
		return;
	}
	while (i > 0) {
		push_back(i % 10);
		i /= 10;
	}
}

P_Int& P_Int::operator=(const P_Int &rhs) {
	std::vector<char>::operator=(rhs);
	return *this;
}

size_t P_Int::length() const {
	return size();
}


/**
 * Overloaded comparison operators
 */

bool P_Int::operator>=(const P_Int &rhs) const {
	if (size() > rhs.size()) return true;
	else if (size() < rhs.size()) return false;
	size_t len = size();
	for (size_t i = 0; i < len; ++i) {
		if (at(len - i - 1) < rhs.at(len - i - 1))
			return false;
		else if (at(len - i - 1) > rhs.at(len - i - 1))
			return true;
	}
	return true;
}

bool P_Int::operator<=(const P_Int &rhs) const {
	if (size() < rhs.size()) return true;
	else if (size() > rhs.size()) return false;	
	size_t len = size();
	for (size_t i = 0; i < len; ++i) {
		if (at(len - i - 1) > rhs.at(len - i - 1))
			return false;
		else if (at(len - i - 1) < rhs.at(len - i - 1))
			return true;
	}
	return true;
}

bool P_Int::operator>(const P_Int &rhs) const { return !operator<=(rhs); }

bool P_Int::operator<(const P_Int &rhs) const { return !operator>=(rhs); }

bool P_Int::operator==(const P_Int &rhs) const {
	if (size() != rhs.size()) return false;
	size_t len = size();
	for (size_t i = 0; i < len; ++i) {
		if (at(len - i - 1) != rhs.at(len - i - 1))
			return false;
	}
	return true;
}

bool P_Int::operator!=(const P_Int &rhs) const { return !operator==(rhs); }

bool operator>(unsigned int lhs, const P_Int &rhs) { return rhs < lhs; }

bool operator<(unsigned int lhs, const P_Int &rhs) { return rhs > lhs; }

bool operator>=(unsigned int lhs, const P_Int &rhs) { return rhs <= lhs; }

bool operator<=(unsigned int lhs, const P_Int &rhs) { return rhs >= lhs; }

bool operator==(unsigned int lhs, const P_Int &rhs) { return rhs == lhs; }

bool operator!=(unsigned int lhs, const P_Int &rhs) { return rhs != lhs; }


/**
 * Increment / decrement operators
 */

P_Int& P_Int::operator++() {
	++at(0);
	size_t i, len = size();
	for (i = 0; i < len - 1; ++i) {
		if (at(i) >= 10) {
			at(i) = 0;
			++at(i + 1);
		}
		else
			break;
	}
	if (at(i) > 10) {
		at(i) = 0;
		push_back(1);
	}
	return *this;
}

P_Int P_Int::operator++(int) {
	P_Int tmp(*this);
	++(*this);
	return tmp;
}

P_Int& P_Int::operator--() {
	if (this->operator==(0))
		throw NegativeExcept();
	--at(0);
	size_t i, len = size();
	for (i = 0; i < len - 1; ++i) {
		if (at(i) < 0) {
			at(i) = 9;
			--at(i + 1);
		}
		else
			break;
	}
	trimLeading0_();
	return *this;
}

P_Int P_Int::operator--(int) {
	P_Int tmp(*this);
	--(*this);
	return tmp;
}

/**
 * Overloaded arithmetic operators
 */

P_Int P_Int::operator+(const P_Int &rhs) const {
	P_Int result;
	size_t i;
	for (i = 0; i < size() && i < rhs.size(); ++i) 
		result.push_back(at(i) + rhs.at(i));
	while (i < size())
		result.push_back(at(i++));
	while (i < rhs.size())
		result.push_back(rhs.at(i++));
	result.carry_();
	return result;
}

P_Int P_Int::operator-(const P_Int &rhs) const {
	if (this->operator<(rhs)) 
		throw NegativeExcept();
	P_Int result;
	size_t i;
	for (i = 0; i < size() && i < rhs.size(); ++i)
		result.push_back(at(i) - rhs.at(i));
	while (i < size())
		result.push_back(at(i++));
	for (size_t j = 0; j < result.size(); ++j) {
		if (result.at(j) < 0) {
			result.at(j) += 10;
			--result.at(j + 1);
		}
	}
	result.trimLeading0_();
	return result;
}

P_Int P_Int::operator*(const P_Int &rhs) const {
	if (this->operator==(0) || rhs == 0) return P_Int();
	else if (this->operator==(1) || rhs == 1) {
		P_Int result = *this + rhs - 1;
		return result;
	}
	P_Int result;
	result.resize(size() + rhs.size(), 0);
	for (size_t i = 0; i < size(); ++i) {
		P_Int tmp(rhs);
		tmp.multiply_(at(i), i);
		result += tmp;
	}
	result.carry_();
	result.trimLeading0_();
	result.shrink_to_fit();
	return result;
}

P_Int operator+(unsigned int lhs, const P_Int &rhs) {
	P_Int result(lhs);
	result += rhs;
	return result;
}

P_Int operator-(unsigned int lhs, const P_Int &rhs) {
	P_Int result(lhs);
	result -= rhs;
	return result;
}
P_Int operator*(unsigned int lhs, const P_Int &rhs){
	P_Int result(lhs);
	result *= rhs;
	return result;
}

P_Int& P_Int::operator+=(const P_Int &rhs) {
	size_t i, len = size();
	for (i = 0; i < rhs.size() && i < len; ++i)
		at(i) += rhs.at(i);
	while (i < rhs.size()) push_back(rhs[i++]);
	carry_();
	return *this;
}

P_Int& P_Int::operator-=(const P_Int &rhs) {
	if (this->operator<(rhs))
		throw NegativeExcept();
	size_t i, len = size();
	for (i = 0; i < rhs.size(); ++i)
		at(i) -= rhs.at(i);
	for (i = 0; i < len - 1; ++i) {
		if (at(i) < 0) {
			--at(i + 1);
			at(i) += 10;
		}
	}
	trimLeading0_();
	return *this;
}

P_Int& P_Int::operator*=(const P_Int &rhs) {
	if (this->operator==(0) || rhs == 0) {
		*this = 0;
		return *this;
	}
	else if (this->operator== (1)) {
		*this = rhs;
		return *this;
	}
	else if (rhs == 1) {
		return *this;
	}
	P_Int result;
	result.resize(size() + rhs.size(), 0);
	for (size_t i = 0; i < size(); ++i) {
		P_Int tmp(rhs);
		tmp.multiply_(at(i), i);
		result += tmp;
	}
	result.carry_();
	result.trimLeading0_();
	result.shrink_to_fit();
	*this = result;
	return *this;
}

/**
 * Friend functions for input and output streams
 */

std::ostream& operator<<(std::ostream& os, const P_Int &rhs) {
	size_t len = rhs.size();
	for (size_t j = 0; j < len; ++j)
		os << (int) rhs.at(len - j - 1);
	return os;
}

std::istream& operator>>(std::istream& is, P_Int &rhs) {
	rhs.resize(0); // clearing the vector
	std::string tmp;
	is >> tmp;
	size_t len = tmp.size();
	for (size_t j = 0; j < len; ++j) {
		if (!isdigit(tmp.at(len - j - 1))) {
			is.setstate(std::ios::failbit);
			rhs.reset_();
			return is;
		}
		rhs.push_back(tmp.at(len - j - 1) - '0');
	}
	rhs.trimLeading0_();
	return is;
}

/**
 * Returning an equal unsigned int
 * might throw an exception
 */
unsigned int P_Int::unsigned_int() const {
	if (this->operator>(std::numeric_limits<unsigned int>::max()))
		throw "Overflowing"; // Perhaps a custom exception object would be better
	unsigned int result = 0;
	for (size_t i = 0; i < size(); ++i) {
		result *= 10;
		result += static_cast<unsigned>(at(i));
	}
	return result;
}

/**
 * Private helper methods
 */ 

void P_Int::reset_() { resize(1); at(0) = 0; }

void P_Int::trimLeading0_() {
	while (!empty() && at(size() - 1) == 0)
		pop_back();
	if (empty()) reset_();
	shrink_to_fit();
}

void P_Int::carry_() {
	size_t i;
	for (i = 0; i < size() - 1; ++i) {
		if (at(i) >= 10) {
			at(i + 1) += at(i) / 10;
			at(i) %= 10;
		}
	}
	if (at(i) >= 10) {
		push_back(at(i) / 10);
		at(i) %= 10;
	}
}

void P_Int::multiply_(char factor, size_t shift) {
	size_t len = size();
	resize(size() + shift);
	for (size_t i = 0; i < len; ++i)
		at(len - i - 1 + shift) = at(len - i - 1) * factor;
	for (size_t i = 0; i < shift; ++i)
		at(i) = 0;
}
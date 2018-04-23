#ifndef BIG_INT_H
#define BIG_INT_H

#include "p_int.h"

// Both positive, (0 and negative) integers
class BigInt: private P_Int {
public:
	BigInt();
	BigInt(const BigInt&);
	BigInt(int);
	BigInt& operator=(const BigInt&);

	/**
	 * Basic IO, using std::istream and std::ostream
	 */
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	friend std::istream& operator>>(std::istream&, BigInt&);

	/**
	 * Arithmetic and comparison operators
	 */
	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);
	bool operator>(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>=(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	friend bool operator>(int, const BigInt&);
	friend bool operator<(int, const BigInt&);
	friend bool operator>=(int, const BigInt&);
	friend bool operator<=(int, const BigInt&);
	friend bool operator==(int, const BigInt&);
	friend bool operator!=(int, const BigInt&);
	BigInt operator+(const BigInt&) const;
	BigInt operator-(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt& operator+=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	friend BigInt operator+(int, const BigInt&);
	friend BigInt operator-(int, const BigInt&);
	friend BigInt operator*(int, const P_Int&);
	
private:
	bool neg_; // True for negative values, false for natural numbers
};

#endif

#ifndef BIG_INT_H
#define BIG_INT_H

#include "p_int.h"

// Both positive, 0 and negative integers
class BigInt: private P_Int {
public:
	BigInt();
	BigInt(const BigInt&);
	BigInt(int);
	BigInt& operator=(const P_Int&);
	
private:
	bool neg_; // True for negative values, false for natural numbers
};

#endif

#ifndef P_INT_H
#define P_INT_H

#include <vector>

// Only positive large integers
class P_Int: private std::vector<char> {
public:
	P_Int();
	P_Int(const P_Int&);
	P_Int(unsigned int);
	P_Int& operator=(const P_Int&);
	friend std::ostream& operator<<(std::ostream&, const P_Int&);
	friend std::istream& operator>>(std::istream&, P_Int&);
	P_Int& operator++();
	P_Int operator++(int);
	P_Int& operator--();
	P_Int operator--(int);
	bool operator>(const P_Int&) const;
	bool operator<(const P_Int&) const;
	bool operator>=(const P_Int&) const;
	bool operator<=(const P_Int&) const;
	bool operator==(const P_Int&) const;
	bool operator!=(const P_Int&) const;
	friend bool operator>(unsigned int, const P_Int&);
	friend bool operator<(unsigned int, const P_Int&);
	friend bool operator>=(unsigned int, const P_Int&);
	friend bool operator<=(unsigned int, const P_Int&);
	friend bool operator==(unsigned int, const P_Int&);
	friend bool operator!=(unsigned int, const P_Int&);
	P_Int operator+(const P_Int&) const;
	P_Int operator-(const P_Int&) const;
	P_Int operator*(const P_Int&) const;
	P_Int& operator+=(const P_Int&);
	P_Int& operator-=(const P_Int&);
	P_Int& operator*=(const P_Int&);
	friend P_Int operator+(unsigned int, const P_Int&);
	friend P_Int operator-(unsigned int, const P_Int&);
	friend P_Int operator*(unsigned int, const P_Int&);
	/**
	 * Put here to remind the existence of these overloads
	 * P_Int operator+(int, const P_Int&);
	 * P_Int operator-(int, const P_Int&);
	 * P_Int operator*(int, const P_Int&);
	 * But += version of these are undefined as they may go overflowed
	 */
	int length() const;

private:
	void reset_();
	void trimLeading0_();
	void carry_();
	// To multiply by a unit number and shift digits
	void multiply_(char, std::size_t);
};

#endif

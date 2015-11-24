//plik naglowkowy

#ifndef VERYLONGINT_H_
#define VERYLONGINT_H_

#include <vector>
#include <string>
typedef std::vector<unsigned long long> digit_list;

class VeryLongInt {
public:
	digit_list digits;
	bool NaN;
	bool Zero;
//public:
	VeryLongInt();
	VeryLongInt(const VeryLongInt &other);
	VeryLongInt(VeryLongInt &&other);
	VeryLongInt(const unsigned long long n);
	VeryLongInt(const unsigned long int n) : VeryLongInt(static_cast<unsigned long long>(n)) {};
	VeryLongInt(const unsigned int n) : VeryLongInt(static_cast<unsigned long long>(n)) {};
	VeryLongInt(const unsigned short n) : VeryLongInt(static_cast<unsigned long long>(n)) {};
	VeryLongInt(const long long n) : VeryLongInt(static_cast<unsigned long long>(n)) {if (n < 0) {NaN = true; digits.clear(); Zero = false;}};
	VeryLongInt(const long n) : VeryLongInt(static_cast<long long>(n)) {};
	VeryLongInt(const int n) : VeryLongInt(static_cast<long long>(n)) {};
	VeryLongInt(const short n) : VeryLongInt(static_cast<long long>(n)) {};
    VeryLongInt(const std::string &s);
    VeryLongInt(const char *s) : VeryLongInt(std::string(s)) {};
    VeryLongInt(const char n) = delete;
    VeryLongInt(const unsigned char n) = delete;
	VeryLongInt(const bool n) = delete;
	VeryLongInt& operator+=(const VeryLongInt &verylongint);
	VeryLongInt& operator-=(const VeryLongInt &verylongint);
	VeryLongInt& operator*=(const VeryLongInt &verylongint);
	VeryLongInt& operator/=(const VeryLongInt &verylongint);
	VeryLongInt& operator%=(const VeryLongInt &verylongint);
	VeryLongInt& operator<<=(const unsigned int shift);
	VeryLongInt& operator>>=(const unsigned int shift);
	VeryLongInt& operator=(const VeryLongInt& other);
	VeryLongInt& operator=(VeryLongInt&& other);
	VeryLongInt& operator=(const unsigned long int n);
	//const VeryLongInt operator-(const VeryLongInt &verylongint) const;
	//const VeryLongInt operator*(const VeryLongInt &verylongint) const;
	//const VeryLongInt operator/(const VeryLongInt &verylongint) const;
	//const VeryLongInt operator%(const VeryLongInt &verylongint) const;
	const VeryLongInt operator<<(const unsigned int shift) const;
	const VeryLongInt operator>>(const unsigned int shift) const;
	//bool operator==(const VeryLongInt &verylongint) const;
	friend bool operator==(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
	//bool operator!=(const VeryLongInt &verylongint) const;
	friend bool operator!=(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
	//bool operator<(const VeryLongInt &verylongint) const;
	friend bool operator<(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
	//bool operator<=(const VeryLongInt &verylongint) const;
	friend bool operator<=(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
	//bool operator>(const VeryLongInt &verylongint) const;
	friend bool operator>(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
	//bool operator>=(const VeryLongInt &verylongint) const;
	friend bool operator>=(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
	explicit operator bool() const {
	    return !Zero && !NaN;
	}
	bool isValid() const;
	VeryLongInt& multiply_by_2();
	VeryLongInt& divide_by_2();
	bool is_divisible_by_2();
	std::ostream &write(std::ostream &os) const;
	void clear();
};

const VeryLongInt operator+(const VeryLongInt &a, const VeryLongInt &b);
const VeryLongInt operator-(const VeryLongInt &a, const VeryLongInt &b);
const VeryLongInt operator*(const VeryLongInt &a, const VeryLongInt &b);
const VeryLongInt operator/(const VeryLongInt &a, const VeryLongInt &b);
const VeryLongInt operator%(const VeryLongInt &a, const VeryLongInt &b);

const VeryLongInt& Zero() {
    static const VeryLongInt zero;
    return zero;
}

const VeryLongInt& NaN() {
    static const VeryLongInt nan = Zero()/Zero();
    return nan;
}

#endif /* VERYLONGINT_H_ */

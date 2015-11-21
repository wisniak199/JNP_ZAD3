//plik naglowkowy

#ifndef VERYLONGINT_H_
#define VERYLONGINT_H_

#include <vector>
#include <string>
typedef std::vector<long int> digit_list;

class VeryLongInt {
private:
	digit_list digits;
	bool NaN;
	bool Zero;
public:
	VeryLongInt();
	VeryLongInt(const VeryLongInt &other);
	VeryLongInt(VeryLongInt &&other);
	VeryLongInt(unsigned int n);
	VeryLongInt(const std::string &s);
	VeryLongInt& operator+=(const VeryLongInt &verylongint);
	VeryLongInt& operator-=(const VeryLongInt &verylongint);
	VeryLongInt& operator*=(const VeryLongInt &verylongint);
	VeryLongInt& operator/=(const VeryLongInt &verylongint);
	VeryLongInt& operator%=(const VeryLongInt &verylongint);
	VeryLongInt& operator<<=(const VeryLongInt &verylongint);
	VeryLongInt& operator>>=(const VeryLongInt &verylongint);
	const VeryLongInt operator+(const VeryLongInt &verylongint) const;
	const VeryLongInt operator-(const VeryLongInt &verylongint) const;
	const VeryLongInt operator*(const VeryLongInt &verylongint) const;
	const VeryLongInt operator/(const VeryLongInt &verylongint) const;
	const VeryLongInt operator%(const VeryLongInt &verylongint) const;
	const VeryLongInt operator<<(const VeryLongInt &verylongint) const;
	const VeryLongInt operator>>(const VeryLongInt &verylongint) const;
	bool operator==(const VeryLongInt &verylongint) const;
	bool operator!=(const VeryLongInt &verylongint) const;
	bool operator<(const VeryLongInt &verylongint) const;
	bool operator<=(const VeryLongInt &verylongint) const;
	bool operator>(const VeryLongInt &verylongint) const;
	bool operator>=(const VeryLongInt &verylongint) const;
	std::ostream &write(std::ostream &os) const;
};

#endif /* VERYLONGINT_H_ */

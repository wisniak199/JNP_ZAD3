//plik naglowkowy

#ifndef VERYLONGINT_H_
#define VERYLONGINT_H_

#include <vector>

typedef std::vector<long int> digit_list;

class VeryLongInt {
private:
	digit_list digits;
	unsigned long len; //dlugosc vectora - unsigned long?
	bool NaN;
	bool Zero;
public:
	VeryLongInt();
	~VeryLongInt();
	unsigned long getlen(); //getter - pomocnicza
	digit_list getdigits(); //getter - pomocnicza
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
};

#endif /* VERYLONGINT_H_ */

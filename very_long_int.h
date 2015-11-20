//plik naglowkowy

#include <vector>

typedef vector<int> digit_list;

#ifndef VERYLONGINT_H_
#define VERYLONGINT_H_

class VeryLongInt {
private:
	digit_list digits;
public:
	VeryLongInt();
	~VeryLongInt();
	VeryLongInt& operator+=(const VeryLongInt &verylongint);
	VeryLongInt& operator-=(const VeryLongInt &verylongint);
	VeryLongInt& operator*=(const VeryLongInt &verylongint);
	VeryLongInt& operator/=(const VeryLongInt &verylongint);
	VeryLongInt& operator%=(const VeryLongInt &verylongint);
	VeryLongInt& operator<<=(const VeryLongInt &verylongint);
	VeryLongInt& operator>>=(const VeryLongInt &verylongint);
};

#endif /* VERYLONGINT_H_ */

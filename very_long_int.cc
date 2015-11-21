#include "very_long_int.h"

/** Magda: porownania, (-, /, >>, %), operatory
 *  Piotrek: kontruktory, (+, *, <<), BinaryDigits
 */

// To CHYBA działa
VeryLongInt& VeryLongInt::operator/=(const VeryLongInt &denumerator){
 /*   VeryLongInt temp; = 1;
    VeryLongInt one; = 1;
    VeryLongInt quotient; = 0;

    while ((*this) <= denumerator) {
        denumerator <<= one;
        temp <<= one;
    }
    while (temp > one) {
        denumerator >>= one;
        temp >>= one;
        if ((*this) >= denumerator) {
            (*this) -= denumerator;
            quotient += temp;
        }
    }
    return quotient; */
    return *this;
}

const VeryLongInt VeryLongInt::operator-(const VeryLongInt &other) const {
    return VeryLongInt(*this) -= other;
}

const VeryLongInt VeryLongInt::operator/(const VeryLongInt &other) const {
    return VeryLongInt(*this) /= other;
}

const VeryLongInt VeryLongInt::operator%(const VeryLongInt &other) const {
    return VeryLongInt(*this) %= other;
}

const VeryLongInt VeryLongInt::operator>>(const VeryLongInt &other) const {
    return VeryLongInt(*this) >>= other;
}

bool VeryLongInt::operator==(const VeryLongInt &other) const{

	// return !(this < other) && !(other < this);

/*	if ((*this).getlen() != other.getlen())
		return false;
	else{
		unsigned long len = (*this).getlen();
		for (unsigned long i = 0; i < len; i++)
			if ((*this).getdigits()[i] != other.getdigits()[i])
				return false;
		return true;
	} */
	return true;
}

bool VeryLongInt::operator!=(const VeryLongInt &other) const{
	return !(*this == other);
}

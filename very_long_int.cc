#include "very_long_int.h"

/** Magda: porownania, (-, /, >>, %), operatory
 *  Piotrek: kontruktory, (+, *, <<), BinaryDigits
 */

VeryLongInt& VeryLongInt::operator/=(const VeryLongInt &denumerator){
 /*   VeryLongInt temp = 1;
    VeryLongInt one = 1;
    VeryLongInt quotient = 0;

    while ((*this) <= denumerator) {
        denumerator <<= 1;
        temp <<= 1;
    }
    while (temp > one) {
        denumerator >>= 1;
        temp >>= 1;
        if ((*this) >= denumerator) {
            (*this) -= denumerator;
            quotient += temp;
        }
    }
    return quotient; */
    return *this;
}

const VeryLongInt VeryLongInt::operator+(const VeryLongInt &other) const {
    return VeryLongInt(*this) += other;
}

const VeryLongInt VeryLongInt::operator-(const VeryLongInt &other) const {
    return VeryLongInt(*this) -= other;
}

const VeryLongInt VeryLongInt::operator*(const VeryLongInt &other) const {
    return VeryLongInt(*this) *= other;
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

const VeryLongInt VeryLongInt::operator<<(const VeryLongInt &other) const {
    return VeryLongInt(*this) <<= other;
}

bool VeryLongInt::operator==(const VeryLongInt &other) const{

	// return !((*this) < other) && !(other < (*this));

	if ((*this).digits.size() != other.digits.size())
		return false;
	else{
		unsigned long len = (*this).digits.size();
		for (unsigned long i = 0; i < len; i++)
			if ((*this).digits[i] != other.digits[i])
				return false;
		return true;
	}
	return true;
}

bool VeryLongInt::operator!=(const VeryLongInt &other) const{
	return !(*this == other);
}

#include <string>
#include <sstream>
#include "very_long_int.h"

/** Magda: porownania, (-, /, >>, %), operatory
 *  Piotrek: kontruktory, (+, *, <<), BinaryDigits
 */

//zmieniac 2 naraz
const int base = 10;
const int base_length = 1;


VeryLongInt::VeryLongInt() {
    digits = digit_list({0L});
    Zero = true;
    NaN = false;
}

VeryLongInt::VeryLongInt(const VeryLongInt &other) : digits(other.digits), Zero(other.Zero), NaN(other.NaN) {}

VeryLongInt::VeryLongInt(VeryLongInt &&other) : digits(std::move(other.digits)), Zero(other.Zero), NaN(other.NaN){}

VeryLongInt::VeryLongInt(unsigned int n) {
    NaN = false;
    if (n == 0) {
        Zero = true;
        digits.push_back(0);
    } else {
        Zero = false;
        while (n != 0) {
            digits.push_back(n % base);
            n /= base;
        }
    }
}

VeryLongInt::VeryLongInt(const std::string &s) {
    NaN = false;
    if (s[0] == '0') {
        Zero = true;
        digits.push_back(0);
    } else {
        std::stringstream stream;
        for (int i = s.length() - base_length; i > -base_length; i -= base_length) {
            stream.str(s.substr(std::max(0, i), i + base_length - 1));
            int temp;
            stream >> temp;
            digits.push_back(temp);
        }
    }
}


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

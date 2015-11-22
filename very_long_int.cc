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

VeryLongInt::VeryLongInt(unsigned long int n) {
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

VeryLongInt& VeryLongInt::operator+=(const VeryLongInt &other){
    NaN = NaN || other.NaN;
    Zero = Zero && other.Zero;
    if (Zero || NaN)
        return *this;

    unsigned long int carry = 0;
    auto this_len = digits.size();
    auto other_len = other.digits.size();
    for (auto i = 0; i < std::max(this_len, other_len); ++i) {
        auto res = carry;
        if (i < other_len)
            res += other.digits[i];
        if (i < this_len) {
            res += digits[i];
            digits[i] = res % base;
        }
        else
            digits.push_back(res % base);
        carry = res / base;
    }
    if (carry != 0)
        digits.push_back(carry);
    return *this;
}

VeryLongInt& VeryLongInt::operator-=(const VeryLongInt &other) {
	if (other.NaN || (*this) < other)
		(*this) = NaN();
	else if (!(*this).NaN && !(*this).NaN) {
		long int c = 0; /*przeniesienie*/
		for (long int i = 0; i < (*this).digits.size(); i++) {
			if (i < other.digits.size())
				(*this).digits[i] = (*this).digits[i] - other.digits[i] +c;
			else
				(*this).digits[i] = (*this).digits[i] + c;
			if ((*this).digits[i] < 0) {
				(*this).digits[i] += base;
				c = -1;
			}
			else
				c = 0;
		}
		/*Usuniecie wiodacych zer*/
		while ((*this).digits.size() > 1 && (*this).digits[(*this).digits.size()-1] == 0) {
			(*this).digits.pop_back();
		}
	}
	return *this;
}

//mnozenie przez 2 - przda sie przy mnozeniu rosyjskich chlopow
//nie wiem czy to dziala bo w koncu korzystamy jednoczesnie z tego samego obiektu
//jezeli nie dzala takie cos to trzeba cos zrobic z dodawaniem
VeryLongInt& VeryLongInt::multiply_by_2() {
    (*this) += *this;
    return *this;
}


VeryLongInt& VeryLongInt::divide_by_2() {
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (i > 0 && digits[i] % 2)
            digits[i - 1] += base;
        digits[i] /= 2;
    }
    for (int i  = digits.size() - 1; i > 0; --i) {
        if (digits[i] != 0)
            break;
        digits.pop_back();
    }
    return *this;
}

bool VeryLongInt::is_divisible_by_2() {
    if (NaN)
        return false;
    return digits[0] % 2 == 0;
}

//algorytm rosyjskich chlopow
VeryLongInt& VeryLongInt::operator*=(const VeryLongInt &other) {
    VeryLongInt multiplicator(other);
    VeryLongInt x(*this);
    *this = VeryLongInt();
    while (!multiplicator.Zero) {
        if (!multiplicator.is_divisible_by_2())
            *this += x;
        x.multiply_by_2();
        multiplicator.divide_by_2();
    }
    return *this;
}

VeryLongInt& VeryLongInt::operator/=(const VeryLongInt &other) {
	if (other.NaN || other.Zero)
		(*this)=NaN();
	else if (!(*this).NaN && !(*this).NaN) {
		if ((*this)<other)
			(*this) = Zero();
		else {
			VeryLongInt quotient;
			VeryLongInt dummy;
			for (size_t i = other.digits.size() - 1; i >= 0; i--)
				dummy.digits.push_back((*this).digits[(*this).digits.size()-1-i]);
			size_t l = (*this).digits.size() - other.digits.size();;
			while (l >= 0) {
				unsigned long int a = 0;
				unsigned long int b = base - 1;
				while (a < b) {
					unsigned long int c = ((a + b)/2) + 1;
					if (other * VeryLongInt(c) > dummy)
						b = c - 1; 
					else
						a = c;
				}
				if (quotient.Zero)
					quotient = a;
				else
					quotient.digits.insert(quotient.digits.begin(), a); 
				dummy = dummy - (other * VeryLongInt(a));
				l--;
				if (l >= 0)
					dummy.digits.insert(dummy.digits.begin(), (*this).digits[l]);
			}
			while (quotient.digits.size() > 0 && quotient.digits[quotient.digits.size() - 1] == 0)
				quotient.digits.pop_back();
			*this = std::move(quotient);
		}
	}
    return *this;
}

VeryLongInt& VeryLongInt::operator%=(const VeryLongInt &other) {
	if (other.NaN || other.Zero)
		(*this)=NaN();
	else if (!(*this).NaN && !(*this).NaN) {
		VeryLongInt quotient = *this;
		quotient /= other;
		VeryLongInt product = other;
		product *= quotient;
		(*this) -= product;
	}
	return (*this);
}

VeryLongInt& VeryLongInt::operator<<=(const unsigned int shift) {
    for (auto i = 0; i < shift; ++i)
        (*this).multiply_by_2();
    return *this;
}

VeryLongInt& VeryLongInt::operator>>=(const unsigned int shift) {
    for (auto i = 0; i < shift; ++i)
        (*this).divide_by_2();
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

bool VeryLongInt::operator==(const VeryLongInt &other) const {

	// return !((*this) < other) && !(other < (*this));

	if ((*this).digits.size() != other.digits.size())
		return false;
	else {
		unsigned long len = (*this).digits.size();
		for (unsigned long i = 0; i < len; i++)
			if ((*this).digits[i] != other.digits[i])
				return false;
		return true;
	}
}

bool VeryLongInt::operator!=(const VeryLongInt &other) const {
	return !(*this == other);
}

bool VeryLongInt::operator<(const VeryLongInt &other) const {
	if ((*this).digits.size() < other.digits.size())
		return true;
	else if ((*this).digits.size() > other.digits.size())
		return false;
	else {
		unsigned long i = (*this).digits.size() -1;
		while (i >= 0 && (*this).digits[i] == other.digits[i])
			i--;
		if (i<0)
			return false;
		else {
			if ((*this).digits[i] < other.digits[i])
				return true;
			return false;
		}
	}
}

bool VeryLongInt::operator>(const VeryLongInt &other) const {
	return (other < (*this));
}

bool VeryLongInt::operator<=(const VeryLongInt &other) const {
	return !((*this) > other);
}

bool VeryLongInt::operator>=(const VeryLongInt &other) const {
	return !((*this) < other);
}

std::ostream &VeryLongInt::write(std::ostream &os) const {
    if (NaN)
        os << "NaN";
    else {
        for (int i = digits.size() - 1; i >= 0; --i)
            os << digits[i];
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const VeryLongInt &verylongint) {
     return verylongint.write(os);
}

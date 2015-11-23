#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include "very_long_int.h"

/** Magda: porownania, (-, /, >>, %), operatory
 *  Piotrek: kontruktory, (+, *, <<), BinaryDigits
 */

//zmieniac 2 naraz
const unsigned long int base = 100000;
const int base_length = 5;


VeryLongInt::VeryLongInt() {
    digits = digit_list({0L});
    Zero = true;
    NaN = false;
}

VeryLongInt::VeryLongInt(const VeryLongInt &other) : digits(other.digits), NaN(other.NaN), Zero(other.Zero) {}

VeryLongInt::VeryLongInt(VeryLongInt &&other) : digits(std::move(other.digits)), NaN(other.NaN), Zero(other.Zero){}

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
        Zero = false;
        std::stringstream stream;
        for (int i = s.length() - base_length; i > -base_length; i -= base_length) {
            stream.clear();
            stream.str(s.substr(std::max(0, i), base_length + std::min(0, i)));
            unsigned long int temp;
            stream >> temp;
            digits.push_back(temp);
        }
    }
}

VeryLongInt& VeryLongInt::operator=(const VeryLongInt &other) {
    if (this != &other) {
        this->digits = digit_list(other.digits);
        this->Zero = other.Zero;
        this->NaN = other.NaN;
    }
    return *this;
}

VeryLongInt& VeryLongInt::operator=(VeryLongInt &&other) {
    if(this != &other) {
        this->digits = digit_list(std::move(other.digits));
        this->Zero = other.Zero;
        this->NaN = other.NaN;
    }
    return *this;
}

VeryLongInt& VeryLongInt::operator+=(const VeryLongInt &other){
    NaN = NaN || other.NaN;
    Zero = Zero && other.Zero;
    if (Zero || NaN)
        return *this;

    unsigned long int carry = 0;
    size_t this_len = digits.size();
    size_t other_len = other.digits.size();
    for (size_t i = 0; i < std::max(this_len, other_len); ++i) {
        unsigned long int res = carry;
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
		(*this).NaN = true;
	else if (!(*this).NaN && !(*this).NaN) {
		long int c = 0; //przeniesienie
		long long temp = 0;
		for (long int i = 0; i < (*this).digits.size(); i++) {
			if (i < other.digits.size())
				//(*this).digits[i] = (*this).digits[i] - other.digits[i] +c;
				temp = digits[i] - other.digits[i] + c;
			else
				//(*this).digits[i] = (*this).digits[i] + c;
				temp = digits[i] + c;
			/*if ((*this).digits[i] < 0) {
				(*this).digits[i] += base;
				c = -1;
			}*/
			if (temp < 0) {
			    temp += base;
                c = -1;
			}
			else
				c = 0;
            digits[i] = temp;
		}
		//Usuniecie wiodacych zer
		while ((*this).digits.size() > 1 && (*this).digits[(*this).digits.size()-1] == 0) {
			(*this).digits.pop_back();
		}
		if (digits.size() == 1 && digits[0] == 0)
		    Zero = true;
	}
	return *this;
}

void VeryLongInt::clear() {
    digits.clear();
    digits.push_back(0);
    NaN = false;
    Zero = true;
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
    if (digits.size() == 1 && digits[0] == 0)
        Zero = true;
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
    //*this = VeryLongInt();
    (*this).clear();
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
		(*this).NaN = true;
	else if (!(*this).NaN && !(*this).NaN) {
		if ((*this)<other)
			(*this).clear();
		else {
			VeryLongInt quotient;
			VeryLongInt dummy;
			for (long int i = other.digits.size() - 1; i >= 0; i--) {
				if (dummy.Zero)
					dummy += VeryLongInt((*this).digits[(*this).digits.size()-1-i]);
				else
					dummy.digits.push_back((*this).digits[(*this).digits.size()-1-i]);
				}
			long int l = (*this).digits.size() - other.digits.size();
			while (l >= 0) {
				unsigned long int a = 0;
				unsigned long int b = base - 1;
				while (a < b) {
					unsigned long int c = ((a + b)/2) + 1;
					if ((other * VeryLongInt(c)) > dummy)
						b = c - 1;
					else
						a = c;
				}
				if (quotient.Zero)
					quotient += VeryLongInt(a);
				else
					quotient.digits.insert(quotient.digits.begin(), a);
				dummy -= (other * VeryLongInt(a));
				l--;
				if (l >= 0) {
					if (dummy.Zero)
						dummy += (*this).digits[l];
					else
						dummy.digits.insert(dummy.digits.begin(), (*this).digits[l]);
				}
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
		(*this).NaN = true;
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

VeryLongInt& VeryLongInt::operator=(const unsigned long int n) {
    *this = VeryLongInt(n);
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

const VeryLongInt VeryLongInt::operator>>(const unsigned int shift) const {
    return VeryLongInt(*this) >>= shift;
}

const VeryLongInt VeryLongInt::operator<<(const unsigned int shift) const {
    return VeryLongInt(*this) <<= shift;
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
	if (*this == other)
		return false;
	else
		return (other < (*this));
}

bool VeryLongInt::operator<=(const VeryLongInt &other) const {
	return !((*this) > other);
}

bool VeryLongInt::operator>=(const VeryLongInt &other) const {
	return !((*this) < other);
}

bool VeryLongInt::isValid() const {
    return !NaN;
}

std::ostream &VeryLongInt::write(std::ostream &os) const {
    if (NaN)
        os << "NaN";
    else {
        os << digits[digits.size() - 1];
        for (int i = digits.size() - 2; i >= 0; --i) {
            unsigned long int base_temp = base / 10;
            while (base_temp > digits[i]) {
                os << "0";
                base_temp /= 10;
            }
            if (digits[i] != 0)
                os << digits[i];
        }
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const VeryLongInt &verylongint) {
     return verylongint.write(os);
}

bool operator==(const unsigned long int n, VeryLongInt& other) {
    return other == n;
}

using namespace std;

int main() {
//    ==== Przykład kodu korzystającego z klasy VeryLongInt ====

    //Segfaulty przy dzieleniu przez 1
    {
        VeryLongInt x = 1;
        x /= 0;
        assert(!x.isValid());
    }

    {
        VeryLongInt x = 100;
        x -= 101;
        assert(!x.isValid());
    }

    {
        VeryLongInt x = 23;
        VeryLongInt y = x;
        assert(x == y);
    }

    {
        VeryLongInt x = 23;
        VeryLongInt y = 32;
        x = y;
        assert(x == y);
    }

    {
        VeryLongInt x = 23;
        VeryLongInt y = 32;
        assert(y > x);
    }

    {
        VeryLongInt x = 23;
        VeryLongInt y = 32;
        assert(y >= x);
    }

    /*{
        VeryLongInt x = NaN();
        assert(!x.isValid());
    }*/

    {
        VeryLongInt x = 10;
        if (x)
            assert(1);
        else
            assert(0);
    }

    {
        VeryLongInt x = 1;
        x <<= 123;
        x >>= 120;
        assert(8 == x);
    }

    /*Segfaulty w %
    {
        VeryLongInt x = 1;
        for (int i = 1; i <= 100; ++i)
            x *= 2;
        assert(x % 3 == 1);
    }*/

    /*{
        VeryLongInt x = Zero();
        assert(x == 0);
    }*/

    /*{
        const int N = 100;
        VeryLongInt x = 1;
        for (int i = 1; i < N; ++i)
            x *= 2;
        assert(x.numberOfBinaryDigits() == N);
    }

    {
        VeryLongInt x("1234567890123456789012345678901234567890");
        VeryLongInt z = x;
        VeryLongInt y("777777777777777777777777777777777777777");
        x = x + y;
        assert(x == VeryLongInt("2012345667901234566790123456679012345667"));
        cout << x <<"\n";
        x -= y;
        cout << x;
        assert(x == z);
    }

    {
        VeryLongInt x(string("12345678"));
        VeryLongInt y(12345678);
        assert(x == y);
    }

    {
        VeryLongInt x("12345678901234567890");
        VeryLongInt y(12345678901234567890UL);
        assert(x == y);
        cout << y << endl;
    }

    {
        VeryLongInt x("1234567890123456789012345678901234567890");
        VeryLongInt y("1204567890123456789012345678901234567890");
        VeryLongInt z(  "30000000000000000000000000000000000000");
        assert(z == x - y);
    }

    {
        VeryLongInt x("10000000000");
        VeryLongInt y("100000000000");
        VeryLongInt z("1000000000000000000000");
        assert(z == x * y);
    }

    {
        const int N = 1000;
        VeryLongInt x = 1;
        for (int i = 2; i <= N; ++i)

            x *= i;
        for (int i = 2; i <= N; ++i);
            //x /= i;
        //assert(x == 1);
    }*/

    /*{
        assert(Zero().numberOfBinaryDigits() == 1);
        assert(NaN().numberOfBinaryDigits() == 0);
    }

//==== Przykład kodu, który nie powinien się kompilować ====

    /*VeryLongInt a('1'); // błąd kompilacji

    VeryLongInt b(true); // błąd kompilacji

    VeryLongInt c;
    c += "123"; // błąd kompilacji

    VeryLongInt d;
    d -= ::std::string("123"); // błąd kompilacji

    VeryLongInt e, f, g;
    e * g = h; // błąd kompilacji

    VeryLongInt h;
    int i = h; // błąd kompilacji
*/

    VeryLongInt x("9999923473434");
    VeryLongInt y(876876);
    //assert(x + y == VeryLongInt("1000000000000000002"));
    cout << "wynik :" << (x / y) << "\n";
}


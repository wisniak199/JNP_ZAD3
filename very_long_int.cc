#include <string>
#include <sstream>
#include "very_long_int.h"

VeryLongInt::VeryLongInt() {
    digits = digit_list({0L});
    Zero = true;
    NaN = false;
}

VeryLongInt::VeryLongInt(unsigned long long n) {
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
    if (s.length() == 0)
        NaN = true;
    else if (s.length() > 1 && s[0] == '0')
        NaN = true;
    if (s[0] == '0') {
        Zero = true;
        digits.push_back(0);
    } else {
        for (char l : s) {
            if (!isdigit(l)) {
                NaN = true;
                Zero = false;
                break;
            }
        }
        if (!NaN){
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
        NaN = true;
    else if (!NaN && !Zero) {
        long int c = 0; //przeniesienie
        long long temp = 0;
        for (size_t i = 0; i < digits.size(); i++) {
            if (i < other.digits.size())
                temp = digits[i] - other.digits[i] + c;
            else
                temp = digits[i] + c;
            if (temp < 0) {
                temp += base;
                c = -1;
            }
            else
                c = 0;
            digits[i] = temp;
        }

        //Usuniecie wiodacych zer
        while (digits.size() > 1 && digits[digits.size()-1] == 0)
            digits.pop_back();
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
        NaN = true;
    else if (!NaN && !Zero) {
        if ((*this)<other)
            (*this).clear();
        else {
            VeryLongInt quotient;
            VeryLongInt dummy;
            for (long long int i = other.digits.size() - 1; i >= 0; i--) {
                if (dummy.Zero) {
                    dummy.Zero = false;
                    dummy.digits[0] = digits[digits.size()-1-i];
                }
                else {
                    dummy.digits.push_back(digits[digits.size()-1-i]);
                }
            }
            long long int l = digits.size() - other.digits.size();
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
                if (quotient.Zero) {
                    quotient.Zero = false;
                    quotient.digits[0] = a;
                }
                else {
                    quotient.digits.insert(quotient.digits.begin(), a);
                }
                dummy -= (other * VeryLongInt(a));
                l--;
                if (l >= 0) {
                    if (dummy.Zero) {
                        dummy.Zero = false;
                        dummy.digits[0] = digits[l];
                    }
                    else {
                        dummy.digits.insert(dummy.digits.begin(), digits[l]);
                    }
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
        *this = *this - (other * ((*this)/other));
    }
    return *this;
}

VeryLongInt& VeryLongInt::operator<<=(const unsigned int shift) {
    for (size_t i = 0; i < shift; ++i)
        (*this).multiply_by_2();
    return *this;
}

VeryLongInt& VeryLongInt::operator>>=(const unsigned int shift) {
    for (size_t i = 0; i < shift; ++i)
        (*this).divide_by_2();
    return *this;
}

const VeryLongInt operator+(const VeryLongInt &a, const VeryLongInt &b) {
    return VeryLongInt(a) += b;
}

const VeryLongInt operator-(const VeryLongInt &a, const VeryLongInt &b) {
    return VeryLongInt(a) -= b;
}

const VeryLongInt operator*(const VeryLongInt &a, const VeryLongInt &b) {
    return VeryLongInt(a) *= b;
}

const VeryLongInt operator/(const VeryLongInt &a, const VeryLongInt &b) {
    return VeryLongInt(a) /= b;
}

const VeryLongInt operator%(const VeryLongInt &a, const VeryLongInt &b) {
    return VeryLongInt(a) %= b;
}

const VeryLongInt VeryLongInt::operator>>(const unsigned int shift) const {
    return VeryLongInt(*this) >>= shift;
}

const VeryLongInt VeryLongInt::operator<<(const unsigned int shift) const {
    return VeryLongInt(*this) <<= shift;
}

bool operator==(const VeryLongInt &it, const VeryLongInt &other) {
    if (it.NaN || other.NaN)
        return false;
    if (it.digits.size() != other.digits.size())
        return false;
    else {
        unsigned long len = it.digits.size();
        for (unsigned long i = 0; i < len; i++)
            if (it.digits[i] != other.digits[i])
                return false;
        return true;
    }
}

bool operator!=(const VeryLongInt &it, const VeryLongInt &other) {
    if (it.NaN || other.NaN)
        return false;
    return !(it == other);
}

bool operator<(const VeryLongInt &it, const VeryLongInt &other) {
    if (it.NaN || other.NaN)
        return false;
     if (it.digits.size() < other.digits.size())
        return true;
    else if (it.digits.size() > other.digits.size())
        return false;
    else {
        long long i = it.digits.size() -1;
        while (i >= 0 && it.digits[i] == other.digits[i])
            i--;
        if (i<0)
            return false;
        else {
            if (it.digits[i] < other.digits[i])
                return true;
            return false;
        }
    }
    return false;
}

bool operator>(const VeryLongInt &it, const VeryLongInt &other) {
    if (it.NaN || other.NaN)
        return false;
    if (it == other)
        return false;
    else
        return (other < it);
}

bool operator<=(const VeryLongInt &it, const VeryLongInt &other) {
    if (it.NaN || other.NaN)
        return false;
    return !(it > other);
}

bool operator>=(const VeryLongInt &it, const VeryLongInt &other) {
    if (it.NaN || other.NaN)
        return false;
    return !(it < other);
}

bool VeryLongInt::isValid() const {
    return !NaN;
}

size_t VeryLongInt::numberOfBinaryDigits() const {
    if (NaN)
        return 0;
    size_t res = 1;
    VeryLongInt x = 2;
    while (x - 1 < (*this)) {
        res++;
        x *= 2;
    }
    return res;
}

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

bool VeryLongInt::is_divisible_by_2() const {
    if (NaN)
        return false;
    return digits[0] % 2 == 0;
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

    #include "very_long_int.h"
    #include <iostream>
    #include <cassert>
    #include <cstdlib>
    #include <ctime>

    using namespace std;

    const int MAXN = 9999999999999999999LL;
    unsigned long long randRange(unsigned long long a, unsigned long long b)
    {
      return a+rand()%(b-a+1);
    }

    /*int main()
    {
        VeryLongInt p;
        p = 42;
        VeryLongInt c(nullptr);
        cout << c.isValid();
      srand(time(NULL));

      int num_of_tests = 100000;
      VeryLongInt x(210000000);
      VeryLongInt y(38390241);
      cout << x / y << "\n" <<210000000 / 38390241;
      VeryLongInt a(5);
      cout << a;
        assert(5 == a);
        assert(a == a);
        assert( 5 <= a);
        assert( a <= 5);
        assert( a < 6);
        assert(4 < a);
        assert(6 != a);
        assert(a != 6);
      while (num_of_tests--) {
        unsigned long long a = randRange(0, MAXN);
        unsigned long long b = randRange(1, a);
        VeryLongInt x = VeryLongInt(a);
        VeryLongInt y = VeryLongInt(b);
        std::cout << "a " << a << "\n";
        std::cout << "b " << b << "\n";
        //std::cout << "a/b" << a / b << "\n";
        assert(x + y == VeryLongInt(a+b));
        assert(x - y == VeryLongInt(a-b));
        assert(x * y == VeryLongInt(a*b));
        assert(x / y == VeryLongInt(a/b));
        assert(x % y == VeryLongInt(a%b));
     }
    }*/


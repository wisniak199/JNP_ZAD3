//plik naglowkowy

#ifndef VERYLONGINT_H_
#define VERYLONGINT_H_

#include <vector>
#include <string>

class VeryLongInt {
    public:
        //KONSTRUKTORY
        VeryLongInt();
        VeryLongInt(const VeryLongInt &other) : digits(other.digits),
                                                NaN(other.NaN), Zero(other.Zero) {};
        VeryLongInt(VeryLongInt &&other) : digits(std::move(other.digits)),
                                            NaN(other.NaN), Zero(other.Zero){};
        VeryLongInt(const unsigned long long n);
        VeryLongInt(const unsigned long int n) : VeryLongInt(static_cast<unsigned long long>(n)) {};
        VeryLongInt(const unsigned int n) : VeryLongInt(static_cast<unsigned long long>(n)) {};
        VeryLongInt(const unsigned short n) : VeryLongInt(static_cast<unsigned long long>(n)) {};
        VeryLongInt(const long long n) : VeryLongInt(static_cast<unsigned long long>(n))
            {if (n < 0) {NaN = true; Zero = false;}};
        VeryLongInt(const long n) : VeryLongInt(static_cast<long long>(n)) {};
        VeryLongInt(const int n) : VeryLongInt(static_cast<long long>(n)) {};
        VeryLongInt(const short n) : VeryLongInt(static_cast<long long>(n)) {};
        explicit VeryLongInt(const std::string &s);
        explicit VeryLongInt(const char *c) : VeryLongInt(c == nullptr ? "" : std::string(c)) {};
        VeryLongInt(const char n) = delete;
        VeryLongInt(const unsigned char n) = delete;
        VeryLongInt(const bool n) = delete;

        //OPERATORY
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
        const VeryLongInt operator<<(const unsigned int shift) const;
        const VeryLongInt operator>>(const unsigned int shift) const;
        friend bool operator==(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
        friend bool operator!=(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
        friend bool operator<(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
        friend bool operator<=(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
        friend bool operator>(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
        friend bool operator>=(const VeryLongInt &verylongint1, const VeryLongInt &verylongint2);
        explicit operator bool() const { return !Zero && !NaN;};
        //wypisywanie
        friend std::ostream &operator<<(std::ostream &os, const VeryLongInt &verylongint) {
            return verylongint.write(os);
        }

        bool isValid() const;
        void clear();
        size_t numberOfBinaryDigits() const;

    private:
        typedef std::vector<unsigned long long> digit_list;
        static const unsigned long int base = 100000;
        static const int base_length = 5;

        //informacje o liczbie
        digit_list digits;
        bool NaN;
        bool Zero;

        VeryLongInt& multiply_by_2();
        VeryLongInt& divide_by_2();
        std::ostream &write(std::ostream &os) const;
        bool is_divisible_by_2() const;
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

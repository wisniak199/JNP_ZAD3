#include "very_long_int.h"

/** Magda: porownania, (-, /, >>, %), operatory
 *  Piotrek: kontruktory, (+, *, <<), BinaryDigits
 */

VeryLongInt& VeryLongInt::operator-=(const VeryLongInt &other){
	//Jezeli other > this return NaN!!!
	//Jezeli other /= NaN return NaN
	//Jezeli other = 0 return (*this) ?
	long int c = 0; /*przeniesienie*/
	for (long int i = 0; i < (*this).digits.size(); i++){
		if (i < other.digits.size())
			(*this).digits[i] = (*this).digits[i] - other.digits[i] +c;
		else
			(*this).digits[i] = (*this).digits[i] + c;
		if ((*this).digits[i] < 0){
			(*this).digits[i] += 1000000000; //TUTAJ BĘDZIE BAZA
			c = -1;
		}
		else
			c = 0;
	}
	/*Usuniecie wiodacych zer*/
	while ((*this).digits.size() > 1 && (*this).digits[(*this).digits.size()-1] == 0){
			(*this).digits.pop_back();
		}
	return *this;
}


VeryLongInt& VeryLongInt::operator/=(const VeryLongInt &denumerator){
	//jezeli denumerator = 0 return NaN!!!
 /*   VeryLongInt temp = 1;
    VeryLongInt one = 1;
    VeryLongInt quotient = 0;
    while ((*this) <= denumerator){
        denumerator <<= 1;
        temp <<= 1;
    }
    while (temp > one){
        denumerator >>= 1;
        temp >>= 1;
        if ((*this) >= denumerator){
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
}

bool VeryLongInt::operator!=(const VeryLongInt &other) const{
	return !(*this == other);
}

bool VeryLongInt::operator<(const VeryLongInt &other) const{
	if ((*this).digits.size() < other.digits.size())
		return true;
	else if ((*this).digits.size() > other.digits.size())
		return false;
	else{
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

bool VeryLongInt::operator>(const VeryLongInt &other) const{
	return (other < (*this));
}

bool VeryLongInt::operator<=(const VeryLongInt &other) const{
	return !((*this) > other);
}

bool VeryLongInt::operator>=(const VeryLongInt &other) const{
	return !((*this) < other);
}

/** Magda: porownania, (-, /, >>, %), operatory
 *  Piotrek: kontruktory, (+, *, <<), BinaryDigits
 */

// To CHYBA działa
VeryLongInt& operator/=(const VeryLongInt &denumerator);
    VeryLongInt temp = 1;
    VeryLongInt one = 1;
    VeryLongInt quotient = 0;

    while (this <= denumerator) {
        denumerator <<= 1;
        temp <<= 1;
    }

    while (temp > one) {
        denumerator >>= 1;
        temp >>= 1;

        if (this >= denumerator) {
            this -= denumerator;
            quotient += temp;
        }
    }

    return quotient;
}

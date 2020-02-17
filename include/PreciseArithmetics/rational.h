#ifndef INC_1ST_SEMESTER_RATIONAL_H
#define INC_1ST_SEMESTER_RATIONAL_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <limits>
#include <string>

namespace Numbers {

    class BigInteger: private std::vector<uint> {
    private:
        enum ESign { neg = 0, pos = 1 };
        // Convention: When value is zero, sign is positive
        ESign sign;
        void ensure_zero_sign();
        void shrink_zeros();
        void normalize();
        void internal_add(const BigInteger& right, bool substract);
    public:
        BigInteger();
        BigInteger(int val);
        BigInteger (uint val);
        BigInteger (size_t val);
        explicit BigInteger(std::string s);
        explicit operator bool() const;
        explicit operator int() const;

        BigInteger& operator+=(const BigInteger& right);
        BigInteger& operator-=(const BigInteger& right);
        BigInteger& operator*=(const BigInteger& right);
        BigInteger& operator/=(BigInteger right);
        BigInteger& operator%=(BigInteger right);

        std::string toString() const;
        BigInteger abs () const;
        bool isZero () const;
        friend bool operator<(const BigInteger& left, const BigInteger& right);
    };

    // Arithmetic operators

    BigInteger operator* (BigInteger left, const BigInteger& right) {
        return left *= right;
    }

    BigInteger operator- (const BigInteger& x) {
        return BigInteger(-1) * x;
    }

    BigInteger& BigInteger::operator-= (const BigInteger& right) {
        return *this += (-right);
    }

    BigInteger operator+ (BigInteger left, const BigInteger& right) {
        return left += right;
    }

    BigInteger operator- (BigInteger left, const BigInteger& right) {
        return left -= right;
    }

    BigInteger operator/ (BigInteger left, const BigInteger& right) {
        return left /= right;
    }

    BigInteger operator+ (const BigInteger& x) {
        return x;
    }

    BigInteger operator++ (BigInteger& x, int) {
        auto copy = x;
        x += 1;
        return copy;
    }

    BigInteger operator-- (BigInteger& x, int) {
        auto copy = x;
        x -= 1;
        return copy;
    }

    BigInteger& operator++ (BigInteger& x) {
        return x += 1;
    }

    BigInteger& operator--(BigInteger& x) {
        return x -= 1;
    }

    // Relational operators

    bool operator> (const BigInteger& left, const BigInteger& right) {
        return right < left;
    }

    bool operator!= (const BigInteger& left, const BigInteger& right) {
        return left < right || right < left;
    }

    bool operator<= (const BigInteger& left, const BigInteger& right) {
        return !(left > right);
    }

    bool operator>= (const BigInteger& left, const BigInteger& right) {
        return !(left < right);
    }

    bool operator== (const BigInteger& left, const BigInteger& right) {
        return !(left < right) && !(left > right);
    }

    // In/Out operators

    std::istream& operator>>(std::istream& stream, BigInteger& buf) {
        std::string str;
        stream >> str;
        buf = BigInteger(str);
        return stream;
    }

    std::ostream& operator<<(std::ostream &stream, BigInteger val) {
        return stream << val.toString();
    }

    BigInteger::BigInteger() : BigInteger(0) {}
    BigInteger::BigInteger (int val) : sign(val < 0 ? ESign::neg : ESign::pos) {
        push_back(::abs(val));
        normalize();
    }
    BigInteger::BigInteger (uint val) : sign(ESign::pos) {
        push_back(val);
        normalize();
    }

    BigInteger::BigInteger(std::string s) {
        std::reverse(s.begin(), s.end());
        BigInteger order = 1;
        sign = ESign::pos;
        for (size_t i = 0; i < s.size() && isdigit(s[i]); ++i, order *= 10) {
            operator+=(order * BigInteger(s[i] - '0'));
        }
        if (s.back() == '-') {
            sign = ESign::neg;
        }
    }

    BigInteger::operator bool() const {
        return !empty();
    }

    void BigInteger::internal_add(const BigInteger& right, bool substract) {
        bool carry = false;
        for (size_t i = 0; i < std::max(size(), right.size()) || carry; ++i) {
            if (i == size()) {
                push_back(0);
            }
            uint term = i < right.size() ? right[i] : 0;
            uint new_val = at(i) + (substract ? -1 : 1) * (carry + term);
            carry = (carry != 0 || term != 0) && (substract ? (new_val >= at(i)) : new_val <= at(i));
            at(i) = new_val;
        }
        normalize();
    }

    BigInteger& BigInteger::operator+=(const BigInteger& right) {
        BigInteger& left = *this;
        if (left.sign == right.sign) {
            internal_add(right, false);
        } else {
            if (left.abs() > right.abs()) {
                internal_add(right, true);
            } else {
                BigInteger copy(*this);
                *this = right;
                internal_add(copy, true);
            }
        }
        return left;
    }

    bool operator<(const BigInteger& left, const BigInteger& right) {
        if (left.sign != right.sign) {
            return left.sign < right.sign;
        }

        auto sign = left.sign;
        if (left.size() != right.size()) {
            return (left.size() < right.size()) ^ !sign;
        }

        auto iter_left = left.rbegin();
        auto iter_right = right.rbegin();

        assert (left.size() == right.size());

        // Comparing only left iterator
        // Safe because sizes are equal
        for (; iter_left < left.rend(); iter_left++, iter_right++) {
            if (*iter_left != *iter_right) {
                return *iter_left < *iter_right;
            }
        }

        return false;
    }

    BigInteger& BigInteger::operator*=(const BigInteger& right) {
        const BigInteger& left = *this;
        BigInteger res;
        res.sign = left.sign == right.sign ? ESign::pos : ESign::neg;
        res.resize(left.size() + right.size());
        for (size_t i = 0; i < left.size(); ++i) {
            uint carry = 0;
            for (size_t j = 0; j < right.size() || carry; ++j) {
                uint64_t current = uint64_t(res[i + j]) +
                                   uint64_t(at(i)) * uint64_t(j < right.size() ? right[j] : 0) +
                                   uint64_t(carry);
                // carry = current / base
                carry = (current >> 32u);
                // res[i + j] = current % base
                res[i + j] = current & 0xFFFFFFFF;
            }
        }
        res.normalize();
        return *this = res;
    }

    BigInteger& BigInteger::operator/=(BigInteger right) {
        BigInteger current = 0;
        BigInteger res = 0;
        res.sign = sign == right.sign ? ESign::pos : ESign::neg;
        *this = this->abs();
        right = right.abs();
        for (int i = int(size()) - 1; i >= 0; i--) {
            current = current * BigInteger(std::to_string(1llu << 32u)) + BigInteger(at(i));
            if (current >= right) {
                uint64_t l = 1, r = std::numeric_limits<unsigned int>::max();
                while (l < r - 1) {
                    uint m = (l + r) / 2;
                    BigInteger cc = BigInteger(m) * right;
                    if (cc <= current) {
                        l = m;
                    } else {
                        r = m;
                    }
                }
                uint cdiv = BigInteger(uint(r)) * right <= current ? r : l;
                res.push_back(cdiv);
                current -= BigInteger(cdiv) * right;
            } else {
                res.push_back(0);
            }
        }
        std::reverse(res.begin(), res.end());
        res.normalize();
        return *this = res;
    }

    BigInteger& BigInteger::operator%=(BigInteger right) {
        right = right.abs();
        return *this = *this - (*this / right) * right;
    }

    BigInteger BigInteger::abs() const {
        BigInteger copy(*this);
        copy.sign = ESign::pos;
        return copy;
    }

    bool BigInteger::isZero() const {
        return empty();
    }

    void BigInteger::ensure_zero_sign() {
        if (isZero()) {
            sign = ESign::pos;
        }
    }

    void BigInteger::normalize() {
        shrink_zeros();
        ensure_zero_sign();
    }

    void BigInteger::shrink_zeros() {
        while (!empty() && back() == 0) {
            pop_back();
        }
    }

    BigInteger operator% (BigInteger left, const BigInteger& right) {
        return left %= right;
    }

    BigInteger::operator int() const {
        assert(size() <= 1);
        if (isZero()) {
            return 0;
        }
        return int(at(0)) * (sign == ESign::neg ? -1 : 1);
    }

    std::string BigInteger::toString() const {
        if (isZero()) {
            return "0";
        }
        BigInteger copy = this->abs();
        std::string result;
        while (copy) {
            result += char('0' + int(copy % 10));
            copy /= 10;
        }
        result += (sign == ESign::neg ? "-" : "");
        std::reverse(result.begin(), result.end());
        return result;
    }

    BigInteger::BigInteger(size_t val) : BigInteger((uint)val) {}

    BigInteger gcd(const BigInteger &a, const BigInteger& b) {
        return a.isZero() ? b : gcd(b % a, a);
    }

    class Rational {
    private:
        BigInteger numerator, denominator;
        void normalize();

    public:
        Rational(BigInteger a, BigInteger b);
        Rational(const BigInteger &a);
        Rational(int a);
        Rational();
        explicit operator double() const;
        Rational inversed() const;
        Rational& operator+=(const Rational &right);
        Rational& operator-=(const Rational &right);
        Rational& operator*=(const Rational &right);
        Rational& operator/=(const Rational &right);
        std::string toString() const;
        std::string asDecimal(size_t precision = 0) const;
        bool operator<(const Rational &right) const;
    };

    // Arithmetic operators

    Rational operator* (Rational left, const Rational& right) {
        return left *= right;
    }

    Rational operator- (const Rational& x) {
        return Rational(-1) * x;
    }

    Rational operator+ (Rational left, const Rational& right) {
        return left += right;
    }

    Rational operator- (Rational left, const Rational& right) {
        return left -= right;
    }

    Rational operator/ (Rational left, const Rational& right) {
        return left /= right;
    }

    Rational operator+ (const Rational& x) {
        return x;
    }

    Rational operator++ (Rational& x, int) {
        auto copy = x;
        x += 1;
        return copy;
    }

    Rational operator-- (Rational& x, int) {
        auto copy = x;
        x -= 1;
        return copy;
    }

    Rational& operator++ (Rational& x) {
        return x += 1;
    }

    Rational& operator--(Rational& x) {
        return x -= 1;
    }

    void Rational::normalize() {
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        BigInteger currentGCD = gcd(numerator.abs(), denominator.abs());
        numerator /= currentGCD;
        denominator /= currentGCD;
    }

    bool Rational::operator<(const Rational &right) const {
        return numerator * right.denominator < denominator * right.numerator;
    }

    std::string Rational::asDecimal(size_t precision) const {
        std::string result = (numerator < 0 ? "-" : "");
        auto cnum = numerator.abs();
        auto cdet = denominator.abs();
        BigInteger intPart = cnum / cdet;
        result += intPart.toString();
        if (precision) {
            result += '.';
            for (size_t i = 0; i < precision; ++i) {
                cnum = 10 * (cnum % cdet);
                result += (cnum / cdet).toString();
            }
        }
        return result;
    }

    std::string Rational::toString() const {
        std::string result = numerator.toString();
        if (denominator != 1) {
            result += '/' + denominator.toString();
        }
        return result;
    }

    Rational& Rational::operator/=(const Rational& right) {
        return *this *= right.inversed();
    }

    Rational& Rational::operator*=(const Rational& right) {
        return *this = Rational(numerator * right.numerator, denominator * right.denominator);
    }

    Rational Rational::inversed() const {
        return Rational(denominator, numerator);
    }

    Rational::operator double() const {
        static const int DOUBLE_PRECISION = 16;
        return std::stod(asDecimal(DOUBLE_PRECISION));
    }

    Rational::Rational(int a) : numerator(a), denominator(1) {}

    Rational::Rational(const BigInteger& a) : Rational(a, 1) {}

    Rational::Rational(BigInteger a, BigInteger b) : numerator(std::move(a)), denominator(std::move(b)) {
        normalize();
    }

    Rational::Rational() : Rational(0) {}

    Rational& Rational::operator+=(const Rational &right) {
        return *this = Rational(numerator * right.denominator + denominator * right.numerator, denominator * right.denominator);
    }

    Rational&  Rational::operator-=(const Rational &right) {
        return operator+=(-right);
    }

    // Relational operators

    bool operator> (const Rational& left, const Rational& right) {
        return right < left;
    }

    bool operator!= (const Rational& left, const Rational& right) {
        return left < right || right < left;
    }

    bool operator<= (const Rational& left, const Rational& right) {
        return !(left > right);
    }

    bool operator>= (const Rational& left, const Rational& right) {
        return !(left < right);
    }

    bool operator== (const Rational& left, const Rational& right) {
        return !(left < right) && !(left > right);
    }

    // Out operator

    std::ostream& operator<<(std::ostream &stream, const Rational& val) {
        return stream << val.toString();
    }
}

using namespace Numbers;

#endif //INC_1ST_SEMESTER_RATIONAL_H
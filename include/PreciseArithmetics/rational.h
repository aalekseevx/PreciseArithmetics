#ifndef PRECISEARITHMETICS_RATIONAL_H
#define PRECISEARITHMETICS_RATIONAL_H

#include "PreciseArithmetics/integer.h"
#include "rational_base.h"

namespace pa {
    class Rational: private RationalBase {
    public:
        Rational();
        Rational(const int8_t& value);
        Rational(const int16_t& value);
        Rational(const int32_t& value);
        Rational(const int64_t& value);
        Rational(const int128_t& value);
        Rational(const uint8_t& value);
        Rational(const uint16_t& value);
        Rational(const uint32_t& value);
        Rational(const uint64_t& value);
        Rational(const uint128_t& value);
        Rational(const bool& value);
        Rational(const char& value);
        Rational(const double& value);
        Rational(const long double& value);
        explicit Rational(const Rational& value);
        explicit Rational(const Real& value);
        explicit Rational(const Complex& value);
        Rational(const std::string& value, std::ios_base::fmtflags flags);
        explicit Rational(const std::string& value);

        explicit operator int8_t() const;
        explicit operator int16_t() const;
        explicit operator int32_t() const;
        explicit operator int64_t() const;
        explicit operator int128_t() const;
        explicit operator uint8_t() const;
        explicit operator uint16_t() const;
        explicit operator uint32_t() const;
        explicit operator uint128_t() const;
        explicit operator bool() const;
        explicit operator char() const;
        explicit operator double() const;
        explicit operator long double() const;
        explicit operator Integer() const;
        operator Rational() const;
        operator Complex() const;

        Rational& operator+=(const Rational& right);
        Rational& operator-=(const Rational& right);
        Rational& operator*=(const Rational& right);
        Rational& operator/=(const Rational& right);
    };

    std::string to_string(
            const Rational& value,
            char fill,
            std::streamsize precision,
            std::streamsize width,
            std::ios_base::fmtflags flags);

    bool operator<(const Rational& left, const Rational& right);
    bool operator>(const Rational& left, const Rational& right);
    bool operator<=(const Rational& left, const Rational& right);
    bool operator>=(const Rational& left, const Rational& right);
    bool operator==(const Rational& left, const Rational& right);
    bool operator!=(const Rational& left, const Rational& right);

    Rational operator+(const Rational& right);
    Rational operator-(const Rational& right);

    Rational operator+(const Rational& left, const Rational& right);
    Rational operator*(const Rational& left, const Rational& right);
    Rational operator/(const Rational& left, const Rational& right);

    inline namespace literals {
        Rational operator ""_par(uint64_t value);
        Rational operator ""_par(long double value);
        Rational operator ""_par(const char16_t*, size_t);
    }
}

#endif //PRECISEARITHMETICS_RATIONAL_H

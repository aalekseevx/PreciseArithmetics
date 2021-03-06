#ifndef PRECISEARITHMETICS_INTEGER_H
#define PRECISEARITHMETICS_INTEGER_H

#include <cstdint>
#include <string>
#include "number_base.h"
#include <integer_base.h>

namespace pa {
    class Integer: private IntegerBase {
    public:
        class BitReference {
        private:
            size_t byte;
            std::byte shift;
        public:
            operator bool() const;
            BitReference& operator=(bool value);
            BitReference& operator=(const BitReference& value);
            BitReference& flip();
            bool operator~() const;
        };

        Integer();
        Integer(const int8_t& value);
        Integer(const int16_    t& value);
        Integer(const int32_t& value);
        Integer(const int64_t& value);
        Integer(const int128_t& value);
        Integer(const uint8_t& value);
        Integer(const uint16_t& value);
        Integer(const uint32_t& value);
        Integer(const uint64_t& value);
        Integer(const uint128_t& value);
        Integer(const bool& value);
        Integer(const char& value);
        Integer(const double& value);
        Integer(const long double& value);
        Integer(const std::string& value, std::ios_base::fmtflags flags);
        explicit Integer(const std::string& value);

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

        Integer& operator+=(const Integer& right);
        Integer& operator-=(const Integer& right);
        Integer& operator*=(const Integer& right);
        Integer& operator/=(const Integer& right);
        Integer& operator%=(const Integer& right);

        bool operator[] (size_t pos) const;
        BitReference& operator[](size_t pos);
        Integer& operator>>=(uint32_t);
        Integer& operator<<=(uint32_t);
        Integer& operator|=(uint32_t);
        Integer& operator&=(uint32_t);
        Integer& operator^=(uint32_t);
        Integer& flip_bits (size_t bits);
        Integer& flip_bytes (size_t bytes);
    };

    std::string to_string(
            const Integer& value,
            char fill,
            std::streamsize precision,
            std::streamsize width,
            std::ios_base::fmtflags flags);

    bool operator<(const Integer& left, const Integer& right);
    bool operator>(const Integer& left, const Integer& right);
    bool operator<=(const Integer& left, const Integer& right);
    bool operator>=(const Integer& left, const Integer& right);
    bool operator==(const Integer& left, const Integer& right);
    bool operator!=(const Integer& left, const Integer& right);

    Integer operator+(const Integer& right);
    Integer operator-(const Integer& right);

    Integer operator+(const Integer& left, const Integer& right);
    Integer operator*(const Integer& left, const Integer& right);
    Integer operator/(const Integer& left, const Integer& right);
    Integer operator%(const Integer& left, const Integer& right);

    inline namespace literals {
        Integer operator ""_pai(uint64_t value);
        Integer operator ""_pai(long double value);
        Integer operator ""_pai(const char16_t*, size_t);
    }

    Integer operator<<(const Integer& value, int shift);
    Integer operator>>(const Integer& value, int shift);
    Integer operator&(const Integer& left, const Integer& right);
    Integer operator|(const Integer& left, const Integer& right);
    Integer operator^(const Integer& left, const Integer& right);

    std::istream& operator>>(std::istream& stream, Integer& buf);
    std::ostream& operator<<(std::ostream& stream, const Integer& value);
}

#endif //PRECISEARITHMETICS_INTEGER_H

#ifndef PRECISEARITHMETICS_MATH_H
#define PRECISEARITHMETICS_MATH_H

namespace pa {
    // Trigonometric functions
    Real cos(const Real& x);
    Real sin(const Real& x);
    Real tan(const Real& x);
    Real acos(const Real& x);
    Real asin(const Real& x);
    Real atan(const Real& x);
    Real atan2(const Real& x);

    // Hyperbolic functions
    Real cosh(const Real& x);
    Real sinh(const Real& x);
    Real tanh(const Real& x);
    Real acosh(const Real& x);
    Real asinh(const Real& x);
    Real atanh(const Real& x);

    // Exponential and logarithmic functions
    Real exp(const Real& x);
    Real ln(const Real& x);
    Real log(const Real& base, const Real& x);

    // Power functions
    Real pow(const Real& base, const Real& exp);
    Integer pow(const Integer& base, const Integer& exp);
    Integer pow(const Integer& base, const Integer& exp, const Integer& mod);
    Real sqrt(const Real& x);
    Real cbrt(const Real& x);

    // Error and gamma functions
    Real erf(const Real& x);
    Real erfc(const Real& x);
    Real tgamma(const Real& x);
    Real lgamma(const Real& x);

    // Rounding and remainder functions
    Real ceil(const Real& x);
    Rational ceil(const Raional& x);
    Real floor(const Real& x);
    Rational floor(const Raional& x);
    Real fmod(const Real& x);
    Rational fmod(const Raional& x);
    Real trunc(const Real& x);
    Rational trunc(const Raional& x);
    Real round(const Real& x);
    Rational round(const Raional& x);
    Real remainder(const Real& x);
    Rational remainder(const Raional& x);
    Real remquo(const Real& x);
    Rational remquo(const Raional& x);


    Integer abs(const Integer& a);
    Rational abs(const Rational& a);
    Real abs(const Real& a);

    Integer gcd(const Integer& a, const Integer& b);
    Integer lcm(const Integer& a, const Integer& b);
}

#endif //PRECISEARITHMETICS_MATH_H

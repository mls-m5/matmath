//! Copyright © Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt

#pragma once

#include "pi.h"

namespace constmath {

//! Constant abs
template <typename T>
constexpr T cabs(T x) {
    if (x >= 0) {
        return x;
    }
    else {
        return -x;
    }
}

template <typename T>
constexpr T floor(T x) {
    long long num = (long long)x;
    if (x >= 0) {
        return (double)num;
    }
    else {
        return (double)(num - 1);
    }
}

template <typename T>
constexpr T round(T x) {
    return floor(x + .5);
}

namespace detail {
constexpr double ffactorial(double x) {
    double factorial = 1;
    double d = 2;
    for (int i = 2; i <= x; ++i) {
        factorial *= d;
        ++d;
    }
    return factorial;
}

//! pow with integer exponentials
constexpr double whole_pow(double x, int power) {
    double product = x;
    for (int i = 1; i < power; ++i) {
        product *= x;
    }
    return product;
}

} // namespace detail

//! Constexpr version of sin
template <typename T>
constexpr T sin(T x) {
    // Fold angle to always be around 0
    x -= (pi2)*round(x / (pi2));
    if (x > pi_2) {
        x = pi - x;
    }
    else if (x < -pi_2) {
        x = -pi - x;
    }

    // Tailor expansion around 0
    double ret = 0;
    double sign = 1;
    for (int i = 1; i < 20; i += 2) {
        ret += detail::whole_pow(x, i) / detail::ffactorial(i) * sign;
        sign *= -1;
    }
    return ret;
}

//! Constexpr version of cos
template <typename T>
constexpr T cos(T x) {
    return sin(x + pi / 2.);
}

template <typename T>
constexpr T atan2(T x, T y) {
    // Todo: implement this

    return 0;
}

template <typename T>
constexpr T sqrt(T x) {
    // Todo: implement this
    return 0;
}

} // namespace constmath

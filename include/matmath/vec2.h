//! Vec2: Copyright © Mattias Larsson Sköld 2020
#pragma once

#include "pi.h"
#include <cmath>

template <class T>
class Vec2T {
public:
    Vec2T(T x, T y);

    T x = 0, y = 0;

    constexpr T abs2() {
        return x * x + y * y;
    }

    constexpr T abs() {
        return sqrt(abs2());
    }

    constexpr T length() {
        return abs();
    }
};

template <class T>
T abs(const Vec2T<T> &v) {
    return v.abs();
}

using Vec2f = Vec2T<float>;
using Vec2d = Vec2T<double>;
using Vec2 = Vec2d;

//! Vec2: Copyright © Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence

#pragma once

#include "matmath/export.h"

#ifndef matmath_use_modules

#include "pi.h"
#include <cmath>
#include <limits>
#include <ostream>

#if __cplusplus >= 201103L
#include <tuple>
#endif

#endif

matmath_export template <class T>
class Vec2T {
public:
    static constexpr auto e = std::numeric_limits<T>::min();
    T x = 0, y = 0;

    constexpr Vec2T(T x, T y) : x(x), y(y) {}

    constexpr Vec2T() = default;
    constexpr Vec2T(const Vec2T &) = default;
    constexpr Vec2T(Vec2T &&) = default;
    constexpr Vec2T &operator=(const Vec2T &) = default;
    constexpr Vec2T &operator=(Vec2T &&) = default;

    constexpr T abs2() const {
        return x * x + y * y;
    }

    constexpr T abs() const {
        return sqrt(abs2());
    }

    constexpr T length() const {
        return abs();
    }

    //! Relative angle
    constexpr T angle(T a) const {
        T angle = atan2(x, y) - a;

        while (angle < pi) {
            angle += pi2;
        }

        while (angle > pi) {
            angle -= pi2;
        }
        return angle;
    }

    constexpr T angle() const {
        return atan2(x, y);
    }

    constexpr Vec2T operator+(Vec2T v) const {
        return {x + v.x, y + v.y};
    }

    constexpr Vec2T operator-(Vec2T v) const {
        return {x - v.x, y - v.y};
    }

    //! Vector multiplication
    //! @returns double
    constexpr double operator*(Vec2T v) const {
        return x * v.x + y * v.y;
    }

    constexpr Vec2T operator*(T value) const {
        return {x * value, y * value};
    }

    constexpr Vec2T &operator*=(T value) {
        x *= value;
        y *= value;
        return *this;
    }

    constexpr Vec2T &scale(T value) {
        return *this *= value;
    }

    constexpr Vec2T operator/(Vec2T v) const {
        return {x / v.x, y / v.y};
    }

    constexpr Vec2T operator/(T value) const {
        return {x / value, y / value};
    }

    constexpr Vec2T &operator+=(Vec2T v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    constexpr Vec2T &operator-=(Vec2T v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    constexpr bool isNear(const Vec2T &v, T e) const {
        return !(x + e < v.x || x > v.x + e || y + e < v.y || y > v.y + e);
    }

    constexpr bool operator==(const Vec2T &v) const {
        return isNear(v, e);
    }

#if __cplusplus >= 201103L && !defined(matmath_use_modules)
    // Convert to reference tuple<...>
    // Operators to use with for example std::tie
    // syntax example:
    // VecT v(1, 2, 3);
    // T x, y, z
    // std::tie(x, y, z) = v
    // result: x = 1, y = 2, z = 3
    operator std::tuple<T &, T &>() {
        return {x, y};
    }
#endif
};

matmath_export template <class T>
constexpr T abs(const Vec2T<T> &v) {
    return v.abs();
}

matmath_export template <class T>
constexpr auto operator*(T amount, Vec2T<T> v) {
    return v * amount;
}


matmath_export template <class T>
constexpr std::ostream &operator<<(std::ostream &stream, const Vec2T<T> &v) {
    stream << "(" << v.x << ", " << v.y << ")";
    return stream;
}

matmath_export using Vec2f = Vec2T<float>;
matmath_export using Vec2d = Vec2T<double>;
matmath_export using Vec2 = Vec2d;

//! vec.h: Copyright Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt

#pragma once

#ifndef matmath_export

#define matmake_export

#include <cmath>
#include <ostream>
#if __cplusplus >= 201103L
#include <tuple>
#endif

#include "pi.h"

#endif

matmath_export template <typename T>
class VecT {
public:
    T x = 0, y = 0, z = 0;

    constexpr VecT() = default;
    constexpr VecT(T nx, T ny, T nz = 0) : x(nx), y(ny), z(nz) {}

    template <typename U>
    constexpr VecT(const VecT<U> &v) : x(v.x), y(v.y), z(v.z) {}

    template <class pointerType>
    constexpr VecT(const pointerType *p) {
        x = p[0];
        y = p[1];
        z = p[2];
    }

    template <class U>
    constexpr VecT &operator=(const VecT<U> &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    template <class pointerType>
    constexpr VecT &operator=(const pointerType *p) {
        x = p[0];
        y = p[1];
        z = p[2];
        return *this;
    }

    constexpr VecT &operator+=(VecT v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr VecT &operator-=(VecT v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr VecT &operator*=(T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    constexpr VecT &operator/=(T t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }

    constexpr VecT operator-() const {
        return *this * -1.;
    }

    //! @brief scale all axis independently
    constexpr VecT &scale(T x, T y, T z) {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        return *this;
    }

    //! @brief scale all axis by the same amount
    constexpr VecT operator*(T t) const {
        return VecT(x * t, y * t, z * t);
    }
    constexpr VecT operator/(T t) const {
        return VecT(x / t, y / t, z / t);
    }

    constexpr T operator*(VecT v2) const {
        return x * v2.x + y * v2.y + z * v2.z;
    }

    constexpr VecT operator-(VecT v) const {
        return VecT(x - v.x, y - v.y, z - v.z);
    }

    constexpr VecT operator+(VecT v) const {
        return VecT(x + v.x, y + v.y, z + v.z);
    }

    constexpr T &operator[](int index) {
        return (&x)[index];
    }

    constexpr inline T operator[](int index) const {
        return (&x)[index];
    }

    constexpr inline void operator()(T x, T y, T z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template <class U>
    constexpr bool operator==(VecT<U> v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    constexpr T abs() const {
        return sqrt(x * x + y * y + z * z);
    }

    constexpr T abs2() const {
        return x * x + y * y + z * z;
    }

    constexpr VecT &normalize() {
        *this /= abs();
        return *this;
    }

    constexpr VecT cross(VecT v) const {
        // clang-format off
        return VecT(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
        // clang-format on
    }

    //! Relative angle
    constexpr T angle(T a) const {
        T angle = atan2(x, y) + a;

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

#if __cplusplus >= 201103L
    // Convert to reference tuple<...>
    // Operators to use with for example std::tie
    // syntax example:
    // VecT v(1, 2, 3);
    // T x, y, z
    // std::tie(x, y, z) = v
    // result: x = 1, y = 2, z = 3
    constexpr operator std::tuple<T &, T &>() {
        return {x, y};
    }
    constexpr operator std::tuple<T &, T &, T &>() {
        return {x, y, z};
    }
#endif
};

//! @brief Write as a string to output
matmath_export template <class T>
constexpr std::ostream &operator<<(std::ostream &out, const VecT<T> &v) {
    out << v.x << ", " << v.y << ", " << v.z;
    return out;
}

matmath_export template <class T, class U>
constexpr auto operator*(T f, const VecT<U> &v) {
    return v * f;
}

matmath_export template <typename T>
constexpr T abs(const VecT<T> &v) {
    return v.abs();
}

matmath_export template <class Ar, typename T>
constexpr void serialize(Ar &ar, VecT<T> &v) {
    ar &v.x;
    ar &v.y;
    ar &v.z;
}

matmath_export using Vecd = VecT<double>;
matmath_export using Vecf = VecT<float>;
matmath_export using Vec = Vecd;

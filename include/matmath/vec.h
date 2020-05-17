/*
 * vec.h
 *
 *      Author: Mattias Larsson Sköld
 */

#pragma once

#include <cmath>
#include <ostream>
#if __cplusplus >= 201103L
#include <tuple>
#endif

#include "pi.h"

template <typename T>
class VecT {
public:
    T x = 0, y = 0, z = 0;

    VecT() = default;
    VecT(T nx, T ny, T nz = 0) : x(nx), y(ny), z(nz) {
    }

    template <typename U>
    VecT(const VecT<U> &v) : x(v.x), y(v.y), z(v.z) {
    }

    template <class pointerType>
    VecT(const pointerType *p) {
        x = p[0];
        y = p[1];
        z = p[2];
    }

    template <class U>
    VecT &operator=(const VecT<U> &v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    template <class pointerType>
    VecT &operator=(const pointerType *p) {
        x = p[0];
        y = p[1];
        z = p[2];
        return *this;
    }

#if __cplusplus >= 201103L
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
    operator std::tuple<T &, T &, T &>() {
        return {x, y, z};
    }
#endif

    VecT &operator+=(VecT v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    VecT &operator-=(VecT v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    VecT &operator*=(T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    VecT &operator/=(T t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }

    VecT operator-() const {
        return *this * -1.;
    }

    //! @brief scale all axis independently
    VecT &scale(T x, T y, T z) {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        return *this;
    }

    //! @brief scale all axis by the same amount
    VecT operator*(T t) const {
        return VecT(x * t, y * t, z * t);
    }
    VecT operator/(T t) const {
        return VecT(x / t, y / t, z / t);
    }

    T operator*(VecT v2) const {
        return x * v2.x + y * v2.y + z * v2.z;
    }

    VecT operator-(VecT v) const {
        return VecT(x - v.x, y - v.y, z - v.z);
    }

    VecT operator+(VecT v) const {
        return VecT(x + v.x, y + v.y, z + v.z);
    }

    inline T &operator[](int index) {
        return (&x)[index];
    }

    inline T operator[](int index) const {
        return (&x)[index];
    }

    inline void operator()(T x, T y, T z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template <class U>
    bool operator==(VecT<U> v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    T abs() const {
        return sqrt(x * x + y * y + z * z);
    }

    T abs2() const {
        return x * x + y * y + z * z;
    }

    VecT &normalize() {
        *this /= abs();
        return *this;
    }

    VecT cross(VecT v) const {
        // clang-format off
        return VecT(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
        // clang-format on
    }

    T angle(T a) const {
        T angle = atan2(x, y) + a;

        while (angle < pi) {
            angle += pi2;
        }

        while (angle > pi) {
            angle -= pi2;
        }
        return angle;
    }

    T angle() const {
        return atan2(x, y);
    }
};

//! @brief Write as a string to output
template <class T>
inline std::ostream &operator<<(std::ostream &out, const VecT<T> &v) {
    out << v.x << ", " << v.y << ", " << v.z;
    return out;
}

template <class T, class U>
inline auto operator*(T f, const VecT<U> &v) {
    return v * f;
}

template <typename T>
inline T abs(const VecT<T> &v) {
    return v.abs();
}

template <class Ar, typename T>
void serialize(Ar &ar, VecT<T> &v) {
    ar &v.x;
    ar &v.y;
    ar &v.z;
}

using Vec = VecT<double>;
using Vecf = VecT<float>;

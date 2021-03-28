/*
 * quaternion.h
 *
 *  Created on: 2 okt. 2018
 *      Author: Mattias Larsson Sköld
 */

#pragma once

#include "matmath/export.h"

#ifndef matmath_use_modules

#include "matrix.h"
#include <cmath>

#endif

matmath_export struct Quaternion {
    typedef float T;
    T w = 1, x = 0, y = 0, z = 0;

    Quaternion() {}
    Quaternion(T w, T x = 0, T y = 0, T z = 0) : w(w), x(x), y(y), z(z) {}

    // Create quaternion from a rotation matrix
    Quaternion(const Matrix<T> matrix) {
        float diagonal = matrix.x1 + matrix.y2 + matrix.z3;
        if (diagonal > 0) {
            float w4 = (float)(sqrt(diagonal + 1.) * 2.);
            w = w4 / 4.;
            x = (matrix.y3 - matrix.z2) / w4;
            y = (matrix.z1 - matrix.x3) / w4;
            z = (matrix.x2 - matrix.y1) / w4;
        }
        else if ((matrix.x1 > matrix.y2) && (matrix.x1 > matrix.z3)) {
            float x4 =
                (float)(sqrt(1. + matrix.x1 - matrix.y2 - matrix.z3) * 2.);
            w = (matrix.y3 - matrix.z2) / x4;
            x = x4 / 4.;
            y = (matrix.y1 + matrix.x2) / x4;
            z = (matrix.z1 + matrix.x3) / x4;
        }
        else if (matrix.y2 > matrix.z3) {
            float y4 =
                (float)(sqrt(1. + matrix.y2 - matrix.x1 - matrix.z3) * 2.);
            w = (matrix.z1 - matrix.x3) / y4;
            x = (matrix.y1 + matrix.x2) / y4;
            y = y4 / 4.;
            z = (matrix.z2 + matrix.y3) / y4;
        }
        else {
            float z4 =
                (float)(sqrt(1. + matrix.z3 - matrix.x1 - matrix.y2) * 2.);
            w = (matrix.x2 - matrix.y1) / z4;
            x = (matrix.z1 + matrix.x3) / z4;
            y = (matrix.z2 + matrix.y3) / z4;
            z = z4 / 4.;
        }
    }

    Quaternion operator*(const Quaternion q) const {
        //		T e = q.x, f = q.y, g = q.z, h = q.w;
        return Quaternion(w * q.w - x * q.x - y * q.y - z * q.z,
                          w * q.x + x * q.w + y * q.z - z * q.y,
                          w * q.y + y * q.w + z * q.x - x * q.z,
                          w * q.z + z * q.w + x * q.y - y * q.x);
    }

    Quaternion &operator*=(const Quaternion q) {
        return *this = *this * q;
    }

    Quaternion operator/(const Quaternion q) const {
        return *this * q.inverse();
    }

    Quaternion &operator*=(T value) {
        w *= value;
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    Quaternion &operator/=(T value) {
        w /= value;
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    operator Matrix<T>() const {
        T xy = x * y;
        T xz = x * z;
        T xw = x * w;
        T yz = x * z;
        T yw = y * w;
        T zw = z * w;
        T x2 = x * x;
        T y2 = y * y;
        T z2 = z * z;
        return Matrix<T>({1 - 2 * (y2 + z2),
                          2 * (xy - zw),
                          2 * (xz + yw),
                          0,

                          2 * (xy + zw),
                          1 - 2 * (x2 + z2),
                          2 * (yz - xw),
                          0,

                          2 * (xz - yw),
                          2 * (yz + xw),
                          1 - 2 * (x2 + y2),
                          0,

                          0,
                          0,
                          0,
                          1});
    }

    // Interpolates between this and q using normalized lerp
    Quaternion interpolate(const Quaternion &q, T blend) const {
        float blendI = 1. - blend;
        if (q.dot(*this) < 0) {
            return Quaternion(blendI * w + blend * -q.w,
                              blendI * x + blend * -q.x,
                              blendI * y + blend * -q.y,
                              blendI * z + blend * -q.z)
                .normalize();
        }
        else {
            return Quaternion(blendI * w + blend * q.w,
                              blendI * x + blend * q.x,
                              blendI * y + blend * q.y,
                              blendI * z + blend * q.z)
                .normalize();
        }
    }

    inline Quaternion operator*(T value) const {
        return Quaternion(w * value, x * value, y * value, z * value);
    }

    inline Quaternion inverse() const {
        return conjugate() / abs2();
    }

    Quaternion &normalize() {
        *this /= abs();
        return *this;
    }

    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    Quaternion operator+(const Quaternion q) const {
        return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
    }

    Quaternion operator-(const Quaternion q) const {
        return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
    }

    T dot(Quaternion q) const {
        return w * q.w + x * q.x + y + q.y + z * q.z;
    }

    T abs2() const {
        return w * w + x * x + y * y + z * z;
    }

    T abs() const {
        return sqrt(abs2());
    }

    inline T norm() const {
        return abs();
    }
};

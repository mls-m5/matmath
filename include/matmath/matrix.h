//!  Created on: 3 sep. 2018
//! Copyright Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt

#pragma once

#include "export.h"

#ifndef matmath_use_modules

#include "vec.h"
#include <cmath>

#endif

matmath_export template <class T>
class Matrix {
public:
    // clang-format off
    constexpr Matrix(T x1    , T y1 = 0, T z1 = 0, T w1 = 0, //
           T x2 = 0, T y2 = 1, T z2 = 0, T w2 = 0, //
           T x3 = 0, T y3 = 0, T z3 = 1, T w3 = 0, //
           T x4 = 0, T y4 = 0, T z4 = 0, T w4 = 1)
        : x1(x1), y1(y1), z1(z1), w1(w1)
        , x2(x2), y2(y2), z2(z2), w2(w2)
        , x3(x3), y3(y3), z3(z3), w3(w3)
        , x4(x4), y4(y4), z4(z4), w4(w4)
    {}
    // clang-format on

    constexpr Matrix(
        VecT<T> row1, VecT<T> row2, VecT<T> row3, VecT<T> row4, T w4 = 1)
        : Matrix(
              // clang-format off
              row1.x, row1.y, row1.z, 0,
              row2.x, row2.y, row2.z, 0,
              row3.x, row3.y, row3.z, 0,
              row4.x, row4.y, row4.z, w4
              // clang-format on
          ) {}

    constexpr Matrix() = default;
    constexpr Matrix(const Matrix &) = default;
    constexpr Matrix &operator=(const Matrix &) = default;

    constexpr T *get() {
        return &x1;
    }

    constexpr T *get() const {
        return &x1;
    }

    constexpr T &at(int i) {
        return (&x1)[i];
    }

    constexpr T at(int i) const {
        return (&x1)[i];
    }

    constexpr T &at(int x, int y) {
        return at(x + y * 4);
    }

    constexpr T at(int x, int y) const {
        return at(x + y * 4);
    }

    constexpr T &operator[](int i) {
        return at(i);
    }

    constexpr T operator[](int i) const {
        return at(i);
    }

    constexpr T operator()(int i) const {
        return at(i);
    }

    constexpr T &operator()(int i) {
        return at(i);
    }

    constexpr T operator()(int x, int y) const {
        return at(x, y);
    }

    constexpr T &operator()(int x, int y) {
        return at(x, y);
    }

    constexpr operator T *() {
        return &x1;
    }

    constexpr operator const T *() const {
        return &x1;
    }

    constexpr T *data() {
        return &x1;
    }

    constexpr const T *data() const {
        return &x1;
    }

    constexpr Matrix &identity() {
        // clang-format off
        *this = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
        };
        // clang-format on
        return *this;
    }

    constexpr Matrix &clear() {
        for (int i = 0; i < 16; ++i) {
            at(i) = 0;
        }
        return *this;
    }

    constexpr Matrix &fill(T value) {
        for (int i = 0; i < 16; ++i) {
            at(i) = value;
        }
        return *this;
    }

    constexpr Matrix &translateGlobal(T x, T y, T z = 0) {
        x4 += x;
        y4 += y;
        z4 += z;
        return *this;
    }

    constexpr Matrix &translate(T x, T y, T z = 0) {
        x4 += x1 * x + x2 * y + x3 * z;
        y4 += y1 * x + y2 * y + y3 * z;
        z4 += z1 * x + z2 * y + z3 * z;
        return *this;
    }

    constexpr Matrix &translateGlobal(Vec p) {
        return translateGlobal(p.x, p.y, p.z);
    }

    constexpr Matrix &translate(Vec p) {
        return translate(p.x, p.y, p.z);
    }

    // Set the tranlation in absolute numbers
    constexpr Matrix &setTranslation(T x, T y, T z = 0.) {
        x4 = x;
        y4 = y;
        z4 = z;
        return *this;
    }

    constexpr Matrix &setTranslation(const Vec &v) {
        return setTranslation(v.x, v.y, v.z);
    }

    //! Scale including positioning
    constexpr Matrix &scaleGlobal(T x, T y, T z = 1.) {
        // clang-format off
        x1 *= x; y1 *= y; z1 *= z;
        x2 *= x; y2 *= y; z2 *= z;
        x3 *= x; y3 *= y; z3 *= z;
        x4 *= x; y4 *= y; z4 *= 1;
        // clang-format on
        return *this;
    }

    constexpr Matrix &scaleGlobal(Vec v) {
        return scaleGlobal(v.x, v.y, v.z);
    }

    //! Scale local only
    constexpr Matrix &scale(T x, T y, T z = {}) {
        // clang-format off
        x1 *= x; y1 *= x; z1 *= x;
        x2 *= y; y2 *= y; z2 *= y;
        x3 *= z; y3 *= z; z3 *= z;
        // clang-format on
        return *this;
    }

    constexpr Matrix &scale(const Vec &v) {
        return scale(v.x, v.y, v.z);
    }

    // Return the global scale
    //! Actually not constexpr before cmath functions is
    constexpr Vec scaleGlobal() const {
        return Vec{
            Vec{x1, y1, z1}.abs(),
            Vec{x2, y2, z2}.abs(),
            Vec{x3, y3, z3}.abs(),
        };
    }

    constexpr Matrix &scaleGlobal(T s) {
        return scaleGlobal(s, s, s);
    }

    constexpr Matrix &normalizeScale() {
        auto l1 = (T)1. / sqrt(x1 * x1 + y1 * y1 + z1 * z1);
        auto l2 = (T)1. / sqrt(x2 * x2 + y2 * y2 + z2 * z2);
        auto l3 = (T)1. / sqrt(x3 * x3 + y3 * y3 + z3 * z3);
        // clang-format off
        x1 *= l1; y1 *= l1; z1 *= l1;
        x2 *= l2; y2 *= l2; z2 *= l2;
        x3 *= l3; y3 *= l3; z3 *= l3;
        // clang-format on
        return *this;
    }

    constexpr Matrix operator*(const Matrix &m) const {
        Matrix product;

        for (int y = 0; y < 4; ++y)
            for (int x = 0; x < 4; ++x) {
                T value = 0;
                for (int i = 0; i < 4; ++i) {
                    T temp = at(x, i) * m(i, y);
                    value += temp;
                }
                product(x, y) = value;
            }

        return product;
    }

    constexpr Vec operator*(const Vec &v) const {
        Vec product;

        for (int x = 0; x < 3; ++x) {
            T value = 0;
            for (int i = 0; i < 3; ++i) {
                T temp = at(x, i) * v[i];
                value += temp;
            }
            product[x] = value + (&x4)[x];
        }

        return product;
    }

    constexpr Matrix &operator*=(const Matrix &m) {
        Matrix mTemp(*this * m);
        (*this) = mTemp;
        return *this;
    }

    template <class type>
    constexpr Matrix operator-(const Matrix<type> &m) const {
        Matrix difference;

        for (int i = 0; i < 16; ++i) {
            difference[i] = at(i) - m[i];
        }

        return difference;
    }

    constexpr T sum() const {
        T sum = 0;
        for (int i = 0; i < 16; ++i) {
            sum += at(i);
        }
        return sum;
    }

    constexpr T abs2() const {
        T sum = 0;
        for (int i = 0; i < 16; ++i) {
            T value = at(i);
            sum += value * value;
        }
        return sum;
    }

    constexpr T abs() const {
        return sqrt(abs2());
    }

    // Return a transposed copy of the matrix
    constexpr Matrix transpose() const {
        Matrix ret;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                ret(i, j) = (*this)(j, i);
            }
        return ret;
    }

    // The heaviest invertion method
    // Invert a invertible matrix
    // Consider using inverseOrthogonal or inverseNormalized for faster
    // computations
    constexpr Matrix inverse() const {
        // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
        auto &m = *this;
        Matrix inv;
        double det = 0;

        int i = 0;

        // clang-format off
        inv[0] = m[5]  * m[10] * m[15] -
                 m[5]  * m[11] * m[14] -
                 m[9]  * m[6]  * m[15] +
                 m[9]  * m[7]  * m[14] +
                 m[13] * m[6]  * m[11] -
                 m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] +
                  m[4]  * m[11] * m[14] +
                  m[8]  * m[6]  * m[15] -
                  m[8]  * m[7]  * m[14] -
                  m[12] * m[6]  * m[11] +
                  m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9] * m[15] -
                 m[4]  * m[11] * m[13] -
                 m[8]  * m[5] * m[15] +
                 m[8]  * m[7] * m[13] +
                 m[12] * m[5] * m[11] -
                 m[12] * m[7] * m[9];

        inv[12] = -m[4]  * m[9] * m[14] +
                   m[4]  * m[10] * m[13] +
                   m[8]  * m[5] * m[14] -
                   m[8]  * m[6] * m[13] -
                   m[12] * m[5] * m[10] +
                   m[12] * m[6] * m[9];

        inv[1] = -m[1]  * m[10] * m[15] +
                  m[1]  * m[11] * m[14] +
                  m[9]  * m[2] * m[15] -
                  m[9]  * m[3] * m[14] -
                  m[13] * m[2] * m[11] +
                  m[13] * m[3] * m[10];

        inv[5] = m[0]  * m[10] * m[15] -
                 m[0]  * m[11] * m[14] -
                 m[8]  * m[2] * m[15] +
                 m[8]  * m[3] * m[14] +
                 m[12] * m[2] * m[11] -
                 m[12] * m[3] * m[10];

        inv[9] = -m[0]  * m[9] * m[15] +
                  m[0]  * m[11] * m[13] +
                  m[8]  * m[1] * m[15] -
                  m[8]  * m[3] * m[13] -
                  m[12] * m[1] * m[11] +
                  m[12] * m[3] * m[9];

        inv[13] = m[0]  * m[9] * m[14] -
                  m[0]  * m[10] * m[13] -
                  m[8]  * m[1] * m[14] +
                  m[8]  * m[2] * m[13] +
                  m[12] * m[1] * m[10] -
                  m[12] * m[2] * m[9];

        inv[2] = m[1]  * m[6] * m[15] -
                 m[1]  * m[7] * m[14] -
                 m[5]  * m[2] * m[15] +
                 m[5]  * m[3] * m[14] +
                 m[13] * m[2] * m[7] -
                 m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] +
                  m[0]  * m[7] * m[14] +
                  m[4]  * m[2] * m[15] -
                  m[4]  * m[3] * m[14] -
                  m[12] * m[2] * m[7] +
                  m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] -
                  m[0]  * m[7] * m[13] -
                  m[4]  * m[1] * m[15] +
                  m[4]  * m[3] * m[13] +
                  m[12] * m[1] * m[7] -
                  m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] +
                   m[0]  * m[6] * m[13] +
                   m[4]  * m[1] * m[14] -
                   m[4]  * m[2] * m[13] -
                   m[12] * m[1] * m[6] +
                   m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
                  m[1] * m[7] * m[10] +
                  m[5] * m[2] * m[11] -
                  m[5] * m[3] * m[10] -
                  m[9] * m[2] * m[7] +
                  m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
                 m[0] * m[7] * m[10] -
                 m[4] * m[2] * m[11] +
                 m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] -
                 m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
                   m[0] * m[7] * m[9] +
                   m[4] * m[1] * m[11] -
                   m[4] * m[3] * m[9] -
                   m[8] * m[1] * m[7] +
                   m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
                  m[0] * m[6] * m[9] -
                  m[4] * m[1] * m[10] +
                  m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] -
                  m[8] * m[2] * m[5];
        // clang-format on

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0) {
            throw "could not invert matrix";
        }

        det = 1.0 / det;

        for (i = 0; i < 16; i++) {
            inv[i] *= det;
        }

        return inv;
    }

    // Inverse a orthogonal rotation + translation matrix
    // That is a matrix with rows 1 2 3 othogonal and row 4 as translation
    constexpr Matrix inverseOrthogonal() const {
        // clang-format off
        auto l1 = (T)1. / (x1 * x1 + x2 * x2 + x3 * x3);
        auto l2 = (T)1. / (y1 * y1 + y2 * y2 + y3 * y3);
        auto l3 = (T)1. / (z1 * z1 + z2 * z2 + z3 * z3);
        Matrix p = {
            x1 * l1, x2 * l1, x3 * l1, 0,
            y1 * l2, y2 * l2, y3 * l2, 0,
            z1 * l3, z2 * l3, z3 * l3, 0,
            -x4 * x1 * l1 - y4 * y1 * l2 - z4 * z1 * l3,
            -x4 * x2 * l1 - y4 * y2 * l2 - z4 * z2 * l3,
            -x4 * x3 * l1 - y4 * y3 * l2 - z4 * z3 * l3,
             1
        };
        // clang-format on

        return p;
    }

    // Inverse a normalized transformation matrix
    // That is a matrix with rows 1 2 3 with x*x + y*y + z*z = 1
    constexpr Matrix inverseNormalized() const {
        // clang-format off
        Matrix p = {
            x1, x2, x3, 0,
            y1, y2, y3, 0,
            z1, z2, z3, 0,
            -x4 * x1 - y4 * y1 - z4 * z1,
            -x4 * x2 - y4 * y2 - z4 * z2,
            -x4 * x3 - y4 * y3 - z4 * z3,
            1
        };
        // clang-format on

        return p;
    }

    constexpr Vec row(int num) const {
        return Vec(at(0, num), at(1, num), at(2, num));
    }

    [[deprecated("use row(...) instead")]] inline Vec getRow(int num) const {
        return row(num);
    }

    constexpr Vec col(int num) const {
        return Vec(at(num, 0), at(num, 1), at(num, 2));
    }

    [[deprecated("use col(...) instead")]] inline Vec getCol(int num) const {
        return col(num);
    }

    constexpr Matrix &row(int num, Vec v) {
        at(0, num) = v.x;
        at(1, num) = v.y;
        at(2, num) = v.z;

        return *this;
    }

    [[deprecated]] inline Matrix &setRow(int num, Vec v) {
        return row(num, v);
    }

    constexpr Matrix &col(int num, Vec v) {
        at(num, 0) = v.x;
        at(num, 1) = v.y;
        at(num, 2) = v.z;

        return *this;
    }

    [[deprecated("use col(...) instead")]] inline Matrix &setCol(int num,
                                                                 Vec v) {
        return col(num, v);
    }

    constexpr Matrix flippedCol(int col1, int col2) const {
        Matrix ret = *this;
        for (int y = 0; y < 4; ++y) {
            ret(col1, y) = at(col2, y);
            ret(col2, y) = at(col1, y);
        }
        return ret;
    }

    constexpr static Matrix Identity() {
        // clang-format off
        return Matrix({
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
        });
        // clang-format on
    }

    constexpr static Matrix Translation(T x, T y, T z = 0) {
        // clang-format off
        return Matrix({
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            x, y, z, 1,
        });
        // clang-format on
    }

    constexpr static Matrix Translation(Vec v) {
        return Translation(v.x, v.y, v.z);
    }

    template <class type>
    constexpr Matrix &operator=(const type *p) {
        for (int i = 0; i < 16; ++i) {
            at(i) = p(i);
        }
        return *this;
    }

    //! Convert to Matrix of new type
    template <class type>
    constexpr operator Matrix<type>() const {
        // clang-format off
        return Matrix<type> {
            x1, y1, z1, w1,
            x2, y2, z2, w2,
            x3, y3, z3, w3,
            x4, y4, z4, w4,
        };
        // clang-format on
    }

    constexpr static Matrix Scale(T x, T y, T z = 1) {
        // clang-format off
        return Matrix({
            x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1,
        });
        // clang-format on
    }

    constexpr static Matrix Scale(T s) {
        return Scale(s, s, s);
    }

    constexpr Matrix &rotate(T angle, Vec axis) {
        Vec position = row(3);
        *this = rotationFromThis(angle, axis);
        row(3, position);
        return *this;
    }

    constexpr static Matrix Rotation(T angle, Vec axis) {
        return Identity().rotationFromThis(angle, axis);
    }

    // This is borrowed from
    // https://github.com/LWJGL --> Matrix4f
    constexpr Matrix rotationFromThis(T angle, Vec axis) const {
        Matrix dest = Identity();
        T c = (T)cos(angle);
        T s = (T)sin(angle);
        T ci = 1.0f - c;
        T xy = axis.x * axis.y;
        T yz = axis.y * axis.z;
        T xz = axis.x * axis.z;
        T xs = axis.x * s;
        T ys = axis.y * s;
        T zs = axis.z * s;

        T f00 = axis.x * axis.x * ci + c;
        T f01 = xy * ci + zs;
        T f02 = xz * ci - ys;
        // n[3] not used
        T f10 = xy * ci - zs;
        T f11 = axis.y * axis.y * ci + c;
        T f12 = yz * ci + xs;
        // n[7] not used
        T f20 = xz * ci + ys;
        T f21 = yz * ci - xs;
        T f22 = axis.z * axis.z * ci + c;

        T t00 = x1 * f00 + x2 * f01 + x3 * f02;
        T t01 = y1 * f00 + y2 * f01 + y3 * f02;
        T t02 = z1 * f00 + z2 * f01 + z3 * f02;
        T t03 = w1 * f00 + w2 * f01 + w3 * f02;
        T t10 = x1 * f10 + x2 * f11 + x3 * f12;
        T t11 = y1 * f10 + y2 * f11 + y3 * f12;
        T t12 = z1 * f10 + z2 * f11 + z3 * f12;
        T t13 = w1 * f10 + w2 * f11 + w3 * f12;
        dest.x3 = x1 * f20 + x2 * f21 + x3 * f22;
        dest.y3 = y1 * f20 + y2 * f21 + y3 * f22;
        dest.z3 = z1 * f20 + z2 * f21 + z3 * f22;
        dest.w3 = w1 * f20 + w2 * f21 + w3 * f22;
        dest.x1 = t00;
        dest.y1 = t01;
        dest.z1 = t02;
        dest.w1 = t03;
        dest.x2 = t10;
        dest.y2 = t11;
        dest.z2 = t12;
        dest.w2 = t13;
        return dest;
    }

    constexpr static Matrix RotationX(double angle) {
        Matrix m = Identity();
        double c = cos(angle);
        double s = sin(angle);
        m.y2 = c;
        m.z2 = -s;
        m.y3 = s;
        m.z3 = c;
        return m;
    }

    constexpr static Matrix RotationY(double angle) {
        Matrix m = Identity();
        double c = cos(angle);
        double s = sin(angle);
        m.x1 = c;
        m.z1 = s;
        m.x3 = s;
        m.z3 = -c;
        return m;
    }

    static constexpr Matrix RotationZ(double angle) {
        Matrix m = Identity();
        double c = cos(angle);
        double s = sin(angle);
        m.x1 = c;
        m.y1 = -s;
        m.x2 = s;
        m.y2 = c;
        return m;
    }

    constexpr Matrix rotationPart() const {
        Matrix product = *this;
        product.x4 = 0;
        product.y4 = 0;
        product.z4 = 0;
        product.w4 = 1;
        return product;
    }

    // Notice the format
    // The rows below is what is usually
    // columns in mathematical examples
    // for examel x4, y4 and z4 is used for translation
    // and x1 to x3 is used to describe the x-axis

    T x1 = 1, y1 = 0, z1 = 0, w1 = 0;
    T x2 = 0, y2 = 1, z2 = 0, w2 = 0;
    T x3 = 0, y3 = 0, z3 = 1, w3 = 0;
    T x4 = 0, y4 = 0, z4 = 0, w4 = 1;
};

matmath_export typedef Matrix<float> Matrixf;
matmath_export typedef Matrix<double> Matrixd;

matmath_export template <class T>
constexpr T abs(Matrix<T> m) {
    return m.abs();
}

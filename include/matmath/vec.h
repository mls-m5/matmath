/*
 * vec.h
 *
 *      Author: Mattias Larsson Sköld
 */

#ifndef __Vec__
#define __Vec__

#include "common.h" //for PI
#include <math.h>
#include <ostream>
#if __cplusplus >= 201103L
#include <tuple>
#endif

class Vec {
public:
    double x = 0, y = 0, z = 0;

    Vec() = default;
    Vec(double nx, double ny, double nz = 0) : x(nx), y(ny), z(nz) {}
    Vec(const Vec &v) = default;
    template <class pointerType>
    Vec(const pointerType *p) {
        x = p[0];
        y = p[1];
        z = p[2];
    }

    Vec &operator=(const Vec &) = default;

    template <class pointerType>
    Vec &operator=(const pointerType *p) {
        x = p[0];
        y = p[1];
        z = p[2];
        return *this;
    }

#if __cplusplus >= 201103L
    // Convert to reference tuple<...>
    // Operators to use with for example std::tie
    // syntax example:
    // Vec v(1, 2, 3);
    // double x, y, z
    // std::tie(x, y, z) = v
    // result: x = 1, y = 2, z = 3
    operator std::tuple<double &, double &>() {
        return {x, y};
    }
    operator std::tuple<double &, double &, double &>() {
        return {x, y, z};
    }
#endif

    Vec &operator+=(Vec v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec &operator-=(Vec v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec &operator*=(double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec &operator/=(double t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }

    Vec operator-() const {
        return *this * -1.;
    }

    //! @brief scale all axis independently
    Vec &scale(double x, double y, double z) {
        this->x *= x;
        this->y *= y;
        this->z *= z;
        return *this;
    }

    //! @brief scale all axis by the same amount
    Vec operator*(double t) const {
        return Vec(x * t, y * t, z * t);
    }
    Vec operator/(double t) const {
        return Vec(x / t, y / t, z / t);
    }

    double operator*(Vec v2) const {
        return x * v2.x + y * v2.y + z * v2.z;
    }

    Vec operator-(Vec v) const {
        return Vec(x - v.x, y - v.y, z - v.z);
    }

    Vec operator+(Vec v) const {
        return Vec(x + v.x, y + v.y, z + v.z);
    }

    inline double &operator[](int index) {
        return (&x)[index];
    }

    inline double operator[](int index) const {
        return (&x)[index];
    }

    inline void operator()(double x, double y, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(Vec v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    double abs() const {
        return sqrt(x * x + y * y + z * z);
    }

    double abs2() const {
        return x * x + y * y + z * z;
    }

    Vec &normalize() {
        *this /= abs();
        return *this;
    }

    Vec cross(Vec v) const {
        // clang-format off
        return Vec(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
        // clang-format on
    }

    double angle(double a) const {
        using namespace Engine;
        double angle = atan2(x, y) + a;


        while (angle < pi) {
            angle += pi2;
        }

        while (angle > pi) {
            angle -= pi2;
        }
        return angle;
    }

    double angle() const {
        return atan2(x, y);
    }
};

//! @brief Write as a string to output
inline std::ostream &operator<<(std::ostream &out, const Vec &v) {
    out << v.x << ", " << v.y << ", " << v.z;
    return out;
}


template <class T>
inline Vec operator*(T f, const Vec &v) {
    return v * f;
}


class MapVec {
public:
    MapVec() {}
    MapVec(int nx, int ny, double z = 0) : x(nx), y(ny), z(z) {}
    MapVec(const Vec &v, int size = 1.) {
        conv(v, size);
    }
    int x = 0, y = 0;
    double z = 0;

    void conv(Vec v, int size = 1.) {
        x = v.x - (double)size / 2.;
        y = v.y - (double)size / 2.;
        z = v.z;
    }

    inline Vec toVec(int size = 1.) const {
        return Vec(
            (double)x + (double)size / 2., (double)y + (double)size / 2., z);
    }

    inline MapVec &operator()(int x, int y, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
        return *this;
    }

    // Return the manhatan/taxicab-distance
    int l1Norm() {
        return std::abs(x) + std::abs(y);
    }

    int diagonalDistance() {
        auto absx = std::abs(x);
        auto absy = std::abs(y);
        bool xIsMore = absx > absy;
        return xIsMore * absx + (!xIsMore) * absy;
    }

    float abs() {
        return sqrt((double)abs2());
    }

    int abs2() {
        return x * x + y * y;
    }

    MapVec &operator+=(MapVec v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    MapVec &operator-=(MapVec v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    MapVec operator+(MapVec v) const {
        return MapVec(x + v.x, y + v.y);
    }

    MapVec operator-(MapVec v) const {
        return MapVec(x - v.x, y - v.y);
    }
    bool operator==(MapVec v) const {
        if (v.x == x && v.y == y) {
            return true;
        }
        return false;
    }
    bool operator!=(MapVec v) const {
        if (v.x == x && v.y == y) {
            return false;
        }
        return true;
    }

    operator bool() const {
        return x != 0 || y != 0;
    }
};

inline double abs(const Vec &v) {
    return v.abs();
}

template <class Ar>
void serialize(Ar &ar, Vec &v) {
    ar &v.x;
    ar &v.y;
    ar &v.z;
}

#endif

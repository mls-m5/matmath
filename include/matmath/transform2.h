//! Copyright © Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt
#pragma once

#include "constmath.h"
#include "vec2.h"
#include <iosfwd>

template <class T>
class Transform2T {
public:
    static constexpr auto e = std::numeric_limits<T>::min();

    constexpr Transform2T(Vec2T<T> pos, Vec2T<T> rotation = {1, 0})
        : pos(pos), rotation(rotation) {}

    constexpr Transform2T(Vec2T<T> pos, double angle, double scale = 1)
        : pos(pos), rotation(scale * constmath::cos(angle),
                             scale * constmath::sin(angle)) {}

    // Everything else is default
    constexpr Transform2T() = default;
    ~Transform2T() = default;
    constexpr Transform2T(const Transform2T &) = default;
    constexpr Transform2T(Transform2T &) = default;
    constexpr Transform2T &operator=(const Transform2T &) = default;
    constexpr Transform2T &operator=(Transform2T &) = default;

    //! Translate and rotate
    template <class U>
    constexpr Vec2T<U> operator*(Vec2T<U> v) const {
        return {
            v.x * rotation.x + v.y * rotation.y + pos.x,
            v.y * rotation.x - v.x * rotation.y + pos.y,
        };
    }

    constexpr Transform2T operator*(Transform2T other) const {
        return {
            *this * other.pos,
            {
                rotation.x * other.rotation.x - rotation.y * other.rotation.y,
                rotation.x * other.rotation.y + rotation.y * other.rotation.x,
            },
        };
    }

    constexpr bool operator==(Transform2T t) const {
        return pos == t.pos;
    }

    constexpr static Transform2T Scale(double value) {
        return Transform2T{{}, {value, 0}};
    }

    constexpr static Transform2T Translate(Vec2T<T> v) {
        return {v};
    }

    constexpr static Transform2T Identity() {
        return {};
    }

    //! More readable version to create rotation transform
    constexpr static Transform2T Rotation(double angle) {
        return {{}, angle};
    }

    Vec2T<T> pos;
    Vec2T<T> rotation = {1, 0};
};

template <class T>
constexpr Transform2T<T> lerp(Transform2T<T> a, Transform2T<T> b, T amount) {
    auto angleA = a.rotation.angle();
    auto dAngle = b.rotation.angle(angleA);
    if (dAngle > pi) {
        dAngle -= pi2;
    }
    else if (dAngle < -pi) {
        dAngle += pi2;
    }

    const auto angleC = angleA + dAngle * amount;
    const auto lenA = abs(a.rotation);
    const auto lenB = abs(b.rotation);
    const auto lenC = lenA * (1. - amount) + lenB * amount;
    const auto posC = a.pos * (1. - amount) + b.pos * amount;

    return {posC, angleC, lenC};
}

template <class T>
constexpr std::ostream &operator<<(std::ostream &stream,
                                   const Transform2T<T> &t) {
    stream << "transform<" << t.pos << " " << t.rotation << ">";
    return stream;
}

using Transform2d = Transform2T<double>;
using Transform2f = Transform2T<float>;
using Transform2 = Transform2d;

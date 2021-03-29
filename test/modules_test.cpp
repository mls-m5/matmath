
#include "mls-unit-test/unittest.h"
#include <limits>

import matmath.constmath;
import matmath.mathfwd;
import matmath.matrix;
import matmath.pi;
import matmath.quaternion;
import matmath.transform2;
import matmath.vec2;
import matmath.vec;

TEST_SUIT_BEGIN

TEST_CASE("do something with a matrix") {
    auto matrix = Matrixf::RotationZ(1);

    std::cout << matrix << std::endl;
}

TEST_CASE("do something with vec") {
    auto vec = Vecd(1, 2, 3);

    std::cout << vec << std::endl;
}

TEST_CASE("do something with pi") {
    std::cout << "pi = " << pi << std::endl;
}

TEST_CASE("do somoething with constmath") {
    std::cout << constmath::floor(1.) << std::endl;
}

TEST_CASE("do something with quaternion") {
    auto quaternion = Quaternion{};

    std::cout << quaternion.w << std::endl;
}

TEST_CASE("do something with transform2") {
    auto transform2 = Transform2{};

    std::cout << transform2.pos.x << std::endl;
}

TEST_CASE("do something with vec2") {
    auto vec2 = Vec2{};

    std::cout << vec2.x << std::endl;
}

TEST_SUIT_END

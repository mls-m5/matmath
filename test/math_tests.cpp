#include "matmath/constmath.h"
#include "mls-unit-test/unittest.h"

constexpr double small_number = 0.00000001;

constexpr bool isNear(double a, double b, double e = small_number) {
    return a + e > b && a < b + e;
}

TEST_SUIT_BEGIN

TEST_CASE("sin") {
    using namespace constmath;
    // These tests runs in compile time
    static_assert(isNear(sin(0.), 0.));
    static_assert(isNear(sin(pi / 6.), 1. / 2.));
    static_assert(isNear(sin(pi / -6.), -1. / 2.));
    static_assert(isNear(sin(pi / 2), 1.));
    static_assert(isNear(sin(-pi / 2), -1.));
    static_assert(isNear(sin(pi), 0.));

    static_assert(isNear(sin(30), sin(-30)));
    static_assert(isNear(sin(340.), sin(340. + pi * 2)));
}

TEST_CASE("cos") {
    using namespace constmath;
    static_assert(isNear(cos(0), 1));
}

TEST_CASE("catan2") {
    using namespace constmath;
    //    static_assert(isNear(atan2(0, 1), 0.));
    //    static_assert(isNear(atan2(1, 1), 1.));
}

TEST_SUIT_END

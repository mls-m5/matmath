#include "matmath/vec2.h"
#include "mls-unit-test/unittest.h"

constexpr double smallNumber = .000001;

TEST_SUIT_BEGIN

TEST_CASE("initialization") {
    auto v = Vec2{1, 3};
    auto v2 = Vec2(1, 3);
    (void)v;
    (void)v2;
}

TEST_CASE("comparison") {
    ASSERT(Vec2(1, 2).isNear(Vec2(1, 2), smallNumber), "not near");
}

TEST_CASE("vector multiplication") {
    ASSERT_NEAR(Vec2(1, 0) * Vec2(0, 1), 0, smallNumber);
    ASSERT_NEAR(Vec2(2, 0) * Vec2(2, 0), 4, smallNumber);
    ASSERT_NEAR(Vec2(0, 2) * Vec2(0, 2), 4, smallNumber);
}

TEST_CASE("double multiplication)") {
    EXPECT((Vec2(2, 3) * 2).isNear(Vec2(4, 6), smallNumber));
}

TEST_SUIT_END

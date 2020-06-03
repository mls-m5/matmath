// Copyright © Mattias Larsson Sköld

#include "matmath/transform2.h"
#include "matmath/vec2.h"

#include "mls-unit-test/unittest.h"

TEST_SUIT_BEGIN

TEST_CASE("instantiation") {
    {
        constexpr Transform2 t;

        static_assert(t.pos.x == 0, "wrong default value");
        static_assert(t.pos.y == 0, "wrong default value");
        static_assert(t.rotation.x == 1, "wrong default value");
        static_assert(t.rotation.y == 0, "wrong default value");
    }

    {
        constexpr Transform2 t{{1, 2}, 0};

        static_assert(t.pos.x == 1, "wrong default value");
        static_assert(t.pos.y == 2, "wrong default value");
        static_assert(t.rotation.x == 1, "wrong default value");
        static_assert(t.rotation.y == 0, "wrong default value");
    }
}

TEST_CASE("comparison") {
    constexpr auto t1 = Transform2{{0, 0}};
    constexpr auto t2 = Transform2{{0, 1}};

    ASSERT_EQ(t1, t1);
    ASSERT_NE(t1, t2);
}

TEST_CASE("lerping position") {
    constexpr Transform2 t1{{0, 0}};
    constexpr Transform2 t2{{2, 2}};

    const auto t3 = lerp(t1, t2, .5);

    const auto t4 = Transform2{{1, 1}};

    ASSERT_EQ(t3, t4);
}

TEST_CASE("lerping rotation") {
    constexpr Transform2 t1({0, 0}, 0);
    constexpr Transform2 t2({0, 0}, 2);

    const auto t3 = lerp(t1, t2, .5);
    const auto t4 = Transform2({0, 0}, 1);

    ASSERT_EQ(t3, t4);
}

TEST_CASE("transform position") {
    constexpr Transform2 t1({1, 2}, 0);

    ASSERT_EQ((t1 * Vec2{3, 4}), (Vec2{4, 6}));
}

TEST_CASE("multiplying transforms (pos only)") {
    {
        constexpr Transform2 t1({0, 0}, 0);
        constexpr Transform2 t2({3, 4}, 0);

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{3, 4}, 0};
        ASSERT_EQ(t3, t4);
    }
    {
        constexpr Transform2 t1({3, 4}, 0);
        constexpr Transform2 t2({0, 0}, 0);

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{3, 4}, 0};
        ASSERT_EQ(t3, t4);
    }
    {
        constexpr Transform2 t1({1, 2}, 0);
        constexpr Transform2 t2({3, 4}, 0);

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{4, 6}};
        ASSERT_EQ(t3, t4);
    }
}

TEST_CASE("multiplying transforms (rot only)") {
    {
        constexpr Transform2 t1({0, 0}, 0);
        constexpr Transform2 t2({0, 0}, {0, 1});

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{0, 0}, {0, 1}};
        ASSERT_EQ(t3, t4);
    }
    {
        constexpr Transform2 t1({0, 0}, {0, 1});
        constexpr Transform2 t2({0, 0}, 0);

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{0, 0}, {0, 1}};
        ASSERT_EQ(t3, t4);
    }
    {
        constexpr Transform2 t1({0, 0}, {0, 1});
        constexpr Transform2 t2({0, 0}, {0, 1});

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{0, 0}, {-1, 0}};
        ASSERT_EQ(t3, t4);
    }
}

TEST_CASE("multiplying transforms (pos rot)") {
    {
        constexpr Transform2 t1({1, 2}, 0);
        constexpr Transform2 t2({0, 0}, {0, 1});

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{1, 2}, {0, 1}};
        ASSERT_EQ(t3, t4);
    }
    {
        constexpr Transform2 t1({0, 0}, {0, 1});
        constexpr Transform2 t2({1, 2}, 0);

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{2, -1}, {0, 1}};
        ASSERT_EQ(t3, t4);
    }
    {
        constexpr Transform2 t1({0, 0}, {-1, 0});
        constexpr Transform2 t2({1, 0}, {1, 0});

        const auto t3 = t1 * t2;
        const auto t4 = Transform2{{-1, 0}, {-1, 0}};
        ASSERT_EQ(t3, t4);
    }
}
TEST_SUIT_END

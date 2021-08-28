/*
 * matrix_test.cpp
 *
 *  Created on: 4 sep. 2018
 *      Author: mattias
 */

#include "matmath/matrix.h"
#include "mls-unit-test/unittest.h"
#include <iomanip> //setprecision

constexpr double epsilon = 0.000000001;

constexpr bool almostEqual(float a, float b, double epsilon = ::epsilon) {
    return std::abs(b - a) < epsilon;
}

template <class T1, class T2>
constexpr bool almostEqual(T1 a, T2 b, double epsilon = ::epsilon) {
    return abs(b - a) < epsilon;
}

using namespace std;
template <class Matrix>
void printMatrixFunction(Matrix m) {
    for (int y = 0; y < 4; ++y) {

        for (int x = 0; x < 4; ++x) {
            cout << setprecision(4) << m(x, y) << "\t";
        }
        cout << endl;
    }
}

#define printMatrix(variable)                                                  \
    cout << #variable << ":" << endl;                                          \
    printMatrixFunction(variable);                                             \
    cout << endl;

using namespace std;
void printVectorFunction(Vec v) {
    for (int x = 0; x < 3; ++x) {
        cout << setprecision(4) << v[x] << "\t";
    }
    cout << endl;
}

#define printVector(variable)                                                  \
    cout << #variable << ":" << endl;                                          \
    printVectorFunction(variable);

TEST_SUIT_BEGIN

TEST_CASE("inverse not normalized") {
    const auto identity = Matrixf::Identity();
    auto m = Matrixf::Identity();

    ASSERT_LT((identity - m).sum(), epsilon);

    m = Matrixf::RotationX(2);
    m.scaleGlobal(2, 3, 4);

    auto inv = m.inverse();

    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);

    m.translateGlobal(Vec(30, 40, 50));
    m *= Matrixf::RotationZ(.4);
    inv = m.inverse();
    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);
}

TEST_CASE("inverse translation") {
    const auto identity = Matrixf::Identity();
    auto m = identity;

    ASSERT_LT((identity - m).sum(), epsilon);

    m.translateGlobal(20, 30, 40);

    auto inv = m.inverse();
    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);
}

TEST_CASE("inverse scale") {
    const auto identity = Matrixf::Identity();
    auto m = identity;

    ASSERT_LT((identity - m).sum(), epsilon);

    m.scaleGlobal(20, 30, 40);

    auto inv = m.inverse();
    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);
}

TEST_CASE("inverse scale + translation") {
    const auto identity = Matrixf::Identity();
    auto m = identity;

    ASSERT_LT((identity - m).sum(), epsilon);

    m.scaleGlobal(20, 30, 40);
    m.translateGlobal(50, 60, 70);

    auto inv = m.inverse();
    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);
}

TEST_CASE("inverse non orthogonal") {
    const auto identity = Matrixf::Identity();
    // clang-format off
    Matrixf m({
        1,2,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    });
    // clang-format on

    auto inv = m.inverse();
    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);
}

TEST_CASE("inverse scale + rot + translation") {
    const auto identity = Matrixf::Identity();
    auto m = identity;

    ASSERT_LT((identity - m).sum(), epsilon);

    m.scaleGlobal(20, 30, 40);
    m *= m.RotationX(.4);
    m *= m.RotationY(.4);
    m.translateGlobal(50, 60, 70);

    auto inv = m.inverse();
    printMatrix(m);
    printMatrix(inv);
    printMatrix(m * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m * inv - identity).abs2(), epsilon);
    ASSERT_LT((inv * m - identity).abs2(), epsilon);
}

TEST_CASE("inverse normalized rot+trans") {
    const auto identity = Matrixf::Identity();
    auto m2 = Matrixf::Identity();

    ASSERT_LT((identity - m2).sum(), epsilon);

    m2 = Matrixf::RotationX(2);

    auto inv = m2.inverseNormalized();

    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m2 * inv - identity).abs2(), epsilon);

    m2.translateGlobal(Vec(30, 40, 50));
    m2 *= Matrixf::RotationZ(.4);
    inv = m2.inverseNormalized();
    printMatrix(m2);
    printMatrix(inv);
    printMatrix(m2 * inv);
    ASSERT_GT(inv.abs2(), epsilon);
    ASSERT_LT((m2 * inv - identity).abs2(), epsilon);
}

TEST_CASE("move vertex") {
    const auto identity = Matrixf::Identity();
    auto m = identity;

    ASSERT_LT((identity - m).sum(), epsilon);

    Vec v(2, 3, 4);

    printVector(v);

    m.translateGlobal(1, 2, 3);

    printMatrix(m);

    printVector(m * v);
    ASSERT_LT((m * v - Vec(3, 5, 7)).abs2(), epsilon);
}

TEST_CASE("rotate vertex") {
    auto m = Matrixf::RotationZ(pi);

    Vec v(2, 3, 4);

    printVector(v);

    printMatrix(m);

    printVector(m * v);
    ASSERT_LT((m * v - Vec(-2, -3, 4)).abs2(), epsilon);
}

TEST_CASE("normalize scale") {
    auto m = Matrixf::Scale(2, 3, 4);

    printMatrix(m);

    m.normalizeScale();

    printMatrix(m);

    ASSERT_LT((m - Matrixf::Identity()).abs2(), epsilon);
}

TEST_CASE("transpose") {
    // clang-format off
    Matrixf m1({
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10,11,12,
        13,14,15,16
    });

    Matrixf m2({
        1, 5, 9,13,
        2, 6,10,14,
        3, 7,11,15,
        4, 8,12,16
    });
    // clang-format on

    printMatrix(m1);
    printMatrix(m1.transpose());
    printMatrix(m2);
    ASSERT(almostEqual(m1.transpose(), m2),
           "m1.transpose() and m2 are not equal");
}

TEST_CASE("set row") {
    // clang-format off
    Matrixf m1({
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    });

    Matrixf m2({
        0, 0, 0, 0,
        1, 2, 3, 0,
        4, 5, 6, 0,
        0, 0, 0, 0,
    });
    // clang-format on

    printMatrix(m1);

    m1.row(1, Vec(1, 2, 3));
    m1.row(2, Vec(4, 5, 6));

    printMatrix(m1);
    printMatrix(m2);
    ASSERT(almostEqual(m1, m2), "m1.transpose() and m2 are not equal");
}

TEST_CASE("convert from float to double") {
    // clang-format off
    Matrixf m1({
        1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
        13,14,15,16
    });
    // clang-format on

    Matrixd m2 = m1;

    printMatrix(m1);
    printMatrix(m2);
    ASSERT(almostEqual(m1, m2), "conversion failed");
}

TEST_CASE("local scaling of matrices") {
    // clang-format off
    Matrixf m1({
        3, 4, 0, 0,
        0, 4, 3, 0,
        0, 6, 8, 0,
        0, 0, 0, 1,
    });
    // clang-format on

    printMatrix(m1);
    printVector(m1.scaleGlobal());

    ASSERT(almostEqual(m1.scaleGlobal(), Vec(5, 5, 10)),
           "scale is wrong in matrix");

    auto m2 = m1;
    m2.scale(Vec(2, 2, .5));
    printMatrix(m2);
    printVector(m2.scaleGlobal());
    ASSERT(almostEqual(m2.scaleGlobal(), Vec(10, 10, 5)),
           "scale is wrong in matrix after rescaling");
}

TEST_CASE("simple translation") {
    constexpr auto m = [] {
        auto m = Matrixf{};

        m.translate(2, 3, 4);

        return m;
    }();

    static_assert(almostEqual(m.x4, 2.f));
    static_assert(almostEqual(m.y4, 3.f));
    static_assert(almostEqual(m.z4, 4.f));
}

TEST_CASE("rotated translation") {
    constexpr auto m = [] {
        // Cols for each axis
        // clang-format off
        auto m = Matrixf{
            1, 5, 9,  0,
            2, 6, 10, 0,
            3, 7, 11, 0,
            4, 8, 12, 0,
        };
        // clang-format on

        m.translate(2, 2, 2);

        return m;
    }();

    static_assert(almostEqual(m.x4, (1.f + 2.f + 3.f) * 2.f + 4.f));
    static_assert(almostEqual(m.y4, (5.f + 6.f + 7.f) * 2.f + 8.f));
    static_assert(almostEqual(m.z4, (9.f + 10.f + 11.f) * 2.f + 12.f));
}

TEST_SUIT_END

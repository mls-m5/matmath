/*
 * quaternion-test.cpp
 *
 *  Created on: 2 okt. 2018
 *      Author: Mattias Larsson Sköld
 */

#include "matmath/quaternion.h"
#include "mls-unit-test/unittest.h"
#include <iomanip> //setprecision

using namespace std;

float epsilon = 0.00001;

std::ostream &operator<<(std::ostream &os, Quaternion const &q) {
    return os << "Q(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z
              << ")";
}

// template <class Matrix>
std::ostream &operator<<(std::ostream &os, Matrixf m) {
    for (int y = 0; y < 4; ++y) {

        for (int x = 0; x < 4; ++x) {
            auto val = m(x, y);
            os << setprecision(4) << (float)((abs(val) < epsilon) ? 0. : val)
               << "\t";
        }
        os << endl;
    }
    return os;
}

bool isAlmostEqual(const Matrixf &m1,
                   const Matrixf &m2,
                   float epsilon = ::epsilon) {
    return (m1 - m2).sum() < epsilon;
}

TEST_SUIT_BEGIN

TEST_CASE("Quaternion basic operations") {
    Quaternion q1 = {1, 2, 3, 4};
    Quaternion q2 = {5, 6, 7, 8};

    Quaternion expectedAddResult = {6, 8, 10, 12};
    Quaternion expectedSubResult = {-4, -4, -4, -4};
    Quaternion expectedMultResult = {-60, 12, 30, 24};

    ASSERT_LT(((q1 + q2) - expectedAddResult).abs2(), epsilon);
    ASSERT_LT(((q1 - q2) - expectedSubResult).abs2(), epsilon);

    cout << q1 << endl;
    cout << q2 << endl;
    cout << q1 * q2 << endl;
    cout << expectedMultResult << endl;
    ASSERT_LT(((q1 * q2) - expectedMultResult).abs2(), epsilon);
}

TEST_CASE("conversion to matrix") {
    {
        Quaternion q(1, 2, 3, 4);

        cout << q << endl;
        cout << (Matrixf)q << endl;
    }
}

TEST_CASE("Conversion from matrix") {

    {
        auto m = Matrixf::Identity();
        Quaternion q(m);

        ASSERT(isAlmostEqual(m, q), "conversion with identity failed");
    }

    {
        auto m = Matrixf::RotationX(pi / 2.);
        Quaternion q(m);

        cout << m << endl;
        cout << q << endl;
        cout << (Matrixf)q << endl;

        ASSERT(isAlmostEqual(m, q), "conversion with 90 deg x rot failed");
    }

    {
        auto m = Matrixf::Rotation(2, Vec(1, 0, 0));
        Quaternion q(m);

        //		cout << "x rotation" << endl;
        //		cout << m << endl;
        //		cout << q << endl;
        //		cout << (Matrixf) q << endl;

        ASSERT(isAlmostEqual(m, q), "conversion with x-rotation failed");
    }

    {
        auto m = Matrixf::Rotation(2, Vec(0, 1, 0));
        Quaternion q(m);

        //		cout << "x rotation" << endl;
        //		cout << m << endl;
        //		cout << q << endl;
        //		cout << (Matrixf) q << endl;

        ASSERT(isAlmostEqual(m, q), "conversion with y-rotation failed");
    }

    {
        //		auto m = Matrixf::Rotation(2, Vec(0, 0, 1));
        auto m = Matrixf::RotationZ(2);
        Quaternion q(m);

        //		cout << "x rotation" << endl;
        //		cout << m << endl;
        //		cout << q << endl;
        //		cout << (Matrixf) q << endl;

        ASSERT(isAlmostEqual(m, q), "conversion with z-rotation failed");
    }
}

TEST_SUIT_END

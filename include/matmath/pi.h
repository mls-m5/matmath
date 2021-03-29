//! Pi constants. Copyright Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt

#pragma once

#include "matmath/export.h"

matmath_export constexpr double pi =
    3.1415926535897932384626433832795028841971693;
matmath_export constexpr double pi2 = pi * 2.;
matmath_export constexpr double pi_2 = pi / 2.;
matmath_export constexpr float pif = static_cast<float>(pi);
matmath_export constexpr float pi2f = static_cast<float>(pi2);

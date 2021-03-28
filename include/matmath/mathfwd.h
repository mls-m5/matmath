//! Copyright © Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt

#pragma once

#include "matmath/export.h"

matmath_export template <typename T>
class VecT;

matmath_export using Vec = VecT<double>;
matmath_export using Vecd = VecT<double>;
matmath_export using Vecf = VecT<float>;

matmath_export template <typename T>
class Matrix;

matmath_export using Matrixf = Matrix<float>;
matmath_export using Matrixd = Matrix<double>;

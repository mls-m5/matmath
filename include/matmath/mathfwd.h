//! Copyright © Mattias Larsson Sköld 2020
//! Distributed under terms specified under licence.txt

#pragma once

template <typename T>
class VecT;

using Vec = VecT<double>;
using Vecd = VecT<double>;
using Vecf = VecT<float>;

template <typename T>
class Matrix;

using Matrixf = Matrix<float>;
using Matrixd = Matrix<double>;

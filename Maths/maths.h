////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: maths.h
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////

class Field;

template <typename T>
class Polynomial;
template <typename T>
class Matrix;

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Polynomial {
    public:
    Field* field;
    vector<T> coefficients;

    public:
    Polynomial<T>();
    Polynomial<T>(Field* field, vector<T> coefficients);
    ~Polynomial<T>() = default;

    public:
    bool operator==(const Polynomial<T>& polynomial) const;
    bool operator!=(const Polynomial<T>& polynomial) const;
    Polynomial<T> operator-() const;
    Polynomial<T> operator*(T scalar) const;
    Polynomial<T> operator+(const Polynomial<T>& polynomial) const;
    Polynomial<T> operator-(const Polynomial<T>& polynomial) const;
    Polynomial<T> operator*(const Polynomial<T>& polynomial) const;
    Polynomial<T> operator/(const Polynomial<T>& polynomial) const;
    Polynomial<T> operator%(const Polynomial<T>& polynomial) const;

    public:
    int degree() const;
    Polynomial<T> redegree(int degree) const;
    Polynomial<T> align() const;
    T evaluate(T argument) const;
    Polynomial<T> derivative() const;
};

template <typename T>
ostream& operator<<(ostream& output, const Polynomial<T>& polynomial);

namespace polynomials {
    template <typename T>
    static Polynomial<T> empty_polynomial;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Matrix {
    public:
    Field* field;
    vector<vector<T>> elements;

    public:
    Matrix<T>();
    Matrix<T>(Field* field, vector<vector<T>> elements);
    ~Matrix<T>() = default;

    public:
    bool operator==(const Matrix<T>& matrix) const;
    bool operator!=(const Matrix<T>& matrix) const;
    Matrix<T> operator-() const;
    Matrix<T> operator~() const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator+(const Matrix<T>& matrix) const;
    Matrix<T> operator-(const Matrix<T>& matrix) const;
    Matrix<T> operator*(const Matrix<T>& matrix) const;
    Matrix<T> operator/(const Matrix<T>& matrix) const;

    public:
    int row() const;
    int column() const;
    int size() const;
    Matrix<T> resize(int row, int column) const;

    public:
    Matrix<T> transpose() const;
    T determinant() const;
};

template <typename T>
ostream& operator<<(ostream& output, const Matrix<T>& matrix);

namespace matrices {
    template <typename T>
    static Matrix<T> empty_matrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../FFA/ffa.h"
#include "matrix.cpp"
#include "polynomial.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
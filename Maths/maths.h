////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: maths.h
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Matrix;
template <typename T>
class Polynomial;

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Polynomial {
    public:
    vector<T> coefficients;

    public:
    Polynomial<T>() : coefficients(vector<T>()) {}
    Polynomial<T>(vector<T> coefficients) : coefficients(coefficients) {}
    ~Polynomial<T>() = default;

    public:
    inline bool operator==(const Polynomial<T>& polynomial) const;
    inline bool operator!=(const Polynomial<T>& polynomial) const;
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
    inline Polynomial<T> align() const;
    T evaluate(T argument) const;
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
    vector<vector<T>> elements;

    public:
    Matrix<T>() : elements(vector<vector<T>>()) {}
    Matrix<T>(vector<vector<T>> elements) : elements(elements) {}
    ~Matrix<T>() = default;

    public:
    inline bool operator==(const Matrix<T>& matrix) const;
    inline bool operator!=(const Matrix<T>& matrix) const;
    Matrix<T> operator-() const;
    Matrix<T> operator~() const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator+(const Matrix<T>& matrix) const;
    Matrix<T> operator-(const Matrix<T>& matrix) const;
    Matrix<T> operator*(const Matrix<T>& matrix) const;
    Matrix<T> operator/(const Matrix<T>& matrix) const;

    public:
    inline int row() const;
    inline int column() const;
    inline int size() const;
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

#include "matrix.cpp"
#include "polynomial.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
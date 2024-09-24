////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: matrix.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "maths.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline bool Matrix<T>::operator==(const Matrix<T>& matrix) const {
    return this->elements = matrix.elements;
}

template <typename T>
inline bool Matrix<T>::operator!=(const Matrix<T>& matrix) const {
    return !(*this == matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
    int new_row = this->row();
    int new_column = this->column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->elements[0][0].field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = -this->elements[i][j];
        }
    }
    return Matrix<T>(new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator~() const {}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    int new_row = this->row();
    int new_column = this->column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->elements[0][0].field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = this->elements[i][j] * scalar;
        }
    }
    return Matrix<T>(new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix) const {
    if (this->row() != matrix.row() || this->column() != matrix.column()) throw "ERROR";
    int new_row = this->row();
    int new_column = this->column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->elements[0][0].field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = this->elements[i][j] + matrix.elements[i][j];
        }
    }
    return Matrix<T>(new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix) const {}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) const {}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& matrix) const {}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline int Matrix<T>::row() const {
    return this->elements.size();
}

template <typename T>
inline int Matrix<T>::column() const {
    return this->elements[0].size();
}

template <typename T>
inline int Matrix<T>::size() const {
    return this->row() * this->column();
}

template <typename T>
Matrix<T> Matrix<T>::resize(int row, int column) const {
    vector<vector<T>> new_elements(row, vector<T>(column, T(this->elements[0][0].field)));
    for (int i = 0; i < min(row, this->row()); i ++) {
        for (int j = 0; j < min(column, this->column()); j ++) {
            new_elements[i][j] = this->elements[i][j];
        }
    }
    return Matrix<T>(new_elements);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::transpose() const {}

template <typename T>
T Matrix<T>::determinant() const {}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ostream& operator<<(ostream& output, const Matrix<T>& matrix) {
    output << "'{";
    for (int i = 0; i < matrix.row(); i ++) {
        output << "'{";
        for (int j = 0; j < matrix.column(); j ++) {
            output << matrix.elements[i][j];
            if (j != matrix.column() - 1) {
                output << ", ";
            }
        }
        output << "}";
        if (i != matrix.row() - 1) {
            output << ", ";
        }
    }
    output << "}";
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
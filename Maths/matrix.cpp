////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: matrix.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "maths.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T>::Matrix() {
    this->field = &fields::empty_field;
    this->elements = vector<vector<T>>();
}

template <typename T>
Matrix<T>::Matrix(Field* field, vector<vector<T>> elements) {
    for (int i = 1; i < elements.size(); i ++) {
        if (elements[i].size() != elements[0].size()) throw "ERROR 2756";
    }
    for (int i = 0; i < elements.size(); i ++) {
        for (int j = 0; j < elements[0].size(); j ++) {
            if (*elements[i][j].field != *field) throw "ERROR 0534";
        }
    }
    this->field = field;
    this->elements = elements;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& matrix) const {
    return *this->field == *matrix.field && this->elements == matrix.elements;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& matrix) const {
    return !(*this == matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
    int new_row = this->row();
    int new_column = this->column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = -this->elements[i][j];
        }
    }
    return Matrix<T>(this->field, new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator~() const {
    if (this->row() != this->column()) throw "ERROR 5643";
    if (this->determinant() == this->field->zero_element()) throw "ERROR 3726";
    Matrix<T> temp_0_matrix = *this;
    vector<vector<T>> temp_1_elements(this->row(), vector<T>(this->column(), T(this->field)));
    for (int i = 0; i < this->row(); i ++) {
        temp_1_elements[i][i] = this->field->unit_element();
    }
    Matrix<T> temp_2_matrix(this->field, temp_1_elements);
    for (int i = 0; i < this->row(); i ++) {
        if (temp_0_matrix.elements[i][i] == this->field->zero_element()) {
            for (int j = i + 1; j < this->row(); j ++) {
                if (temp_0_matrix.elements[j][i] != this->field->zero_element()) {
                    swap(temp_0_matrix.elements[i], temp_0_matrix.elements[j]);
                    swap(temp_2_matrix.elements[i], temp_2_matrix.elements[j]);
                    break;
                }
                if (j == this->row() - 1) throw "ERROR 8712";
            }
        }
        T temp_3_diagonal = temp_0_matrix.elements[i][i];
        for (int j = 0; j < this->row(); j ++) {
            temp_0_matrix.elements[i][j] = temp_0_matrix.elements[i][j] / temp_3_diagonal;
            temp_2_matrix.elements[i][j] = temp_2_matrix.elements[i][j] / temp_3_diagonal;
        }
        for (int j = 0; j < this->row(); j ++) {
            if (j != i) {
                T temp_4_factor = temp_0_matrix.elements[j][i];
                for (int k = 0; k < this->row(); k ++) {
                    temp_0_matrix.elements[j][k] = temp_0_matrix.elements[j][k] - (temp_4_factor * temp_0_matrix.elements[i][k]);
                    temp_2_matrix.elements[j][k] = temp_2_matrix.elements[j][k] - (temp_4_factor * temp_2_matrix.elements[i][k]);
                }
            }
        }
    }
    return temp_2_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    if (*scalar.field != *this->field) throw "ERROR 4921";
    int new_row = this->row();
    int new_column = this->column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = this->elements[i][j] * scalar;
        }
    }
    return Matrix<T>(this->field, new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix) const {
    if (*matrix.field != *this->field) throw "ERROR 7004";
    if (this->row() != matrix.row() || this->column() != matrix.column()) throw "ERROR 4496";
    int new_row = this->row();
    int new_column = this->column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = this->elements[i][j] + matrix.elements[i][j];
        }
    }
    return Matrix<T>(this->field, new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix) const {
    if (*matrix.field != *this->field) throw "ERROR 4825";
    return (*this) + (-matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) const {
    if (*matrix.field != *this->field) throw "ERROR 6520";
    if (this->column() != matrix.row()) throw "ERROR 5853";
    int new_row = this->row();
    int new_column = matrix.column();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            for (int k = 0; k < this->column(); k ++) {
                new_elements[i][j] = new_elements[i][j] + (this->elements[i][k] * matrix.elements[k][j]);
            }
        }
    }
    return Matrix<T>(this->field, new_elements);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& matrix) const {
    if (*matrix.field != *this->field) throw "ERROR 1582";
    return (*this) * (~matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int Matrix<T>::row() const {
    return this->elements.size();
}

template <typename T>
int Matrix<T>::column() const {
    return this->elements[0].size();
}

template <typename T>
int Matrix<T>::size() const {
    return this->row() * this->column();
}

template <typename T>
Matrix<T> Matrix<T>::resize(int row, int column) const {
    if (row <= 0 || column <= 0) throw "ERROR 7923";
    vector<vector<T>> new_elements(row, vector<T>(column, T(this->field)));
    for (int i = 0; i < min(row, this->row()); i ++) {
        for (int j = 0; j < min(column, this->column()); j ++) {
            new_elements[i][j] = this->elements[i][j];
        }
    }
    return Matrix<T>(this->field, new_elements);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    int new_row = this->column();
    int new_column = this->row();
    vector<vector<T>> new_elements(new_row, vector<T>(new_column, T(this->field)));
    for (int i = 0; i < new_row; i ++) {
        for (int j = 0; j < new_column; j ++) {
            new_elements[i][j] = this->elements[j][i];
        }
    }
    return Matrix<T>(this->field, new_elements);
}

template <typename T>
T Matrix<T>::determinant() const {
    if (this->row() != this->column()) throw "ERROR 0531";
    vector<int> temp_0_permutation(this->row());
    for (int i = 0; i < this->row(); i ++) {
        temp_0_permutation[i] = i;
    }
    T temp_1_determinant = this->field->zero_element();
    bool temp_2_sign = false;
    do {
        T temp_3_product = this->field->unit_element();
        for (int i = 0; i < this->row(); i ++) {
            temp_3_product = temp_3_product * this->elements[i][temp_0_permutation[i]];
        }
        temp_2_sign = !temp_2_sign;
        if (temp_2_sign) {
            temp_1_determinant = temp_1_determinant + temp_3_product;
        } else {
            temp_1_determinant = temp_1_determinant - temp_3_product;
        }
    } while (next_permutation(temp_0_permutation.begin(), temp_0_permutation.end()));
    return temp_1_determinant;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ostream& operator<<(ostream& output, const Matrix<T>& matrix) {
    output << "{";
    for (int i = 0; i < matrix.row(); i ++) {
        output << "{";
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

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: polynomial.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "maths.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline bool Polynomial<T>::operator==(const Polynomial<T>& polynomial) const {
    return this->align().coefficients == polynomial.align().coefficients;
}

template <typename T>
inline bool Polynomial<T>::operator!=(const Polynomial<T>& polynomial) const {
    return !(*this == polynomial);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Polynomial<T> Polynomial<T>::operator-() const {
    int new_degree = this->degree();
    vector<T> new_coefficients(new_degree + 1, T(this->coefficients[0].field));
    for (int i = 0; i <= new_degree; i ++) {
        new_coefficients[i] = -this->coefficients[i];
    }
    return Polynomial<T>(new_coefficients);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(T scalar) const {
    int new_degree = this->degree();
    vector<T> new_coefficients(new_degree + 1, T(this->coefficients[0].field));
    for (int i = 0; i <= new_degree; i ++) {
        new_coefficients[i] = this->coefficients[i] * scalar;
    }
    return Polynomial<T>(new_coefficients);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& polynomial) const {
    int new_degree = max(this->degree(), polynomial.degree());
    Polynomial<T> temp_0_polynomial = this->redegree(new_degree);
    Polynomial<T> temp_1_polynomial = polynomial.redegree(new_degree);
    vector<T> new_coefficients(new_degree + 1, T(this->coefficients[0].field));
    for (int i = 0; i <= new_degree; i ++) {
        new_coefficients[i] = temp_0_polynomial.coefficients[i] + temp_1_polynomial.coefficients[i];
    }
    return Polynomial<T>(new_coefficients);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& polynomial) const {
    return (*this) + (-polynomial);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& polynomial) const {
    int new_degree = this->degree() + polynomial.degree();
    Polynomial<T> temp_0_polynomial = this->align();
    Polynomial<T> temp_1_polynomial = polynomial.align();
    vector<T> new_coefficients(new_degree + 1, T(this->coefficients[0].field));
    for (int i = 0; i <= temp_0_polynomial.degree(); i ++) {
        for (int j = 0; j <= temp_1_polynomial.degree(); j ++) {
            new_coefficients[i + j] = new_coefficients[i + j] + (temp_0_polynomial.coefficients[i] * temp_1_polynomial.coefficients[j]);
        }
    }
    return Polynomial<T>(new_coefficients);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator/(const Polynomial<T>& polynomial) const {
    int new_degree = this->degree() - polynomial.degree();
    if (new_degree < 0) return Polynomial<T>({this->coefficients[0].field});
    Polynomial<T> temp_0_polynomial = this->align();
    Polynomial<T> temp_1_polynomial = polynomial.align();
    vector<T> new_coefficients(new_degree + 1, T(this->coefficients[0].field));
    for (int i = 0; i <= new_degree; i ++) {
        new_coefficients[new_degree - i] = temp_0_polynomial.coefficients[this->degree() - i] / temp_1_polynomial.coefficients[temp_1_polynomial.degree()];
        temp_0_polynomial = *this + (temp_1_polynomial * Polynomial<T>(new_coefficients));
    }
    return Polynomial<T>(new_coefficients);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator%(const Polynomial<T>& polynomial) const {
    int new_degree = polynomial.degree() - 1;
    if (new_degree < 0) return Polynomial<T>({this->coefficients[0].field});
    Polynomial<T> tambaytamba = *this / polynomial;
    return (*this - (polynomial * (*this / polynomial))).redegree(new_degree);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int Polynomial<T>::degree() const {
    for (int i = 0; i < this->coefficients.size(); i ++) {
        if (this->coefficients[this->coefficients.size() - i - 1] != T(this->coefficients[0].field)) {
            return this->coefficients.size() - i - 1;
        }
    }
    return 0;
}

template <typename T>
Polynomial<T> Polynomial<T>::redegree(int degree) const {
    vector<T> new_coefficients(degree + 1, T(this->coefficients[0].field));
    for (int i = 0; i <= min(degree, this->degree()); i ++) {
        new_coefficients[i] = this->coefficients[i];
    }
    return Polynomial<T>(new_coefficients);
}

template <typename T>
inline Polynomial<T> Polynomial<T>::align() const {
    return this->redegree(this->degree());
}

template <typename T>
T Polynomial<T>::evaluate(T argument) const {
    T temp_0_value = this->coefficients[0];
    for (int i = 0; i < this->degree(); i ++) {
        T temp_1_value = this->coefficients[i + 1];
        for (int j = 0; j <= i; j ++) {
            temp_1_value = temp_1_value * argument;
        }
        temp_0_value = temp_0_value + temp_1_value;
    }
    return temp_0_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ostream& operator<<(ostream& output, const Polynomial<T>& polynomial) {
    output << "'{";
    for (int i = 0; i < polynomial.coefficients.size(); i ++) {
        output << polynomial.coefficients[i];
        if (i != polynomial.coefficients.size() - 1) {
            output << ", ";
        }
    }
    output << "}";
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
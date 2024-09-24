////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: fec.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "fec.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

RS::RS(const Polynomial<Binary>& primitive_polynomial, int correction_capability) {
    this->symbol_field = new Field(const_cast<Polynomial<Binary>*>(&primitive_polynomial));
    this->generator_polynomial = Polynomial<Element>({this->symbol_field->unit_element()});
    for (int i = 0; i < 2 * correction_capability; i ++) {
        this->generator_polynomial = this->generator_polynomial * Polynomial<Element>({this->symbol_field->general_elements[i + 1], this->symbol_field->unit_element()});
    }
}

RS::~RS() {
    delete this->symbol_field;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

inline int RS::codeword_length() const {
    return this->symbol_field->size() - 1;
}

inline int RS::message_length() const {
    return this->symbol_field->size() - this->generator_polynomial.degree() - 1;
}

inline int RS::parity_length() const {
    return this->codeword_length() - this->message_length();
}

inline int RS::symbol_size() const {
    return this->symbol_field->primitive_polynomial->degree();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Polynomial<Element> RS::systematic_encode(const Polynomial<Element>& message) const {
    Polynomial<Element> temp_0_polynomial(vector<Element>(this->parity_length() + 1, this->symbol_field->zero_element()));
    temp_0_polynomial.coefficients[this->parity_length()] = this->symbol_field->unit_element();
    return ((message * temp_0_polynomial) + ((message * temp_0_polynomial) % this->generator_polynomial)).redegree(this->codeword_length() - 1);
}

Polynomial<Element> RS::nonsystematic_encode(const Polynomial<Element>& message) const {
    return (message * this->generator_polynomial).redegree(this->codeword_length() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Element> RS::syndrome_calculate(const Polynomial<Element>& received) const {
    vector<Element> temp_0_elements(this->parity_length(), this->symbol_field->zero_element());
    for (int i = 0; i < temp_0_elements.size(); i ++) {
        temp_0_elements[i] = received.evaluate(this->symbol_field->general_elements[i + 1]);
    }
    return temp_0_elements;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

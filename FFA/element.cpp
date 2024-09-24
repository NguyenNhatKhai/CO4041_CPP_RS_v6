////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: element.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ffa.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool Element::operator==(const Element& element) const {
    return *(this->field) == *(element.field) && this->values == element.values;
}

inline bool Element::operator!=(const Element& element) const {
    return !(*this == element);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Element Element::operator-() const {
    for (int i = 0; i < this->field->general_elements.size(); i ++) {
        if (*this + this->field->general_elements[i] == this->field->zero_element()) return this->field->general_elements[i];
    }
    return this->field->zero_element();
}

Element Element::operator~() const {
    for (int i = 0; i < this->field->general_elements.size(); i ++) {
        if (*this * this->field->general_elements[i] == this->field->unit_element()) return this->field->general_elements[i];
    }
    throw "ERROR";
}

Element Element::operator+(const Element& element) const {
    Polynomial<Binary> temp_0_polynomial(this->values);
    Polynomial<Binary> temp_1_polynomial(element.values);
    // vector<Binary> temp_2_values = (temp_0_polynomial + temp_1_polynomial).redegree(this->field->primitive_polynomial->degree() - 1).coefficients;
    vector<Binary> temp_2_values = (temp_0_polynomial + temp_1_polynomial).redegree(this->degree()).coefficients;
    return Element(this->field, temp_2_values);
}

Element Element::operator-(const Element& element) const {
    return (*this) + (-element);
}

Element Element::operator*(const Element& element) const {
    Polynomial<Binary> temp_0_polynomial(this->values);
    Polynomial<Binary> temp_1_polynomial(element.values);
    vector<Binary> temp_2_values = ((temp_0_polynomial * temp_1_polynomial) % *(this->field->primitive_polynomial)).coefficients;
    return Element(this->field, temp_2_values);
}

Element Element::operator/(const Element& element) const {
    return (*this) * (~element);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

inline int Element::degree() const {
    return this->field->primitive_polynomial->degree() - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& output, const Element& element) {
    output << "'{";
    for (int i = 0; i < element.values.size(); i ++) {
        output << element.values[i];
        if (i != element.values.size() - 1) {
            output << ", ";
        }
    }
    output << "}";
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
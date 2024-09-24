////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: element.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ffa.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

Element::Element(Field* field) {
    this->field = field;
    this->values = field->zero_element().values;
}

Element::Element(Field* field, vector<Binary> values) {
    if (field->primitive_polynomial->degree() != values.size()) throw "ERROR 6178";
    this->field = field;
    this->values = values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool Element::operator==(const Element& element) const {
    return *this->field == *element.field && this->values == element.values;
}

bool Element::operator!=(const Element& element) const {
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
    throw "ERROR 3063";
}

Element Element::operator+(const Element& element) const {
    if (*this->field != *element.field) throw "ERROR 9281";
    Polynomial<Binary> temp_0_polynomial(&fields::empty_field, this->values);
    Polynomial<Binary> temp_1_polynomial(&fields::empty_field, element.values);
    vector<Binary> temp_2_values = (temp_0_polynomial + temp_1_polynomial).redegree(this->degree()).coefficients;
    return Element(this->field, temp_2_values);
}

Element Element::operator-(const Element& element) const {
    if (*this->field != *element.field) throw "ERROR 9515";
    return (*this) + (-element);
}

Element Element::operator*(const Element& element) const {
    if (*this->field != *element.field) throw "ERROR 4480";
    Polynomial<Binary> temp_0_polynomial(&fields::empty_field, this->values);
    Polynomial<Binary> temp_1_polynomial(&fields::empty_field, element.values);
    vector<Binary> temp_2_values = (temp_0_polynomial * temp_1_polynomial % *this->field->primitive_polynomial).coefficients;
    return Element(this->field, temp_2_values);
}

Element Element::operator/(const Element& element) const {
    if (*this->field != *element.field) throw "ERROR 9857";
    return (*this) * (~element);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int Element::degree() const {
    return this->field->primitive_polynomial->degree() - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& output, const Element& element) {
    output << "{";
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
////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: field.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ffa.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

Field::Field(Polynomial<Binary>* primitive_polynomial) {
    this->primitive_polynomial = primitive_polynomial;
    this->general_elements = vector<Element>(this->size() - 1, Element(const_cast<Field*>(this), vector<Binary>(primitive_polynomial->degree(), Binary(false))));
    this->general_elements[0].values[0] = Binary(true);
    this->general_elements[1].values[1] = Binary(true);
    Element temp_0_element = this->primitive_element();
    for (int i = 2; i < this->general_elements.size(); i ++) {
        temp_0_element = temp_0_element * this->primitive_element();
        this->general_elements[i] = temp_0_element;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool Field::operator==(const Field& field) const {
    return this->primitive_polynomial == field.primitive_polynomial;
}

inline bool Field::operator!=(const Field& field) const {
    return !(*this == field);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

inline int Field::size() const {
    return pow(2, this->primitive_polynomial->degree());
}

inline Element Field::zero_element() const {
    return Element(const_cast<Field*>(this), vector<Binary>(this->primitive_polynomial->degree(), Binary(false)));
}

inline Element Field::unit_element() const {
    return this->general_elements[0];
}

inline Element Field::primitive_element() const {
    return this->general_elements[1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
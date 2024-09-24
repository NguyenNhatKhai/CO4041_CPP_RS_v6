////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: binary.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ffa.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

Binary::Binary(Field* field) {
    this->field = &fields::empty_field;
    this->value = false;
}

Binary::Binary(bool value) {
    this->field = &fields::empty_field;
    this->value = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool Binary::operator==(const Binary& binary) const {
    return this->value == binary.value;
}

bool Binary::operator!=(const Binary& binary) const {
    return !(*this == binary);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Binary Binary::operator-() const {
    return Binary(this->value);
}

Binary Binary::operator~() const {
    if (this->value == 0) throw "ERROR 6274";
    return Binary(this->value);
}

Binary Binary::operator+(const Binary& binary) const {
    if (*this->field != *binary.field) throw "ERROR 8333";
    return Binary(this->value ^ binary.value);
}

Binary Binary::operator-(const Binary& binary) const {
    if (*this->field != *binary.field) throw "ERROR 4131";
    return (*this) + (-binary);
}

Binary Binary::operator*(const Binary& binary) const {
    if (*this->field != *binary.field) throw "ERROR 1720";
    return Binary(this->value & binary.value);
}

Binary Binary::operator/(const Binary& binary) const {
    if (*this->field != *binary.field) throw "ERROR 9526";
    return (*this) * (~binary);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& output, const Binary& binary) {
    output << binary.value;
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

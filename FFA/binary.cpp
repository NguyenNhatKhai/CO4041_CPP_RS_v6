////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: binary.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ffa.h"

inline bool Binary::operator==(const Binary& binary) const {
    return this->value == binary.value;
}

inline bool Binary::operator!=(const Binary& binary) const {
    return !(*this == binary);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

inline Binary Binary::operator-() const {
    return Binary(this->value);
}

inline Binary Binary::operator~() const {
    if (this->value == 0) throw "ERROR";
    return Binary(this->value);
}

inline Binary Binary::operator+(const Binary& binary) const {
    return Binary(this->value ^ binary.value);
}

inline Binary Binary::operator-(const Binary& binary) const {
    return (*this) + (-binary);
}

inline Binary Binary::operator*(const Binary& binary) const {
    return Binary(this->value & binary.value);
}

inline Binary Binary::operator/(const Binary& binary) const {
    return (*this) * (~binary);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& output, const Binary& binary) {
    output << binary.value;
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

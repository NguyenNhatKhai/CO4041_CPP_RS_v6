////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: ffa.h
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _FFA_H_
#define _FFA_H_

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "../Maths/maths.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////

class Binary;
class Element;
class Field;

////////////////////////////////////////////////////////////////////////////////////////////////////

class Field {
    public:
    Polynomial<Binary>* primitive_polynomial;
    vector<Element> general_elements;

    public:
    Field() : primitive_polynomial(&polynomials::empty_polynomial<Binary>), general_elements(vector<Element>()) {}
    Field(Polynomial<Binary>* primitive_polynomial);
    ~Field() = default;

    public:
    inline bool operator==(const Field& field) const;
    inline bool operator!=(const Field& field) const;

    public:
    inline int size() const;
    inline Element zero_element() const;
    inline Element unit_element() const;
    inline Element primitive_element() const;
};

namespace fields {
    static Field empty_field;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

class Binary {
    public:
    Field* field;
    bool value;

    public:
    Binary() = delete;
    Binary(Field* field) : field(&fields::empty_field), value(false) {}
    Binary(bool value) : field(&fields::empty_field), value(value) {}
    ~Binary() = default;

    public:
    inline bool operator==(const Binary& binary) const;
    inline bool operator!=(const Binary& binary) const;
    inline Binary operator-() const;
    inline Binary operator~() const;
    inline Binary operator+(const Binary& binary) const;
    inline Binary operator-(const Binary& binary) const;
    inline Binary operator*(const Binary& binary) const;
    inline Binary operator/(const Binary& binary) const;
};

ostream& operator<<(ostream& output, const Binary& binary);

////////////////////////////////////////////////////////////////////////////////////////////////////

class Element {
    public:
    Field* field;
    vector<Binary> values;

    public:
    Element() = delete;
    Element(Field* field) : field(field), values(field->zero_element().values) {}
    Element(Field* field, vector<Binary> values) : field(field), values(values) {}
    ~Element() = default;

    public:
    inline bool operator==(const Element& element) const;
    inline bool operator!=(const Element& element) const;
    Element operator-() const;
    Element operator~() const;
    Element operator+(const Element& element) const;
    Element operator-(const Element& element) const;
    Element operator*(const Element& element) const;
    Element operator/(const Element& element) const;

    public:
    inline int degree() const;
};

template <typename T>
ostream& operator<<(ostream& output, const Element& element);

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "binary.cpp"
#include "element.cpp"
#include "field.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
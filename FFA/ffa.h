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

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Polynomial;

class Binary;
class Element;
class Field;

////////////////////////////////////////////////////////////////////////////////////////////////////

class Field {
    public:
    Polynomial<Binary>* primitive_polynomial;
    vector<Element> general_elements;

    public:
    Field();
    Field(Polynomial<Binary>* primitive_polynomial);
    ~Field() = default;

    public:
    bool operator==(const Field& field) const;
    bool operator!=(const Field& field) const;

    public:
    int size() const;
    Element zero_element() const;
    Element unit_element() const;
    Element primitive_element() const;
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
    Binary(Field* field);
    Binary(bool value);
    ~Binary() = default;

    public:
    bool operator==(const Binary& binary) const;
    bool operator!=(const Binary& binary) const;

    public:
    Binary operator-() const;
    Binary operator~() const;
    Binary operator+(const Binary& binary) const;
    Binary operator-(const Binary& binary) const;
    Binary operator*(const Binary& binary) const;
    Binary operator/(const Binary& binary) const;
};

ostream& operator<<(ostream& output, const Binary& binary);

////////////////////////////////////////////////////////////////////////////////////////////////////

class Element {
    public:
    Field* field;
    vector<Binary> values;

    public:
    Element() = delete;
    Element(Field* field);
    Element(Field* field, vector<Binary> values);
    ~Element() = default;

    public:
    bool operator==(const Element& element) const;
    bool operator!=(const Element& element) const;

    public:
    Element operator-() const;
    Element operator~() const;
    Element operator+(const Element& element) const;
    Element operator-(const Element& element) const;
    Element operator*(const Element& element) const;
    Element operator/(const Element& element) const;

    public:
    int degree() const;
};

template <typename T>
ostream& operator<<(ostream& output, const Element& element);

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../Maths/maths.h"
#include "binary.cpp"
#include "element.cpp"
#include "field.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
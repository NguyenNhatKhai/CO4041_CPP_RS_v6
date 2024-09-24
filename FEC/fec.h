////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: fec.h
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _FEC_H_
#define _FEC_H_

#include <iostream>
#include <string>
#include <vector>

#include "../FFA/ffa.h"
#include "../Maths/maths.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////

class RS;

////////////////////////////////////////////////////////////////////////////////////////////////////

class RS {
    public:
    Field* symbol_field;
    Polynomial<Element> generator_polynomial;

    public:
    RS() = delete;
    RS(const Polynomial<Binary>& primitive_polynomial, int correction_capability);
    ~RS();

    public:
    inline int codeword_length() const;
    inline int message_length() const;
    inline int parity_length() const;
    inline int symbol_size() const;

    public:
    Polynomial<Element> systematic_encode(const Polynomial<Element>& message) const;
    Polynomial<Element> nonsystematic_encode(const Polynomial<Element>& message) const;

    public:
    vector<Element> syndrome_calculate(const Polynomial<Element>& received) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rs.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
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
    RS(Field* symbol_field, int correction_capability);
    ~RS() = default;

    public:
    int codeword_length() const;
    int message_length() const;
    int parity_length() const;
    int symbol_size() const;
    int detection_capability() const;
    int correction_capability() const;

    public:
    Polynomial<Element> systematic_encode(const Polynomial<Element>& message) const;
    Polynomial<Element> nonsystematic_encode(const Polynomial<Element>& message) const;

    public:
    vector<Element> syndrome(const Polynomial<Element>& received) const;
    Polynomial<Element> syndrome(const vector<Element>& syndrome);
    Polynomial<Element> pgz_error_locator(const vector<Element>& syndrome);
    Polynomial<Element> pgz_error_evaluator(const Polynomial<Element>& syndrome, const Polynomial<Element>& error_locator);
    vector<Element> chien_roots(const Polynomial<Element>& error_locator);
    vector<Element> pgz_error_values(const Polynomial<Element>& error_locator, const Polynomial<Element>& error_evaluator, const vector<Element>& roots);
    Polynomial<Element> estimated_error(const vector<Element>& roots, const vector<Element>& error_values);
    Polynomial<Element> estimated_codeword(const Polynomial<Element>& received, const Polynomial<Element>& estimated_error);
    Polynomial<Element> estimated_message(const Polynomial<Element>& estimated_codeword);
    
    public:
    Polynomial<Element> pgz_decode(const Polynomial<Element>& received) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rs.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
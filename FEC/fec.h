////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: fec.h
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _FEC_H_
#define _FEC_H_

#include <fstream>
#include <iomanip>
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
    Polynomial<Element> systematic_encode(const Polynomial<Element>& message, const string& output_path) const;
    Polynomial<Element> nonsystematic_encode(const Polynomial<Element>& message, const string& output_path) const;

    public:
    Polynomial<Element> add_error(const Polynomial<Element>& codeword, const Polynomial<Element>& error, const string& output_path) const;

    public:
    Polynomial<Element> pgz_decode(const Polynomial<Element>& received, const string& output_path) const;
    Polynomial<Element> bm_decode(const Polynomial<Element>& received, const string& output_path) const;
    Polynomial<Element> euclidean_decode(const Polynomial<Element>& received, const string& output_path) const;

    public:
    vector<Element> syndrome(const Polynomial<Element>& received) const;
    Polynomial<Element> syndrome(const vector<Element>& syndrome) const;

    Polynomial<Element> pgz_error_locator(const vector<Element>& syndrome) const;
    Polynomial<Element> bm_error_locator(const vector<Element>& syndrome) const;
    Polynomial<Element> euclidean_error_locator(const Polynomial<Element>& syndrome) const;

    Polynomial<Element> pgz_error_evaluator(const Polynomial<Element>& syndrome, const Polynomial<Element>& error_locator) const;
    Polynomial<Element> bm_error_evaluator(const Polynomial<Element>& syndrome, const Polynomial<Element>& error_locator) const;
    Polynomial<Element> euclidean_error_evaluator(const Polynomial<Element>& syndrome) const;

    vector<Element> chien_roots(const Polynomial<Element>& error_locator) const;

    vector<Element> pgz_error_values(const Polynomial<Element>& error_locator, const Polynomial<Element>& error_evaluator, const vector<Element>& roots) const;
    vector<Element> bm_error_values(const Polynomial<Element>& error_locator, const Polynomial<Element>& error_evaluator, const vector<Element>& roots) const;
    vector<Element> euclidean_error_values(const Polynomial<Element>& error_locator, const Polynomial<Element>& error_evaluator, const vector<Element>& roots) const;

    Polynomial<Element> estimated_error(const vector<Element>& roots, const vector<Element>& error_values) const;
    Polynomial<Element> estimated_codeword(const Polynomial<Element>& received, const Polynomial<Element>& estimated_error) const;
    Polynomial<Element> estimated_message(const Polynomial<Element>& estimated_codeword) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rs.cpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
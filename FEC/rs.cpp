////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: fec.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "fec.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

RS::RS(Field* symbol_field, int correction_capability) {
    if (correction_capability <= 0 || 2 * correction_capability >= symbol_field->size() - 1) throw "ERROR 8690";
    this->symbol_field = symbol_field;
    this->generator_polynomial = Polynomial<Element>(this->symbol_field, {this->symbol_field->unit_element()});
    for (int i = 0; i < 2 * correction_capability; i ++) {
        this->generator_polynomial = this->generator_polynomial * Polynomial<Element>(this->symbol_field, {this->symbol_field->general_elements[i + 1], this->symbol_field->unit_element()});
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int RS::codeword_length() const {
    return this->symbol_field->size() - 1;
}

int RS::message_length() const {
    return this->symbol_field->size() - this->generator_polynomial.degree() - 1;
}

int RS::parity_length() const {
    return this->codeword_length() - this->message_length();
}

int RS::symbol_size() const {
    return this->symbol_field->primitive_polynomial->degree();
}

int RS::detection_capability() const {
    return this->parity_length();
}

int RS::correction_capability() const {
    return this->parity_length() / 2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Polynomial<Element> RS::systematic_encode(const Polynomial<Element>& message) const {
    if (message.coefficients.size() != this->message_length()) throw "ERROR 3233";
    if (*message.field != *this->symbol_field) throw "ERROR 7062";
    Polynomial<Element> temp_0_polynomial(this->symbol_field, vector<Element>(this->parity_length() + 1, this->symbol_field->zero_element()));
    temp_0_polynomial.coefficients[this->parity_length()] = this->symbol_field->unit_element();
    return ((message * temp_0_polynomial) + ((message * temp_0_polynomial) % this->generator_polynomial)).redegree(this->codeword_length() - 1);
}

Polynomial<Element> RS::nonsystematic_encode(const Polynomial<Element>& message) const {
    if (message.coefficients.size() != this->message_length()) throw "ERROR 4410";
    if (*message.field != *this->symbol_field) throw "ERROR 5666";
    return (message * this->generator_polynomial).redegree(this->codeword_length() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Element> RS::syndrome(const Polynomial<Element>& received) const {
    if (received.coefficients.size() != this->codeword_length()) throw "ERROR 5824";
    if (*received.field != *this->symbol_field) throw "ERROR 8901";
    vector<Element> temp_0_elements(this->parity_length(), this->symbol_field->zero_element());
    for (int i = 0; i < temp_0_elements.size(); i ++) {
        temp_0_elements[i] = received.evaluate(this->symbol_field->general_elements[i + 1]);
    }
    return temp_0_elements;
}

Polynomial<Element> RS::syndrome(const vector<Element>& syndrome) {
    if (syndrome.size() != 2 * this->correction_capability()) throw "ERROR 0256";
    for (int i = 0; i < syndrome.size(); i ++) {
        if (*syndrome[i].field != *this->symbol_field) throw "ERROR 1028";
    }
    return Polynomial<Element>(this->symbol_field, syndrome);
}

Polynomial<Element> RS::pgz_error_locator(const vector<Element>& syndrome) {
    if (syndrome.size() != 2 * this->correction_capability()) throw "ERROR 3102";
    for (int i = 0; i < syndrome.size(); i ++) {
        if (*syndrome[i].field != *this->symbol_field) throw "ERROR 4487";
    }
    vector<Element> temp_0_coefficients(1, this->symbol_field->unit_element());
    for (int i = this->correction_capability(); i > 0; i --) {
        vector<vector<Element>> temp_1_elements(i, vector<Element>(i, this->symbol_field->zero_element()));
        for (int j = 0; j < i; j ++) {
            for (int k = 0; k < i; k ++) {
                temp_1_elements[j][k] = syndrome[j + k];
            }
        }
        Matrix<Element> temp_2_matrix(this->symbol_field, temp_1_elements);
        if (temp_2_matrix.determinant() != this->symbol_field->zero_element()) {
            vector<vector<Element>> temp_3_elements(i, vector<Element>(1, this->symbol_field->zero_element()));
            for (int j = 0; j < i; j ++) {
                temp_3_elements[j][0] = -syndrome[i + j];
            }
            Matrix<Element> temp_4_matrix(this->symbol_field, temp_3_elements);
            Matrix<Element> temp_5_matrix = ~temp_2_matrix * temp_4_matrix;
            for (int j = 1; j <= i; j ++) {
                temp_0_coefficients.push_back(temp_5_matrix.elements[i - j][0]);
            }
            break;
        }
    }
    return Polynomial<Element>(this->symbol_field, temp_0_coefficients);
}

Polynomial<Element> RS::pgz_error_evaluator(const Polynomial<Element>& syndrome, const Polynomial<Element>& error_locator) {
    if (syndrome.degree() >= 2 * this->correction_capability() || error_locator.degree() > this->correction_capability()) throw "ERROR 8078";
    if (*syndrome.field != *this->symbol_field || *error_locator.field != *this->symbol_field) throw "ERROR 3280";
    vector<Element> temp_0_coefficients(2 * this->correction_capability() + 1, this->symbol_field->zero_element());
    temp_0_coefficients[2 * this->correction_capability()] = this->symbol_field->unit_element();
    Polynomial<Element> temp_1_polynomial(this->symbol_field, temp_0_coefficients);
    return ((syndrome * error_locator) % temp_1_polynomial).redegree(this->correction_capability() - 1);
}

vector<Element> RS::chien_roots(const Polynomial<Element>& error_locator) {
    if (error_locator.degree() > this->correction_capability()) throw "ERROR 4766";
    if (*error_locator.field != *this->symbol_field) throw "ERROR 8683";
    vector<Element> temp_0_elements;
    for (int i = 0; i < this->symbol_field->size() - 1; i ++) {
        if (error_locator.evaluate(this->symbol_field->general_elements[i]) == this->symbol_field->zero_element()) {
            temp_0_elements.push_back(this->symbol_field->general_elements[i]);
        }
    }
    return temp_0_elements;
}

vector<Element> RS::pgz_error_values(const Polynomial<Element>& error_locator, const Polynomial<Element>& error_evaluator, const vector<Element>& roots) {
    if (error_locator.degree() > this->correction_capability() || error_evaluator.degree() >= 2 * this->correction_capability() || roots.size() > this->correction_capability()) throw "ERROR 5801";
    if (*error_locator.field != *this->symbol_field || *error_evaluator.field != *this->symbol_field) throw "ERROR 7011";
    for (int i = 0; i < roots.size(); i ++) {
        if (*roots[i].field != *this->symbol_field) throw "ERROR 2996";
    }
    vector<Element> temp_0_elements;
    for (int i = 0; i < roots.size(); i ++) {
        temp_0_elements.push_back(error_evaluator.evaluate(roots[i]) / error_locator.derivative().evaluate(roots[i]));
    }
    return temp_0_elements;
}

Polynomial<Element> RS::estimated_error(const vector<Element>& roots, const vector<Element>& error_values) {
    if (roots.size() != error_values.size() || roots.size() > this->correction_capability()) throw "ERROR 9519";
    for (int i = 0; i < roots.size(); i ++) {
        if (*roots[i].field != *this->symbol_field || *error_values[i].field != *this->symbol_field) throw "ERROR 5484";
    }
    vector<Element> temp_0_coefficients(this->codeword_length(), this->symbol_field->zero_element());
    for (int i = 0; i < roots.size(); i ++) {
        Element temp_1_element = ~roots[i];
        for (int j = 0; j < this->symbol_field->size() - 1; j ++) {
            if (temp_1_element == this->symbol_field->general_elements[j]) {
                temp_0_coefficients[j] = error_values[i];
                break;
            }
            if (j == this->symbol_field->size() - 2) throw "ERROR 6565";
        }
    }
    return Polynomial<Element>(this->symbol_field, temp_0_coefficients);
}

Polynomial<Element> RS::estimated_codeword(const Polynomial<Element>& received, const Polynomial<Element>& estimated_error) {
    if (received.coefficients.size() != this->codeword_length() || estimated_error.coefficients.size() != this->codeword_length()) throw "ERROR 7857";
    if (*received.field != *this->symbol_field || *estimated_error.field != *this->symbol_field) throw "ERROR 8884";
    return (received - estimated_error).redegree(this->codeword_length() - 1);
}

Polynomial<Element> RS::estimated_message(const Polynomial<Element>& estimated_codeword) {
    if (estimated_codeword.coefficients.size() != this->codeword_length()) throw "ERROR 8808";
    if (*estimated_codeword.field != *this->symbol_field) throw "ERROR 0333";
    return estimated_codeword.redegree(this->message_length() - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

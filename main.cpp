////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: main.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Example 6.7 - Page 239

// Binary BIN0(false);
// Binary BIN1(true);
// int INT0 = 3;

// Polynomial<Binary> POL0(&fields::empty_field, {BIN1, BIN1, BIN0, BIN0, BIN1});
// Field FIE0(&POL0);
// RS RS0(&FIE0, INT0);

// #define ELE(i) FIE0.general_elements[i]

// int main() {
//     ofstream output_file("output.txt");
//     try {
//         output_file << "n" << RS0.codeword_length() << " k" << RS0.message_length() << " p" << RS0.parity_length() << " s" << RS0.symbol_size() << " d" << RS0.detection_capability() << " c" << RS0.correction_capability() << endl;
//         output_file << "g " << RS0.generator_polynomial << endl;

//         Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
//         Polynomial<Element> polCod = RS0.systematic_encode(polMes);
//         output_file << "m " << polMes << endl;
//         output_file << "c " << polCod << endl;

//         Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
//         polErr.coefficients[3] = ELE(7); polErr.coefficients[6] = ELE(3); polErr.coefficients[12] = ELE(4);
//         Polynomial<Element> polRec = (polCod + polErr).redegree(RS0.codeword_length() - 1);
//         output_file << "e " << polErr << endl;
//         output_file << "r " << polRec << endl;

//         vector<Element> vecSyn = RS0.syndrome(polRec);
//         Polynomial<Element> polSyn = RS0.syndrome(vecSyn);
//         for (int i = 0; i < vecSyn.size(); i ++) output_file << "s" << i << " " << vecSyn[i] << endl;
//         output_file << "syn " << polSyn << endl;

//         Polynomial<Element> polErrLoc = RS0.pgz_error_locator(vecSyn);
//         Polynomial<Element> polErrEva = RS0.pgz_error_evaluator(polSyn, polErrLoc);
//         output_file << "loc " << polErrLoc << endl;
//         output_file << "eva " << polErrEva << endl;

//         vector<Element> vecRoo = RS0.chien_roots(polErrLoc);
//         vector<Element> vecVal = RS0.pgz_error_values(polErrLoc, polErrEva, vecRoo);
//         for (int i = 0; i < vecRoo.size(); i ++) output_file << "r" << i << " " << vecRoo[i] << endl;
//         for (int i = 0; i < vecVal.size(); i ++) output_file << "v" << i << " " << vecVal[i] << endl;

//         Polynomial<Element> polEstErr = RS0.estimated_error(vecRoo, vecVal);
//         Polynomial<Element> polEstCod = RS0.estimated_codeword(polRec, polEstErr);
//         Polynomial<Element> polEstMes = RS0.estimated_message(polEstCod);
//         output_file << "err " << polEstErr << endl;
//         output_file << "cod " << polEstCod << endl;
//         output_file << "mes " << polEstMes << endl;
//     } catch (const char* error_message) {
//         cout << error_message << endl;
//     }
//     output_file.close();
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Example 6.8 - Page 241

// Binary BIN0(false);
// Binary BIN1(true);
// int INT0 = 3;

// Polynomial<Binary> POL0(&fields::empty_field, {BIN1, BIN0, BIN1, BIN0, BIN0, BIN1});
// Field FIE0(&POL0);
// RS RS0(&FIE0, INT0);

// #define ELE(i) FIE0.general_elements[i]

// int main() {
//     ofstream output_file("output.txt");
//     try {
//         output_file << "n" << RS0.codeword_length() << " k" << RS0.message_length() << " p" << RS0.parity_length() << " s" << RS0.symbol_size() << " d" << RS0.detection_capability() << " c" << RS0.correction_capability() << endl;
//         output_file << "g " << RS0.generator_polynomial << endl;

//         Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
//         Polynomial<Element> polCod = RS0.systematic_encode(polMes);
//         output_file << "m " << polMes << endl;
//         output_file << "c " << polCod << endl;

//         Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
//         polErr.coefficients[0] = ELE(2); polErr.coefficients[12] = ELE(21); polErr.coefficients[20] = ELE(7);
//         Polynomial<Element> polRec = (polCod + polErr).redegree(RS0.codeword_length() - 1);
//         output_file << "e " << polErr << endl;
//         output_file << "r " << polRec << endl;

//         vector<Element> vecSyn = RS0.syndrome(polRec);
//         Polynomial<Element> polSyn = RS0.syndrome(vecSyn);
//         for (int i = 0; i < vecSyn.size(); i ++) output_file << "s" << i << " " << vecSyn[i] << endl;
//         output_file << "syn " << polSyn << endl;

//         Polynomial<Element> polErrLoc = RS0.pgz_error_locator(vecSyn);
//         Polynomial<Element> polErrEva = RS0.pgz_error_evaluator(polSyn, polErrLoc);
//         output_file << "loc " << polErrLoc << endl;
//         output_file << "eva " << polErrEva << endl;

//         vector<Element> vecRoo = RS0.chien_roots(polErrLoc);
//         vector<Element> vecVal = RS0.pgz_error_values(polErrLoc, polErrEva, vecRoo);
//         for (int i = 0; i < vecRoo.size(); i ++) output_file << "r" << i << " " << vecRoo[i] << endl;
//         for (int i = 0; i < vecVal.size(); i ++) output_file << "v" << i << " " << vecVal[i] << endl;

//         Polynomial<Element> polEstErr = RS0.estimated_error(vecRoo, vecVal);
//         Polynomial<Element> polEstCod = RS0.estimated_codeword(polRec, polEstErr);
//         Polynomial<Element> polEstMes = RS0.estimated_message(polEstCod);
//         output_file << "err " << polEstErr << endl;
//         output_file << "cod " << polEstCod << endl;
//         output_file << "mes " << polEstMes << endl;
//     } catch (const char* error_message) {
//         cout << error_message << endl;
//     }
//     output_file.close();
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Example 6.10 - Page 248

Binary BIN0(false);
Binary BIN1(true);
int INT0 = 3;

Polynomial<Binary> POL0(&fields::empty_field, {BIN1, BIN1, BIN0, BIN0, BIN1});
Field FIE0(&POL0);
RS RS0(&FIE0, INT0);

#define ELE(i) FIE0.general_elements[i]

int main() {
    ofstream output_file("output.txt");
    try {
        output_file << "n" << RS0.codeword_length() << " k" << RS0.message_length() << " p" << RS0.parity_length() << " s" << RS0.symbol_size() << " d" << RS0.detection_capability() << " c" << RS0.correction_capability() << endl;
        output_file << "g " << RS0.generator_polynomial << endl;

        Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
        Polynomial<Element> polCod = RS0.systematic_encode(polMes);
        output_file << "m " << polMes << endl;
        output_file << "c " << polCod << endl;

        Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
        polErr.coefficients[3] = ELE(7); polErr.coefficients[10] = ELE(11);
        Polynomial<Element> polRec = (polCod + polErr).redegree(RS0.codeword_length() - 1);
        output_file << "e " << polErr << endl;
        output_file << "r " << polRec << endl;

        vector<Element> vecSyn = RS0.syndrome(polRec);
        Polynomial<Element> polSyn = RS0.syndrome(vecSyn);
        for (int i = 0; i < vecSyn.size(); i ++) output_file << "s" << i << " " << vecSyn[i] << endl;
        output_file << "syn " << polSyn << endl;

        Polynomial<Element> polErrLoc = RS0.pgz_error_locator(vecSyn);
        Polynomial<Element> polErrEva = RS0.pgz_error_evaluator(polSyn, polErrLoc);
        output_file << "loc " << polErrLoc << endl;
        output_file << "eva " << polErrEva << endl;

        vector<Element> vecRoo = RS0.chien_roots(polErrLoc);
        vector<Element> vecVal = RS0.pgz_error_values(polErrLoc, polErrEva, vecRoo);
        for (int i = 0; i < vecRoo.size(); i ++) output_file << "r" << i << " " << vecRoo[i] << endl;
        for (int i = 0; i < vecVal.size(); i ++) output_file << "v" << i << " " << vecVal[i] << endl;

        Polynomial<Element> polEstErr = RS0.estimated_error(vecRoo, vecVal);
        Polynomial<Element> polEstCod = RS0.estimated_codeword(polRec, polEstErr);
        Polynomial<Element> polEstMes = RS0.estimated_message(polEstCod);
        output_file << "err " << polEstErr << endl;
        output_file << "cod " << polEstCod << endl;
        output_file << "mes " << polEstMes << endl;
    } catch (const char* error_message) {
        cout << error_message << endl;
    }
    output_file.close();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
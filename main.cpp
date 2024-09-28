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
//         Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
//         Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
//         polErr.coefficients[3] = ELE(7); polErr.coefficients[6] = ELE(3); polErr.coefficients[12] = ELE(4);

//         Polynomial<Element> polCod = RS0.systematic_encode(polMes, "rs_encode");
//         Polynomial<Element> polRec = RS0.add_error(polCod, polErr, "rs_add_error");
//         Polynomial<Element> polEstMes = RS0.bm_decode(polRec, "rs_decode");

//         cout << "n" << RS0.codeword_length() << ", k" << RS0.message_length() << ", p" << RS0.parity_length() << ", s" << RS0.symbol_size() << ", d" << RS0.detection_capability() << ", c" << RS0.correction_capability() << ", g" << RS0.generator_polynomial << endl;
//         cout << boolalpha << (polMes == polEstMes) << endl;
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
//         Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
//         Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
//         polErr.coefficients[0] = ELE(2); polErr.coefficients[12] = ELE(21); polErr.coefficients[20] = ELE(7);

//         Polynomial<Element> polCod = RS0.systematic_encode(polMes, "rs_encode");
//         Polynomial<Element> polRec = RS0.add_error(polCod, polErr, "rs_add_error");
//         Polynomial<Element> polEstMes = RS0.bm_decode(polRec, "rs_decode");

//         cout << "n" << RS0.codeword_length() << ", k" << RS0.message_length() << ", p" << RS0.parity_length() << ", s" << RS0.symbol_size() << ", d" << RS0.detection_capability() << ", c" << RS0.correction_capability() << ", g" << RS0.generator_polynomial << endl;
//         cout << boolalpha << (polMes == polEstMes) << endl;
//     } catch (const char* error_message) {
//         cout << error_message << endl;
//     }
//     output_file.close();
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Example 6.10 - Page 248

// Binary BIN0(false);
// Binary BIN1(true);
// int INT0 = 3;

// Polynomial<Binary> POL0(&fields::empty_field, {BIN1, BIN1, BIN0, BIN0, BIN1});
// Field FIE0(&POL0);
// RS RS0(&FIE0, INT0);

// #define ELE(i) FIE0.general_elements[i]

// int main() {
//     try {
//         Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
//         Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
//         polErr.coefficients[3] = ELE(7); polErr.coefficients[10] = ELE(11);

//         Polynomial<Element> polCod = RS0.systematic_encode(polMes, "rs_encode");
//         Polynomial<Element> polRec = RS0.add_error(polCod, polErr, "rs_add_error");
//         Polynomial<Element> polEstMes = RS0.euclidean_decode(polRec, "rs_decode");

//         cout << "n" << RS0.codeword_length() << ", k" << RS0.message_length() << ", p" << RS0.parity_length() << ", s" << RS0.symbol_size() << ", d" << RS0.detection_capability() << ", c" << RS0.correction_capability() << ", g" << RS0.generator_polynomial << endl;
//         cout << boolalpha << (polMes == polEstMes) << endl;
//     } catch (const char* error_message) {
//         cout << error_message << endl;
//     }
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Example 6.11 - Page 249

Binary BIN0(false);
Binary BIN1(true);
int INT0 = 3;

Polynomial<Binary> POL0(&fields::empty_field, {BIN1, BIN0, BIN1, BIN0, BIN0, BIN1});
Field FIE0(&POL0);
RS RS0(&FIE0, INT0);

#define ELE(i) FIE0.general_elements[i]

int main() {
    ofstream output_file("output.txt");
    try {
        Polynomial<Element> polMes(&FIE0, vector<Element>(RS0.message_length(), FIE0.zero_element()));
        Polynomial<Element> polErr(&FIE0, vector<Element>(RS0.codeword_length(), FIE0.zero_element()));
        polErr.coefficients[0] = ELE(2); polErr.coefficients[12] = ELE(21); polErr.coefficients[20] = ELE(7);

        Polynomial<Element> polCod = RS0.systematic_encode(polMes, "rs_encode");
        Polynomial<Element> polRec = RS0.add_error(polCod, polErr, "rs_add_error");
        Polynomial<Element> polEstMes = RS0.euclidean_decode(polRec, "rs_decode");

        cout << "n" << RS0.codeword_length() << ", k" << RS0.message_length() << ", p" << RS0.parity_length() << ", s" << RS0.symbol_size() << ", d" << RS0.detection_capability() << ", c" << RS0.correction_capability() << ", g" << RS0.generator_polynomial << endl;
        cout << boolalpha << (polMes == polEstMes) << endl;
    } catch (const char* error_message) {
        cout << error_message << endl;
    }
    output_file.close();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: main.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"

Binary BIN0(false);
Binary BIN1(true);

////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    try {
        Polynomial<Binary> pol0(&fields::empty_field, {BIN1, BIN1, BIN0, BIN0, BIN1});
        Field fie0(&pol0);
        RS rs0(&fie0, 3);
        cout << "n" << rs0.codeword_length() << " k" << rs0.message_length() << " p" << rs0.parity_length() << " s" << rs0.symbol_size() << endl;
        cout << "g " << rs0.generator_polynomial << endl;

        Polynomial<Element> pol1(&fie0, vector<Element>(rs0.message_length(), fie0.zero_element()));
        Polynomial<Element> pol2 = rs0.systematic_encode(pol1);
        cout << "m " << pol1 << endl;
        cout << "c " << pol2 << endl;

        Polynomial<Element> pol3 = pol2; pol3.coefficients[3] = fie0.general_elements[7]; pol3.coefficients[6] = fie0.general_elements[3]; pol3.coefficients[12] = fie0.general_elements[4];
        cout << "r " << pol3 << endl;
        vector<Element> ele0s = rs0.syndrome_calculate(pol3);
        for (int i = 0; i < rs0.parity_length(); i ++) {
            cout << "s" << i << " " << ele0s[i] << endl;
        }
    } catch (const char* error_message) {
        cout << error_message << endl;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// int main() {
//     try {
//         Polynomial<Binary> pol0(&fields::empty_field, {BIN1, BIN1, BIN0, BIN1});
//         Field fie0(&pol0);
//         Matrix<Element> mat0(&fie0, {
//             {fie0.general_elements[1], fie0.general_elements[2], fie0.general_elements[5]}, 
//             {fie0.general_elements[5], fie0.general_elements[1], fie0.general_elements[2]}, 
//             {fie0.general_elements[2], fie0.general_elements[5], fie0.general_elements[1]}
//         });
//         cout << mat0.determinant() << endl;
//         cout << ~mat0 << endl;
//     } catch (const char* error_message) {
//         cout << error_message << endl;
//     }
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////
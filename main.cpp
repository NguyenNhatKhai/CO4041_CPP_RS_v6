////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File: main.cpp
// Author: Nhat Khai Nguyen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"

// int main() {
//     try {
//         Binary bin0(false);
//         Binary bin1(true);
//         Polynomial<Binary> pol0({bin1, bin1, bin0, bin0, bin1});
//         RS rs0(pol0, 3);
//         cout << "n" << rs0.codeword_length() << " k" << rs0.message_length() << " p" << rs0.parity_length() << " s" << rs0.symbol_size() << endl;
//         cout << "g " << rs0.generator_polynomial << endl;

//         Field fie0(&pol0);
//         Polynomial<Element> pol1(vector<Element>(rs0.message_length(), fie0.zero_element()));
//         Polynomial<Element> pol2 = rs0.systematic_encode(pol1);
//         cout << "m " << pol1 << endl;
//         cout << "c " << pol2 << endl;

//         Polynomial<Element> pol3 = pol2; pol3.coefficients[3] = fie0.general_elements[7]; pol3.coefficients[6] = fie0.general_elements[3]; pol3.coefficients[12] = fie0.general_elements[4];
//         cout << "r " << pol3 << endl;
//         vector<Element> ele0s = rs0.syndrome_calculate(pol3);
//         for (int i = 0; i < rs0.parity_length(); i ++) {
//             cout << "s" << i << " " << ele0s[i] << endl;
//         }
//     } catch (const char* error_message) {
//         cout << error_message << endl;
//     }
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    return 0;
}

#include <iostream>
#include <string>
#include <iomanip>

double extractNumeric(const std::string& input) {
    bool hasDecimal = false; // To track if a single decimal exists
    bool hasSign = false;    // To track if a sign (+ or -) exists
    bool hasDigit = false;   // To confirm at least one digit
    int decimalCount = 0;    // Tracks the number of decimal points
    int signCount = 0;       // Tracks the number of signs
    size_t i = 0;            // Index to iterate through the string

    // Allow a leading '+' or '-'
    if (input[i] == '+' || input[i] == '-') {
        hasSign = true;
        ++i;
        ++signCount;
    }

    for (; i < input.length(); ++i) {
        char c = input[i];
        if (isdigit(c)) {
            hasDigit = true;
        } else if (c == '.') {
            ++decimalCount;
            if (decimalCount > 1) return -999999.99; // Multiple decimals
            hasDecimal = true;
        } else {
            return -999999.99; // Invalid character
        }
    }

    // Check overall validity
    if (!hasDigit || (signCount > 1) || (decimalCount > 1)) {
        return -999999.99;
    }

    // Convert valid string to double using manual parsing
    double result = 0.0;
    double factor = 1.0;
    bool negative = input[0] == '-';

    size_t start = (hasSign) ? 1 : 0; // Start after sign if present
    for (i = start; i < input.length(); ++i) {
        if (input[i] == '.') {
            factor = 0.1; // Decimal detected, switch to fractional part
            continue;
        }

        if (factor == 1.0) { // Processing integer part
            result = result * 10 + (input[i] - '0');
        } else { // Processing fractional part
            result += (input[i] - '0') * factor;
            factor *= 0.1;
        }
    }

    return negative ? -result : result;
}

int main() {
    std::string userInput;

    std::cout << "Enter a string (type END to exit):" << std::endl;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if (userInput == "END") {
            break;
        }

        double number = extractNumeric(userInput);

        if (number == -999999.99) {
            std::cout << "The input is invalid." << std::endl;
        } else {
            std::cout << "The input is: " << std::fixed << std::setprecision(4) << number << std::endl;
        }
    }

    return 0;
}


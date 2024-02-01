#include "result_generate.h"
#include <iostream>

#include <cmath>

double calculate_postfix(const char* output) {
    Stack mystack;
    int i = 0;
    while (output[i] != '\0') {
        if (isdigit(output[i]) || (output[i] == '.' && isdigit(output[i + 1]))) {
            double num = std::stod(output + i);
            mystack.push(num);
            while (isdigit(output[i]) || output[i] == '.') {
                i++;
            }
        } else if (output[i] == ' ') {
            i++;
        } else {
            if (output[i] == '!') {
                double operand = mystack.pop();
                double result = 1;
                for (int j = 1; j <= operand; j++) {
                    result *= j;
                }
                mystack.push(result);
            } else if (output[i] == '^') {
                double exponent = mystack.pop();
                double base = mystack.pop();
                double result = std::pow(base, exponent);
                mystack.push(result);
            } else {
                double operand2 = mystack.pop();
                double operand1 = mystack.pop();

                if (output[i] == '+')
                    mystack.push(operand1 + operand2);
                else if (output[i] == '-')
                    mystack.push(operand1 - operand2);
                else if (output[i] == '*')
                    mystack.push(operand1 * operand2);
                else if (output[i] == '/')
                    mystack.push(operand1 / operand2);
            }
            i++;
        }
    }
    return mystack.pop();
}

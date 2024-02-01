#include "calculator_functions.h"
#include <cmath>
#include <iostream>

bool CalculatorFunctions::performCalculation(Stack* numStack, Stack* opStack) {
    double operand2, operand1, result;
    operand2 = numStack->pop();

    if (opStack->show_top() == '+') {
        operand1 = numStack->pop();
        result = operand1 + operand2;
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == '-') {
        operand1 = numStack->pop();
        result = operand1 - operand2;
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == '*') {
        operand1 = numStack->pop();
        result = operand1 * operand2;
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == '/') {
        if (operand2 == 0) {
            std::cerr << "\nIt cannot be divided by 0!\n";
            return false;
        }
        operand1 = numStack->pop();
        result = operand1 / operand2;
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == '^') {
        operand1 = numStack->pop();
        result = pow(operand1, operand2);
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == 's') {
        result = sin(operand2);
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == 'c') {
        result = cos(operand2);
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == 't') {
        if (cos(operand2) == 0) {
            std::cerr << "\nInvalid argument for tangent!\n";
            return false;
        }
        result = tan(operand2);
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == 'g') {
        if (sin(operand2) == 0) {
            std::cerr << "\nInvalid argument for cotangence!\n";
            return false;
        }
        result = 1.0 / tan(operand2);  // calculateCtg(operand2);
        numStack->push(result);
        opStack->pop();
    } else if (opStack->show_top() == 'e') {
        result = exp(operand2);
        numStack->push(result);
        opStack->pop();
    } else {
        std::cerr << "\nWrong Expression!\n";
        return false;
    }
    return true;
}

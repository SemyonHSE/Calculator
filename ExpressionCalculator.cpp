#include "ExpressionCalculator.h"
#include <cmath>
#include <iostream>
#include <sstream>

ExpressionCalculator::ExpressionCalculator() = default;

int ExpressionCalculator::getPriority(char symbol) {
    if (symbol == 's' || symbol == 'c' || symbol == 't' || symbol == 'g' || symbol == 'e')
        return 4;
    else if (symbol == '^')
        return 3;
    else if (symbol == '+' || symbol == '-')
        return 1;
    else if (symbol == '*' || symbol == '/' || symbol == '%')
        return 2;
    else return 0;
}

double ExpressionCalculator::calculateSin(double x) {
    return (round(sin(x) * 10000000) / 10000000);
}

double ExpressionCalculator::calculateCos(double x) {
    return (round(cos(x) * 10000000) / 10000000);
}

double ExpressionCalculator::calculateTan(double x) {
    return calculateSin(x) / calculateCos(x);
}

double ExpressionCalculator::calculateCotan(double x) {
    return calculateCos(x) / calculateSin(x);
}

bool ExpressionCalculator::performCalculation() {
    double operand2, operand1, result;
    operand2 = NumberStack.pop();

    if (OperatorStack.show_top() == '+') {
        operand1 = NumberStack.pop();
        result = operand1 + operand2;
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == '-') {
        operand1 = NumberStack.pop();
        result = operand1 - operand2;
        NumberStack.push(result);
        OperatorStack.pop();
    }else if (OperatorStack.show_top() == '*') {
        operand1 = NumberStack.pop();
        result = operand1 * operand2;
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == '/') {
        if (operand2 == 0) {
            std::cerr << "\nIt cannot be divided by 0!\n";
            return false;
        }
        operand1 = NumberStack.pop();
        result = operand1 / operand2;
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == '%') {
        operand1 = NumberStack.pop();
        //result = modf(operand1, &operand2);
        result = fmod(operand1, operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    }else if (OperatorStack.show_top() == '^') {
        operand1 = NumberStack.pop();
        result = pow(operand1, operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == 's') {
        result = calculateSin(operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == 'c') {
        result = calculateCos(operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == 't') {
        if (calculateCos(operand2) == 0) {
            std::cerr << "\nInvalid argument for tangent!\n";
            return false;
        }

        result = calculateTan(operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == 'g') {
        if (calculateSin(operand2) == 0) {
            std::cerr << "\nInvalid argument for cotangence!\n";
            return false;
        }

        result = calculateCotan(operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    } else if (OperatorStack.show_top() == 'e') {
        result = exp(operand2);
        NumberStack.push(result);
        OperatorStack.pop();
    } else {
        std::cerr << "Error";
        return false;
    }

    return true;
}

std::string ExpressionCalculator::replaceSymbolWithNumber(std::string &expression) {
    int length = expression.length();
    int flag = 1;

    while (flag) {
        flag = 0;

        if (97 <= expression[0] && expression[0] <= 122 && (expression[1] < 97 || expression[1] > 122) && expression[0] != 'p') {
            std::string param;
            std::cout << expression[0] << '=';
            std::cin >> param;
            char current = expression[0];

            for (int j = 1; j < length; ++j) {
                if (expression[j] == current && (expression[j - 1] < 97 || expression[j - 1] > 122) &&
                    (expression[j + 1] < 97 || expression[j + 1] > 122) && expression[j] != 'p') {
                    expression.replace(j, 1, param);
                }
            }

            expression.replace(0, 1, param);
        }

        for (int i = 1; i < length; ++i) {
            if (expression[i] >= 97 && expression[i] <= 122 &&
                (expression[i - 1] < 97 || expression[i - 1] > 122) &&
                (expression[i + 1] < 97 || expression[i + 1] > 122) && expression[i] != 'p') {
                std::string param;
                std::cout << expression[i] << '=';
                std::cin >> param;
                char current = expression[i];

                for (int j = i + 1; j < length; ++j) {
                    if (expression[j] == current && (expression[j - 1] < 97 || expression[j - 1] > 122) &&
                        (expression[j + 1] < 97 || expression[j + 1] > 122)&& expression[j] != 'p') {
                        expression.replace(j, 1, param);
                    }
                }

                expression.replace(i, 1, param);
            }
        }

        length = expression.length();

        if (97 <= expression[0] && expression[0] <= 122 && (expression[1] < 97 || expression[1] > 122) && expression[0] != 'p') {
            flag = 1;
        } else {
            for (int i = 1; i < length; ++i) {
                if (expression[i] >= 97 && expression[i] <= 122 &&
                    (expression[i - 1] < 97 || expression[i - 1] > 122) &&
                    (expression[i + 1] < 97 || expression[i + 1] > 122) && expression[i] != 'p') {
                    flag = 1;
                }
            }
        }
    }

    return expression;
}


void ExpressionCalculator::runCalculator() {
    while (true) {
        std::cout << "Type your expression" << std::endl;
        std::string inputExpression;
        getline(std::cin, inputExpression);

        ExpressionCalculator::replaceSymbolWithNumber(inputExpression);

        std::stringstream sstream{inputExpression};

        char currentSymbol;
        double value;
        bool negative = true;



        while (true) {
            currentSymbol = sstream.peek();

            if (currentSymbol == '\377')
                break;

            if (currentSymbol == ' ') {
                sstream.ignore();
                continue;
            }

            if (currentSymbol == 's' || currentSymbol == 'c' || currentSymbol == 't' || currentSymbol == 'e') {
                char function[3];
                for (int i = 0; i < 3; i++) {
                    currentSymbol = sstream.peek();
                    function[i] = currentSymbol;
                    sstream.ignore();
                }

                if (function[0] == 's' && function[1] == 'i' && function[2] == 'n') {
                    OperatorStack.push('s');
                    continue;
                }

                if (function[0] == 'c' && function[1] == 'o' && function[2] == 's') {
                    OperatorStack.push('c');
                    continue;
                }

                if (function[0] == 't' && function[1] == 'a' && function[2] == 'n') {
                    OperatorStack.push('t');
                    continue;
                }

                if (function[0] == 'c' && function[1] == 't' && function[2] == 'g') {
                    OperatorStack.push('g');
                    continue;
                }

                if (function[0] == 'e' && function[1] == 'x' && function[2] == 'p') {
                    OperatorStack.push('e');
                    continue;
                }
            }

            if (currentSymbol == 'p') {
                NumberStack.push(M_PI);
                negative = 0;
                sstream.ignore();
                continue;
            }

            if (currentSymbol >= '0' && currentSymbol <= '9' || currentSymbol == '-' && negative == 1) {
                sstream >> value;
                NumberStack.push(value);
                negative = 0;
                continue;
            }

            if (currentSymbol == '+' || currentSymbol == '-' && negative == 0 || currentSymbol == '*' ||
                currentSymbol == '/' || currentSymbol == '%' || currentSymbol == '^') {
                if (OperatorStack.size() == 0) {
                    OperatorStack.push(currentSymbol);
                    sstream.ignore();
                    continue;
                }

                if (OperatorStack.size() != 0 && getPriority(currentSymbol) > getPriority(OperatorStack.show_top())) {
                    OperatorStack.push(currentSymbol);
                    sstream.ignore();
                    continue;
                }

                if (OperatorStack.size() != 0 && getPriority(currentSymbol) <= getPriority(OperatorStack.show_top())) {
                    if (!performCalculation()) {
                        system("pause");
                        return;
                    }
                    continue;
                }
            }

            if (currentSymbol == '(') {
                OperatorStack.push(currentSymbol);
                sstream.ignore();
                continue;
            }

            if (currentSymbol == ')') {
                while (OperatorStack.show_top() != '(') {
                    if (!performCalculation()) {
                        system("pause");
                        return;
                    } else continue;
                }
                OperatorStack.pop();
                sstream.ignore();
                continue;
            } else {
                std::cout << "\nWrong Expression!\n";
                system("pause");
                return;
            }
        }

        while (OperatorStack.size() != 0) {
            if (!performCalculation()) {
                system("pause");
                return;
            } else continue;
        }

        std::cout << "Answer: " << NumberStack.show_top() << std::endl;
    }
}


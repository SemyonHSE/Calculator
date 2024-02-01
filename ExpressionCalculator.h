#ifndef EXPRESSIONCALCULATOR_H
#define EXPRESSIONCALCULATOR_H

#include "stack/stack.h"
#include <string>

class ExpressionCalculator {
public:
    ExpressionCalculator();

    void runCalculator();

private:
    Stack NumberStack;
    Stack OperatorStack;

    int getPriority(char symbol);
    double calculateSin(double x);
    double calculateCos(double x);
    double calculateTan(double x);
    double calculateCotan(double x);
    bool performCalculation();
    std::string replaceSymbolWithNumber(std::string &expression);
};

#endif

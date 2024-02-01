#include <iostream>
#include "stack/stack.h"
#include <string>
#include "cmath"


int priority(char symbol);
const double Pi = acos(-1);
double Sin(double x);
double Cos(double x);
double Tg(double x);
double Ctg(double x);


int main() {

    return 0;
}

int priority(char symbol) {
    if (symbol == 's' || symbol == 'c' || symbol == 't' || symbol == 'g' || symbol == 'e')
        return 4;
    else if (symbol == '^')
        return 3;
    else if (symbol == '+' || symbol == '-')
        return 1;
    else if (symbol == '*' || symbol == '/')
        return 2;
    else return 0;
}

double Sin(double x) {
    return (round(sin(x) * 10000000) / 10000000);
}
double Cos(double x) {
    return (round(cos(x) * 10000000) / 10000000);
}
double Tg(double x) {
    double a = Sin(x);
    double b = Cos(x);
    return (a / b);
}
double Ctg(double x) {
    double a = Cos(x);
    double b = Sin(x);
    return (a / b);
}

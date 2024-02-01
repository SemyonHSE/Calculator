#include <iostream>
#include "stack/stack.h"
#include <string>
#include "cmath"

using namespace std;

int priority(char symbol);
const double Pi = acos(-1);
double Sin(double x);
double Cos(double x);
double Tg(double x);
double Ctg(double x);
double calculation(Stack *NumberStack, Stack *OperatorStack);

int main() {
    /*NumberStack
    OperatorStack*/
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
double calculation(Stack *NumberStack, Stack *OperatorStack){
    double operand2, operand1, rez;
    operand2 = NumberStack->pop();
    if (OperatorStack->show_top()=='+'){
        operand1 = NumberStack->pop();
        rez = operand1 + operand2;
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='-'){
        operand1 = NumberStack->pop();
        rez = operand1 - operand2;
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='*'){
        operand1 = NumberStack->pop();
        rez = operand1 * operand2;
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='/'){
        if (operand2 ==0){
            cerr << "\nIt cannot be divided by 0!\n";
            return -1;
        }
        operand1 = NumberStack->pop();
        rez = operand1 / operand2;
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='^'){
        operand1 = NumberStack->pop();
        rez = pow(operand1, operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if (OperatorStack->show_top()=='s'){
        rez = sin(operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if (OperatorStack->show_top()=='c'){
        rez = cos(operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='t'){
        if (cos(operand2)==0){
            cerr << "\nInvalid argument for tangent!\n";
            return -1;
        }
        rez = tan(operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='g'){
        if (sin(operand2)==0){
            cerr << "\nInvalid argument for cotangence!\n";
            return -1;
        }
        rez = Ctg(operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='e'){
        rez = exp(operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else{
        cerr<<"Error";
        return -1;
    }

}
















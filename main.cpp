#include <iostream>
#include "stack/stack.h"
#include <string>
#include "cmath"
#include "sstream"

using namespace std;

int priority(char symbol);
const double Pi = acos(-1);
double Sin(double x);
double Cos(double x);
double Ctg(double x);
bool calculation(Stack *NumberStack, Stack *OperatorStack);


std::string replaceSymbolWithNumber(std::string& a) {
    int ln = a.length();
    //std::string zam = std::to_string(b);
    int flag = 1;
    while (flag)
    {
        flag = 0;
        if (97<=a[0] && a[0]<=122 && (a[1] < 97 || a[1]>122))
        {
            std::string param;
            std::cout << a[0] << '=';
            std::cin >> param;
            char tek = a[0];
            for (int j = 1; j < ln; ++j)
            {
                if (a[j] == tek && (a[j - 1] < 97 || a[j - 1]>122) && (a[j + 1] < 97 || a[j + 1]>122))
                {
                    a.replace(j, 1, param);
                }
            }
            a.replace(0, 1, param);
        }
        for (int i = 1; i < ln; ++i)
        {
            if (a[i] >= 97 && a[i] <= 122 && (a[i - 1] < 97 || a[i - 1]>122) && (a[i + 1] < 97 || a[i + 1]>122))
            {
                std::string param;
                std::cout << a[i] << '=';
                std::cin >> param;
                char tek = a[i];
                for (int j = i + 1; j < ln; ++j)
                {
                    if (a[j] == tek && (a[j - 1] < 97 || a[j - 1]>122) && (a[j + 1] < 97 || a[j + 1]>122))
                    {
                        a.replace(j, 1, param);
                    }
                }
                a.replace(i, 1, param);
            }
        }
        ln = a.length();
        if (97 <= a[0] && a[0] <= 122 && (a[1] < 97 || a[1]>122))
        {
            flag = 1;
        }
        else
        {
            for (int i = 1; i < ln; ++i)
            {
                if (a[i] >= 97 && a[i] <= 122 && (a[i - 1] < 97 || a[i - 1]>122) && (a[i + 1] < 97 || a[i + 1]>122))
                {
                    flag = 1;
                }
            }
        }
    }
    return a;
}
int main() {
    Stack numStack; // Стек для хранения чисел
    Stack opStack;  // Стек для хранения операций

    while (true) {
        std::cout << "Type an expression: ";
        std::string inputStr;

        getline(std::cin, inputStr);
        std::stringstream strStream{inputStr};

        char currentSymbol;
        double numericValue;
        bool isNegative = true;

        while (true) {
            currentSymbol = strStream.peek();
            if (currentSymbol == '\377')
                break;
            if (currentSymbol == ' ') {
                strStream.ignore();
                continue;
            }
            if (currentSymbol == 's' || currentSymbol == 'c' || currentSymbol == 't' || currentSymbol == 'e') {
                char function[3];
                for (int i = 0; i < 3; i++) {
                    currentSymbol = strStream.peek();
                    function[i] = currentSymbol;
                    strStream.ignore();
                }
                if (function[0] == 's' && function[1] == 'i' && function[2] == 'n') {
                    opStack.push('s');
                    continue;
                }
                if (function[0] == 'c' && function[1] == 'o' && function[2] == 's') {
                    opStack.push('c');
                    continue;
                }
                if (function[0] == 't' && function[1] == 'a' && function[2] == 'n') {
                    opStack.push('t');
                    continue;
                }
                if (function[0] == 'c' && function[1] == 't' && function[2] == 'g') {
                    opStack.push('g');
                    continue;
                }
                if (function[0] == 'e' && function[1] == 'x' && function[2] == 'p') {
                    opStack.push('e');
                    continue;
                }
            }
            if (currentSymbol == 'p') {
                numStack.push(Pi);
                isNegative = false;
                strStream.ignore();
                continue;
            }
            if (currentSymbol >= '0' && currentSymbol <= '9' || currentSymbol == '-' && isNegative == 1) {
                strStream >> numericValue;
                numStack.push(numericValue);
                isNegative = false;
                continue;
            }
            if (currentSymbol == '+' || currentSymbol == '-' && isNegative == 0 || currentSymbol == '*' || currentSymbol == '/' || currentSymbol == '^') {
                if (opStack.size() == 0) {
                    opStack.push(currentSymbol);
                    strStream.ignore();
                    continue;
                }
                if (opStack.size() != 0 && priority(currentSymbol) > priority(opStack.show_top())) {
                    opStack.push(currentSymbol);
                    strStream.ignore();
                    continue;
                }

                if (opStack.size() != 0 && priority(currentSymbol) <= priority(opStack.show_top())) {
                    if (!calculation(&numStack, &opStack)) {
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
            if (currentSymbol == '(') {
                opStack.push(currentSymbol);
                strStream.ignore();
                continue;
            }
            if (currentSymbol == ')') {
                while (opStack.show_top() != '(') {
                    if (!calculation(&numStack, &opStack)) {
                        system("pause");
                        return 0;
                    } else continue;
                }
                opStack.pop();
                strStream.ignore();
                continue;
            } else {
                std::cout << "\nWrong expression!\n";
                system("pause");
                return 0;
            }
        }
        while (opStack.size() != 0) {
            if (!calculation(&numStack, &opStack)) {
                system("pause");
                return 0;
            } else continue;
        }
        std::cout << "Answer: " << numStack.show_top() << std::endl;
    }
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

double Ctg(double x) {
    return Cos(x) / Sin(x);
}

bool calculation(Stack *NumberStack, Stack *OperatorStack){
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
            return false;
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
            return false;
        }
        rez = tan(operand2);
        NumberStack->push(rez);
        OperatorStack->pop();
    }
    else if(OperatorStack->show_top()=='g'){
        if (sin(operand2)==0){
            cerr << "\nInvalid argument for cotangence!\n";
            return false;
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
        return false;
    }
    return true;
}
















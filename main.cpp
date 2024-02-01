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
double Tg(double x);
double Ctg(double x);
bool calculation(Stack *NumberStack, Stack *OperatorStack);

std::string replaceSymbolWithNumber(std::string& a) {
    int ln = a.length();
    //std::string zam = std::to_string(b);
    int flag = 1;
    while (flag)
    {
        flag = 0;
        if (97<=a[0] && a[0]<=122 && (a[1] < 97 || a[1]>122) && a[0]!='p')
        {
            std::string param;
            std::cout << a[0] << '=';
            std::cin >> param;
            char tek = a[0];
            for (int j = 1; j < ln; ++j)
            {
                if (a[j] == tek && (a[j - 1] < 97 || a[j - 1]>122) && (a[j + 1] < 97 || a[j + 1]>122) && a[j]!='p')
                {
                    a.replace(j, 1, param);
                }
            }
            a.replace(0, 1, param);
        }
        for (int i = 1; i < ln; ++i)
        {
            if (a[i] >= 97 && a[i] <= 122 && (a[i - 1] < 97 || a[i - 1]>122) && (a[i + 1] < 97 || a[i + 1]>122) && a[i]!='p')
            {
                std::string param;
                std::cout << a[i] << '=';
                std::cin >> param;
                char tek = a[i];
                for (int j = i + 1; j < ln; ++j)
                {
                    if (a[j] == tek && (a[j - 1] < 97 || a[j - 1]>122) && (a[j + 1] < 97 || a[j + 1]>122) && a[i] != 'p')
                    {
                        a.replace(j, 1, param);
                    }
                }
                a.replace(i, 1, param);
            }
        }
        ln = a.length();
        if (97 <= a[0] && a[0] <= 122 && (a[1] < 97 || a[1]>122)&& a[0] != 'p')
        {
            flag = 1;
        }
        else
        {
            for (int i = 1; i < ln; ++i)
            {
                if (a[i] >= 97 && a[i] <= 122 && (a[i - 1] < 97 || a[i - 1]>122) && (a[i + 1] < 97 || a[i + 1]>122)&& a[i] != 'p')
                {
                    flag = 1;
                }
            }
        }
    }
    return a;
}
int main() {

    Stack NumberStack;
    Stack OperatorStack;

    while (true) {
        std::cout << "Type your expression" << std::endl;
        std::string str;
        getline(std::cin, str);
        str =replaceSymbolWithNumber(str);
        std::stringstream sstr{str};

        char symbol; //Переменная, в которую будет записываться текущий обрабатываемый символ
        double value;
        bool minus = true; //Нужен для того, чтобы программа смогла отличить унарный минус (-5) от вычитания (2-5)

        while (true) {
            symbol = sstr.peek(); //Смотрим на первый символ
            if (symbol == '\377')
                break; //Если достигнут конец строки, выходим из цикла
            if (symbol == ' ') { //Игнорирование пробелов
                sstr.ignore();
                continue;
            }
            if (symbol == 's' || symbol == 'c' || symbol == 't' || symbol == 'e') { //Если прочитана функция
                char function[3]; //массив на 3 символа для определения типа прочитанной функции
                for (int i = 0; i < 3; i++) {
                    symbol = sstr.peek();
                    function[i] = symbol;
                    sstr.ignore();
                }
                if (function[0] == 's' && function[1] == 'i' && function[2] == 'n') { //Если прочитанная функция - синус
                    OperatorStack.push('s'); //Операция кладется в стек с операциями
                    continue;
                }
                if (function[0] == 'c' && function[1] == 'o' &&
                    function[2] == 's') { //Если прочитанная функция - косинус
                    OperatorStack.push('c'); //Операция кладется в стек с операциями
                    continue;
                }
                if (function[0] == 't' && function[1] == 'a' &&
                    function[2] == 'n') { //Если прочитанная функция - тангенс
                    OperatorStack.push('t'); //Операция кладется в стек с операциями
                    continue;
                }
                if (function[0] == 'c' && function[1] == 't' &&
                    function[2] == 'g') { //Если прочитанная функция - котангенс
                    OperatorStack.push('g'); //Операция кладется в стек с операциями
                    continue;
                }
                if (function[0] == 'e' && function[1] == 'x' &&
                    function[2] == 'p') { //Если прочитанная функция - экспонента
                    OperatorStack.push('e'); //Операция кладется в стек с операциями
                    continue;
                }
            }
            if (symbol == 'p') { //Если прочитано число Пи
                NumberStack.push(Pi); //Число кладется в стек с числами
                minus = 0;
                sstr.ignore();
                continue;
            }
            if (symbol >= '0' && symbol <= '9' || symbol == '-' && minus == 1) { //Если прочитано число
                sstr >> value;
                NumberStack.push(value); //Число кладется в стек с числами
                minus = 0;
                continue;
            }
            if (symbol == '+' || symbol == '-' && minus == 0 || symbol == '*' || symbol == '/' ||
                symbol == '^') { //Если прочитана операция
                if (OperatorStack.size() == 0) { //Если стек с операциями пуст
                    OperatorStack.push(symbol); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }
                if (OperatorStack.size() != 0 && priority(symbol) > priority(
                        OperatorStack.show_top())) { //Если стек с операциями НЕ пуст, но приоритет текущей операции выше верхней в стеке с операциями
                    OperatorStack.push(symbol); //Операция кладется в стек с операциями
                    sstr.ignore();
                    continue;
                }

                if (OperatorStack.size() != 0 && priority(symbol) <= priority(
                        OperatorStack.show_top())) {//Если стек с операциями НЕ пуст, но приоритет текущей операции ниже либо равен верхней в стеке с операциями
                    if (calculation(&NumberStack, &OperatorStack) == false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }
            if (symbol == '(') { //Если прочитана открывающаяся скобка
                OperatorStack.push(symbol); //Операция кладется в стек с операциями
                sstr.ignore();
                continue;
            }
            if (symbol == ')') { //Если прочитана закрывающаяся скобка
                while (OperatorStack.show_top() != '(') {
                    if (calculation(&NumberStack, &OperatorStack) ==
                        false) { //Если функция вернет "false", то прекращаем работу
                        system("pause");
                        return 0;
                    } else continue; //Если все хорошо
                }
                OperatorStack.pop();
                sstr.ignore();
                continue;
            } else { //Если прочитан какой-то странный символ
                std::cout << "\nWrong Expression!\n";
                system("pause");
                return 0;
            }
        }
        while (OperatorStack.size() != 0) { //Вызываем матем. функцию до тех пор, пока в стеке с операциями не будет 0 элементов
            if (calculation(&NumberStack, &OperatorStack) == false) { //Если функция вернет "false", то прекращаем работу
                system("pause");
                return 0;
            } else continue; //Если все хорошо
        }
        std::cout << "Answer: " << NumberStack.show_top() << std::endl; //Выводим ответ
        system("pause");
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
double Tg(double x) {
    return Sin(x) / Cos(x);
}

double Ctg(double x) {
    return Cos(x) / Sin(x);
}
bool calculation(Stack *NumberStack, Stack *OperatorStack){
    double operand2, operand1, rez;
    operand2 = NumberStack->pop();
    if (OperatorStack->show_top()=='+'){
        /*
        if (NumberStack->isEmpty())
        {
            throw "\nWrong Expression!\n";
        }
        */
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
        cerr<<"\nWrong Expression!\n";
        return false;
    }
    return true;
}















#include "result_generate.h"
#include <iostream>
#include <cmath>

double actions(char element, double operand) {
    switch (element) {
        case 's':
            return sin(operand);
        case 'c':
            return cos(operand);
        case 't':
            return tan(operand);
        case 'g':
            return 1 / (tan(operand));
        default:
            return -1;
    }
}

void process(char* output, const char* input, int& k, int& i, const char element) {
    i += 4;
    int l = 0;
    char kira[MAX_SIZE] = { 0 };
    while (isdigit(input[i]) || input[i] == '.') {
        kira[l] = input[i++];
        l++;
    }
    double shaposhnikov = actions(element, std::atoi(kira));
    for (char j: std::to_string(shaposhnikov)) {
        output[k++] = j;
    }
    output[k++] = ' ';
    i--;
}

void postfix(char* output, const char* input, Stack* mystack) {
    int i = 0; // index for input
    int k = 0; // index for output
    for (i = 0; input[i]; ++i) {
        if (!is_operator(input[i]) && input[i] != '(' && input[i] != ')' && input[i] != 's') {
            while (!is_operator(input[i]) && input[i] != '(' && input[i] != ')' && input[i]) {
                output[k++] = input[i];
                i++;
            }
            output[k++] = ' ';
            i--;
        }
        else if (input[i] == '(')
            mystack->push(input[i]);
        else if (input[i] == ')') {
            while (!mystack->isEmpty() && mystack->show_top() != '(') {
                output[k++] = mystack->pop();
                output[k++] = ' ';
            }
            if (!mystack->isEmpty()) {
                mystack->pop();
            }
        }
        else if (input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n' && input[i + 3] == '(') {
            process(output, input, k, i, 's');
        }
        else if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's' && input[i + 3] == '(') {
            process(output, input, k, i, 'c');
        }
        else if (input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'g' && input[i + 3] == '(') {
            process(output, input, k, i, 't');
        }
        else if (input[i] == 'c' && input[i + 1] == 't' && input[i + 2] == 'g' && input[i + 3] == '(') {
            process(output, input, k, i, 'g');
        }
        else if (is_operator(input[i])) {
            while (!mystack->isEmpty() && priority(input[i]) <= priority(mystack->show_top())) {
                output[k++] = mystack->pop();
                output[k++] = ' ';
            }
            mystack->push(input[i]);
        }
    }
    while (!mystack->isEmpty()) {
        output[k++] = mystack->pop();
        output[k++] = ' ';
    }
    output[k] = '\0';
}

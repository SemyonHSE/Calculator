#include "result_generate.h"

int is_operator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^' || op == '!';
}

int priority(char sign) {
    if (sign == '(' || sign == ')')
        return 0;
    if (sign == '+' || sign == '-')
        return 1;
    if (sign == '*' || sign == '/' || sign == '%')
        return 2;
    if (sign == '^' || sign == '!')
        return 3;
    return -1;
}
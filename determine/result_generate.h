#ifndef LOGIC_H
#define LOGIC_H

#include "../stack/stack.h"

#define MAX_SIZE 100

int is_operator(char op);
int priority(char sign);
void postfix(char* output, const char* input, Stack* mystack);
double calculate_postfix(const char* output);

#endif

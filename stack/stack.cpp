#include "stack.h"
#include <iostream>
void Stack::push(double num)
{
	if (top < MAX_SIZE)
		arr[++top] = num;
	else
		std::cout << "Stack overflow!" << std::endl;
}

double Stack::pop()
{
	if (top >= 0)
		return arr[top--];
}

bool Stack::isEmpty() const
{
	return top == -1;
}

bool Stack::isFull() const
{
	return top == MAX_SIZE - 1;
}

int Stack::size() const
{
	return top + 1;
}

double Stack::show_top() const
{
	return arr[top];
}

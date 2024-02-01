#ifndef STACK
#define STACK

#define MAX_SIZE 100

class Stack {
private:
	double arr[MAX_SIZE];
	int top;

public:
	Stack() : top(-1) {}
	void push(double num);
	double pop();
	bool isEmpty() const;
	bool isFull() const;
	int size() const;
    double show_top() const;
};

#endif

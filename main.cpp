#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <cstring>
#include "determine/result_generate.h"
#include "stack/stack.h"
#include <string>
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
    char output[MAX_SIZE] = { 0 };
    Stack mystack;

    int key;
    std::cin >> key;
    std::cin.ignore(INT_MAX, '\n');

    if (key == 1) {
        char input[MAX_SIZE] = { 0 };
        std::cin.getline(input, MAX_SIZE);
        int size = std::strlen(input);
        if (input[size - 1] == '\n') {
            input[size - 1] = 0;
            size -= 1;
        }
        postfix(output, input, &mystack);
        std::cout << output << std::endl;
        std::cout << "Result: " << calculate_postfix(output);
    } else if (key == 2) {
    } else if (key == 3) {
    }

    return 0;
}

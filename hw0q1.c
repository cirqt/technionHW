#include <stdio.h>


int main() {
    char equation[] = "";
    scanf("%s", equation);
    char num1[] = "";
    char ch = equation[0];
    int i = 0;
    int j = 0;
    while (ch != '+' || ch != '-' || ch != '/' || ch != '*') {
        num1[j] += equation[i];
        i += 1;
    }
}
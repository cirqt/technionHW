#include <stdio.h>

int main() {
    int input = 0;
    while (scanf("%d", &input) != EOF) {
        if ((input >= 100 && input <= 999) || (-1*input >= 100 && -1*input <= 999))
            printf("Triple Digit.\n");
        else if (input % 2 == 0 && input > 0)
            printf("Positive Even.\n");
        else if (input % 2 == -1 && input < 0)
            printf("Negative Odd.\n");
        else
            printf("Other.\n");
    }

}
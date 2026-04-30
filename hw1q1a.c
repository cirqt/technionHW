#include <stdio.h>

int main() {
    int input = 0;
    scanf("%d", &input);
    if (input >= 100 && input <= 999)
        printf("Triple Digit.");
    else if (input % 2 == 0 && input > 0)
        printf("Positive Even.");
    else if (input % 2 == -1 && input < 0)
        printf("Negative Odd.");
    else
        printf("Other.");

}
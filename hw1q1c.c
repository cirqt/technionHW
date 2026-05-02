#include <stdio.h>

int main() {
    char c = 'a';
    double k = 0;
    scanf("%lf", &k);
    scanf("%c", &c);
    int roundK = (int)k;
    if (roundK - k == 0) {
        if (c == 'z') {
            c = 'a';
            k--;
        }
        if (c == 'Z') {
            c = 'A';
            k--;
        }
            c = 'A';
        int letter = 0;
        if (c >= 'A' && c <= 'Z') {
            c += 32;
            letter = 1;
        }
        else if (c >= 'a' && c <= 'z') {
            c -= 32;
            letter = 1;

        }
        else
            printf("Not A Letter.");
        if (letter == 1) {
            while (k != 0) {
                k--;
                c++;
                printf("%c",c);
            }
        }
    }
    else
        printf("Wrong Input Type.");
}
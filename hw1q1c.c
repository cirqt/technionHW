#include <stdio.h>

int main() {
    char c = 'a';
    double k = 0;
    scanf("%lf", &k);
    scanf("%c", &c);
    c++;
    int roundK = (int)k;
    if (roundK - k == 0) {
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
                if (c == 'z'+1) {
                    c = 'a';
                }
                else if (c == 'Z'+1) {
                    c = 'A';
                }
                k--;
                printf("%c",c);
                c++;
            }
        }
    }
    else
        printf("Wrong Input Type.");
}
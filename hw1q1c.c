#include <stdio.h>

int main() {
    char c = 'a';
    int k = 0;
    if (scanf("%d %c", &k, &c) == 2) {
        if (c >= 'A' && c <= 'Z') {
            c += 33;
            for (int i = 0; i < k; i++) {
                if (c == 'z'+1)
                    c = 'a';
                printf("%c", c);
                c++;
            }
        }
        else if (c >= 'a' && c < 'z') {
            c -= 33;
            for (int i = 0; i < k; i++) {
                if (c == 'A'-1)
                    c = 'Z';
                printf("%c", c);
                c--;
            }
        }
        else
            printf("Not A Letter.");
    }
    else
        printf("Wrong Input Type.");
}
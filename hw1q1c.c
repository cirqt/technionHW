#include <stdio.h>

int main() {
    char c = 'a';
    int k = 0;
    if (scanf("%d %c", &k, &c) == 2) { //check input type matching
        if (c >= 'A' && c <= 'Z') { //check uppercase
            c += 33;
            for (int i = 0; i < k; i++) { //iterate k times onwards from c
                if (c == 'z'+1) {
                    //if reaches the end go back to a
                    c = 'a';
                }
                printf("%c", c);
                c++;
            }
        } else if (c >= 'a' && c < 'z') { //check lowercase
            c -= 33;
            for (int i = 0; i < k; i++) { //iterate k times backwards from c
                if (c == 'A'-1) {
                    //if reaches the end go back to Z
                    c = 'Z';
                }
                printf("%c", c);
                c--;
            }
        } else {
            printf("Not A Letter.");
        }
    } else {
        printf("Wrong Input Type.");
    }
}
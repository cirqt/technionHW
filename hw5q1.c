
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int mergeAteliers(int a[], int na, int b[], int nb, int out[]) {
    int i = 0, j = 0, k = 0;
    while (i < na || j < nb) {
        int val;
        if (a[i] > b[j] && i < na) {
            val = a[i];
            i++;
        } else if (b[j] > a[i]) {
            val = b[j];
            j++;
        } else {
            val = i >= na ? b[j] : a[i];
            i++;
            j++;
        }
        if (k == 0 || out[k - 1] != val) {
            out[k] = val;
            k++;
        }
    }
    return k;
}

int main() {
    int na;
    scanf("%d", &na);
    int a[1000];
    for (int i = 0; i < na; i++) {
        scanf("%d", &a[i]);
    }
    int nb;
    scanf("%d", &nb);
    int b[1000];
    for (int i = 0; i < nb; i++) {
        scanf("%d", &b[i]);
    }
    int out[2000];
    int len = mergeAteliers(a, na, b, nb, out);
    for (int i = 0; i < len; i++) {
        printf("%d ", out[i]);
    }
    printf("\n");
    return 0;
}

/* HW5 Q2 - The Devil Wears Prada: moving the tower of designer boxes. */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void moveBoxes(int n, char from, char to, char via) {
    if (n == 0) //end case, no boxes do nothing
        return;
    moveBoxes(n-1, from, via, to);
    //assume can move all except last box to via
    printf("%d: %c -> %c\n", n, from, to);
    //print the move of the biggest box to C
    moveBoxes(n-1, via, to, from);
    //back to starting case but without the largest box

}

int main() {
    int n;
    scanf("%d", &n);
    moveBoxes(n, 'A', 'C', 'B');
    return 0;
}
#include <stdio.h>

int main() {
    int n, m = 0;
    int sumOfDigits = 0; //summing up the digits whenever we divide n/10
    scanf("%d", &n);
    scanf("%d", &m);
    int temp = n;
    int digitsOfN = 0;
    while (temp != 0) { //count the number of digits in the original number
        digitsOfN++; //example: n:12345 -> 5
        temp/=10;
    }
    int firstPart = 0;
    int multiplier = 1;
    for (int i = digitsOfN - m; i > 0; i--) { //get the last n.length-m digits of n to remain
        firstPart += n%10 * multiplier; //from n:12345 m:3 -> 5-3 last digits are 45
        multiplier *= 10;
        sumOfDigits += n%10;
        n /= 10;
    }
    int secondPart = 0;
    while (m != 1) { //set up the multiplier such that the number will switch spots as intended
        multiplier *= 10; //such the third digit will be multiplied by 10^x such that it will become the first digit
        m--;
    }
    while (n != 0) { //multiply the digits by the corresponding multiplier to reverse them as intended
        secondPart += n%10 * multiplier; //in the example case, 123 become 32100
        multiplier /= 10;
        sumOfDigits += n%10;
        n /= 10;
    }
    printf("second Part: %d\n", secondPart);
    printf("Reversed: %d, Average: %d",firstPart+secondPart, sumOfDigits/digitsOfN); //add both numbers 32100 + 45 divide the sum of the digits by the number of digits
}

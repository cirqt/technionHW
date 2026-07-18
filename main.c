#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


char* center_of_mass(char* arr);
char* mass_distance(char** wordsS, int lenS);

char** get_all_sub_strings(char* str, int n);

int main() {
    int len;
    // 1. Get length parameter
    if (scanf("%d", &len) != 1) return 0;


    char* arr = (char*)malloc((len + 3) * sizeof(char));
    if (!arr) return 0;

    // 2. Read the array string
    if (scanf(" %[^\n]", arr) != 1) return 0;



    // 3. Evaluate
    char* res = center_of_mass(arr);
    if (res) {
        printf("%s \n", res); // Prints answer
        free(res);
    }

    free(arr);
    return 0;
}


char* center_of_mass(char* arr) {
    int cnt = 0;
    int wordcnt = 1;
    while (arr[cnt] != '\0') {
        if (arr[cnt] == ' ' && arr[cnt+1] <= 'z' && arr[cnt+1] >= 'a') {
            wordcnt++;
        }
        cnt++;
    }
    char** words = (char**) malloc(wordcnt *sizeof(char*));
    int iterate = 0;
    for (int i = 0; i<wordcnt; i++) {
        int letter = 0;
        int lettercount = 0;
        while (arr[iterate+lettercount] != ' ' && arr[iterate+lettercount] != '\0')
            lettercount++;
        char* word = (char*)malloc(lettercount+1*(sizeof(char)));
        while (arr[iterate] != '\0' && arr[iterate] != ' ') {
            word[letter] = arr[iterate];
            iterate++;
            letter++;
        }
        word[lettercount] = '\0';
        iterate++;
        words[i] = word;
    }
    char* result = mass_distance(words, wordcnt);
    for (int i = 0; i< wordcnt; i++) {
        free(words[i]);
    }
    free(words);
    return result;
}

// auxiliary functions for get_all_sub_strings:
int count_num_of_one(int n) {
    int count = 0;
    while (n > 0) {
        count+= n%2;
        n = n/2;
    }
    return count;
}


char* get_sub_string(char* str, int num_of_ones, int mask) {
    char* sub_str, * sub_str_i;
    sub_str_i = sub_str = (char*) malloc(num_of_ones+1);
    while(*str) {
        if(mask%2) {
            *sub_str_i = *str;
            sub_str_i++;
        }
        mask = mask/2;
        str++;
    }
    *sub_str_i = 0;
    return sub_str;
}

int pow_of_2(int n) {
    int p = 1;
    while(n-->0) {
        p*=2;
    }
    return p;
}

char** get_all_sub_strings(char* str, int n) {
    int amount_of_sub_strings = pow_of_2(n);
    char** arr = (char**) malloc(amount_of_sub_strings *sizeof(char*));
    for(int i = 0; i < amount_of_sub_strings; i++) {
        arr[i] = get_sub_string(str,count_num_of_one(i),i);
    }
    return arr;
}

int same_length_two_word_distance(char* wordA, int lenA, char* wordB) {
    int sum = 0;
    for (int i = 0; i<lenA; i++) { //assuming words are the same length
        sum += wordA[i] >= wordB[i] ? wordA[i] - wordB[i] : wordB[i] - wordA[i];
    }
    return sum;
}

int two_word_distance(char* wordA, int lenA, char* wordB, int lenB) {
    int min = 2147483647; //assuming wordA is longer than wordB
    char** substrings = get_all_sub_strings(wordA, lenA);
    for (int i = 0; i<pow_of_2(lenA); i++) {
            char* substring = substrings[i];
            int cnt = 0;
            while (substring[cnt] != '\0')
                cnt++;
        if (cnt == lenB) {
            min = same_length_two_word_distance(substring, cnt, wordB) < min ? same_length_two_word_distance(substring, cnt, wordB) : min;
        }
        free(substring);
    }
    free(substrings);
    return min;
}

int group_to_word_distance(char* wordu, int lenU, char** wordsS, int wordsLen) {
    int max = 0;
    char* substring = "";
    int cnt = 0;
    for (int i = 0; i<wordsLen; i++) {
        substring = wordsS[i];
        int lenA = 0;
        while (substring[lenA] != '\0')
            lenA++;

        int compare = lenU > lenA ? two_word_distance(wordu, lenU, substring, lenA) : two_word_distance(substring, lenA, wordu, lenU);
        max = compare > max ? compare : max;
    }
    return max;
}

char* mass_distance(char** wordsS, int lenS) {
    char* word = (char*)malloc((lenS + 1) * sizeof(char));
    char* candidate = (char*)malloc((lenS + 1) * sizeof(char));
    candidate[0] = '\0';
    for (int i = 0; i < lenS; i++) {
        candidate[i] = 'a';
        candidate[i+1] = '\0';
        word[i+1] = '\0';
        for (int j = 0; j<26; j++) {
            word[i] = 'a' + j;
            int distword = group_to_word_distance(word, i+1, wordsS, lenS);
            int distcand = group_to_word_distance(candidate, i+1, wordsS, lenS);
            if (distword < distcand)
                candidate[i] = 'a' + j;
        }
        word[i] = candidate[i];
    }
    free(word);
    return candidate;
}
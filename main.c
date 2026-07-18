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
    while (arr[cnt] != '\0') { //given string, count number of words
        if (arr[cnt] == ' ' && arr[cnt+1] <= 'z' && arr[cnt+1] >= 'a') {
            wordcnt++;
        }
        cnt++;
    }
    char** words = (char**) malloc(wordcnt *sizeof(char*));
    int iterate = 0;
    for (int i = 0; i<wordcnt; i++) { //for each word find the length
        int letter = 0;
        int lettercount = 0; 
        while (arr[iterate+lettercount] != ' ' && arr[iterate+lettercount] != '\0')
            lettercount++; //find word length
        char* word = (char*)malloc(lettercount+1*(sizeof(char)));
        while (arr[iterate] != '\0' && arr[iterate] != ' ') { //save the word in the 2d array
            word[letter] = arr[iterate];
            iterate++;
            letter++;
        }
        word[lettercount] = '\0';
        if (i < wordcnt-1) iterate++;
        words[i] = word;
    } //send the array to calculate the mass distance
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
        sum += wordA[i] >= wordB[i] ? wordA[i] - wordB[i] : wordB[i] - wordA[i]; //sum the difference
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
        if (cnt == lenB) { //save the minimum dist between the word and the substrings
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
    for (int i = 0; i<wordsLen; i++) {
        substring = wordsS[i];
        int lenA = 0;
        while (substring[lenA] != '\0')
            lenA++;
        //compare the word with the substring according to the given defintion
        int compare = lenU > lenA ? two_word_distance(wordu, lenU, substring, lenA) : two_word_distance(substring, lenA, wordu, lenU);
        max = compare > max ? compare : max;
    }
    return max;
}

char* mass_distance(char** wordsS, int lenS) {
    char* word = (char*)malloc((lenS + 1) * sizeof(char));
    char* candidate = (char*)malloc((lenS + 1) * sizeof(char));

    for (int i = 0; i < lenS; i++) {
        word[i] = 'a'; //initialize the word with 'a's
    }
    word[lenS] = '\0';

    for (int i = 0; i <= lenS; i++) {
        candidate[i] = word[i]; //initialize the candidate the same way
    }
    int minDist = group_to_word_distance(candidate, lenS, wordsS, lenS);
    //calculate initial distance
    bool check = true;
    while (check) {
        int pos = lenS - 1;
        while (pos >= 0 && word[pos] == 'z') {
            word[pos] = 'a'; //if reached z resent and move to next characters
            pos--;
        }
        if (pos < 0) { //break if reached thew start of the word
            check = false;
            continue;
        }
        word[pos]++; //increment the character at lexi order
        int dist = group_to_word_distance(word, lenS, wordsS, lenS); //calculate the distance of the new word
        if (dist < minDist) {
            minDist = dist;
            for (int i = 0; i <= lenS; i++) {// save if better
                candidate[i] = word[i];
            }
        }
    }
    free(word);
    return candidate;
}
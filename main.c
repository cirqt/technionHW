
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* subset_from_mask(int* src, int n, int mask);
bool is_subset(int* a, int sizeA, int* b, int sizeB);
bool is_sum(int* a, int sizeA);
void lexiographic_sort(int* arr, int n);
int  count_num_of_one(int n);
int  pow_of_2(int n);
void free_arr(int** arr_2d, int* size_of_row, int num_of_rows);
void no_sums_sets(int* src, int n, int*** arr_2d, int** size_of_row, int* num_of_rows);

int main() {
    int n;

    // Get the array size
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for the number of elements.\n");
        return 1;
    }

    // Dynamically allocate the source array
    int* src = (int*)malloc(n * sizeof(int));
    if (src == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Get the array elements
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &src[i]) != 1) {
            printf("Invalid input for array elements.\n");
            free(src);
            return 1;
        }
    }
    int** arr_2d = NULL;
    int* size_of_row = NULL;
    int num_of_rows = 0;

    // Call the function
    no_sums_sets(src, n, &arr_2d, &size_of_row, &num_of_rows);
    // Print the results
    for (int i = 0; i < num_of_rows; i++) {

        for (int j = 0; j < size_of_row[i]; j++) {
            printf("%d ", arr_2d[i][j]);
        }
        printf("\n");
    }

    // Free all dynamically allocated memory
    free_arr(arr_2d, size_of_row, num_of_rows);
    free(src);

    return 0;
}
void no_sums_sets(int* src, int n, int*** arr_2d, int** size_of_row, int* num_of_rows){
    int count = 0;
    int* valid_subsets = (int*)malloc(pow_of_2(n) * sizeof(int));
    for (int i = 0; i < pow_of_2(n); i++) {
        bool invalid = false;
        int* subsetA = subset_from_mask(src, n, i);
        //construct the 1d array of valid subsets using binary representation
        //iterate each binary representation and its corresponding subset
        for (int j = 0; j < pow_of_2(n); j++) {
            if (i != j) {
                int* subsetB = subset_from_mask(src, n, j);
                if (!is_sum(subsetA, count_num_of_one(i))) {
                    invalid = true;//exclude subsets that are not sum-free
                }
                if (is_subset(subsetA, count_num_of_one(i), subsetB, count_num_of_one(j)) && is_sum(subsetB, count_num_of_one(j))) {
                    invalid = true;//exclude subsets that are subsets of other sum-free sets
                }
                free(subsetB);
            }
        }
        free(subsetA);
        if (!invalid) {
            valid_subsets[count] = i;
            count++; //count for length of subset array
        }

    }
    *num_of_rows = count;
    *size_of_row = (int*)malloc(count * sizeof(int));
    *arr_2d = (int**)malloc(count * sizeof(int*));
    lexiographic_sort(valid_subsets, count);//sort
    for (int i = 0; i < count; i++) {
        (*arr_2d)[i] = subset_from_mask(src, n, valid_subsets[i]);
        (*size_of_row)[i] = count_num_of_one(valid_subsets[i]);
    }
    free(valid_subsets);

}
int* subset_from_mask(int* src, int n, int mask) {
    int* subset = (int*)malloc(count_num_of_one(mask) * sizeof(int));
    int cnt = 0; //create the array from the mask
    for (int i = 0; i < n; i++) { //if bit is 0 exclude, if bit is 1 include
        if (mask % 2 == 1) {
            subset[cnt] = src[i];
            cnt++;
        }
        mask /= 2;
    }
    return subset;
}
bool is_subset(int* subsetA, int sizeA, int* subsetB, int sizeB) {
    for (int i = 0; i < sizeA; i++) { //check if every element in subsetA is in subsetB
        bool found = false;
        for (int j = 0; j < sizeB; j++) {
            if (subsetA[i] == subsetB[j]) {
                found = true;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
bool is_sum(int* subsetA, int sizeA) { //check if array is sum-free
    for (int i = 0; i < sizeA; i++) {
        for (int j = 0; j < sizeA; j++) {
            if (i != j) { 
                for (int k = 0; k < sizeA; k++) { //compare two distinct elements with third element
                    if (subsetA[i] + subsetA[j] == subsetA[k] && k != i && k != j) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
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

int pow_of_2(int n) { //function to calculate 2^n
    int p = 1;
    while(n-->0) {
        p*=2;
    }
    return p;
}

void free_arr(int** arr_2d, int* size_of_row, int num_of_rows) { //free memory for 2d array 
    for (int i = 0; i < num_of_rows; i++) { //and each array in it
        free(arr_2d[i]); //and size of row array
    }
    free(arr_2d);
    free(size_of_row);
}
void lexiographic_sort(int* arr, int n) { //sort lexiographically the array 
    int a = 0; //of binary representations of the subsets of the final array
    int b = 1;
    bool done = false;
    while (done == false) {
        if (arr[a] > arr[b]) { //if next element is smaller, swap
            int temp = arr[a];
            arr[a] = arr[b];
            arr[b] = temp;
            a = 0;
            b = 1;
        }
        else {
            a++;
            b++;
        }
        if (b == n) {
            done = true;
        }
    }
}
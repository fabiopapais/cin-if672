#include <stdio.h>

// assumes ascending ordered array
int binary_search(int* array, int array_size, int key) { // "bottom-up" approach
    int l = 0; int r = array_size - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (array[m] == key) {
            return m;
        } else if (array[m] > key) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}

int main() {
    int array_size = 0; scanf("%d", &array_size);

    // reads array and key
    int* array_to_search = new int[array_size];
    for (int i = 0; i < array_size; i++) scanf("%d", &array_to_search[i]);
    int key = 0; scanf("%d", &key);

    // uses algorithm
    int result = binary_search(array_to_search, array_size, key);

    // prints value found
    printf("%d\n", result);

    delete array_to_search;
    return 0;
}
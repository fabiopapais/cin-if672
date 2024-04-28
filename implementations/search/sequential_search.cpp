#include <stdio.h>

int sequential_search(int* array, int array_size, int key) {
    int i = 0;
    while (i < array_size && array[i] != key) {
        i++;
    }
    if (i < array_size) {
        return i;
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
    int result = sequential_search(array_to_search, array_size, key);

    // prints value found
    printf("%d\n", result);

    delete array_to_search;
    return 0;
}
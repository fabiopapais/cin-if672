#include <stdio.h>

void bubble_sort(int* array, int size) {
    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                // swap
                array[j] = array[j + 1]; array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int array_size = 0; scanf("%d", &array_size);

    // Reads array
    int* unsorted_array = new int[array_size];
    for(int i=0; i<array_size; i++) scanf("%d", &unsorted_array[i]);

    // Uses algorithm
    bubble_sort(unsorted_array, array_size);

    // Prints array
    for(int i=0; i<array_size; i++) printf("%d ", unsorted_array[i]);
    printf("\n");

    delete unsorted_array;
    return 0;
}
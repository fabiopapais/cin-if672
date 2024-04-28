#include <stdio.h>

void insertion_sort(int* array, int size) {
    for (int i = 1; i < size; i++) {
        int current_element = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > current_element) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = current_element;
    }
}

int main() {
    int array_size = 0; scanf("%d", &array_size);

    int* unsorted_array = new int[array_size];
    for(int i=0; i<array_size; i++) scanf("%d", &unsorted_array[i]);

    insertion_sort(unsorted_array, array_size);

    for(int i=0; i<array_size; i++) printf("%d ", unsorted_array[i]);
    printf("\n");

    delete unsorted_array;
    return 0;
}
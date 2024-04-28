#include <stdio.h>

int selection_sort(int* array, int size) {
    for (int i=0; i < size; i++) {
        int min = array[i];
        for (int j=i + 1; j < size; j++) {
            if (array[j] < min){
                min = array[j];
            }
        int temp = array[i];
        array[i] = array[j]; array[j] = temp;
        }
    }
    return 0;
}

int main() {
    int array_size = 0; scanf("%d", &array_size);

    int* unsorted_array = new int[array_size];
    for(int i=0; i<array_size; i++) scanf("%d", &unsorted_array[i]);

    selection_sort(unsorted_array, array_size);

    for(int i=0; i<array_size; i++) printf("%d ", unsorted_array[i]);
    printf("\n");

    delete unsorted_array;
    return 0;
}
#include <stdio.h>

void merge(int* array, int l, int r) {
    // copy array
    int* temp_array = new int[r + 1];
    for (int i = l; i <= r; i++) temp_array[i] = array[i];

    int m = (l + r) / 2;
    int i1 = l; int i2 = m + 1;

    for (int i = l; i <= r; i++) {
        if (i1 == m + 1) { // if i1 reaches subarray end
            array[i] = temp_array[i2++];
        } else if (i2 > r) { // if i2 reaches subarray end
            array[i] = temp_array[i1++];
        } else if (temp_array[i1] <= temp_array[i2]) {
            array[i] = temp_array[i1++];
        } else {
            array[i] = temp_array[i2++];
        }
    }
    delete temp_array;
}

void merge_sort(int* array, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort(array, l, m);
        merge_sort(array, m + 1, r);
        merge(array, l, r);
    }
}

int main() {
    int array_size = 0; scanf("%d", &array_size);

    // Reads array
    int* unsorted_array = new int[array_size];
    for(int i=0; i<array_size; i++) scanf("%d", &unsorted_array[i]);

    // Uses algorithm
    merge_sort(unsorted_array, 0, array_size - 1);

    // Prints array
    for(int i=0; i<array_size; i++) printf("%d ", unsorted_array[i]);
    printf("\n");

    delete unsorted_array;
    return 0;
}
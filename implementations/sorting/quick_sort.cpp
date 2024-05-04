#include <stdio.h>

// swaps values in specified adresseses
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b; *b = temp;
}

int hoare_partition(int* array, int l, int r) {
    int pivot = array[l]; // simple pivot selection
    int i = l; int j = r + 1; 

    do {
        do {
            i++;
        } while (!(array[i] >= pivot || i >= r));
        do {
            j--;
        } while (!(array[j] <= pivot));
        swap(&array[i], &array[j]);
    } while (!(i >= j)); // "until"
    // There's a last case when i >= j (pointers cross)
    // so we need to undo the last swap made by this case
    swap(&array[i], &array[j]);
    // Change our initial pivot with it's final position
    swap(&array[l], &array[j]); 
    return j;
}

void quicksort(int* array, int l, int r) {
    if (l < r) {
        int s = hoare_partition(array, l, r);
        quicksort(array, l, s-1);
        quicksort(array, s+1, r);
    }
}

int main() {
    int array_size = 0; scanf("%d", &array_size);

    // reads array
    int* unsorted_array = new int[array_size];
    for (int i = 0; i < array_size; i++) scanf("%d", &unsorted_array[i]);

    // uses algorithm
    quicksort(unsorted_array, 0, array_size - 1);

    // prints array
    for (int i = 0; i < array_size; i++) printf("%d ", unsorted_array[i]);
    printf("\n");

    delete[] unsorted_array;
    return 0;
}
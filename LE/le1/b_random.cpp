#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b; *b = temp;
}

int hoare_partition(int* array, int l, int r) {
    int pivot = array[l];
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
    swap(&array[i], &array[j]);
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
    unsigned int n, k; scanf("%d %d", &n, &k);
    
    int* array = new int[n]; 
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    quicksort(array, 0, n - 1);

    unsigned int pairs = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (array[j] - array[i] > k) {
                break;
            } else if (array[j] - array[i] == k) {
                pairs++;
            }
        }
    }
    delete[] array;

    printf("%d", pairs);
    return 0;
}
#include <stdio.h>

void swap(unsigned int* a, unsigned int* b) {
    unsigned int temp = *a;
    *a = *b; *b = temp;
}

int hoare_partition(unsigned int* array, int l, int r) {
    unsigned int pivot = array[l];
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

void quicksort(unsigned int* array, int l, int r) {
    if (l < r) {
        int s = hoare_partition(array, l, r);
        quicksort(array, l, s-1);
        quicksort(array, s+1, r);
    }
}

long long sum_array(unsigned int* array, int array_size) {
    long long sum = 0;
    for (int i = 0; i < array_size; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    int chocolates_quantity = 0; scanf("%d", &chocolates_quantity);
    unsigned int* chocolates_prices = new unsigned int[chocolates_quantity];

    for (int i = 0; i < chocolates_quantity; i++) scanf("%d", &chocolates_prices[i]);
    quicksort(chocolates_prices, 0, chocolates_quantity - 1);

    int coupons_quantity = 0; scanf("%d", &coupons_quantity);
    long long full_price = sum_array(chocolates_prices, chocolates_quantity);
    for (int i = 0; i < coupons_quantity; i++) {
        int current_coupon = 0; scanf("%d", &current_coupon);
        int discard_index =  chocolates_quantity - current_coupon;
        long long new_price = full_price - chocolates_prices[discard_index]; 

        printf("%lld\n", new_price);
    }

    delete[] chocolates_prices;
}
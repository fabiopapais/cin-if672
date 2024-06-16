#include <stdlib.h>
#include <iostream>
using namespace std;

#define EMPTY_ELEMENT 100001 // problem especific

// min-heap int implementation 
class Heap {
public:
    Heap(int size, int* starting_array): size(size) {
        max_size = size;
        array = new int[max_size + 1];
        for (int i = 1; i <= max_size; i++) { // populates array
            array[i] = starting_array[i - 1];
        }
        bottom_up(); // heapifies
    }

    int min_delete() {
        // removes min element
        int removed_element = array[1];
        array[1] = array[size];
        array[size] = EMPTY_ELEMENT;
        // decrease heap size
        size--;
        // heapify
        bottom_up();
        return removed_element;
    }

    void clear() { delete[] array; }

    void vanilla_print() {
        for (int i = 1; i <= size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    void pretty_print() { pretty_printhelp(1, 0); }

    int size;

private:

    // min-heap bottom-up heapifier
    void bottom_up() {
        for (int i = (int) max_size / 2; i >= 1; i--) {
            int k = i; int v = array[k];
            bool heap = false;
            while (!heap && 2*k <= max_size) {
                int j = 2 * k;
                if (j < max_size) {
                    if (array[j] > array[j+1]) {
                        j++; // moves to lowest child
                    }
                }
                if (v < array[j]) { // elements in order
                    heap = true;
                }
                else {
                    array[k] = array[j];
                    k = j;
                }
            }
            array[k] = v;
        }
    }

    void pretty_printhelp(int index, int level) {
        if (index > max_size) return;
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << array[index] << endl;
        pretty_printhelp(index * 2, level + 1);
        pretty_printhelp((index * 2) + 1, level + 1);
    }

    int max_size;
    int* array;
};

int main() {
    int c; cin >> c;
    for (int i = 0; i < c; i++) {
        int size; cin >> size;
        int* starting_array = new int[size];
        for (int j = 0; j < size; j++) {
            int current; cin >> current;
            starting_array[j] = current;
        }

        Heap heap = Heap(size, starting_array);
        
        int* sorted_array = new int[size];
        // heapsort
        for (int j = 0; j < size; j++) {
            heap.vanilla_print();
            sorted_array[j] = heap.min_delete(); 
        }

        // array
        for (int j = 0; j < size; j++) {
            cout << sorted_array[j] << " ";
        }
        cout << endl; cout << endl;

        heap.clear();
        delete[] starting_array;
        delete[] sorted_array;
    }
    return 0;
}
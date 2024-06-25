#include <iostream>
using namespace std;

// min-heap implementation with int key values
class Heap {
public:
    // bottom up heap constructor
    // assumes elements[] is 1-indexed
    Heap(int size, int* elements): size(size) {
        array = new int[size + 1];
        array = elements;
        bottom_up(); // heapify
    }

    // returns lower element
    int min_delete() {
        int removed_element = array[1];
        array[1] = array[size];
        size--;
        index_bottom_up(1); // heapify
        return removed_element;
    }

    void add(int key) {
        array[size + 1] = key;
        size++;
        index_bottom_up(size);
    }

    void clear() { delete[] array; }

    void pretty_print() { pretty_printhelp(1, 0); }

    int size;
private:
    void bottom_up() { // heapifies whole tree
        for (int i = (int) size / 2; i > 0; i--) {
            int k = i;
            int v = array[k];
            bool heap = false;
            while (!heap && 2*k <= size) {
                int j = 2*k;
                if (j < size) {
                    if (array[j] > array[j+1]) j++; // gets lowest child
                }
                if (v < array[j]) { // nodes in order
                    heap = true;
                } else {
                    array[k] = array[j];
                    k = j;
                }
            }
            array[k] = v;
        }
    }

    void index_bottom_up(int i) {
        int k = i;
        int v = array[k];
        bool heap = false;
        while (!heap && 2*k <= size) {
            int j = 2*k;
            if (j < size) {
                if (array[j] > array[j+1]) j++; // gets lowest child
            }
            if (v < array[j]) { // nodes in order
                heap = true;
            } else {
                array[k] = array[j];
                k = j;
            }
        }
        array[k] = v;
    }

    void pretty_printhelp(int index, int level) {
        if (index > size) return;
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << array[index] << endl;
        pretty_printhelp(index * 2, level + 1);
        pretty_printhelp((index * 2) + 1, level + 1);
    }

    int* array;
};

int main() {
    while (true) { // use while true
        int size; cin >> size; if (size == 0) break;
        int* elements = new int[size + 1]; elements[0] = 0;
        for (int i = 1; i < size + 1; i++) cin >> elements[i];

        Heap heap = Heap(size, elements);

        int total_cost = 0;
        while (heap.size > 1) {
            int a = heap.min_delete();
            int b = heap.min_delete();
            total_cost += a + b;
            heap.add(a + b);
        }

        cout << total_cost << endl;;

        heap.clear();
    }
    return 0;
}
// 3
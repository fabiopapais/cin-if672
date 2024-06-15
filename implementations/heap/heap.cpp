#include <stdlib.h>
#include <iostream>
using namespace std;

// defines element representing empty node
#define EMPTY_ELEMENT -1;

// max-heap with int key values
class Heap {
public:
    // default empty array constructor
    Heap(int max_size): max_size(max_size) {
        size = 0;
        array = new int[max_size + 1];
    }
    // bottom up constructor from starting elements
    Heap(int max_size, int starting_size, int* starting_elements): max_size(max_size) {
        size = starting_size;
        array = new int[max_size + 1];

        // fills array with starting elements
        // if it is always started with max_size elements, 
        // use a single pointer attribution 
        for (int i = 1; i <= max_size; i++) {
            if (i <= starting_size) {
                array[i] = starting_elements[i - 1];
            } else {
                array[i] = EMPTY_ELEMENT;
            }
        }
        bottom_up(); // heapify
    }

    // adds value and finds correct index with top_down
    void add(int key) {
        if (size >= max_size) return;
        array[size + 1] = key;
        size++;
        top_down(size + 1); // finds correct place to new added item
    }

    // deletes root value and heapifies with bottom_up
    void max_delete() {
        if (size <= 0) return;
        // exchanging root with last key and deleting root (max)
        array[1] = array[size];
        array[size] = EMPTY_ELEMENT;
        // decrease size by 1
        size--;
        // heapify whole tree (use index to optimize)
        bottom_up();
    }

    // prints all elements in a binary tree representation
    void pretty_print() {
        cout << "size: " << size << endl;
        cout << "max_size: " << max_size << endl;
        pretty_printhelp(1, 0);
    }
    // prints all elements in the array sequentially
    void vanilla_print() {
        for (int i = 0; i <= max_size; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    int size;
private:
    void bottom_up() { // Note that it heapifies the whole tree
        for (int i = (int) max_size / 2; i > 0; i--) {
            int k = i; // current position of the i-th internal node
            int v = array[k]; // value of the i-th internal node
            bool heap = false;
            while (!heap && 2* k <= max_size) {
                int j = 2 * k;
                if (j < max_size) {
                    if (array[j] < array[j+1]) { j++; } // goes to biggest child, change it here to make max and minimum heaps
                }
                if (v >= array[j]) { // nodes in order, change it here to make max and minimum heaps 
                    heap = true;
                } else { // nodes not in order
                    array[k] = array[j];
                    k = j;
                }
            }
            array[k] = v;
        }
    }

    void top_down(int index) {
        if (index <= 1) return;
        if (array[(int) index / 2] >= array[index]) { // nodes in order, change it here to make max and minimum heaps 
            return;
        } else {
            int temp = array[(int) index / 2];
            array[(int) index / 2] = array[index];
            array[index] = temp;
            top_down((int) index / 2);
        }
    }

    void pretty_printhelp(int index, int level) {
        if (index > max_size) return;
        for (int i = 0; i < level; i++) {
            cout << " ";
        }
        cout << array[index] << endl;
        pretty_printhelp(index * 2, level + 1);
        pretty_printhelp((index * 2) + 1, level + 1);
    }

    int max_size;
    int* array;
};

int main() {
    int starting_elements[] = {2, 9, 7, 6, 5, 8, 10};
    Heap heap = Heap(7, 7, starting_elements);

    heap.pretty_print();
    heap.max_delete();
    heap.pretty_print();
    heap.max_delete();
    heap.pretty_print();
    heap.max_delete();
    heap.pretty_print();
    heap.max_delete();
    heap.add(9);
    heap.pretty_print();
    // heap.max_delete();
    // heap.pretty_print();
    // heap.max_delete();
    // heap.pretty_print();
    // heap.max_delete();
    // heap.pretty_print();
    heap.vanilla_print();

    return 0;
}
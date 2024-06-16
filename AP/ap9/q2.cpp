#include <stdlib.h>
#include <iostream>
using namespace std;

#define EMPTY_ELEMENT '\0'

// max-heap char implementation
class Heap {
public:
    Heap(int max_size): max_size(max_size), size(0) {
        array = new char[max_size + 1];
        fill(array, array + max_size + 1, EMPTY_ELEMENT); // optional
    }

    char add(char key) {
        if (size >= max_size) return EMPTY_ELEMENT;
        array[size + 1] = key;
        top_down(size + 1);
        size++;
        return key;
    }

    char max_remove() {
        if (size <= 0) return EMPTY_ELEMENT;
        // exchanging root with last key and deleting root (max)
        char temp = array[1];
        array[1] = array[size];
        array[size] = EMPTY_ELEMENT;
        // decrease size by 1
        size--;
        // heapify tree
        bottom_up();
        return temp;
    }

    char find_max() {
        if (size <= 0) return EMPTY_ELEMENT;
        return array[1];
    }

    int size;

private:

    void top_down(int index) {
        if (index <= 1) return;
        int parent_index = (int) index / 2;
        // cout << parent_index << ":" << array[parent_index] << endl;
        if (array[parent_index] >= array[index]) {
            return;
        } else {
            char temp = array[parent_index];
            array[parent_index] = array[index];
            array[index] = temp;
            top_down(parent_index);
        }
    }

    void bottom_up() {
        for (int i = (int) max_size / 2; i > 0; i--) {
            int k = i; // current position of the i-th internal node
            char v = array[k]; // value of the i-th internal node
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

    int max_size;
    char* array;
};

int main() {
    int size; int commands;
    cin >> size; cin >> commands;

    Heap heap = Heap(size);
    for (int i = 0; i < commands; i++) {
        string command; cin >> command;
        if (command == "remove") {
            char removed = heap.max_remove();
            if (removed == EMPTY_ELEMENT) {
                cout << "Heap vazia." << endl;
            }
        } else if (command == "max") {
            char top = heap.find_max();
            if (top == EMPTY_ELEMENT) {
                cout << "Não há elemento no topo." << endl;
            } else {
                cout << top << endl;
            }
        } else if (command == "insert") {
            char element; cin >> element;
            char added = heap.add(element);
            if (added == EMPTY_ELEMENT) {
                cout << "Tamanho máximo atingido!" << endl;
            }
        }

    }

    return 0;
}
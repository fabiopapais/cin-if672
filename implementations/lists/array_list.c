#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int maxSize;
    int listSize;
    int curr;
    int* listArray;
} List;

// moves cursor to start
void move_to_start(List* l) { l->curr = 0; }
// moves cursor to end
void move_to_end(List* l) { l->curr = l->listSize; }
// moves cursor to previous position
void prev(List* l) { if (l->curr != 0) { l->curr--; } }
// moves cursor to next position
void next(List* l) { if (l->curr < l->listSize) { l->curr++; } }

// returns a new array list pointer with desired size
List* create_list(int size) {
    List* l = (List*) malloc(sizeof(List));
    l->maxSize = size;
    l->listSize = l->curr = 0;
    l->listArray = (int*) malloc(size * sizeof(int));
    return l;
};

// Clears array, setting all to 0 if trueClear = 1
void clear_list(List* l, int trueClear) {
    if (trueClear == 1) {
        for (int i = 0; i < l->listSize; i++) {
            l->listArray[i] = 0;
        }
    }
    l->listSize = 0;
    l->curr = 0;
}

// inserts element at current cursor position
// returns -1 if error is found
int insert_element(List* l, int it) {
    // checks if list is not full:
    if (l->listSize >= l->maxSize) return -1;
    int i = l->listSize;
    // iteratively shifts elements right (starting from right)
    while (i > l->curr) {
        l->listArray[i] = l->listArray[i - 1];
        i--;
    }
    l->listArray[l->curr] = it;
    l->listSize++;
    return 0;
}

// appends element at end of array
int append_element(List* l, int it) {
    move_to_end(l);
    return insert_element(l, it);
}

// removes element at current cursor position
// returns -1 if error is found
int remove_element(List* l) {
    // checks full array or cursor out of bounds
    if (l->curr < 0 || l->curr >= l->listSize) { return -1; } 
    int i = l->curr;
    // iteratively shifts elements left (starting from curr)
    while (i < l->listSize - 1) {
        l->listArray[i] = l->listArray[i + 1];
        i++;
    }
    l->listSize--;
    return 0;
}

// deallocates memory taken by a List
void free_list(List* l) {
    if (l != NULL) {
        // free array
        if (l->listArray != NULL) {
            free(l->listArray);
            l->listArray = NULL;
        }
        free(l);
    }
}


int main() {
    int list_size = 0; scanf("%d", &list_size);

    // Adding elements
    List* new_list = create_list(list_size);
    for (int i = 0; i < list_size; i++) {
        int number; scanf("%d", &number);
        append_element(new_list, number);
    }

    // Just testing functions
    move_to_end(new_list);
    prev(new_list);
    prev(new_list);
    prev(new_list);
    next(new_list);
    int error_code = remove_element(new_list);
    if (error_code == -1) { printf("Element could not be removed"); }

    // Print elements
    move_to_start(new_list);
    for (int i = 0; i < new_list->listSize; i++) {
        printf("%d", new_list->listArray[new_list->curr]);
        next(new_list);
    }

    clear_list(new_list, 0);
    // Nothing happens (list is cleared)
    for (int i = 0; i < new_list->listSize; i++) {
        printf("%d", new_list->listArray[new_list->curr]);
        next(new_list);
    }

    free_list(new_list);

    return 0;
}
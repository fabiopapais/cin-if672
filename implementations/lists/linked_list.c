#include <stdio.h>
#include <stdlib.h> 

typedef struct link {
    int element; // actual element in node
    struct link* next; // pointer to next node
} Link;

// creates new Link pointing to nextval
Link* create_link(int it, Link* nextval, int first_node) {
    Link* new_link = (Link*) malloc(sizeof(Link));
    if (first_node == 0) new_link->element = it;
    new_link->next = nextval;
    return new_link;
}

typedef struct list {
    Link* head; // head node pointer
    Link* tail; // tail node pointer
    Link* curr; // cursor (current) node pointer
    int cnt; // list size
} List;

// creates new linked-list
List* create_list() {
    List* new_list = (List*) malloc(sizeof(List));
    // Assigning same adresseses to curr, tail and head 
    new_list->curr = new_list->tail = new_list->head = create_link(0, NULL, 1);
    new_list->cnt = 0;
    return new_list;
}

// moves cursor to first element (head element)
void move_to_start(List* l) { l->curr = l->head; }

// moves cursor to previous element
void prev(List* l) {
    if (l->curr == l->head) return;
    Link* temp = l->head;
    while (temp->next != l->curr) { // iterates through linked-list
        temp = temp->next;
    }
    l->curr = temp;
}

// moves cursor to next element
void next(List* l) { if (l->curr != l->tail) l->curr = l->curr->next; }

// inserts element at the current cursor position
void insert_element(List* l, int it) {
    // creates link pointing to current next node and the make it the current next node
    l->curr->next = create_link(it, l->curr->next, 0);
    // updates tail address if cursor was before last element (tail element)
    if (l->tail == l->curr) { l->tail = l->curr->next; }
    l->cnt++;
}

// removes element at current cursor position
void remove_element(List* l) {
    if (l->curr->next == NULL) return;
    if (l->curr->next == l->tail) {
        l->curr = l->tail; // if curr is the second-last // CAUTION
    }
    l->curr->next = l->curr->next->next;
    l->cnt--;
}

// Clears linked_list, setting all to 0 if trueClear == 1
void clear_list(List* l, int trueClear) {
    if (trueClear == 1) {
        while (l->curr != l->tail) { // iterates through linked-list
            l->curr->next->element = 0;
            next(l);
        }
    }
    l->curr = l->tail = l->head;
}

// Deallocates linked-list and nodes memory
void free_list(List* l) {
    if (l != NULL) {
        move_to_start(l);
        Link* next;
        while (l->curr != NULL) { // iterates through linked-list
            next = l->curr->next;
            free(l->curr);
            l->curr = next;
        }
        // free(next); not necessary since last node is NULL
        l->head = l->tail = NULL;
        free(l);
    }
}

int main() {
    int list_size = 0; scanf("%d", &list_size);

    // Adding elements
    List* new_list = create_list();
    for (int i = 0; i < list_size; i++) {
        int number; scanf("%d", &number);
        insert_element(new_list, number);
        next(new_list);
    }

    // Just testing functions

    insert_element(new_list, 6);
    printf("current element: %d\n", new_list->curr->element);
    prev(new_list);
    next(new_list);
    prev(new_list);
    prev(new_list);
    prev(new_list);
    next(new_list);
    printf("current element: %d\n", new_list->curr->element);
    remove_element(new_list); 

    // Print elements
    move_to_start(new_list);
    while (new_list->curr != new_list->tail) { // iterates through linked-list
        printf("%d ", new_list->curr->next->element);
        next(new_list);
    }

    clear_list(new_list, 1);
    move_to_start(new_list);
    // Nothing happens (list is cleared)
    while (new_list->curr != new_list->tail) {
        printf("%d", new_list->curr->next->element);
        next(new_list);
    }

    free_list(new_list);

    return 0;
}
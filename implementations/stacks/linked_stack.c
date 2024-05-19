#include <stdio.h>
#include <stdlib.h> 

typedef struct link {
    int element; // actual element in node
    struct link* next; // pointer to next node
} Link;

// creates new Link pointing to nextval
Link* create_link(int it, Link* nextval) {
    Link* new_link = (Link*) malloc(sizeof(Link));
    new_link->element = it;
    new_link->next = nextval;
    return new_link;
}

typedef struct stack {
    Link* top; // reference to the first element
    int size; // number of elements
} Stack;

// creates new stack without header node
Stack* create_stack() {
    Stack* new_stack = (Stack*) malloc(sizeof(Stack));
    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}

void push(Stack* s, int it) {
    s->top = create_link(it, s->top);
    s->size++;
}

void pop(Stack* s) {
    if (s->top == NULL) return;
    Link* last_adress = s->top;
    s->top = s->top->next;
    free(last_adress);
    s->size--;
}

void free_stack(Stack* s) {
    while(s->top != NULL) {
        Link* temp_top = s->top;
        s->top = s->top->next;
        free(temp_top);
    }
    free(s);
}

int main() {
    int stack_size = 0; scanf("%d", &stack_size);

    // Adding elements
    Stack* new_stack = create_stack();
    for (int i = 0; i < stack_size; i++) {
        int number; scanf("%d", &number);
        push(new_stack, number);
    }

    // Testing functions

    printf("%d\n", new_stack->top->element);
    push(new_stack, 1000);
    pop(new_stack);

    push(new_stack, 3000);
    printf("%d\n", new_stack->top->element);

    free_stack(new_stack);
}
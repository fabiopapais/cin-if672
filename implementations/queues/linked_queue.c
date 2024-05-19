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

typedef struct queue {
    Link* front;
    Link* rear;
    int size;
} Queue;

// creates queue with a header node
Queue* create_queue() {
    Queue* new_queue = (Queue*) malloc(sizeof(Queue));
    new_queue->front = new_queue->rear = create_link(0, NULL, 1);
    new_queue->size = 0;
    return new_queue;
}

// appends new node at rear;
void enqueue(Queue* q, int it) {
    q->rear->next = create_link(it, NULL, 0);
    q->rear = q->rear->next;
    q->size++;
}

// removes node at front
void dequeue(Queue* q) {
    if (q->size == 0) return;
    Link* temp_next = q->front->next;
    q->front->next = q->front->next->next;
    if (q->front->next == NULL) q->rear = q->front;
    free(temp_next);
    q->size--;
}

// frees and clears all the queue
void free_queue(Queue* q) {
    while (q->size > 0) {
        dequeue(q);
    }
    free(q);
}

int main() {
    int queue_size = 0; scanf("%d", &queue_size);

    // Adding elements
    Queue* new_queue = create_queue();
    for (int i = 0; i < queue_size; i++) {
        int number; scanf("%d", &number);
        enqueue(new_queue, number);
    }

    // Testing functions
    printf("%d\n", new_queue->front->next->element);
    printf("%d\n", new_queue->rear->element);
    enqueue(new_queue, 1000);
    dequeue(new_queue);
    printf("%d\n", new_queue->front->next->element);
    printf("%d\n", new_queue->rear->element);
    enqueue(new_queue, 2000);
    dequeue(new_queue);
    printf("%d\n", new_queue->front->next->element);
    printf("%d\n", new_queue->rear->element);

    free_queue(new_queue);

    return 0;
}
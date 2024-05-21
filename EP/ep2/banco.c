#include <stdio.h>
#include <stdlib.h>

typedef struct link {
    int element;
    struct link* next; // CAUTION
} Link;

Link* create_link(int it, Link* nextval, int is_first_node) {
    Link* n = (Link*) malloc(sizeof(Link));
    if (is_first_node == 0) n->element = it;
    n->next = nextval;
    return n;
}

typedef struct queue {
    Link* front;
    Link* rear;
    long int size;
} Queue;

Queue* create_queue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->front = q->rear = create_link(0, NULL, 1);
    q->size = 0;
    return q;
}

void enqueue(Queue* q, long int it) {
    q->rear->next = create_link(it, NULL, 0);
    q->rear = q->rear->next;
    q->size++;
}

int dequeue(Queue* q) {
    if (q->size == 0) return -1;
    Link* temp = q->front->next;
    q->front->next = q->front->next->next;
    if (q->front->next == NULL) q->rear = q->front;
    q->size--;
    free(temp);
    return 0;
}

int is_end(char* str) {
    char end[3] = { 'e', 'n', 'd' };
    for (int i = 0; i < 3; i++) {
        if (str[i] != end[i]) {
            return 0; 
        }
    }
    return 1;
}
int is_add(char* str) {
    char add[3] = { 'a', 'd', 'd' };
    for (int i = 0; i < 3; i++) {
        if (str[i] != add[i]) {
            return 0; 
        }
    }
    return 1;
}
int is_solve(char* str) {
    char solve[5] = { 's', 'o', 'l', 'v', 'e' };
    for (int i = 0; i < 5; i++) {
        if (str[i] != solve[i]) {
            return 0; 
        }
    }
    return 1;
}
int is_print(char* str) {
    char print[5] = { 'p', 'r', 'i', 'n', 't' };
    for (int i = 0; i < 5; i++) {
        if (str[i] != print[i]) {
            return 0; 
        }
    }
    return 1;
}
int is_stats(char* str) {
    char stats[5] = { 's', 't', 'a', 't', 's' };
    for (int i = 0; i < 5; i++) {
        if (str[i] != stats[i]) {
            return 0; 
        }
    }
    return 1;
}

int main() {
    char* str = malloc(sizeof(char) * 7);
    int number = 0;

    Queue* pendent_questions = create_queue();
    long int solved_questions = 0;

    while (1) {
        scanf("%s", str);
        if (is_end(str)) break;

        if (is_add(str)) {
            scanf("%d", &number);
            enqueue(pendent_questions, number);
        } else if (is_solve(str)) {
            int result = dequeue(pendent_questions);
            if (result != -1) solved_questions++;
        } else if (is_print(str)) {
            if (pendent_questions->size == 0) printf("x\n");
            else {
                // Iterate queue from front to rear
                Link* temp = pendent_questions->front;
                while (temp->next != pendent_questions->rear) {
                    printf("%d", temp->next->element);
                    printf(" ");
                    temp = temp->next;
                }
                printf("%d", pendent_questions->rear->element);
                printf("\n");
            }
        } if (is_stats(str)) {
            printf("%ld %ld\n", solved_questions, pendent_questions->size);
        }
    }

    return 0;
}
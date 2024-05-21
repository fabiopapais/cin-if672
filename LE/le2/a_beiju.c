#include <stdio.h>
#include <stdlib.h> 

typedef struct link {
    char element;
    struct link* next;
} Link;

Link* create_link(char it, Link* nextval, int first_node) {
    Link* new_link = (Link*) malloc(sizeof(Link));
    if (first_node == 0) new_link->element = it;
    new_link->next = nextval;
    return new_link;
}

typedef struct list {
    Link* head;
    Link* tail;
    Link* curr;
    int cnt;
} List;

List* create_list() {
    List* new_list = (List*) malloc(sizeof(List));
    new_list->curr = new_list->tail = new_list->head = create_link('0', NULL, 1);
    new_list->cnt = 0;
    return new_list;
}

void move_to_start(List* l) { l->curr = l->head; }
void move_to_end(List* l) { l->curr = l->tail; }

void next(List* l) { if (l->curr != l->tail) l->curr = l->curr->next; }

void insert_element(List* l, char it) {
    l->curr->next = create_link(it, l->curr->next, 0);
    if (l->tail == l->curr) { l->tail = l->curr->next; }
    l->cnt++;
}

void free_list(List* l) {
    if (l != NULL) {
        move_to_start(l);
        Link* next;
        while (l->curr != NULL) {
            next = l->curr->next;
            free(l->curr);
            l->curr = next;
        }
        l->head = l->tail = NULL;
        free(l);
    }
}

int main() {
    int read_char = 0;
    List* text = create_list();
    int curr_mode = 0;
    while ((read_char = getchar()) != EOF) {
        char curr_char = (char) read_char;
        if (read_char == '\n') {
            move_to_start(text);
            next(text);
            Link* next;
            while (text->curr != NULL) {
                next = text->curr->next;
                printf("%c", text->curr->element);
                free(text->curr);
                text->curr = next;
            }
            printf("\n");
            free(text);
            text = create_list();
        }
        else if (curr_char == '[') curr_mode = 0;
        else if (curr_char == ']') curr_mode = 1;
        else if (curr_mode == 0) {
            move_to_start(text);
            insert_element(text, curr_char);
            curr_mode = 2;
        } else if (curr_mode == 1) {
            move_to_end(text);
            insert_element(text, curr_char);
        } else if (curr_mode == 2) {
            next(text);
            insert_element(text, curr_char);
        }
    }
    return 0;
}
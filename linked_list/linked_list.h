#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node {
    int val;
    struct node* next;
} node_t;

// Fonctions de base
void add_begin(node_t **head, int val);
int add_end(node_t **head, int val);
int add_at(node_t **head, int val, int pos);

int pop(node_t **head);
int pop_last(node_t **head);
int pop_at(node_t **head, int index);
int pop_by_value(node_t **head, int val);

void print_list(node_t *head);
void free_list(node_t *head);

#endif

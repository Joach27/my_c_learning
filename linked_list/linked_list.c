#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// Ajouter un élément au début de la liste
void add_begin(node_t **head, int val) {
    node_t *new_node = malloc(sizeof(node_t)); // Allouer de la mémoire pour un nouveau noeud
    if (!new_node) { // Vérifier si l'allocation a échoué
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }

    new_node->val = val; // Initialiser la valeur du noeud
    new_node->next = *head; // Le prochain élément pointe vers l'ancien premier élément
    *head = new_node; // Le nouveau noeud devient le premier de la liste
}

// Ajouter un élément à la fin de la liste
int add_end(node_t **head, int val) {
    node_t *new_node = malloc(sizeof(node_t)); // Allouer de la mémoire pour un nouveau noeud
    if (!new_node) { // Vérifier si l'allocation a échoué
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return -1; // Retourner une erreur si l'allocation a échoué
    }

    new_node->val = val; // Initialiser la valeur du noeud
    new_node->next = NULL; // Le prochain élément est NULL car il s'agit du dernier noeud

    if (*head == NULL) { // Si la liste est vide, le nouveau noeud devient le premier
        *head = new_node;
        return val;
    }

    node_t *current = *head; // Pointer au début de la liste
    while (current->next != NULL) { // Chercher le dernier élément
        current = current->next;
    }

    current->next = new_node; // Ajouter le nouveau noeud à la fin de la liste
    return val;
}

// Ajouter un élément à une position donnée
int add_at(node_t **head, int val, int pos) {
    if (pos == 0) { // Si la position est 0, ajouter au début
        add_begin(head, val);
        return val;
    }

    node_t *current = *head; // Pointer au début de la liste
    for (int i = 0; i < pos - 1 && current != NULL; i++) { // Parcourir la liste jusqu'à la position souhaitée
        current = current->next;
    }

    if (current == NULL) return -1; // Si on atteint la fin de la liste, retourner une erreur

    node_t *new_node = malloc(sizeof(node_t)); // Allouer de la mémoire pour un nouveau noeud
    if (!new_node) { // Vérifier si l'allocation a échoué
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return -1;
    }

    new_node->val = val; // Initialiser la valeur du noeud
    new_node->next = current->next; // Le prochain élément devient celui qui était après la position donnée
    current->next = new_node; // Relier le noeud courant au nouveau noeud

    return val;
}

// Supprimer le premier élément de la liste
int pop(node_t **head) {
    if (*head == NULL) return -1; // Si la liste est vide, retourner une erreur

    node_t *temp = *head; // Pointer sur le premier noeud
    int val = temp->val; // Sauvegarder la valeur du premier noeud
    *head = temp->next; // Le premier élément devient le deuxième
    free(temp); // Libérer la mémoire du premier noeud
    return val;
}

// Supprimer le dernier élément de la liste
int pop_last(node_t **head) {
    if (*head == NULL) return -1; // Si la liste est vide, retourner une erreur

    node_t *current = *head;

    if (current->next == NULL) { // Si la liste n'a qu'un seul élément
        int val = current->val; // Sauvegarder la valeur
        free(current); // Libérer le noeud
        *head = NULL; // La liste devient vide
        return val;
    }

    while (current->next->next != NULL) { // Parcourir jusqu'à l'avant-dernier élément
        current = current->next;
    }

    int val = current->next->val; // Sauvegarder la valeur du dernier noeud
    free(current->next); // Libérer la mémoire du dernier noeud
    current->next = NULL; // L'avant-dernier noeud devient le dernier
    return val;
}

// Supprimer un élément à une position donnée
int pop_at(node_t **head, int index) {
    if (*head == NULL) { // Si la liste est vide, retourner une erreur
        return -1;
    }

    node_t *current = *head;

    if (index == 0) {  // Cas spécial : suppression du premier élément
        *head = current->next; // Le deuxième élément devient le premier
        int val = current->val; // Sauvegarder la valeur
        free(current); // Libérer la mémoire
        return val;
    }

    for (int i = 0; current != NULL && i < index - 1; i++) { // Parcourir la liste jusqu'à l'élément avant celui à supprimer
        current = current->next;
    }

    if (current == NULL || current->next == NULL) { // Si l'index est invalide
        return -1;  // Retourner une erreur
    }

    node_t *temp = current->next; // Pointer sur l'élément à supprimer
    current->next = current->next->next; // Relier l'élément précédent au suivant
    int val = temp->val; // Sauvegarder la valeur de l'élément supprimé
    free(temp); // Libérer la mémoire
    return val;
}

// Supprimer un élément par sa valeur
int pop_by_value(node_t **head, int val) {
    if (*head == NULL) { // Si la liste est vide, retourner une erreur
        return -1;
    }

    node_t *current = *head;

    if (current->val == val) { // Cas spécial : suppression du premier élément si sa valeur correspond
        *head = current->next; // Le deuxième élément devient le premier
        int ret_val = current->val; // Sauvegarder la valeur
        free(current); // Libérer la mémoire
        return ret_val;
    }

    while (current->next != NULL && current->next->val != val) { // Parcourir la liste pour trouver la valeur
        current = current->next;
    }

    if (current->next == NULL) { // Si la valeur n'est pas trouvée
        return -1;  // Retourner une erreur
    }

    node_t *temp = current->next; // Pointer sur le noeud à supprimer
    current->next = current->next->next; // Relier l'élément précédent au suivant
    int ret_val = temp->val; // Sauvegarder la valeur de l'élément supprimé
    free(temp); // Libérer la mémoire
    return ret_val;
}

// Afficher la liste
void print_list(node_t *head) {
    node_t *current = head;
    while (current != NULL) { // Parcourir la liste et afficher les éléments
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n"); // Indiquer la fin de la liste
}

// Libérer toute la mémoire de la liste
void free_list(node_t *head) {
    node_t *current = head;
    while (current != NULL) { // Parcourir toute la liste
        node_t *temp = current; // Sauvegarder l'élément courant
        current = current->next; // Passer au suivant
        free(temp); // Libérer la mémoire de l'élément courant
    }
}

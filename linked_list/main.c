#include <stdio.h>
#include "linked_list.h"

int main() {
    node_t *head = NULL;

    // Ajouter des éléments à la liste
    add_begin(&head, 5);    // Ajouter 5 au début de la liste
    add_end(&head, 10);     // Ajouter 10 à la fin de la liste
    add_at(&head, 7, 1);    // Ajouter 7 à la position 1, donc entre 5 et 10
    print_list(head);       // Affiche: 5 -> 7 -> 10 -> NULL

    // Supprimer le premier élément
    pop(&head); 
    print_list(head);       // Affiche: 7 -> 10 -> NULL

    // Supprimer le dernier élément
    pop_last(&head);
    print_list(head);       // Affiche: 7 -> NULL

    // Essayer de supprimer un élément à une position donnée
    pop_at(&head, 0); // Suppression de l'élément à la position 0
    print_list(head); // Affiche: NULL (liste vide)

    // Tester la suppression d'un élément par sa valeur
    add_end(&head, 20);
    add_end(&head, 30);
    print_list(head);       // Affiche: 20 -> 30 -> NULL
    pop_by_value(&head, 20); // Supprimer l'élément avec la valeur 20
    print_list(head);       // Affiche: 30 -> NULL

    // Libérer la mémoire allouée pour la liste
    free_list(head);
    return 0;
}

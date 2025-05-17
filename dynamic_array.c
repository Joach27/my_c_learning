#include <stdio.h>
#include <stdlib.h>

// Définition du nœud de la liste
typedef struct node {
    int val;
    struct node* next;
} node_t;

// ➕ Insertion en début de liste
void push_front(node_t **head, int val) {
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

// ➕ Insertion en fin de liste
void push_end(node_t *head, int val) {
    node_t *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    new_node->val = val;
    new_node->next = NULL;
    current->next = new_node;
}

// ➖ Suppression du premier élément (pop)
int pop(node_t **head) {
    if (*head == NULL) {
        return -1; // Liste vide
    }
    node_t *temp = *head;
    int retval = temp->val;
    *head = temp->next;
    free(temp);
    return retval;
}

// ➖ Suppression du dernier élément
int remove_last(node_t **head) {
    if (*head == NULL) return -1;

    node_t *current = *head;

    if (current->next == NULL) {
        int retval = current->val;
        free(current);
        *head = NULL;
        return retval;
    }

    while (current->next->next != NULL) {
        current = current->next;
    }

    int retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}

// 🔍 Recherche d'une valeur dans la liste
int contains(node_t *head, int val) {
    node_t *current = head;
    while (current != NULL) {
        if (current->val == val)
            return 1;
        current = current->next;
    }
    return 0;
}

// 🖨️ Affichage de la liste
void print_list(node_t *head) {
    node_t *current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

// 🧹 Libération de toute la liste
void free_list(node_t **head) {
    while (*head != NULL) {
        pop(head);
    }
}

/*Delete an item by value*/
int remove_by_value(node_t **head, int val) {
    // Si la liste est vide, rien à supprimer
    if (*head == NULL) {
        return -1;  // ou une autre valeur d'erreur
    }

    node_t *current = *head;
    node_t *previous = NULL;

    // Cas particulier : la valeur est dans le premier nœud
    if (current->val == val) {
        pop(head);  // supprime le premier nœud
        return val;
    }

    // Parcours de la liste pour trouver la valeur
    while (current != NULL && current->val != val) {
        previous = current;
        current = current->next;
    }

    // Si on est arrivé à la fin sans trouver la valeur
    if (current == NULL) {
        return -1;  // valeur non trouvée
    }

    // À ce stade, current pointe sur le nœud à supprimer
    // previous pointe sur le nœud juste avant

    previous->next = current->next;  // On saute le nœud courant
    free(current);                   // On libère la mémoire du nœud supprimé

    return val;  // On retourne la valeur supprimée
}

// Delete all occurence of an item
int remove_all_by_value(node_t **head, int val) {
    int count = 0;

    // Cas où la liste est vide
    if (*head == NULL)
        return 0;

    node_t *current = *head;

    // ⚠️ Cas spécial : la valeur est présente au début plusieurs fois
    while (current != NULL && current->val == val) {
        *head = current->next;  // avance le head
        free(current);
        current = *head;
        count++;
    }

    // À ce stade, current est soit NULL, soit un nœud dont la valeur != val
    node_t *prev = current;
    if (current == NULL)
        return count;

    current = current->next;

    // Parcours normal du reste de la liste
    while (current != NULL) {
        if (current->val == val) {
            prev->next = current->next; // on saute le nœud courant
            free(current);              // on libère la mémoire
            current = prev->next;       // on avance sans changer prev
            count++;
        } else {
            prev = current;             // on avance les deux pointeurs
            current = current->next;
        }
    }

    return count;  // retourne combien de nœuds ont été supprimés
}




// 🧪 Exemple d'utilisation dans main
int main() {
    node_t *head = NULL;

    // Ajout d'éléments
    push_front(&head, 10); // Listoe : 10
    push_front(&head, 20); // Liste : 20 -> 10
    push_end(head, 30);    // Liste : 20 -> 10 -> 30

    print_list(head);

    printf("pop() = %d\n", pop(&head));         // Retire 20
    printf("remove_last() = %d\n", remove_last(&head)); // Retire 30

    print_list(head); // Liste : 10

    printf("Contient 10 ? %s\n", contains(head, 10) ? "Oui" : "Non");
    printf("Contient 99 ? %s\n", contains(head, 99) ? "Oui" : "Non");

    free_list(&head);
    return 0;
}

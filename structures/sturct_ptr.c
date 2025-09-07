#include <stdio.h>
#include <stdlib.h>

// ----------------------------
// Définition commune
// ----------------------------
struct node {
    int data;
};

// ----------------------------
// ❌ VERSION INCORRECTE : passage par copie de pointeur
// ----------------------------
void addnode_incorrect(struct node* n1) {
    n1 = (struct node*)malloc(sizeof(struct node)); // alloue une struct node
    n1->data = 9; // affecte 9 à la copie du pointeur
    // Cette modification est perdue après le retour
}

// ----------------------------
// ✅ VERSION CORRECTE : passage par adresse du pointeur (double pointeur)
// ----------------------------
void addnode_correct(struct node** n1) {
    *n1 = (struct node*)malloc(sizeof(struct node)); // alloue et met à jour le pointeur original

    if (*n1 == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    (*n1)->data = 9; // affecte 9 à la vraie structure pointée
}

int main() {
    // ----------------------------
    // Test de la version incorrecte
    // ----------------------------
    struct node* n1_incorrect = NULL;

    addnode_incorrect(n1_incorrect); // passe un pointeur (copie)
    printf("Après addnode_incorrect:\n");

    if (n1_incorrect == NULL) {
        printf("n1_incorrect est toujours NULL (échec de l'affectation)\n");
    } else {
        // Ne devrait jamais s'exécuter
        printf("n1_incorrect->data = %d\n", n1_incorrect->data);
        free(n1_incorrect);
    }

    printf("\n");

    // ----------------------------
    // Test de la version correcte
    // ----------------------------
    struct node* n1_correct = NULL;

    addnode_correct(&n1_correct); // passe l'adresse du pointeur (double pointeur)
    printf("Après addnode_correct:\n");

    if (n1_correct == NULL) {
        printf("n1_correct est NULL (erreur d'allocation)\n");
    } else {
        printf("n1_correct->data = %d\n", n1_correct->data); // Devrait afficher 9
        free(n1_correct); // Libération mémoire
    }

    return 0;
}

// Tout se passe par valeur en C
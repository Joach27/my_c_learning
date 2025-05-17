#include <stdio.h>
#include <stdlib.h>

// Définition de la structure du nœud
typedef struct Node {
    char value;
    struct Node* left;
    struct Node* right;
} Node;

// Fonction pour créer un nouveau nœud
Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Pré-ordre : Visite - Gauche - Droite
void preOrder(Node* root) {
    if (root == NULL) return;
    printf("%c ", root->value);
    preOrder(root->left);
    preOrder(root->right);
}

// En-ordre : Gauche - Visite - Droite
void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%c ", root->value);
    inOrder(root->right);
}

// Post-ordre : Gauche - Droite - Visite
void postOrder(Node* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c ", root->value);
}

// Programme principal
int main() {
    /*
        Arbre utilisé :
              A
             / \
            B   C
           / \
          D   E
    */

    Node* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');

    printf("Pré-ordre : ");
    preOrder(root);
    printf("\n");

    printf("En-ordre : ");
    inOrder(root);
    printf("\n");

    printf("Post-ordre : ");
    postOrder(root);
    printf("\n");

    // Libération de la mémoire
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

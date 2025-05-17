#include <stdio.h>
#include <stdlib.h>

// Définition du nœud
typedef struct Node {
    char value;
    struct Node* left;
    struct Node* right;
} Node;

// Fonction de création de nœud
Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Structure de la file (queue) pour BFS
#define MAX 100

typedef struct Queue {
    Node* data[MAX];
    int front;
    int rear;
} Queue;

// Initialisation
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

// Vérifie si la file est vide
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// Ajoute un élément à la fin
void enqueue(Queue* q, Node* node) {
    if (q->rear < MAX) {
        q->data[q->rear++] = node;
    }
}

// Retire l'élément en tête
Node* dequeue(Queue* q) {
    if (!isEmpty(q)) {
        return q->data[q->front++];
    }
    return NULL;
}

// Parcours level-order (BFS)
void levelOrder(Node* root) {
    if (root == NULL) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        Node* current = dequeue(&q);
        printf("%c ", current->value);

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
}

// Main
int main() {
    /*
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

    printf("Level-order (BFS) : ");
    levelOrder(root);
    printf("\n");

    // Libération
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}

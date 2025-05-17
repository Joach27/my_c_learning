#include <stdio.h>

// 1. Fonctions d'opération
int addition(int a, int b) {
    return a + b;
}

int soustraction(int a, int b) {
    return a - b;
}

int multiplication(int a, int b) {
    return a * b;
}

int division(int a, int b) {
    // Une vérification simple pour éviter la division par zéro
    if (b == 0) {
        printf("Erreur : Division par zero !\n");
        return 0; // Ou gérer l'erreur d'une autre manière
    }
    return a / b;
}

// 2. Déclaration du typedef pour le pointeur de fonction
typedef int (*Operation)(int, int);

// 4. Fonction pour effectuer l'opération
void effectuerOperation(int nombre1, int nombre2, Operation operation_ptr) {
    int result;
    result = operation_ptr(nombre1, nombre2);
    printf("Le resultat de cette operation est : %d\n", result);
}

int main() {
    // 3. Création et initialisation du tableau de pointeurs de fonctions
    Operation operations_array[4] = {addition, soustraction, multiplication, division};

    int num1, num2;
    int choix_operation;

    // 5. Demander l'entrée de l'utilisateur
    printf("Entrez le premier nombre entier : ");
    scanf("%d", &num1);

    printf("Entrez le deuxieme nombre entier : ");
    scanf("%d", &num2);

    printf("\nChoisissez une operation :\n");
    printf("0 : Addition\n");
    printf("1 : Soustraction\n");
    printf("2 : Multiplication\n");
    printf("3 : Division\n");
    printf("Votre choix (0-3) : ");
    scanf("%d", &choix_operation);

    // 6. Utiliser l'entrée de l'utilisateur pour appeler la bonne fonction
    if (choix_operation >= 0 && choix_operation < 4) {
        effectuerOperation(num1, num2, operations_array[choix_operation]);
    } else {
        printf("Choix d'operation invalide.\n");
    }

    return 0;
}
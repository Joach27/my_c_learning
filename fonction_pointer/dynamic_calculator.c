// Online C compiler to run C program online
#include <stdio.h>

typedef int (*operation_function)(int, int);

typedef struct {
    char *nom;
    operation_function fonction;
}Operation;

int ad(int n1, int n2){return n1 + n2;}
int sous(int n1, int n2){return n1 - n2;}
int divi(int n1, int n2){
    if (n2 == 0){
        printf("Opération impossible (dénominateur est nul)");
        return 0;
    }
    return n1 / n2;
}
int mul(int n1, int n2){return n1 * n2;}

int calculateur(int nombre1, int nombre2, Operation operation){
    return operation.fonction(nombre1, nombre2);
}

int main() {
    Operation operations[] = {{"Addition", ad}, {"Soustraction", sous}, {"Division", divi}, {"Multiplication", mul}};
    int nombre_operation = sizeof(operations) / sizeof(Operation);
    
    int nombre1, nombre2, choix;
    
    printf("Nomber 1: \n");
    scanf("%d", &nombre1);
    printf("Nomber 2: \n");
    scanf("%d", &nombre2);

    printf("Choisissez une opération (1-4) ou '0' pour quitter): \n");
    for (int i = 0; i < nombre_operation; i++){
        printf("%d: %s\n", i + 1, operations[i].nom);
    }
    printf("Votre choix: \n");
    scanf("%d", &choix);

    while (choix != 0){
        if (choix >= 1 && choix <= nombre_operation){
            int resultat = operations[choix - 1].fonction(nombre1, nombre2);
            printf("Le résultat de l'opération est : %d \n", resultat);
        }

        printf("Choisissez une opération (1-%d) ou '0' pour quitter: \n", nombre_operation);
        for (int i = 0; i < nombre_operation; i++){
            printf("%d: %s\n", i + 1, operations[i].nom);
        }
        printf("Votre choix: \n");
        scanf("%d", &choix);
    }
    

    return 0;
}
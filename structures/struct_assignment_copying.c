#include <stdio.h>   // Pour les fonctions d'affichage comme printf
#include <stdlib.h>  // Pour malloc et free
#include <string.h>

void struct_assignment() {
    // Définition d'une structure contenant des types de base et un tableau
    struct data {
        int i;         // un entier
        char c;        // un caractère
        int j;         // un autre entier
        int arr[2];    // un tableau de 2 entiers
    };

    // Définition d'une structure contenant un pointeur vers un caractère
    struct datawptr {
        int i;         // un entier
        char *c;       // un pointeur vers un caractère
    };

    // Déclaration de deux variables de type datawptr
    struct datawptr dptr1;
    struct datawptr dptr2;

    // Déclaration de deux variables normales de type data
    struct data svar1;
    struct data svar2;

    // Initialisation des membres de la structure svar1
    svar1.c = 'a';
    svar1.i = 1;
    svar1.j = 2;
    svar1.arr[0] = 10;
    svar1.arr[1] = 20;

    // Affectation par copie de la structure svar1 à svar2
    svar2 = svar1;

    // Affichage des valeurs contenues dans la structure svar2
    printf("Value of second variable \n");
    printf("Member c = %c\n", svar2.c);
    printf("Member i = %d\n", svar2.i);
    printf("Member j = %d\n", svar2.j);
    printf("Member arr0th = %d\n", svar2.arr[0]);
    printf("Member arr1st = %d\n", svar2.arr[1]);

    // Initialisation de la structure avec pointeur
    dptr1.i = 10;  // Affectation directe de l'entier
    dptr1.c = (char*)malloc(sizeof(char));  // Allocation dynamique pour le pointeur char
    *(dptr1.c) = 'c';  // Affectation de la valeur pointée

    // Allocation de mémoire pour dptr2.c (mais elle sera écrasée)
    dptr2.c = (char*)malloc(sizeof(char));

    // Copie de toute la structure dptr1 dans dptr2 (shallow copy)
    dptr2 = dptr1;

    // Affichage des membres de la structure dptr2
    printf("int member = %d\n", dptr2.i);
    printf("char ptr member = %c\n", *(dptr2.c));  // Affiche le caractère pointé

    // Libération de la mémoire (éviter les fuites mémoire)
    free(dptr1.c);
    // Pas besoin de free(dptr2.c) car dptr2.c pointe vers la même zone mémoire

}

int struct_assignment_with_memcpy()
{
    struct datawptr
    {
        int i;
        char *c;
    };
    struct datawptr dptr1;
    struct datawptr dptr2;
    dptr1.i = 10;
    dptr1.c = (char*)malloc(sizeof(char));
    *(dptr1.c) = 'c';
    dptr2.c = (char*)malloc(sizeof(char));
    memcpy(&dptr2, &dptr1, sizeof(struct datawptr));
    printf("Int member value of 2nd variable = %d\n", dptr2.i);
    printf("Char ptr member value of 2nd variable = %c\n", *(dptr2.c));
    printf("value of char ptr in 1st variable = %p\n", dptr1.c);
    printf("value of char ptr in 2nd variable = %p\n", dptr2.c);
    printf("Changing value of 2nd member in 2nd variable (dptr2)\n");
    *(dptr2.c) = 'a';
    printf("value of char ptr of 2nd variable = %c and 1st variable = %c\n", *(dptr2.c),
    *(dptr1.c));
return 0;
}



void copie_profonde() {
    // Définition d'une structure avec un pointeur
    struct datawptr {
        int i;
        char *c;  // pointeur vers caractère
    };

    struct datawptr dptr1;
    struct datawptr dptr2;

    // Initialisation de dptr1
    dptr1.i = 10;
    dptr1.c = (char*)malloc(sizeof(char));  // Allocation mémoire
    *(dptr1.c) = 'x';  // Valeur du caractère pointé

    // --- Copie profonde ---

    // Copie manuelle de la valeur entière
    dptr2.i = dptr1.i;

    // Allocation séparée pour le pointeur de dptr2
    dptr2.c = (char*)malloc(sizeof(char));

    // Copie de la valeur pointée, et non du pointeur lui-même
    *(dptr2.c) = *(dptr1.c);

    // --- Affichage des résultats ---
    printf("dptr1.i = %d, *(dptr1.c) = %c\n", dptr1.i, *(dptr1.c));
    printf("dptr2.i = %d, *(dptr2.c) = %c\n", dptr2.i, *(dptr2.c));

    // --- Modification de dptr1.c pour vérifier l'indépendance ---
    *(dptr1.c) = 'z';
    printf("\nAprès modification de dptr1.c :\n");
    printf("*(dptr1.c) = %c\n", *(dptr1.c));
    printf("*(dptr2.c) = %c\n", *(dptr2.c));  // Ne doit PAS changer

    // Libération de la mémoire allouée
    free(dptr1.c);
    free(dptr2.c);

}

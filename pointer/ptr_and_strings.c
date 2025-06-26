#include <stdio.h>      // Pour printf
#include <string.h>     // Pour strlen et memcpy
#include <stdlib.h>     // Pour malloc et free
#include <stddef.h>

// Prototypes de fonctions
void dynamic_memory_allocation_example();
char* foo();
int* fooWithPointer();
int* foo1(); // Fonction qui retourne l'adresse d'une variable locale (dangereux)

int main(int argc, char* argv[])
{
    // Exemple simple de pointeur sur chaîne de caractères
    char* str = "Hello Pointer";
    char* ptr = str;

    printf("Adresse de str : %p\n", str);
    printf("Adresse de ptr : %p\n", ptr);
    printf("Adresse ptr+1 : %p, Valeur : %c\n", ptr+1, *(ptr+1));

    // Parcours de la chaîne via le pointeur
    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    printf("\n");

    // Appel de la fonction fooWithPointer (malloc dynamique)
    int* m = fooWithPointer();
    printf("Valeur allouée dynamiquement : %d\n", *m);
    free(m); // Libération mémoire

    // Appel de la fonction foo (chaîne littérale)
    char *str2 = foo();
    printf("Chaîne retournée par foo: %s\n", str2);

    // Appel de la fonction d'exemple d'allocation dynamique
    dynamic_memory_allocation_example();

    // ⚠️ Appel de foo1() - DÉMONSTRATION DANGEREUSE
    int* p = foo1();
    printf("Valeur de foo1() (dangereux) : %d (peut être incohérente)\n", *p);
    // Ici, le comportement est indéfini : la mémoire de `i` peut avoir été réutilisée

    /* UNE FOIS UNE CHAINE LITTERALE DEFINIE, ON NE PEUT PLUS LA MODIFIER */
    char* str3 = "Hello";
    // str3[0] = 'A'; // Cette ligne causera un problème car la chaîne est en lecture seule
    printf("Chaîne littérale : %s\n", str3);
    str3 = "New String"; // On peut changer le pointeur, mais pas le contenu
    printf("Chaîne littérale modifiée : %s\n", str3);
    
    /* //// Test de la fonction de concatenantion //// */
    // Déclarez et initializez les chaînes
    char deststr[100] = "Hello, ";   // Doit avoir assez de place pour concaténer
    char srcstr[] = "World!";
    
    // Appelez la fonction str_cat
    str_cat(deststr, srcstr);

    // Afficher le résultat
    printf("Chaîne concaténée : %s\n", deststr);


    return 0;
}


/* Fonction qui retourne une chaîne constante (dans la section en lecture seule) */
char* foo() {
    char *str = "Hello";
    return str;
}

/* Fonction qui retourne un pointeur vers une mémoire dynamiquement allouée */
int* fooWithPointer(void) {
    int* pa = malloc(sizeof(int));
    if (pa == NULL) {
        perror("malloc failed");
        exit(1);
    }
    *pa = 23;
    return pa;
}

/* Exemple d'allocation dynamique de chaîne et de copie */
void dynamic_memory_allocation_example() {
    const char* src = "Hello Pointer";

    // Allocation mémoire
    char* dst = (char*)malloc(strlen(src) + 1);
    if (dst == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        return;
    }

    // Copie de la chaîne source
    memcpy(dst, src, strlen(src) + 1);

    // Affichage
    printf("Copie réussie : %s\n", dst);

    // Libération mémoire
    free(dst);
}

/* ⚠️ Fonction dangereuse : retourne l'adresse d'une variable locale */
int* foo1(void) {
    int i = 10; // Variable locale sur la pile
    return &i;  // ⚠️ Mauvais : i sera détruit une fois la fonction terminée
}

/* Fonction pour copier une chaîne de caractères */
void str_copy(char* source, char* destination){
    char* src = source;
    char* dst = destination;
    
    while (*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

/*VERSION AVEC LA LONGEUR DE LA CHAINE*/
void str_copy_safe(char* destination, const char* source, size_t max_len) {
    if (destination == NULL || source == NULL || max_len == 0) return;

    size_t i = 0;
    while (i < max_len - 1 && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0'; // Assure la terminaison nulle
}

/* VERSION AVEC IDIOME C */
void str_copy_idiome(char* destination, const char* source) {
    if (destination == NULL || source == NULL) return;

    while ((*destination++ = *source++));
}

/* Fonction pour concaténer deux chaînes de caractères */
char* str_concat(char* first_string, char* second_string) {
    if (first_string == NULL || second_string == NULL) return NULL;

    int n1 = strlen(first_string);
    int n2 = strlen(second_string);
    int n = n1 + n2;

    char* result = (char*)malloc(n + 1); // +1 pour le caractère nul
    if (result == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        if (i < n1) {
            result[i] = first_string[i];
        } else {
            result[i] = second_string[i - n1];
        }
    }

    result[n] = '\0'; // Assure la terminaison nulle
    return result;
}

/* Fonction pour concaténer deux chaînes de caractères */
void str_cat(char* deststr, const char* srcstr) {
    char* dtemp = deststr;
    const char* stemp = srcstr;

    // Atteindre la fin de deststr
    while (*dtemp != '\0') {
        dtemp++;
    }

    // Concaténer srcstr à deststr
    while (*stemp != '\0') {
        *dtemp = *stemp;
        dtemp++;
        stemp++;
    }

    // Ajouter un terminateur null à la fin de la nouvelle chaîne
    *dtemp = '\0';
}



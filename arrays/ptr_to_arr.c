#include <stdio.h>

#define N 5

void remplir_tableau(int data[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            data[i][j] = count++;
        }
    }
}

void remplir_tableau_1D(int data_1d[N * N]) {
    for (int i = 0; i < N * N; i++) {
        data_1d[i] = i;
    }
}

// Méthode 1 : pointeur vers tableau + arithmétique
void afficher_par_ptr_arithmetique(int data[N][N]) {
    int (*ptr)[N] = data;

    printf("=== Affichage avec *ptr + j ===\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d, %d: adresse: %p, valeur: %d\n", 
                i, j, (void*)(*ptr + j), *(*ptr + j));
        }
        ptr++;
    }
    printf("\n");
}

// Méthode 2 : accès par &data[i][0]
void afficher_par_adresse_directe(int data[N][N]) {
    printf("=== Affichage avec &data[i][0] ===\n");
    for (int i = 0; i < N; i++) {
        int *dataptr = &data[i][0];
        for (int j = 0; j < N; j++) {
            printf("%d, %d: adresse: %p, valeur: %d\n", 
                i, j, (void*)dataptr, *dataptr);
            dataptr++;
        }
    }
    printf("\n");
}

// Méthode 3 : accès linéaire comme un tableau 1D
void afficher_par_tableau_1D(int data[N][N]) {
    int *flat = &data[0][0];

    printf("=== Affichage linéaire (1D) via *(data[0] + i*N + j) ===\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int index = i * N + j;
            printf("%d, %d: adresse: %p, valeur: %d\n",
                i, j, (void*)(flat + index), *(flat + index));
        }
    }
    printf("\n");
}

// 🔥 Méthode 4 : tableau 1D explicite (int data[25])
void afficher_tableau_1D_explicit(int data_1d[N * N]) {
    printf("=== Affichage avec data_1d[i * N + j] (tableau 1D réel) ===\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int index = i * N + j;
            printf("%d, %d: adresse: %p, valeur: %d\n",
                   i, j, (void*)(data_1d + index), data_1d[index]);
        }
    }
    printf("\n");
}

// Affichage d'un tableau 2D comme un tableau 1D
void afficher_tableau_2D_comme_1D() {
    int data[5][5];
    int i, j;
    int count = 0;
    int (*aptr)[5];
    int *dataptr;

    // Remplissage du tableau data avec des valeurs de 0 à 24
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            data[i][j] = count++;
        }
    }

    aptr = data;

    for (i = 0; i < 5; i++) {
        printf("Address of row %d = %p\n", i, (void*)(aptr+i));
        dataptr = *aptr + i * 5;

        for (j = 0; j < 5; j++) {
            printf("%d,%d = %p val = %d\n", i, j, (void*)dataptr, *dataptr);
            dataptr++;
        }

        printf("\n");
    }

}



int main() {
    int data[N][N];
    int data_1d[N * N];

    remplir_tableau(data);
    remplir_tableau_1D(data_1d);
    
    afficher_par_ptr_arithmetique(data);
    afficher_par_adresse_directe(data);
    afficher_par_tableau_1D(data);
    afficher_tableau_1D_explicit(data_1d);

    afficher_tableau_2D_comme_1D();

    return 0;
}

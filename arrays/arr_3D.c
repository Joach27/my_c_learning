#include <stdio.h>

int main() {
    int cube[2][3][4];
    int count = 0;

    // Remplissage du tableau
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                cube[i][j][k] = count++;
            }
        }
    }

    // Affichage des adresses et des valeurs
    for (int i = 0; i < 2; i++) {
        printf("Bloc %d:\n", i);
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                printf("cube[%d][%d][%d] = %2d at %p\n",
                       i, j, k, cube[i][j][k], (void*)&cube[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}

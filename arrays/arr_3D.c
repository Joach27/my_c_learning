#include <stdio.h>

void print_3D_array_2nd_level();
void print_3D_array_3rd_level();
void print_3D_by_pointer();

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
    
    printf("--------------\n");
    print_3D_array_2nd_level();
    print_3D_array_3rd_level();
    print_3D_by_pointer();
    
    return 0;
}

void print_3D_array_1st_level(){
    int n = 3;
    int data[n][n][n];
    int count = 0;
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                data[i][j][k] = count++;
            }
        }
    }
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                printf("%d%d%d=%d addr %p", i, j, k, data[i][j][k], &data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    printf("Index of value address\n");
    for (int i=0; i<n; i++){
        printf("row %d addr = %p\n", i, data+i);
    }
}



void print_3D_array_2nd_level(){
    int n = 3;
    int data[n][n][n];
    int count = 0;
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                data[i][j][k] = count++;
            }
        }
    }
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                printf("%d%d%d=%d addr %p", i, j, k, data[i][j][k], &data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    /* afficher les adresses des lignes de la première ligne du 3D_array */
    for (int i=0; i<n; i++){
        printf("row %d addr = %p\n", i, data[0][i]);
    }
    
    printf("2D row address\n");
    for (int i=0; i<n; i++){
        printf("3D %d ROW\n", i);
        for (int j=0; j<n; j++){
            printf("2D row %d addr=%p %p\n", j, data[i][j], *(data[i]+j));
        }
        printf("\n");
    }
    printf("\n");
}

void print_3D_array_3rd_level(){
    int n = 3;
    int data[n][n][n];
    int count = 0;
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                data[i][j][k] = count++;
            }
        }
    }
    
    printf("Index=val addr<>\n");
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                printf("%d%d%d=%d addr %p", i, j, k, data[i][j][k], &data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    for (int i=0; i<n; i++){
        printf("row %d addr = %p\n", i, data[0][i]);
    }
    
    printf("2D row address\n");
    for (int i=0; i<n; i++){
        printf("3D %d ROW\n", i);
        for (int j=0; j<n; j++){
            printf("2D row %d addr=%p %p\n", j, data[i][j], *(data[i]+j));
        }
    }
    
    printf("1D element address\n");
    for (int i=0; i<n; i++){
        printf("3D %d ROW\n", i);
        for (int j=0; j<n; j++){
            printf("2D %d row\n", j);
            for (int k=0; k<n; k++){
                printf("%d%d%d = %p val = %d ", i, j, k, *(data[i] + j) + k, *(*(data[i] + j) + k));
            }
            printf("\n");
        }
    }
}


void print_3D_by_pointer(){
    int n = 3;
    int data[n][n][n];
    int count = 0;
    int* dataptr = NULL;
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                data[i][j][k] = count++;
            }
        }
    }
    
    for (int i=0; i<n; i++){
        printf("3D %d ROW\n", i);
        for (int j=0; j<n; j++){
            dataptr = *(data[i] + j);
            for (int k=0; k<n; k++){
                printf("%d%d%d = %p val = %d ", i, j, k, dataptr, *dataptr++);
            }
            printf(("\n"));
        }
    }
}
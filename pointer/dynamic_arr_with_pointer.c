#include <stdio.h>
#include <stdlib.h>

int *ptr = NULL;
static int count = 0;

void insert(int data) {
    if (ptr == NULL) {
        // Allocation initiale pour le premier entier
        ptr = (int *)malloc(sizeof(int));
        ptr[0] = data;
    } else {
        // Réallocation pour insérer un nouvel entier
        ptr = (int *)realloc(ptr, sizeof(int) * (count + 1));
        ptr[count] = data;
    }
    count++;
}

void show() {
    for (int i = 0; i < count; i++) {
        printf("%d\n", ptr[i]);
    }
}


int main(int argc, char *argv[]) {
    int c = 0;
    int data;

    while (c != 3) {
        printf("Insert choice\n");
        printf("1 to insert data\n");
        printf("2 to Show data\n");
        printf("3 to quit\n");
        scanf("%d", &c);

        if (c == 3)
            break;

        switch (c) {
            case 1:
                printf("Data = ");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                printf("Data in array:\n");
                show();
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    // Libération de la mémoire allouée
    free(ptr);
    return 0;
}


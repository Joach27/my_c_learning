#include <stdio.h>
#include <stdlib.h>

// Function to demonstrate array of pointers
// This function creates an array of pointers to the elements of another array
// and prints the addresses of the elements in the original array and the values in the pointer array
void pointerArray(){
    int arr[4] = {1,2,3,4};
    int* arr_ptr[4];
    int i;
    for(i = 0; i<4; i++)
    {
        arr_ptr[i] = arr + i;
    }
    printf("Address of (arr) array element\n");
    
    for(i = 0; i<4; i++)
    {
        printf("Address of %d index = %p\n",i, arr + i);
    }
    printf("------------------------------\n");

    printf("Value of (arr_ptr) array of pointer element \n");
    
    for(i = 0; i<4; i++)
    {
        printf("Value of %d index = %p\n",i, arr_ptr[i]);
    }
}

// Pointer to Array
// This function demonstrates how to use a pointer to an array
void pointerToArray() {
    int arr[4] = {1, 2, 3, 4};
    int (*ptr2arr)[4];  // Pointeur vers un tableau de 4 entiers 
    int i;
    int *ptr = arr;     // Pointeur vers le premier élément du tableau

    ptr2arr = &arr;     // ptr2arr pointe vers le tableau arr (le tableau entier pas juste un élément)

    // Affiche les adresses de chaque élément de arr
    for (i = 0; i < 4; i++) {
        printf("Address of arr[%d] = %p\n", i, (void *)(arr + i));
    }

    // Accès à un élément via ptr2arr
    printf("\nValue at *(ptr2arr[0] + 1) = %d\n", *(ptr2arr[0] + 1));

    // Affiche les valeurs et adresses des éléments du tableau via ptr2arr
    for (i = 0; i < 4; i++) {
        printf("Value at %p = %d\n", 
               (void *)(ptr2arr[0] + i), *(ptr2arr[0] + i));
    }


}


int main(int argc, char *argv[]) {
    pointerArray();
    pointerToArray();
    return 0;
}

/*
| Expression          | Résultat                          |
| ------------------- | --------------------------------- |
| `ptr2arr`           | Adresse de `arr[0]` (tableau)     |
| `ptr2arr[0]`        | Le tableau `arr` lui-même         |
| `ptr2arr[0] + i`    | Adresse de `arr[i]`               |
| `*(ptr2arr[0] + i)` | Valeur `arr[i]`                   |
| `(*ptr2arr)[i]`     | ✔ Même chose, syntaxe équivalente |
*/
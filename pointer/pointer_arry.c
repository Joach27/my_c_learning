#include <stdio.h>
#define LITTLE_ENDIAN 1
#define BIG_ENDIAN 0

// check the endianness of the system
int endian(){
    short int word = 0x0001;

    char *byte = (char *) &word;
    return (byte[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}

// LITTLE ENDIAN (less significant byte at the lowest address)
void display_int_bytes() {
    int x = 0x12345678;
    unsigned char* p = (unsigned char*)&x;

    for (int i = 0; i < sizeof(x); i++) {
        printf("Octet %d : 0x%02x\n", i, p[i]);
    }

}


int main() {
    int iArray[32];
    int i;

    // Remplir le tableau
    for(i = 0; i < 32; i++) {
        iArray[i] = i;
    }

    // Afficher les valeurs et les adresses
    for(i = 0; i < 32; i++) {
        printf("a[%d] %p %d  ", i, (void*)&iArray[i], iArray[i]);

        // Nouvelle ligne après chaque groupe de 4 (sauf au début)
        if((i % 4 == 0) && (i != 0)) {
            printf("\n");
        }
    }

    // Attente manuelle à la fin
    printf("\nAppuie sur Entrée pour quitter...");
    getchar();  // Attendre qu'on appuie sur "Entrée"

    // Afficher les octets d'un entier
    display_int_bytes();

    // Check endianness
    int value = endian();
    if (value == 1)
        printf("LITTLE ENDIAN\n");
    else if (value == 0)
        printf("BIG ENDIAN\n");
    else
        printf("UNKNOWN ENDIANNESS\n");

    return 0;
}

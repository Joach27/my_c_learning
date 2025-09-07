#include <stdio.h>
#include <string.h>

void receivedata(char* buffer) {
    // Simulons des données reçues
    buffer[0] = 'S';      // sign
    buffer[1] = '1';      // version
    buffer[2] = 'A';      // id
    buffer[3] = 'X';      // platform
    strcpy(&buffer[4], "Contenu de test..."); // données
}

#pragma pack(1) // Pour forcer le layout sans padding
struct signature {
    char sign;
    char version;
};

struct id {
    char id;
    char platform;
};

struct data {
    struct signature sig;
    struct id idv;
    char data[100];
};

// Fonctions d'extraction
struct signature* extractsignature(struct data* d) {
    return (struct signature*)d;
}

struct id* extractid(struct data* d) {
    return (struct id*)((char*)d + sizeof(struct signature));
}


int main() {
    char buffer[104];
    receivedata(buffer); // simulation de réception

    // On cast le buffer brut en structure
    struct data* d = (struct data*)buffer;

    // Extraction des parties
    struct signature* sig = extractsignature(d);
    struct id* idv = extractid(d);

    // Affichage
    printf("Signature: %c, Version: %c\n", sig->sign, sig->version);
    printf("ID: %c, Platform: %c\n", idv->id, idv->platform);
    printf("Data: %s\n", d->data);

    return 0;
}

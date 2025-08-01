#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure normale avec padding
struct gif_hdr {
    char signature[3];
    char version[3];
    int width;
    int height;
    char colormap;
    char bgcolor;
    char ratio;
};

// Version packed (sans padding)
struct __attribute__((packed)) gif_hdr_packed {
    char signature[3];
    char version[3];
    int width;
    int height;
    char colormap;
    char bgcolor;
    char ratio;
};

// Fonction d'affichage hexadécimale
void print_bytes(const void* ptr, size_t size) {
    const unsigned char* bytes = (const unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

int main(void) {
    struct gif_hdr hdr = {
        .signature = {'G', 'I', 'F'},
        .version = {'8', '9', 'a'},
        .width = 640,
        .height = 480,
        .colormap = 1,
        .bgcolor = 0,
        .ratio = 0
    };

    struct gif_hdr_packed hdr_packed;
    memcpy(&hdr_packed, &hdr, sizeof(hdr_packed)); // Copier les mêmes valeurs

    // Écriture fichier normal
    FILE* f = fopen("normal.bin", "wb");
    fwrite(&hdr, 1, sizeof(hdr), f);
    fclose(f);

    // Écriture fichier packed
    f = fopen("packed.bin", "wb");
    fwrite(&hdr_packed, 1, sizeof(hdr_packed), f);
    fclose(f);

    // Affichage des tailles et des données
    printf("Taille de gif_hdr (normal)  : %zu octets\n", sizeof(hdr));
    printf("Taille de gif_hdr_packed    : %zu octets\n", sizeof(hdr_packed));

    printf("\nContenu (gif_hdr) écrit :\n");
    print_bytes(&hdr, sizeof(hdr));

    printf("\nContenu (gif_hdr_packed) écrit :\n");
    print_bytes(&hdr_packed, sizeof(hdr_packed));

    return 0;
}

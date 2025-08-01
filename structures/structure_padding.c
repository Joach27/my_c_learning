#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>  // pour offsetof


int padding_acces() {
    // Simulons un buffer mémoire (octets avec des valeurs choisies)
    uint8_t buffer[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22 };

    // On veut lire un int 4 octets à l'adresse 1 (non alignée)
    // Les octets concernés sont donc : BB CC DD EE

    // Lecture simulée des deux blocs alignés (4 octets chacun)
    // Bloc 1 : buffer[0..3] = AA BB CC DD
    // Bloc 2 : buffer[4..7] = EE FF 11 22

    // On convertit ces 4 octets en uint32_t
    uint32_t bloc1 = (buffer[0]) | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
    uint32_t bloc2 = (buffer[4]) | (buffer[5] << 8) | (buffer[6] << 16) | (buffer[7] << 24);

    // Décalage à droite de bloc1 de 8 bits (1 octet) pour enlever AA
    uint32_t part1 = bloc1 >> 8;

    // Masque pour garder EE (premier octet de bloc2)
    uint32_t part2 = bloc2 & 0xFF;

    // Décalage à gauche de EE pour la placer dans l'octet de poids fort
    uint32_t result = (part2 << 24) | part1;

    printf("Valeur reconstituée : 0x%08X\n", result);

    return 0;
}



void struct_padding_gif_format() {
    
    struct gif_hdr {
        char signature[3];
        char version[3];
        int width;
        int height;
        char colormap;
        char bgcolor;
        char ratio;
    };
    
    printf("Taille totale de la structure : %zu octets\n", sizeof(struct gif_hdr));

    printf("Offset de signature : %zu\n", offsetof(struct gif_hdr, signature));
    printf("Offset de version   : %zu\n", offsetof(struct gif_hdr, version));
    printf("Offset de width     : %zu\n", offsetof(struct gif_hdr, width));
    printf("Offset de height    : %zu\n", offsetof(struct gif_hdr, height));
    printf("Offset de colormap  : %zu\n", offsetof(struct gif_hdr, colormap));
    printf("Offset de bgcolor   : %zu\n", offsetof(struct gif_hdr, bgcolor));
    printf("Offset de ratio     : %zu\n", offsetof(struct gif_hdr, ratio));

}


void padding_vs_packing()
{
    struct gif_hdr {
        char signature[3];
        char version[3];
        int width;
        int height;
        char colormap;
        char bgcolor;
        char ratio;
    };
    
    struct __attribute__((packed)) gif_hdr_packed {
        char signature[3];
        char version[3];
        int width;
        int height;
        char colormap;
        char bgcolor;
        char ratio;
    };
    
    printf("Taille struct normale : %zu\n", sizeof(struct gif_hdr));
    printf("Taille struct packed  : %zu\n", sizeof(struct gif_hdr_packed));
}












int main(int argc, char* argv[])
{
    struct data
    {
        int i;
        char c1;
        int j;
        char c2;
        int k;
    };
    
    struct data v1;
    struct data *dsptr;
    
    printf("Size of structure data = %zu\n", sizeof(struct data));
    
    dsptr = (struct data*)malloc(sizeof(struct data));
    if (dsptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Address of member int i = %p\n", (void*)&(dsptr->i));
    printf("Address of member char c1 = %p\n", (void*)&(dsptr->c1));
    printf("Address of member int j = %p\n", (void*)&(dsptr->j));
    printf("Address of member char c2 = %p\n", (void*)&(dsptr->c2));
    printf("Address of member int k = %p\n", (void*)&(dsptr->k));
    
    free(dsptr);
    return 0;
}
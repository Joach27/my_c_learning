#include <stdio.h>


// Structure normale (avec padding)
struct gif_hdr {
    char signature[3];
    char version[3];
    int width;
    int height;
    char colormap;
    char bgcolor;
    char ratio;
};

// Structure packed (alignée sur 1 octet)
struct __attribute__((packed)) gif_hdr_packed {
    char signature[3];
    char version[3];
    int width;
    int height;
    char colormap;
    char bgcolor;
    char ratio;
};

void print_struct(const char* label, const void* ptr, int packed) {
    if (packed) {
        const struct gif_hdr_packed* hdr = (const struct gif_hdr_packed*)ptr;
        printf("--- %s (packed) ---\n", label);
        printf("Signature : %.3s\n", hdr->signature);
        printf("Version   : %.3s\n", hdr->version);
        printf("Width     : %d\n", hdr->width);
        printf("Height    : %d\n", hdr->height);
        printf("Colormap  : %d\n", hdr->colormap);
        printf("Bgcolor   : %d\n", hdr->bgcolor);
        printf("Ratio     : %d\n", hdr->ratio);
    } else {
        const struct gif_hdr* hdr = (const struct gif_hdr*)ptr;
        printf("--- %s (normal) ---\n", label);
        printf("Signature : %.3s\n", hdr->signature);
        printf("Version   : %.3s\n", hdr->version);
        printf("Width     : %d\n", hdr->width);
        printf("Height    : %d\n", hdr->height);
        printf("Colormap  : %d\n", hdr->colormap);
        printf("Bgcolor   : %d\n", hdr->bgcolor);
        printf("Ratio     : %d\n", hdr->ratio);
    }
}

int main(void) {
    FILE* f;
    struct gif_hdr hdr_normal;
    struct gif_hdr_packed hdr_packed;

    // Lire fichier normal.bin
    f = fopen("normal.bin", "rb");
    if (!f) {
        perror("Erreur ouverture normal.bin");
        return 1;
    }
    fread(&hdr_normal, 1, sizeof(hdr_normal), f);
    fclose(f);

    // Lire fichier packed.bin
    f = fopen("packed.bin", "rb");
    if (!f) {
        perror("Erreur ouverture packed.bin");
        return 1;
    }
    fread(&hdr_packed, 1, sizeof(hdr_packed), f);
    fclose(f);

    // Affichage
    print_struct("Lecture de normal.bin dans struct normale", &hdr_normal, 0);
    print_struct("Lecture de packed.bin dans struct packed", &hdr_packed, 1);

    // ➖ Tests inversés (pour montrer les effets du mauvais alignement)
    printf("\n--- Test de Mappage Incorrect ---\n");
    print_struct("Lecture de packed.bin avec struct normale", &hdr_packed, 0); // erreur potentielle !
    print_struct("Lecture de normal.bin avec struct packed", &hdr_normal, 1); // erreur potentielle !

    return 0;
}

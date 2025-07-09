// utils.c
#include "utils.h"

void copy_until(char* dest, const char* src, char stop) {
    int i = 0;
    while (src[i] != '\0' && src[i] != stop) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Terminer la chaîne avec le caractère nul
}

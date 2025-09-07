#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Déclaration de str_lower écrite en assembleur
int64_t str_lower(char *str);

int main() {
    // char s[] = "HeLLo PWn.ColLeGe!";
    char s[] = "ABC xyz 123!";

    printf("Before: %s\n", s);

    int64_t converted = str_lower(s);

    printf("After:  %s\n", s);
    printf("Converted letters: %ld\n", converted);

    return 0;
}



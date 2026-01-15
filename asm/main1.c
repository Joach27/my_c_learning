#include <stdio.h>
#include <stdint.h>

extern long factorial(long n); // déclaration de la fonction assembleur
extern long strlenl(const char *s);
// Prototype de la fonction assembleur
extern uint8_t most_common_byte(uint8_t* src, uint64_t size);


int main() {
    long n = 5;
    long result = factorial(n);
    printf("factorial(%ld) = %ld\n", n, result);
    
    // Test de strlen.s
    const char* s = "Hello, world!";
    printf("Length: %zu\n", strlenl(s));  // devrait afficher 13

    // Test de most common byte 
    uint8_t data[] = {1, 2, 2, 3, 4, 2, 2, 2, 5, 6};
    uint64_t size = sizeof(data);

    uint8_t result1 = most_common_byte(data, size);
    printf("Most common byte: %u\n", result1);  // Devrait afficher 2


    return 0;
}

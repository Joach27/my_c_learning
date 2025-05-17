#include <stdio.h>

union Valeur
{
    int i;
    float f;
    char c;
};

// Les unions sont comme les struct sauf que l'uninon c'est plusieurs types de données qui partagent la même adresse mémoire.
// Donc, on peut stocker un seul type à la fois.

union intParts
{
    int theInt; // 4 bytes
    // 1 byte = 8 bits
    char bytes[sizeof(int)];
};

/* Combining this with a structure allows you to create a "tagged" union which can be used to store multiple different types, one at a time. */

// This way, we can store the type of the variable in the struct and use the union to store the value.
// This is useful when you want to store different types of data in the same variable, but you only need to use one type at a time. 

// To take less memory, we can do this (The size of the struct is the size of the the int type + the the size of the largest type in the union):
struct operator {
    int type;
    union {
      int intNum;
      float floatNum;
      double doubleNum;
    } types;
};

/*
// If you don't give the union a name then it's members are accessed directly from the struct:
struct operator {
    int type;
    union {
        int intNum;
        float floatNum;
        double doubleNum;
    }; // no name!
};

operator op;
op.type = 0; // int
// intNum is part of the union, but since it's not named you access it directly off the struct itself
op.intNum = 352;

*/

int main()
{
    union Valeur v;

    v.i = 10;
    printf("v.i = %d\n", v.i);

    v.f = 3.14;
    printf("v.f = %f\n", v.f); // Maintenant, v.i a été écrasé

    v.c = 'A';
    printf("v.c = %c\n", v.c); // v.f est aussi écrasé

    ////////////////////////////////////

    union intParts parts;
    parts.theInt = 5968145; // arbitrary number > 255 (1 byte)

    printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n",
           parts.theInt, parts.bytes[0], parts.bytes[1], parts.bytes[2], parts.bytes[3]);

    // vs

    int theInt = parts.theInt;
    printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n",
           theInt, *((char *)&theInt + 0), *((char *)&theInt + 1), *((char *)&theInt + 2), *((char *)&theInt + 3));

    // or with array syntax which can be a tiny bit nicer sometimes

    printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n",
           theInt, ((char *)&theInt)[0], ((char *)&theInt)[1], ((char *)&theInt)[2], ((char *)&theInt)[3]);

    /* Combinning structs and unions */
    struct operator op;
    op.type = 1; // int
    op.types.intNum = 10;

    return 0;
}

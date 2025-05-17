#include <stdio.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE
} NumberType;

typedef struct {
    NumberType type;
    union {
        int intVal;
        float floatVal;
        double doubleVal;
    };
} Operator;

void printValue(Operator op) {
    switch (op.type) {
        case TYPE_INT:
            printf("%d", op.intVal);
            break;
        case TYPE_FLOAT:
            printf("%f", op.floatVal);
            break;
        case TYPE_DOUBLE:
            printf("%lf", op.doubleVal);
            break;
    }
}

Operator add(Operator a, Operator b) {
    Operator result;

    // Vérifie que les types sont les mêmes
    if (a.type != b.type) {
        printf("Erreur : types différents !\n");
        result.type = TYPE_INT;
        result.intVal = 0;
        return result;
    }

    result.type = a.type;

    switch (a.type) {
        case TYPE_INT:
            result.intVal = a.intVal + b.intVal;
            break;
        case TYPE_FLOAT:
            result.floatVal = a.floatVal + b.floatVal;
            break;
        case TYPE_DOUBLE:
            result.doubleVal = a.doubleVal + b.doubleVal;
            break;
    }

    return result;
}

int main() {
    Operator op1, op2, res;

    // Exemple 1 : addition d'entiers
    op1.type = TYPE_INT;
    op1.intVal = 10;

    op2.type = TYPE_INT;
    op2.intVal = 20;

    res = add(op1, op2);
    printf("Résultat (int) : ");
    printValue(res);
    printf("\n");

    // Exemple 2 : addition de floats
    op1.type = TYPE_FLOAT;
    op1.floatVal = 1.5f;

    op2.type = TYPE_FLOAT;
    op2.floatVal = 2.5f;

    res = add(op1, op2);
    printf("Résultat (float) : ");
    printValue(res);
    printf("\n");

    // Exemple 3 : erreur de type
    op1.type = TYPE_INT;
    op1.intVal = 5;

    op2.type = TYPE_DOUBLE;
    op2.doubleVal = 7.7;

    res = add(op1, op2); // Affichera un message d'erreur

    return 0;
}

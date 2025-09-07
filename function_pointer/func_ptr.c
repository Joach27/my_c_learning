#include <stdio.h>

// Prototype de la version dans tableau
void FuncPtr();

int add(int a, int b)
{
    return a + b;
}
int divi(int a, int b)
{
    return a / b;
}
int mult(int a, int b)
{
    return a * b;
}
int sous(int a, int b)
{
    return a - b;
}

// Tableau de pointeur des fonctions définies
int (*func_table[])(int a, int b) = {add, divi, mult, sous};

// La fonction qui va retourner le pointur d'une de nos fonction calculateurs
//int (*func_ptr_ret(void))(int a, int b);

// Définit la fonction pointeur à retournée comme un type pour faciliter les écriture utérieurs.
typedef int (*calc)(int a, int b) ;
calc func_ptr_ret(int index) {
    return func_table[index];
}

int main(){
    int choice, a, b, result;
    int (*calculator)(int a, int b);
    printf("Type -1 to quit: \n");
    printf("0 for add | 1 for division | 2 for mult | 3 for soustraction: \n");
    scanf("%d", &choice);
    
    while (choice != -1)
    {
        calculator = func_ptr_ret(choice);
        printf("First member: \n");
        scanf("%d", &a);
        printf("Second member: \n");
        scanf("%d", &b);
        result = calculator(a, b);
        printf("The result is: %d\n", result);
        
        printf("0 for add | 1 for division | 2 for mult | 3 for soustraction: \n");
        scanf("%d", &choice);
    }
    
    /* Appel de la version sans tableau */
    FuncPtr();
    
    return 0;
}


// Version sans tableau de de fonctions
typedef int (*calcul)(int a, int b) ;

calcul calcul_a_faire(int operation){
    switch(operation){
        case 0: return add;
        case 1: return divi;
        case 2: return mult;
        case 3: return sous;
        
        default: return NULL;
    }
}
void FuncPtr(){

    int a, b, operation, result;
    do 
    {
        printf("Enter -1 to quit");
        printf("0 for add | 1 for division | 2 for mult | 3 for soustraction: \n");
        scanf("%d", &operation);
        // on peut faire cette déclaration ici et l'utiliser en bas 
        calcul calc = calcul_a_faire(operation);
        printf("First member: \n");
        scanf("%d", &a);
        printf("Second member: \n");
        scanf("%d", &b);
        
        // on peut alors faire : calc(a, b);
        int result = calcul_a_faire(operation)(a, b);
        printf("Result: %d\n", result);
    }while(operation != -1);
    
}
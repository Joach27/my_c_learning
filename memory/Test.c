#include <stdio.h>
#include <malloc.h>

int glb_uninit; /* Part of a Segment --global uninitialized variable, at runtime it will be initialized to 0 */
int glb_init = 10; /* Part of a DATA Segment --global initialized variable */

void foo(void)
{
    static int num = 0; /* stack frame count */
    int autovar; /* auto variable / Local variable */
    int *ptr_foo = (int*)malloc(sizeof(int)); 

    if (++num == 4) {return;} // Creating four stack frames
    printf("Stack frame number %d: Address of autovar: %p\n", num, &autovar);
    printf("Address of heap allocated inside foo() %p\n", ptr_foo);
    foo(); // Fonction call
    
}

int main()
{
    char *p, *b, *nb;
    int *ptr_main = (int*)malloc(sizeof(int)); // Dynamic memory allocation in main
    printf("Text Segment:\n");
    printf("Address of main: %p\n", main);
    printf("Address of afunc: %p\n", foo);
    printf("Stack Location:\n");
    foo(); // Call to foo to create stack frames
    printf("Data Segment:\n");
    printf("Address of glb_init: %p\n", &glb_init);
    printf("BSS Segment:\n");
    printf("Address of glb_uninit: %p\n", &glb_uninit);
    printf("Heap Segment:\n");
    printf("Adress of heap allocated inside main() %p\n", ptr_main);    


    return 0;
}
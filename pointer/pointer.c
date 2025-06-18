#include <stdio.h>

struct inner_node {
    int in_a;
    int in_b;
};

struct node {
    int *a;
    int *b;
    struct inner_node *in_node;
};


struct data {
  int x; 
  int y;
};

// By value
void func(struct data v1){
  struct data v2 = v1;
  v2.x += 20;
  printf("Dans la fonction appelee\n");
  printf("X: %d\n", v2.x);
  printf("Y: %d\n", v2.y);
}

// By address (reference)
void funcp(struct data* v1){
  struct data* v2 = v1;
  v2->x += 20;
  
  printf("Dans la fonction pointeur appelee\n");
  printf("X: %d\n", v2->x);
  printf("Y: %d\n", v2->y);
  
}

void multiPointer(){
    int num = 10;
    int *ptr = &num;
    int **mptr = &ptr;
    printf("Value of var num = %d\n", num);
    printf("Value of var num = %d\n", *ptr);
    printf("Value of var num = %d\n", **mptr);
    printf("Address of var num = %p\n", &num);
    printf("Address of var num = %p\n", ptr);
    printf("Address of var num = %p\n", *mptr);
    printf("Address of pointer var ptr = %p\n",&ptr);
    printf("Address of pointer var ptr = %p\n",mptr);
    printf("Address of pointer var mptr = %p\n",&mptr);

}


int main() {
    struct node *p;
    int *arrptr;
    int arr[10];
    arrptr = arr;
    
    printf("Size of pointer variable (struct *node) = %zu\n", sizeof(struct node*));
    printf("Size of pointer variable pointing to int array = %zu\n", sizeof(arrptr));


    struct data var;
    var.x = 10;
    var.y = 20;
    
    func(var);
    
    printf("------------------------\n");
    printf("Dans la fonction appelante \n");
    printf("Var.X: %d\n", var.x);
    printf("------------------------\n");
    
    
    funcp(&var);
    
    printf("------------------------\n");
    printf("Dans la fonction appelante \n");
    printf("Var.X: %d\n", var.x);


    //// Pointer to a constant variable ////
    int num1 = 10;
    int num2 = 20;
    int* const ptr1 = &num1; //Initialization of const ptr
    // ptr1 = &num2; (Error: cannot change the address of a constant pointer)
    printf("Value stored at pointer(%p) = %d\n",ptr1, *ptr1);

    // But I can do this:
    int* ptr2 = &num1;
    *ptr2 = 13; // Changing the value pointed to by ptr2
    printf("Value stored at pointer(%p) = %d\n", ptr2, num1);

    //// Constant pointer to a constant variable ////
    int num3 = 10;
    int num4 = 20;
    const int* const ptr3 = &num3; // Initialization of constant pointer to constant variable
    // *ptr3 = 15; (Error: cannot change the value pointed to by a constant pointer)
    printf("Value stored at constant pointer(%p) = %d\n", ptr3, *ptr3);
    // ptr3 = &num4; (Error: cannot change the address of a constant pointer)
    printf("Value stored at constant pointer(%p) = %d\n", ptr3, num3);
    // But I can do this:
    int num5 = 10;
    const int* ptr4 = &num5; // Initialization of constant pointer
    num5 = 15; // Changing the value of num5
    printf("Value stored at constant pointer(%p) = %d\n", ptr4, *ptr4);
    // ptr4 = &num3; (Error: cannot change the address of a constant pointer)
    printf("Value stored at constant pointer(%p) = %d\n", ptr4, num5);
    

    /* MULTI POINTER FONCTION CALL */
    multiPointer();

    return 0;
}

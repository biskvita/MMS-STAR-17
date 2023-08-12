#include "stack-list.h"

int main()
{
    StackList* stack = init_stack_list();

    push((Data){1}, stack);
    push((Data){2}, stack);
    push((Data){3}, stack);
    push((Data){4}, stack);
    push((Data){5}, stack);

    print_stack(stack);

    pop(stack);
    print_stack(stack);

    deinit_stack_list(stack);
    return 0; 
}
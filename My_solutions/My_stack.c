#include <stdio.h>

struct Stack{
  
  int top;
  int capacity;
  int *arr;
    
};

int createStack(int capacity){
    
    struct Stack *stack = (struct stack*) malloc(sizeof(struct Stack));
    stack->arr = (int*)malloc(sizeof(int)*capacity);
    stack->top = 0;
    stack->capacity = capacity;
    
}

int isFull(struct Stack *stack){
    if(stack->top == stack->capacity){
        return 1;
    }
    return 0;
}

int isEmpty(struct Stack *stack){
    
    if(stack->top == 0){
        return 1;
    }
    return 0;
}

int stack_PUSH(struct Stack *stack, int a){
    
    if(isFull(stack)){
        printf("Cant push, stack is full!");
        return 0;
    }
    
    stack->arr[stack->top] = a;
    stack->top++;
    return 1;
}

int stack_POP(struct Stack *stack){
    if(!isEmpty(stack)){
        stack->top--;
        return stack->arr[stack->top];
    }
    return -1;
}

int return_top(struct Stack *stack){
    return stack->top;
}

int main()
{
    
    struct Stack *stack = createStack(10);
    
    stack_PUSH(stack, 3);
    stack_PUSH(stack, 4);
    stack_PUSH(stack, 5);
    stack_PUSH(stack, 7);
    
    for(int i = 0; i < stack->top; i++){
        printf("%d\n", stack->arr[i]);
    }
    
    printf("\n\n");
    stack_POP(stack);
    stack_POP(stack);
    
    for(int i = 0; i < stack->top; i++){
        printf("%d\n", stack->arr[i]);
    }
    
    int top = return_top(stack);
    printf("\n\n%d",top);
    return 0;
}

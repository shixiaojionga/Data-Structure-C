#include <stdio.h>
#include <stdlib.h>

#define Eletype int

typedef struct Node{
    Eletype data;
    struct Node *next;
}Node;

typedef struct{
    Node *head;
    size_t size;
}LiStack;

void StackCreate(LiStack *stk){
    stk->head = NULL;
    stk->size = 0;
}

void StackDestory(LiStack *stk){
    while (stk->head){
        Node *next = stk->head->next;
        free(stk->head);
        stk->head = next;
    }
    stk->size = 0;
}

void StackPush(LiStack *stk, Eletype element){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = element;
    newNode->next = stk->head;
    stk->head = newNode;//链表头加法
    stk->size++;
}

Eletype StackPop(LiStack *stk){
    if(stk->size == 0){
        printf("Stack undefflow\n");
        exit(1);
    }
    Eletype result = stk->head->data;
    Node *next = stk->head->next;
    free(stk->head);
    stk->head = next;
    stk->size--;
    return result;
}

Eletype StackTop(LiStack *stk){
    if(stk->size == 0){
        printf("Stack is empty\n");
        exit(1);
    }
    return stk->head->data;
}

int StackSize(LiStack *stk){
    return stk->size;
}

int main(){
    LiStack stk;
    StackCreate(&stk);
    StackPush(&stk, 10);
    StackPush(&stk, 20);
    StackPush(&stk, 30);
    printf("StackTop is %d\n", StackTop(&stk));
    printf("Stack pop %d\n", StackPop(&stk));
    printf("Stack Size is %d\n", StackSize(&stk));
    StackDestory(&stk);

    return 0;
}

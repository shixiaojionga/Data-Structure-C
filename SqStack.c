#include <stdio.h>
#include <stdlib.h>

#define Eletype int

typedef struct{
    Eletype *elements;
    size_t size;
    size_t capacity;
}SqStack;

void StackCreate(SqStack *stk){
    stk->elements = (Eletype *)malloc(sizeof(Eletype) * 8);
    stk->size = 0;
    stk->capacity = 8;//初始容量为8
}

void StackDestory(SqStack *stk){
    free(stk->elements);
    stk->elements = NULL;
    stk->size = 0;
    stk->capacity = 0;
}

void StackResize(SqStack *stk){
    Eletype *Newelements = (Eletype *)realloc(stk->elements, sizeof(Eletype) * stk->capacity * 2);
    stk->elements = Newelements;
    stk->capacity *= 2;//将容量翻倍
}

void StackPush(SqStack *stk, Eletype element){
    if(stk->size == stk->capacity){
        StackResize(stk);
    }
    stk->elements[stk->size++] = element;//在最后一位插入element同时将长度加一
}

Eletype StackPop(SqStack *stk){
    if(stk->size == 0){
        printf("Stack underflow\n");
        exit(1);//终止程序，将状态设置为1表示程序因错误而退出
    }
    return stk->elements[--stk->size];//得到size-1位置的元素并将size-1
}

Eletype StackTop(SqStack * stk){
    if(stk->size == 0){
        printf("Stack is empty\n");
        exit(1);
    }
    return stk->elements[stk->size - 1];
}

int StackSize(SqStack *stk){
    return stk->size;
}

int main(){
    SqStack stk;
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

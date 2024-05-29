#include<stdio.h>
#include<stdlib.h>

#define Eletype int

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

//以上是栈的模版

typedef struct{
    SqStack s1;
    SqStack s2;
}StQueue;

StQueue *StQueueCreate(){
    StQueue *obj = (StQueue *)malloc(sizeof(StQueue));
    StackCreate(&obj->s1);
    StackCreate(&obj->s2);
    return obj;
}

void StQueuePush(StQueue *obj, Eletype x){
    StackPush(&obj->s1, x);
}

Eletype StQueuePop(StQueue *obj){
    if(StackSize(&obj->s2) == 0){
        while(StackSize(&obj->s1)){
            StackPush(&obj->s2, StackPop(&obj->s1));
        }
    }
    return StackPop(&obj->s2);
}

Eletype StQueueTop(StQueue *obj){
    if(StackSize(&obj->s2) == 0){
        while(StackSize(&obj->s1)){
            StackPush(&obj->s2, StackPop(&obj->s1));
        }
    }
    return StackTop(&obj->s2);
}

int StQueueEmpty(StQueue *obj){
    return StackSize(&obj->s1) + StackSize(&obj->s2) == 0;
}

void StQueueFree(StQueue *obj){
    StackDestory(&obj->s1);
    StackDestory(&obj->s2);
}

int main(){
    StQueue *q = StQueueCreate();

    StQueuePush(q, 10);
    StQueuePush(q, 20);
    StQueuePush(q, 30);

    while(!StQueueEmpty(q)){
        printf("%d\n", StQueueTop(q));
        StQueuePop(q);
    }
    StQueueFree(q);

    return 0;
}
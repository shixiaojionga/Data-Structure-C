#include<stdio.h>
#include<stdlib.h>

#define Eletype int

typedef struct{
    Eletype *elements;
    size_t front;
    size_t rear;
    size_t capacity;
}SqQueue;

void QueueCreate(SqQueue *q){
    q->elements = (Eletype *)malloc(sizeof(Eletype) * 8);
    q->front = 0;
    q->rear = 0;
    q->capacity = 8;
}

void QueueDestory(SqQueue *q){
    free(q->elements);
    q->front = 0;
    q->rear = 0;
    q->capacity = 0;
    q->elements = NULL;
}

void QueueResize(SqQueue *q){
    Eletype *newElements = (Eletype *)realloc(q->elements, sizeof(Eletype) * q->capacity * 2);
    if(newElements == NULL){
        exit(1);
    }
    q->elements = newElements;
    q->capacity *= 2;
}

void QueuePush(SqQueue *q, Eletype element){
    if(q->rear == q->capacity){
        QueueResize(q);
    }
    q->elements[q->rear++] = element;
}

Eletype QueuePop(SqQueue *q){
    if(q->front == q->rear){
        printf("Queue is empty\n");
        exit(1);
    }
    return q->elements[q->front++];
}

Eletype QueueFront(SqQueue *q){
    if(q->front == q->rear){
        printf("Queue is empty\n");
        exit(1);
    }
    return q->elements[q->front];
}

size_t QueueSize(SqQueue *q){
    return q->rear - q->front;
}

//以上是队列的模版

typedef struct{
    SqQueue q1;
    SqQueue q2;
}QuStack;

QuStack *QuStackCreate(){
    QuStack *obj = (QuStack *)malloc(sizeof(QuStack));
    QueueCreate(&obj->q1);
    QueueCreate(&obj->q2);
    return obj;
}

void QuStackPush(QuStack *obj, Eletype x){
    QueuePush(&obj->q1, x);
}

Eletype QuStackPop(QuStack *obj){
    while(QueueSize(&obj->q1) > 1){
        QueuePush(&obj->q2, QueuePop(&obj->q1));
    }
    Eletype result = QueuePop(&obj->q1);
    while(QueueSize(&obj->q2) > 0){
        QueuePush(&obj->q1, QueuePop(&obj->q2));
    }
    return result;
}

Eletype QuStackTop(QuStack *obj){
    while(QueueSize(&obj->q1) > 1){
        QueuePush(&obj->q2, QueuePop(&obj->q1));
    }
    Eletype result = QueuePop(&obj->q1);
    QueuePush(&obj->q2, result);
    while(QueueSize(&obj->q2) > 0){
        QueuePush(&obj->q1, QueuePop(&obj->q2));
    }
    return result;
}

int QuStackEmpty(QuStack *obj){
    return QueueSize(&obj->q1) == 0;
}

void QuStackFree(QuStack *obj){
    QueueDestory(&obj->q1);
    QueueDestory(&obj->q2);
}

int main(){
    QuStack *stk = QuStackCreate();
    QuStackPush(stk, 10);
    QuStackPush(stk, 20);
    QuStackPush(stk, 30);
    while(!QuStackEmpty(stk)){
        printf("%d\n", QuStackTop(stk));
        QuStackPop(stk);
    }
    QuStackFree(stk);
    return 0;
}
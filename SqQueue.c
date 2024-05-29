#include <stdio.h>
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

int main(){
    SqQueue q;
    QueueCreate(&q);
    QueuePush(&q, 10);
    QueuePush(&q, 20);
    QueuePush(&q, 30);
    printf("Queue Pop %d\n", QueuePop(&q));
    printf("Queue Front %d\n", QueueFront(&q));
    printf("Queue Size %d\n", QueueSize(&q));
    QueueDestory(&q);

    return 0;
}
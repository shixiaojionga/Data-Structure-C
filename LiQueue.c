#include <stdio.h>
#include <stdlib.h>

#define Eletype int

typedef struct Node{
    Eletype data;
    struct Node *next;
}Node;

typedef struct{
    Node *front;
    Node *rear;
    size_t size;
}LiQueue;

void QueueCreate(LiQueue *q){
    q->front = q->rear = NULL;
    q->size = 0;
}

void QueueDestory(LiQueue *q){
    while(q->front){
        Node *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
    q->size = 0;
}

void QueuePush(LiQueue *q, Eletype element){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = element;
    newNode->next = NULL;

    if(q->rear == NULL){
        q->front = q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

Eletype QueuePop(LiQueue *q){
    if(q->front == NULL){
        printf("Queue is empty\n");
        exit(1);
    }
    Eletype element = q->front->data;
    Node *temp = q->front;
    q->front = q->front->next;
    free(temp);
    q->size--;
    if(q->size == 0){
        q->rear = NULL;
    }
    return element;
}

Eletype QueueFront(LiQueue *q){
    if(q->front == NULL){
        printf("Queue is empty\n");
        exit(1);
    }
    return q->front->data;
}

size_t QueueSize(LiQueue *q){
    return q->size;
}

int main(){
    LiQueue q;
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
#include<stdio.h>
#include<stdlib.h>

typedef struct EdgeNode{
    int vertex;//边的结尾顶点
    int weight;//边的权重
    struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode{
    int vertex;//边的起始顶点
    EdgeNode* firstEdge;
}VertexNode;

typedef struct{
    int vertices;
    VertexNode* nodes;
}Graph;

void GraphCreate(Graph* g, int vertices){
    g->vertices = vertices;
    g->nodes = (VertexNode*)malloc(sizeof(VertexNode) * vertices);
    for(int i = 0; i < vertices; i ++){
        g->nodes[i].vertex = i;
        g->nodes[i].firstEdge = NULL;
    }
}

void GraphDestory(Graph* g){
    for(int i = 0; i < g->vertices; i ++){
        EdgeNode* curr = g->nodes[i].firstEdge;
        while(curr){
            EdgeNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->nodes);
    g->nodes = NULL;
}

void GraphAddedge(Graph* g, int u, int v, int w){
    EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = g->nodes[u].firstEdge;
    g->nodes[u].firstEdge = newNode;
}

void GraphPrint(Graph* g){
    for(int i = 0; i < g->vertices; i++){
        EdgeNode* curr = g->nodes[i].firstEdge;
        printf("Vertex %d:", i);
        while(curr){
            printf("%d(%d)", curr->vertex, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main(){
    Graph g;
    GraphCreate(&g, 5);

    GraphAddedge(&g, 0, 1, 4);
    GraphAddedge(&g, 0, 2, 2);
    GraphAddedge(&g, 1, 2, 3);
    GraphAddedge(&g, 2, 3, 4);
    GraphAddedge(&g, 3, 4, 2);

    GraphPrint(&g);
    GraphDestory(&g);

    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#define inf 0

typedef struct Graph{
    int vertices;//图的顶点数目
    int** edges;//二级指针
}Graph;

void GraphCreate(Graph* g, int vertices){
    g->vertices = vertices;
    g->edges = (int**)malloc(sizeof(int*) * vertices);
    for (int i = 0; i < vertices; i++){
        g->edges[i] = (int*)malloc(sizeof(int) * vertices);
        for(int j = 0; j < vertices; j++){
            g->edges[i][j] = inf;
        }
    }
}

void GraphDestory(Graph* g){
    for(int i = 0; i < g->vertices; i ++){
        free(g->edges[i]);
    }
    free(g->edges);
    g->edges = NULL;
}

void GraphAddedge(Graph* g, int u, int v, int w){
    g->edges[u][v] = w;
}

void GraphPrint(Graph* g){
    for(int i = 0; i < g->vertices; i++){
        for(int j = 0; j < g->vertices; j++){
            printf("%d\t", g->edges[i][j]);
        }
        printf("\n");
    }
}

int main(){
    Graph graph;

    GraphCreate(&graph, 5);

    GraphAddedge(&graph, 0, 1, 1);
    GraphAddedge(&graph, 0, 2, 3);
    GraphAddedge(&graph, 1, 2, 2);
    GraphAddedge(&graph, 2, 3, 7);
    GraphAddedge(&graph, 3, 4, 9);
    GraphAddedge(&graph, 4, 0, 4);
    GraphAddedge(&graph, 4, 2, 5);

    GraphPrint(&graph);
    GraphDestory(&graph);
    return 0;
}
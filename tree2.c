#include<stdio.h>
#include<stdlib.h>

#define Eletype char

typedef struct TreeNode{
    Eletype val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef struct Tree2{
    TreeNode* nodes;
    TreeNode* root;
    size_t Nodesize;
}Tree2;

void TreeInit(Tree2* t, int size){
    t->Nodesize = size;
    t->nodes = (TreeNode*)malloc(sizeof(TreeNode)*size);
    t->root = NULL;
}

void TreeDestory(Tree2* t){
    free(t->nodes);
    t->nodes = NULL;
    t->Nodesize = 0;
    t->root = NULL;
}

TreeNode* TreeGetNode(Tree2* t, int id){
    return &t->nodes[id];
}

void visit(TreeNode* node){
    printf("%c", node->val);
}

TreeNode* CreateRecursively(Tree2* t, Eletype a[], int size, int nodeID, Eletype nullNode){
    if(nodeID >= size || a[nodeID] == nullNode){
        return NULL;
    }
    TreeNode* nowNode = TreeGetNode(t, nodeID);
    nowNode->val = a[nodeID];
    nowNode->left = CreateRecursively(t, a, size, nodeID*2, nullNode);
    nowNode->right = CreateRecursively(t, a, size, nodeID*2 + 1, nullNode);
    return nowNode;
}

void TreeCreate(Tree2* t, Eletype a[], int size, char nullNode){
    t->root = CreateRecursively(t, a, size, 1, nullNode);
}

void preOrder(Tree2* t, TreeNode* node){
    if(node){
        visit(node);
        preOrder(t, node->left);
        preOrder(t, node->right);
    }
}

void TreePreOrderTraversal(Tree2* t){
    preOrder(t, t->root);
}

void inOrder(Tree2* t, TreeNode* node){
    if(node){
        inOrder(t, node->left);
        visit(node);
        inOrder(t, node->right);
    }
}

void TreeInOrderTraversal(Tree2* t){
    inOrder(t, t->root);
}

void postOrder(Tree2* t, TreeNode* node){
    if(node){
        postOrder(t, node->left);
        postOrder(t, node->right);
        visit(node);
    }
}

void TreePostOrderTraversal(Tree2* t){
    postOrder(t, t->root);
}

int main(){
    const char nullNode = '-';
    char a[15] = {nullNode, 'a', 'b', 'c', 'd', nullNode, 'e', 'f', 'g', 'h', nullNode, nullNode, nullNode, nullNode, 'i'};
    Tree2 T;
    TreeInit(&T, 15);
    TreeCreate(&T, a, 15, nullNode);
    TreePreOrderTraversal(&T);printf("\n");
    TreeInOrderTraversal(&T);printf("\n");
    TreePostOrderTraversal(&T);printf("\n");

    TreeDestory(&T);
    return 0;
}
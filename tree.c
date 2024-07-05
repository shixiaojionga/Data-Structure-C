#include<stdio.h>
#include<stdlib.h>
#define Eletype char

struct TreeNode;

typedef struct ListNode{//由于树的每个节点都有若干个子节点，因此采用表来存储它的子节点
    struct TreeNode* data;//树的节点
    struct ListNode* next;//下一个子节点
}ListNode;

typedef struct TreeNode{
    Eletype data;
    ListNode* ChildrenHead;//该节点的所有孩子节点组成的链表，这里指向第一个子节点
}TreeNode;

void AddTreeChild(TreeNode* parent, TreeNode* child){
    ListNode* childNode = (ListNode*)malloc(sizeof(ListNode));
    childNode->next = NULL;
    childNode->data = child;

    if(parent->ChildrenHead == NULL){
        parent->ChildrenHead = childNode;
    }
    else{
        childNode->next = parent->ChildrenHead;
        parent->ChildrenHead = childNode;
    }
}

typedef struct Tree{
    TreeNode* Nodes;
    TreeNode* root;
}Tree;

void TreeCreate(Tree* t, int size){
    t->Nodes = (TreeNode*)malloc(sizeof(TreeNode)*size);
    t->root = NULL;
}

void TreeDestory(Tree* t){
    free(t->Nodes);
    t->Nodes = NULL;
    t->root = NULL;
}

TreeNode* TreeGetNode(Tree* t, int id){
    return &t->Nodes[id];
}

void TreeSetRoot(Tree* t, int id){
    t->root = TreeGetNode(t, id);
}

void TreeAddChild(Tree* t, int parentid, int childid){
    TreeNode* parentNode = TreeGetNode(t, parentid);
    TreeNode* childNode = TreeGetNode(t, childid);
    AddTreeChild(parentNode, childNode);
}

void TreeAssignData(Tree* t, int id, Eletype data){
    TreeGetNode(t, id)->data = data;
    TreeGetNode(t, id)->ChildrenHead = NULL;
}

void TreePrint(Tree* t, TreeNode* node){
    if(node == NULL){
        node = t->root;
    }
    printf("%c", node->data);
    ListNode* tmp = node->ChildrenHead;
    while (tmp){
        TreePrint(t, tmp->data);
        tmp = tmp->next;
    }
}

int main(){
    Tree T;

    TreeCreate(&T, 9);
    TreeSetRoot(&T, 0);
    TreeAssignData(&T, 0, 'a');
    TreeAssignData(&T, 1, 'b');
    TreeAssignData(&T, 2, 'c');
    TreeAssignData(&T, 3, 'd');
    TreeAssignData(&T, 4, 'e');
    TreeAssignData(&T, 5, 'f');
    TreeAssignData(&T, 6, 'g');
    TreeAssignData(&T, 7, 'h');
    TreeAssignData(&T, 8, 'i');

    TreeAddChild(&T, 0, 2);
    TreeAddChild(&T, 0, 1);
    TreeAddChild(&T, 1, 3);
    TreeAddChild(&T, 2, 5);
    TreeAddChild(&T, 2, 4);
    TreeAddChild(&T, 3, 8);
    TreeAddChild(&T, 3, 7);
    TreeAddChild(&T, 3, 6);

    TreePrint(&T, T.root);

    return 0;
}
#include<stdio.h>
#include<stdlib.h>

#define Eletype int
#define bool int

typedef struct TreeNode{
    Eletype val;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef struct BinarySearchTree{
    TreeNode* root;
}BinarySearchTree;

void BSTCreate(BinarySearchTree* t){
    t->root = NULL;
}

void BSTRemove(BinarySearchTree* t, Eletype value);

void BSTDestory(BinarySearchTree* t){
    while(t->root){
        BSTRemove(t, t->root->val);
    }
}

TreeNode* InsertNode(BinarySearchTree* t, TreeNode* node, Eletype value){//node为要插入的子树的根节点
    if(node == NULL){
        TreeNode* tn = (TreeNode*)malloc(sizeof(TreeNode));
        tn->val = value;
        tn->left = NULL;
        tn->right = NULL;
        return tn;
    }
    if(value < node->val){
        node->left = InsertNode(t, node->left, value);
    }else if(value > node->val){
        node->right = InsertNode(t, node->right, value);
    }
    return node;
}

void BSTInsert(BinarySearchTree* t, Eletype value){
    t->root = InsertNode(t, t->root, value);
}

TreeNode* RemoveNode(BinarySearchTree* t, TreeNode* node, Eletype value){
    if(node == NULL){
        return NULL;
    }
    if(value < node->val){
        node->left = RemoveNode(t, node->left, value);
    }else if(value > node->val){
        node->right = RemoveNode(t, node->right, value);
    }else{
        if(node->left == NULL && node->right == NULL){
            free(node);
            node = NULL;
            return NULL;
        }else if(node->left == NULL){
            TreeNode* RightChild = node->right;
            free(node);
            node = RightChild;
            return node;
        }else if(node->right == NULL){
            TreeNode* LeftChild = node->left;
            free(node);
            node = LeftChild;
            return node;
        }else{
            TreeNode* Replacement = node->right;
            while(Replacement->left){
                Replacement = Replacement->left;
            }
            node->val = Replacement->val;
            node->right = RemoveNode(t, node->right, Replacement->val);
        }
    }
    return node;
}

void BSTRemove(BinarySearchTree* t, Eletype value){
    t->root = RemoveNode(t, t->root, value);
}

bool SearchNode(BinarySearchTree* t, TreeNode* node, Eletype value){
    if(node == NULL){
        return 0;
    }
    if(value < node->val){
        return SearchNode(t, node->left, value);
    }else if(value > node->val){
        return SearchNode(t, node->right, value);
    }else{
        return 1;
    }
}

bool BSTSearch(BinarySearchTree* t, Eletype value){
    return SearchNode(t, t->root, value);
}

void InOrder(BinarySearchTree* t, TreeNode* node){
    if(node){
        InOrder(t, node->left);
        printf("%d,", node->val);
        InOrder(t, node->right);
    }
}

void BSTInOrderTraversal(BinarySearchTree* t){
    InOrder(t, t->root);
    printf("\n");
}

int main(){
    BinarySearchTree bst;
    BSTCreate(&bst);

    BSTInsert(&bst, 50);
    BSTInsert(&bst, 30);
    BSTInsert(&bst, 70);
    BSTInsert(&bst, 40);
    BSTInsert(&bst, 80);
    BSTInsert(&bst, 60);
    BSTInsert(&bst, 100);

    BSTInOrderTraversal(&bst);
    printf("%d\n", BSTSearch(&bst, 100));
    printf("%d\n", BSTSearch(&bst, 110));

    BSTRemove(&bst, 70);
    BSTInOrderTraversal(&bst);
    BSTInsert(&bst, 50);

    BSTInOrderTraversal(&bst);
    return 0;

}
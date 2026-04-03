#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

struct node
{
    int data;
    node* leftChild;
    node* rightChild;

    node(int value);
};

class BST
{
    public:
        node* root;

        BST();
        ~BST();
        void clearTree(node* current);

        void insertNode(node*& root, int data);
        node* searchNode(node*& root, int data);
        void deleteNode(node*& root, int data);

        void preorder(node* root);
        void inorder(node* root);
        void postorder(node* root);

        void printTree(node* root, int space);

        int height(node* root);
        int countNodes(node* root);
        string isBalanced(node* root);
        void BFS(node* root);
};

#endif

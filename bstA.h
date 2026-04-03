#ifndef BSTA_H
#define BSTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>
#include <queue>

using namespace std;

class BST
{
    private:
        int* tree;
        int capacity;

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

        void insertRhelper(int index, int data);
        bool searchRhelper(int index, int data);

        int heightHelper(int index);
        int countNodesHelper(int index);
        void moveSubtree(int fromIndex, int toIndex);
        int minValueIndex(int index);

    public:
        BST(int size);
        ~BST();

        void insertI(int data);
        void insertR(int data);

        bool searchI(int data);
        bool searchR(int data);

        void preorder(int index = 0);
        void inorder(int index = 0);
        void postorder(int index = 0);

        void printTree(int index, int depth);

        int height();
        int countNodes();
        string isBalanced();
        void deleteNode(int data);
        void BFS();
};

#endif

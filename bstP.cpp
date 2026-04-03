#include "bstP.h"

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* current)
{
    if(current == nullptr)
        return;

    clearTree(current->leftChild);
    clearTree(current->rightChild);
    delete current;
}

void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }

    if(data < root->data)
    {
        insertNode(root->leftChild, data);
    }
    else if(data > root->data)
    {
        insertNode(root->rightChild, data);
    }
    else
    {
        cout << "Duplicate value ignored: " << data << endl;
    }
}

node* BST::searchNode(node*& root, int data)
{
    if(root == nullptr || root->data == data)
        return root;

    if(data < root->data)
        return searchNode(root->leftChild, data);

    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if(root == nullptr)
        return;

    if(data < root->data)
    {
        deleteNode(root->leftChild, data);
    }
    else if(data > root->data)
    {
        deleteNode(root->rightChild, data);
    }
    else
    {
        if(root->leftChild == nullptr && root->rightChild == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if(root->leftChild == nullptr)
        {
            node* temp = root;
            root = root->rightChild;
            delete temp;
        }
        else if(root->rightChild == nullptr)
        {
            node* temp = root;
            root = root->leftChild;
            delete temp;
        }
        else
        {
            node* temp = root->rightChild;
            while(temp->leftChild != nullptr)
            {
                temp = temp->leftChild;
            }

            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if(root == nullptr)
        return;

    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if(root == nullptr)
        return;

    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if(root == nullptr)
        return;

    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}

void BST::printTree(node* root, int space)
{
    const int COUNT = 10;

    if(root == nullptr)
        return;

    space += COUNT;

    printTree(root->rightChild, space);

    for(int i = COUNT; i < space; i++)
        cout << " ";

    cout << root->data << endl;

    printTree(root->leftChild, space);
}

int BST::height(node* root)
{
    if(root == nullptr)
        return -1;

    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);

    if(leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int BST::countNodes(node* root)
{
    if(root == nullptr)
        return 0;

    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);
}

string BST::isBalanced(node* root)
{
    if(root == nullptr)
        return "Yes";

    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);

    if(leftHeight - rightHeight > 1)
        return "Left-heavy";
    else if(rightHeight - leftHeight > 1)
        return "Right-heavy";
    else
        return "Yes";
}

void BST::BFS(node* root)
{
    if(root == nullptr)
        return;

    queue<node*> q;
    q.push(root);

    while(!q.empty())
    {
        node* current = q.front();
        q.pop();

        cout << current->data << " ";

        if(current->leftChild != nullptr)
            q.push(current->leftChild);

        if(current->rightChild != nullptr)
            q.push(current->rightChild);
    }
}

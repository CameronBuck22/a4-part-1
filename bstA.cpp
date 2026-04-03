#include "bstA.h"

BST::BST(int size)
{
    capacity = size;
    tree = new int[capacity];

    for(int i = 0; i < capacity; i++)
        tree[i] = INT_MIN;
}

BST::~BST()
{
    delete[] tree;
}

int BST::leftChild(int index)
{
    return 2 * index + 1;
}

int BST::rightChild(int index)
{
    return 2 * index + 2;
}

int BST::parent(int index)
{
    return (index - 1) / 2;
}

void BST::insertI(int data)
{
    if(tree[0] == INT_MIN)
    {
        tree[0] = data;
        return;
    }

    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == data)
        {
            cout << "Duplicate value ignored: " << data << endl;
            return;
        }

        if(data < tree[index])
        {
            int left = leftChild(index);

            if(left >= capacity)
                return;

            if(tree[left] == INT_MIN)
            {
                tree[left] = data;
                return;
            }

            index = left;
        }
        else
        {
            int right = rightChild(index);

            if(right >= capacity)
                return;

            if(tree[right] == INT_MIN)
            {
                tree[right] = data;
                return;
            }

            index = right;
        }
    }
}

void BST::insertR(int data)
{
    insertRhelper(0, data);
}

void BST::insertRhelper(int index, int data)
{
    if(index >= capacity)
        return;

    if(tree[index] == INT_MIN)
    {
        tree[index] = data;
        return;
    }

    if(tree[index] == data)
    {
        cout << "Duplicate value ignored: " << data << endl;
        return;
    }

    if(data < tree[index])
        insertRhelper(leftChild(index), data);
    else
        insertRhelper(rightChild(index), data);
}

bool BST::searchI(int data)
{
    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == INT_MIN)
            return false;

        if(tree[index] == data)
            return true;

        if(data < tree[index])
            index = leftChild(index);
        else
            index = rightChild(index);
    }

    return false;
}

bool BST::searchR(int data)
{
    return searchRhelper(0, data);
}

bool BST::searchRhelper(int index, int data)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return false;

    if(tree[index] == data)
        return true;

    if(data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

void BST::preorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}

void BST::inorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));
}

void BST::postorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    postorder(leftChild(index));
    postorder(rightChild(index));
    cout << tree[index] << " ";
}

void BST::printTree(int index, int depth)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    printTree(rightChild(index), depth + 1);

    for(int i = 0; i < depth; i++)
        cout << "   ";

    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
}

int BST::heightHelper(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return -1;

    int leftHeight = heightHelper(leftChild(index));
    int rightHeight = heightHelper(rightChild(index));

    if(leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int BST::height()
{
    return heightHelper(0);
}

int BST::countNodesHelper(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return 0;

    return 1 + countNodesHelper(leftChild(index)) + countNodesHelper(rightChild(index));
}

int BST::countNodes()
{
    return countNodesHelper(0);
}

string BST::isBalanced()
{
    if(tree[0] == INT_MIN)
        return "Yes";

    int leftHeight = heightHelper(leftChild(0));
    int rightHeight = heightHelper(rightChild(0));

    if(leftHeight - rightHeight > 1)
        return "Left-heavy";
    else if(rightHeight - leftHeight > 1)
        return "Right-heavy";
    else
        return "Yes";
}

int BST::minValueIndex(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return -1;

    while(leftChild(index) < capacity && tree[leftChild(index)] != INT_MIN)
    {
        index = leftChild(index);
    }

    return index;
}

void BST::moveSubtree(int fromIndex, int toIndex)
{
    if(toIndex >= capacity)
        return;

    if(fromIndex >= capacity || tree[fromIndex] == INT_MIN)
    {
        tree[toIndex] = INT_MIN;

        int leftTo = leftChild(toIndex);
        int rightTo = rightChild(toIndex);

        if(leftTo < capacity)
            moveSubtree(capacity, leftTo);
        if(rightTo < capacity)
            moveSubtree(capacity, rightTo);

        return;
    }

    tree[toIndex] = tree[fromIndex];

    int fromLeft = leftChild(fromIndex);
    int fromRight = rightChild(fromIndex);
    int toLeft = leftChild(toIndex);
    int toRight = rightChild(toIndex);

    if(toLeft < capacity)
        moveSubtree(fromLeft, toLeft);
    if(toRight < capacity)
        moveSubtree(fromRight, toRight);

    tree[fromIndex] = INT_MIN;
}

void BST::deleteNode(int data)
{
    int index = 0;

    while(index < capacity && tree[index] != INT_MIN)
    {
        if(data == tree[index])
            break;

        if(data < tree[index])
            index = leftChild(index);
        else
            index = rightChild(index);
    }

    if(index >= capacity || tree[index] == INT_MIN)
        return;

    int left = leftChild(index);
    int right = rightChild(index);

    bool hasLeft = (left < capacity && tree[left] != INT_MIN);
    bool hasRight = (right < capacity && tree[right] != INT_MIN);

    if(!hasLeft && !hasRight)
    {
        tree[index] = INT_MIN;
    }
    else if(hasLeft && !hasRight)
    {
        moveSubtree(left, index);
    }
    else if(!hasLeft && hasRight)
    {
        moveSubtree(right, index);
    }
    else
    {
        int successorIndex = minValueIndex(right);
        tree[index] = tree[successorIndex];
        deleteNode(tree[successorIndex]);
    }
}

void BST::BFS()
{
    if(tree[0] == INT_MIN)
        return;

    queue<int> q;
    q.push(0);

    while(!q.empty())
    {
        int current = q.front();
        q.pop();

        if(current >= capacity || tree[current] == INT_MIN)
            continue;

        cout << tree[current] << " ";

        int left = leftChild(current);
        int right = rightChild(current);

        if(left < capacity && tree[left] != INT_MIN)
            q.push(left);

        if(right < capacity && tree[right] != INT_MIN)
            q.push(right);
    }
}

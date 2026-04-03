#include <stdio.h>
#include <stdlib.h>

#define MAXQ 100

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// ---------- CREATE NODE ----------
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------- INSERT (WITH DUP CHECK) ----------
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Duplicate value %d ignored.\n", value);
    }

    return root;
}

// ---------- HEIGHT ----------
int height(Node* root) {
    if (root == NULL) return -1;

    int leftH = height(root->left);
    int rightH = height(root->right);

    return (leftH > rightH ? leftH : rightH) + 1;
}

// ---------- COUNT NODES ----------
int countNodes(Node* root) {
    if (root == NULL) return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ---------- IS BALANCED ----------
char* isBalanced(Node* root) {
    if (root == NULL) return "Yes";

    int leftH = height(root->left);
    int rightH = height(root->right);

    if (leftH - rightH > 1) return "Left-heavy";
    if (rightH - leftH > 1) return "Right-heavy";
    return "Yes";
}

// ---------- QUEUE FOR BFS ----------
typedef struct {
    Node* arr[MAXQ];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int isEmptyQueue(Queue* q) {
    return q->front > q->rear;
}

void enqueue(Queue* q, Node* node) {
    if (q->rear < MAXQ - 1) {
        q->arr[++q->rear] = node;
    }
}

Node* dequeue(Queue* q) {
    if (isEmptyQueue(q)) return NULL;
    return q->arr[q->front++];
}

// ---------- BFS ----------
void BFS(Node* root) {
    if (root == NULL) return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmptyQueue(&q)) {
        Node* current = dequeue(&q);
        printf("%d ", current->data);

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }
}

// ---------- MAIN (TEST) ----------
int main() {
    Node* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Height: %d\n", height(root));
    printf("Total Nodes: %d\n", countNodes(root));
    printf("Balanced: %s\n", isBalanced(root));

    printf("BFS: ");
    BFS(root);
    printf("\n");

    return 0;
}

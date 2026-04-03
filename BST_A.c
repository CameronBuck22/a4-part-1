#include <stdio.h>

#define SIZE 100
#define MAXQ 100

typedef struct {
    int data;
    int left;
    int right;
    int used;
} ArrayNode;

ArrayNode tree[SIZE];
int root = -1;
int nextFree = 0;

// ---------- CREATE NODE ----------
int createArrayNode(int value) {
    if (nextFree >= SIZE) return -1;

    tree[nextFree].data = value;
    tree[nextFree].left = -1;
    tree[nextFree].right = -1;
    tree[nextFree].used = 1;

    return nextFree++;
}

// ---------- INSERT ----------
int insert(int currentRoot, int value) {
    if (currentRoot == -1) return createArrayNode(value);

    if (value < tree[currentRoot].data) {
        tree[currentRoot].left = insert(tree[currentRoot].left, value);
    } else if (value > tree[currentRoot].data) {
        tree[currentRoot].right = insert(tree[currentRoot].right, value);
    } else {
        printf("Duplicate value %d ignored.\n", value);
    }

    return currentRoot;
}

// ---------- HEIGHT ----------
int height(int index) {
    if (index == -1) return -1;

    int leftH = height(tree[index].left);
    int rightH = height(tree[index].right);

    return (leftH > rightH ? leftH : rightH) + 1;
}

// ---------- COUNT ----------
int countNodes(int index) {
    if (index == -1) return 0;

    return 1 + countNodes(tree[index].left) + countNodes(tree[index].right);
}

// ---------- BALANCED ----------
char* isBalanced(int index) {
    if (index == -1) return "Yes";

    int leftH = height(tree[index].left);
    int rightH = height(tree[index].right);

    if (leftH - rightH > 1) return "Left-heavy";
    if (rightH - leftH > 1) return "Right-heavy";
    return "Yes";
}

// ---------- FIND MIN ----------
int findMinIndex(int index) {
    while (tree[index].left != -1) {
        index = tree[index].left;
    }
    return index;
}

// ---------- DELETE ----------
int deleteNode(int index, int value) {
    if (index == -1) return -1;

    if (value < tree[index].data) {
        tree[index].left = deleteNode(tree[index].left, value);
    } else if (value > tree[index].data) {
        tree[index].right = deleteNode(tree[index].right, value);
    } else {
        if (tree[index].left == -1 && tree[index].right == -1) {
            return -1;
        }

        if (tree[index].left == -1) {
            return tree[index].right;
        }

        if (tree[index].right == -1) {
            return tree[index].left;
        }

        int minRight = findMinIndex(tree[index].right);
        tree[index].data = tree[minRight].data;
        tree[index].right = deleteNode(tree[index].right, tree[minRight].data);
    }

    return index;
}

// ---------- QUEUE ----------
typedef struct {
    int arr[MAXQ];
    int front;
    int rear;
} IntQueue;

void initQueue(IntQueue* q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(IntQueue* q) {
    return q->front > q->rear;
}

void enqueue(IntQueue* q, int val) {
    if (q->rear < MAXQ - 1) {
        q->arr[++q->rear] = val;
    }
}

int dequeue(IntQueue* q) {
    if (isEmpty(q)) return -1;
    return q->arr[q->front++];
}

// ---------- BFS ----------
void BFS(int rootIndex) {
    if (rootIndex == -1) return;

    IntQueue q;
    initQueue(&q);
    enqueue(&q, rootIndex);

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d ", tree[current].data);

        if (tree[current].left != -1)
            enqueue(&q, tree[current].left);

        if (tree[current].right != -1)
            enqueue(&q, tree[current].right);
    }
}

// ---------- MAIN ----------
int main() {
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

    root = deleteNode(root, 30);

    printf("After Delete BFS: ");
    BFS(root);
    printf("\n");

    return 0;
}

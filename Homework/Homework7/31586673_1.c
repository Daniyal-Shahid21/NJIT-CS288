#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 4
#define NxN (N * N)
#define TRUE 1
#define FALSE 0

struct node {
    int squares[N][N];
    int f, g, h;
    short zeroRow, zeroColumn;
    struct node *next;
    struct node *parent;
};

int goalRows[NxN];
int goalColumns[NxN];
struct node *start, *goalState;
struct node *open = NULL, *closed = NULL;
struct node *succNodes[4] = {NULL, NULL, NULL, NULL};

void printNode(struct node *pnode) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", pnode->squares[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

struct node *initialize(char **argv) {
    int index, tile;
    struct node *pnode;

    pnode = (struct node *)malloc(sizeof(struct node));
    index = 1;
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            tile = atoi(argv[index++]);
            pnode->squares[j][k] = tile;
            if (tile == 0) {
                pnode->zeroRow = j;
                pnode->zeroColumn = k;
            }
        }
    }
    pnode->f = 0;
    pnode->g = 0;
    pnode->h = 0;
    pnode->next = NULL;
    pnode->parent = NULL;
    start = pnode;
    printf("Initial state:\n");
    printNode(start);

    pnode = (struct node *)malloc(sizeof(struct node));
    goalRows[0] = 3;
    goalColumns[0] = 3;

    for (index = 1; index < NxN; index++) {
        int j = (index - 1) / N;
        int k = (index - 1) % N;
        goalRows[index] = j;
        goalColumns[index] = k;
        pnode->squares[j][k] = index;
    }
    pnode->squares[N - 1][N - 1] = 0;
    pnode->f = 0;
    pnode->g = 0;
    pnode->h = 0;
    pnode->next = NULL;
    goalState = pnode;
    printf("Goal state:\n");
    printNode(goalState);

    return start;
}

void calculateHeuristic(struct node *pnode) {
    pnode->h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int tile = pnode->squares[i][j];
            if (tile != 0) {
                pnode->h += abs(i - goalRows[tile]) + abs(j - goalColumns[tile]);
            }
        }
    }
    pnode->f = pnode->g + pnode->h;
}

void swap(int row1, int col1, int row2, int col2, struct node *pnode) {
    int temp = pnode->squares[row1][col1];
    pnode->squares[row1][col1] = pnode->squares[row2][col2];
    pnode->squares[row2][col2] = temp;
}

void moveBlank(struct node *pnode, int direction) {
    int row = pnode->zeroRow;
    int col = pnode->zeroColumn;
    switch (direction) {
        case 0: swap(row, col, row - 1, col, pnode); pnode->zeroRow--; break;
        case 1: swap(row, col, row + 1, col, pnode); pnode->zeroRow++; break;
        case 2: swap(row, col, row, col - 1, pnode); pnode->zeroColumn--; break;
        case 3: swap(row, col, row, col + 1, pnode); pnode->zeroColumn++; break;
    }
}

void expand(struct node *cnode) {
    int row = cnode->zeroRow, col = cnode->zeroColumn;
    for (int i = 0; i < 4; i++) {
        if ((i == 0 && row > 0) || (i == 1 && row < N - 1) || (i == 2 && col > 0) || (i == 3 && col < N - 1)) {
            struct node *succ = (struct node *)malloc(sizeof(struct node));
            memcpy(succ, cnode, sizeof(struct node));
            moveBlank(succ, i);
            succ->g = cnode->g + 1;
            succ->parent = cnode;
            calculateHeuristic(succ);
            succNodes[i] = succ;
        } else {
            succNodes[i] = NULL;
        }
    }
}

void filter(int i, struct node *pnodeArray) {
    struct node *pnode = succNodes[i];
    if (pnode == NULL) return;

    while (pnodeArray != NULL) {
        if (memcmp(pnode->squares, pnodeArray->squares, sizeof(int) * NxN) == 0) {
            free(succNodes[i]);
            succNodes[i] = NULL;
            return;
        }
        pnodeArray = pnodeArray->next;
    }
}

void mergeOpen() {
    for (int i = 0; i < 4; i++) {
        if (succNodes[i] != NULL) {
            struct node **current = &open;
            while (*current != NULL && (*current)->f <= succNodes[i]->f) {
                current = &((*current)->next);
            }
            succNodes[i]->next = *current;
            *current = succNodes[i];
            succNodes[i] = NULL;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != NxN + 1) {
        printf("Usage: ./puzzle tile0 tile1 ... tile15\n");
        return 1;
    }

    start = initialize(argv);
    open = start;

    int iter = 0;
    while (open != NULL) {
        struct node *copen = open;
        open = open->next;

        if (memcmp(copen->squares, goalState->squares, sizeof(int) * NxN) == 0) {
            struct node *pathNode[1000];
            int pathLen = 0;

            while (copen != NULL) {
                pathNode[pathLen++] = copen;
                copen = copen->parent;
            }

            for (int i = pathLen - 1; i >= 0; i--) {
                printNode(pathNode[i]);
            }

            printf("Solution found!\n");
            printf("Path length: %d\n", pathLen);
            return 0;
        }

        expand(copen);
        for (int i = 0; i < 4; i++) {
            if (succNodes[i] != NULL) {
                filter(i, open);
                filter(i, closed);
            }
        }
        mergeOpen();
        copen->next = closed;
        closed = copen;

        if (++iter % 1000 == 0) {
            printf("Iteration: %d\n", iter);
        }
    }
}

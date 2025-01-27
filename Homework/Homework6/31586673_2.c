#include <stdio.h>
#include <stdlib.h>

struct node{
    int num;
    struct node *next;
};

struct node *createNode(int num){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->num = num;
    newNode->next = NULL;
    return newNode;
}

void bubbleSort(struct node **headRef){
    if (*headRef == NULL){
        return;
    }

    int swapped;
    struct node **curr;
    struct node *temp;
    struct node *prev = NULL;

    do {
        swapped = 0;
        curr = headRef;

        while ((*curr)->next != prev){
            if ((*curr)->num > (*curr)->next->num){
                temp = (*curr)->next;
                (*curr)->next = temp->next;
                temp->next = *curr;
                *curr = temp;
                swapped = 1;
            }
            curr = &(*curr)->next;
        }
        prev = *curr;
    } 
    while (swapped);
}

void printList(const char *title, struct node *head){
    printf("%s\n", title);
    struct node *temp = head;
    while (temp != NULL){
        printf("Data = %d\n", temp->num);
        temp = temp->next;
    }
}

int main(){
    struct node *head = NULL;
    struct node *tail = NULL;
    struct node *temp;
    int num;
    int nodeCount = 1;

    printf("Please enter integers to create the linked list (press Ctrl+d to finalize):\n");

    while (1){
        printf("Input data for node %d : ", nodeCount);
        if (scanf("%d", &num) == EOF) {
            break;
        }
        temp = createNode(num);
        if (head == NULL) {
            head = tail = temp;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
        nodeCount++;
    }

    printList("\nData entered in the list are:", head);

    bubbleSort(&head);

    printList("\nThe list in order are:", head);

    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

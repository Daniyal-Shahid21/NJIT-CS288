#include <stdio.h>
#include <stdlib.h>

struct node {
    int num;
    struct node *next;
};

struct node *createNode(int num){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL){
        printf("Memory allocation failed.\n");
        exit(0);
    }
    newNode->num = num;
    newNode->next = NULL;
    return newNode;
}

struct node *reverseList(struct node *head){
    struct node *reversed = NULL;
    struct node *temp;

    while (head != NULL){
        temp = head;
        head = head->next;
        temp->next = reversed;
        reversed = temp;
    }
    return reversed;
}

int main() {
    struct node *head = NULL; 
    struct node *tail = NULL; 
    struct node *temp;
    int num = 1; 
    int nodeCount = 1;

    printf("Please enter integers to create the linked list (press Ctrl+d to finalize):\n");

    while (1){
        printf("Input data for node %d : ", nodeCount);
        if (scanf("%d", &num) == EOF){
            break;
        }
        temp = createNode(num);
        if (head == NULL){
            head = tail = temp;
        } 
        else{
            tail->next = temp;
            tail = temp;
        }
        nodeCount++;
    }

    printf("\nData entered in the list are:\n");
    temp = head;
    while (temp != NULL){
        printf("Data = %d\n", temp->num);
        temp = temp->next;
    }

    struct node *reversed_head = reverseList(head);

    printf("\nThe list in reverse are:\n");
    temp = reversed_head;
    while (temp != NULL){
        printf("Data = %d\n", temp->num);
        temp = temp->next;
    }

    while (reversed_head != NULL){
        temp = reversed_head;
        reversed_head = reversed_head->next;
        free(temp);
    }
    return 0;
}
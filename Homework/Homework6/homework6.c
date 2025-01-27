#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next; //int *ptr
}; 

int main (){
    struct node* node1= malloc(sizeof(struct node));
    node1->data = 5;

    struct node* node2= malloc(sizeof(struct node));
    node2->data = 6;

    node1->next = node2;

    printf("%p\n", *(node1->next));

    return 0;
}
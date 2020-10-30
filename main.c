#include <stdio.h>
#include <stdlib.h>

// Data Structure
struct Node{
    unsigned char bit;
    struct Node *next;
};

void insertNode(struct Node **head, unsigned char data){
    struct Node *newNode= (struct Node*)malloc(sizeof(struct Node));
    newNode->bit = data;
    newNode->next = (*head);
    (*head) = newNode;

}
void printLinkedList(struct Node *head){
    struct Node *ptr = head;
    if (ptr == NULL){
        printf("NULL\n");
        return;
    }
    while ( ptr != NULL){
        printf("%d", ptr->bit);
        ptr = ptr->next;
    }
    printf("\n");
}

void freeNodes(struct Node **head){

    struct Node* ptr = *head;
    struct Node *next;

    while (ptr != NULL){
        next =  ptr->next;
        free(ptr);
        ptr = next;
    }
    *head = NULL;
    //printf("Free completed\n");
}

// Binary Transformations

int main() {



    return 0;
}

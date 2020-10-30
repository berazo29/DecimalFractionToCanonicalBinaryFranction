#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void reverseLinkedList(struct Node **head){
    struct Node *ptr = (*head);
    struct Node *next = NULL;
    struct Node *prev = NULL;

    while (ptr != NULL){
        next = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next;
    }
    (*head) = prev;

}
int linkedListNodeCounter(struct Node *head){
    int counter = 0;

    if ( head == NULL){
        return counter;
    }

    while ( head != NULL){
        counter++;
        head = head->next;
    }
    return counter;
}

// Binary Transformations
int decimalToBinary(unsigned long decimal, struct Node **head){

    int counter = 0;
    unsigned long tmp = decimal;
    unsigned char bit;

    if (decimal < 0){
        return -1;
    }
    if ( decimal == 0 ){
        insertNode(head,0);
        return 1;
    }

    while (tmp != 0){
        bit = tmp % 2;
        tmp = tmp/2;
        insertNode(head,bit);
        counter++;
    }
    return counter;
}
long int binaryToDecimal(struct Node *head){

    int numberNodes = linkedListNodeCounter(head);
    long int result=0;

    while (head != NULL){
        if ( head->bit == 1){
            result += (long int)pow(2,numberNodes-1);
        }
        numberNodes--;
        head = head->next;
    }
    return result;
}
int main() {

    struct Node *ptr = NULL;
    decimalToBinary(1,&ptr);
    printLinkedList(ptr);
    printf("Linked list size:%d\n", linkedListNodeCounter(ptr));
    printf("Decimal:%li\n", binaryToDecimal(ptr));

    freeNodes(&ptr);
    return 0;
}

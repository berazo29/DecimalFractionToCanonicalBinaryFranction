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
void printCanonicalBinaryLinkedList(struct Node *head){
    struct Node *ptr = head;
    if (ptr == NULL){
        printf("NULL\n");
        return;
    }
    while ( ptr != NULL){
        if ( ptr->bit == '.'){
            printf("%c", ptr->bit);
            ptr = ptr->next;
            continue;
        }
        printf("%d", ptr->bit);
        ptr = ptr->next;
    }
    //printf("\n");
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
void fractionToBinary(double value, int approximation, struct Node **head){

    struct Node *ptr = *head;

    int long tmp = (long )(value / 1);
    double fraction = value-(int)tmp;

    for (int i = 0; i < approximation; ++i) {
        fraction = fraction*2;
        tmp = (long )(fraction / 1);
        insertNode(head,tmp);
        fraction = fraction-(int)tmp;
    }

    // Check if the linked list is empty and insert 0
    if ( ptr == NULL){
        insertNode(head,0);
    }
    reverseLinkedList(head);

}
void createCanonicalBinaryFraction(struct Node *integerBinaryList, struct Node *fractionBinaryList,
        int approximation, struct Node **canonicalBinaryList){

    int counter = approximation;

    if (integerBinaryList->bit == 1){
        if (integerBinaryList->bit == 1){
            //printf("%d.",integerBinaryList->bit);

            insertNode(canonicalBinaryList,integerBinaryList->bit);
            insertNode(canonicalBinaryList,'.');
            integerBinaryList = integerBinaryList->next;
            counter--;
        }
        while (integerBinaryList != NULL && counter >= 0){
            //printf("%d",integerBinaryList->bit);
            insertNode(canonicalBinaryList,integerBinaryList->bit);
            integerBinaryList = integerBinaryList->next;
            counter--;
        }
        while (fractionBinaryList != NULL && counter >= 0){
            //printf("%d",fractionBinaryList->bit);
            insertNode(canonicalBinaryList,fractionBinaryList->bit);
            fractionBinaryList = fractionBinaryList->next;
            counter--;
        }

    } else{

        // Find closes 1 bit
        if (integerBinaryList->bit == 0){
            // Find the first one
            while (fractionBinaryList != NULL){
                if (fractionBinaryList->bit == 1){
                    // Insert the first one
                    insertNode(canonicalBinaryList,fractionBinaryList->bit);
                    insertNode(canonicalBinaryList,'.');
                    fractionBinaryList =fractionBinaryList->next;
                    break;
                }
                fractionBinaryList =fractionBinaryList->next;
            }
            //Now make the canonical binary list

            while (fractionBinaryList != NULL && counter >= 0){
                //printf("%d",fractionBinaryList->bit);
                insertNode(canonicalBinaryList,fractionBinaryList->bit);
                fractionBinaryList = fractionBinaryList->next;
                counter--;
            }
            // Populate with zeros if not more notes and need better approximation
            while (counter != 0){
                insertNode(canonicalBinaryList,0);
                counter--;
            }
        }
    }
    reverseLinkedList(canonicalBinaryList);

}
int main( int argc, char *argv[argc+1]) {

    struct Node *integerBinaryList = NULL;
    struct Node *fractionBinaryList = NULL;
    struct Node *canonicalBinaryList = NULL;

    //File name from arguments
    if (argc != 2 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data
    double decimalInput;
    int approximation;

    while ( fscanf( fp, "%lf %d", &decimalInput, &approximation ) != EOF ){

        long int integerPart = (int long)decimalInput / 1;

        //printf("integer %li\n", integerPart);
        //printf("fraction %f\n", decimalInput-integerPart);

        decimalToBinary(integerPart,&integerBinaryList);
        fractionToBinary(decimalInput,approximation,&fractionBinaryList);

        // PRINT LINKED LIST
//        printf("Integer Linked list size:%d\n", linkedListNodeCounter(integerBinaryList));
//        printf("Fraction Linked list size:%d\n", linkedListNodeCounter(fractionBinaryList));
//        printLinkedList(integerBinaryList);
//        printLinkedList(fractionBinaryList);

        createCanonicalBinaryFraction(integerBinaryList, fractionBinaryList, approximation,&canonicalBinaryList);

        // Do this for each
        if (integerBinaryList->bit != 0){
            printCanonicalBinaryLinkedList(canonicalBinaryList);
            int size = linkedListNodeCounter(integerBinaryList);
            printf(" %d\n",size-1);
        } else{
            //printf("Zero first\n");
            //Count until we encounter a 1
            struct Node *ptr = fractionBinaryList;
            int spaceRight=0;
            while (ptr != NULL){
                if (ptr->bit == 1){
                    spaceRight--;
                    break;
                }
                spaceRight--;
                ptr = ptr->next;
            }
            printCanonicalBinaryLinkedList(canonicalBinaryList);
            printf(" %d\n",spaceRight);

        }

        // Free linked list after use;
        freeNodes(&integerBinaryList);
        freeNodes(&fractionBinaryList);
        freeNodes(&canonicalBinaryList);
    }

    // Close the file and destroy memory allocations
    fclose(fp);

    return 0;
}

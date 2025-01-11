#ifndef LINKED_H_INCLUDED
#define LINKED_H_INCLUDED

typedef struct lnode{
    char *word;         //word
    struct lnode *next; //pointer to next lnode
}lnode;

typedef struct{
    lnode *head;    //pointer used to point to first node of linked list
    lnode *tail;    //pointer of type lnode used to point to last node of linked list
}list1;

void init_LL(list1 **L);     //initialize the linked list
void destroy_LL(list1 **L);  //destroy whole linked list
void insertNode(list1 **L, char a);  //insert node in linkedlist
void removeNode(list1 **L);  //remove node from linkedlist
char* getstr(list1 *L);        //get the word



#endif // LINKED_H_INCLUDED

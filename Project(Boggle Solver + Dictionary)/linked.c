#include "linked.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void init_LL(list1 **L){
    *L = (list1*)malloc(sizeof(list1));
    if (*L == NULL)     //check if memory is allocated or not
        return;
    (*L)->head = NULL;  //initially head and tail is pointed to null
    (*L)->tail = NULL;
    return;
}

void insertNode(list1 **L, char a){
    lnode *nn;
    nn = (lnode*)malloc(sizeof(lnode));
    if (nn == NULL)
        return;
    nn->next = NULL;
    if ((*L)->tail == NULL){                    //if no node is present
        nn->word = malloc(sizeof(char)+1);      //allocate the memory for a character and '\0' character
        if (nn->word == NULL)
            return 0;
        nn->word[0] = a;
        nn->word[1] = '\0';
        (*L)->head = nn;
        (*L)->tail = nn;
        return;
    }
    int len = strlen(((*L)->tail)->word);        //take length of tail word
    nn->word = malloc(len + sizeof(char)+1);     //allocate memory of tail word and char and null character
    if(nn->word == NULL)
        return;
    strncpy(nn->word, ((*L)->tail)->word, len); //cpy specified length of string
    nn->word[len] = a;
    nn->word[len + 1] = '\0';
    (*L)->tail->next = nn;
    (*L)->tail = (*L)->tail->next;
    return;
}

void removeNode(list1 **L){
    lnode *c, *p;
    if (*L == NULL){                //Empty linked list
        printf("Attempting to delete from empty list\n");
        return;
    }
    if ((*L)->head == (*L)->tail) {     //when there is only one node i.e first node
        free((*L)->head->word);
        free((*L)->head);
        (*L)->head = NULL;
        (*L)->tail = NULL;
        return;
    }
    c = (*L)->head;
    while(c != (*L)->tail){
        p = c;
        c = c->next;
    }
    free((*L)->tail->word);
    free((*L)->tail);
    (*L)->tail = p;
    (*L)->tail->next = NULL;
    return;
}
void destroy_LL(list1 **L){
    if(*L == NULL)
        return;
    lnode *c, *p;       //this are used to track previous and currend node
    c = (*L)->head;
    while (c != NULL){
        free(c->word);
        p = c;
        c = c->next;
        free(p);
    }
    free(*L);
    *L = NULL;
    return;
}

char* getstr(list1 *L){
    return L->tail->word;                   //valid word present in boggle
}

#include"Array.h"
#include<stdio.h>
#include<stdlib.h>

int r,c;
void modifysize(int a,int b){   //this will update the size of the array

    r = a;
    c = b;
    return;
}

int position(int b, int a){      //return index
    return c*b+a;
}

int create_Set(Set** h){        //create the array of size width square and initialize with zero
    *h = (Set*)malloc(sizeof(Set));
    if((*h) == NULL)
        return 0;
    (*h)->arr = (int*)calloc(r*c, sizeof(int));
    if((*h)->arr == NULL)
        return 0;
    return 1;
}

void destroy_Set(Set** h){      //deallocates the memory allocated by set
    free((*h)->arr);
    free(*h);
    return;
}
void insert_val(Set** h,int x,int y){
    if((*h)->arr[position(x,y)] == 0){   //if the value at that index is used then we cannot use it again
        (*h)->arr[position(x,y)] = 1;
        return;
    }
    return;
}

int find(Set* h,int x,int y){       //check is letter is already set
    return h->arr[position(x,y)];
}

void remove_val(Set** h,int x,int y){   //reassigns the value at index to 0
    if((*h)->arr[position(x,y)] == 1){
        (*h)->arr[position(x,y)] = 0;
        return;
    }
    return;
}

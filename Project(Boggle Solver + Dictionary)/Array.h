#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

typedef struct Set{
    int* arr;   //array which will store 0 or 1 value
}Set;


void modifysize(int a,int b);
int position(int x, int y);
int create_Set(Set** h);
void destroy_Set(Set** h);
int find(Set* h, int x, int y);
void insert_val(Set** h, int x, int y);
void remove_val(Set** h, int x, int y);


#endif // ARRAY_H_INCLUDED

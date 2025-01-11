#ifndef BOGGLESOLVER_H_INCLUDED
#define BOGGLESOLVER_H_INCLUDED


#include"Array.h"
#include"dict.h"
#include"linked.h"
int Row,Col; // size of grid
void findword(int x, int y, list1 **p, Set **arr, node1* copy1, node1* Dict);
int free_boggle();
int load_boggle ();
int check_valid(int x, int y);
void solveboggle();

#endif // BOGGLESOLVER_H_INCLUDED

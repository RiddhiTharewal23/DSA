#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define PLUS 1
#define MINUS -1
#define SCALE 8

typedef struct node {
	int num;
	struct node *next, *prev;
}node;
typedef node* N1;
typedef struct number {
	int sign, dec;
	node *head, *tail;
}number;

typedef number* Num;
void initNumber(Num a);
void append(Num a, char ch);
void print(number a);
void insert_f(Num a, int no);
int length(number a);
void zeroRemov(Num a);


int compareEqual(number a, number b);
void decimalEqual(Num a, Num b);
Num add(Num a, Num b);
Num sub(Num a, Num b);
Num mult(Num a, Num b);
Num division(Num a, Num b);




#endif // LIST_H_INCLUDED

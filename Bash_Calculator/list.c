#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <math.h>


void initNumber(Num a) {
	a->head = a->tail = NULL;
	a->dec = 0;
	a->sign = PLUS;
}
void append(Num a, char ch) {
	if(ch < '0' || ch > '9')
		return;
	node *temp = (node *)malloc(sizeof(node));
	if(temp == NULL)
		return;
	temp->num = ch - '0';
	temp->next = NULL;
	if((a->head == NULL) && (a->tail == NULL)) {
		temp->prev = NULL;
		a->head = temp;
		a->tail = temp;
		return;
	}
	temp->prev = a->tail;
	a->tail->next = temp;
	a->tail = temp;
	return;
}
int length(number a) {
	node *p;
       	p = a.head;
	int count = 0;
	while(p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}
void insert_f(Num c, int no) {
	if(no < 0 || no > 9)
		return;
	node *temp = (node *)malloc(sizeof(node));
	if(!temp)
		return;
	temp->num = no;
	temp->prev = NULL;
	if((c->head == NULL) && (c->tail == NULL)){
		temp->next = NULL;
		c->head = c->tail = temp;
		return;
	}
	temp->next = c->head;
	c->head->prev = temp;
	c->head = temp;
	return;
}
void print(number c) {
	node *p;
	int q = 0;
	zeroRemov(&c);
	p = c.head;
	if(c.sign == MINUS) {
		printf("-");
		c.sign = PLUS;
	}
	while(p != NULL) {
		q++;
		if(q == (length(c) - c.dec + 1))
			printf(".");
		printf("%d", p->num);
		p = p->next;
	}
	printf("\n");
}

//Function to remove extra zeroes on left of number.
void zeroRemov(Num a) {
	node *p = a->head;
	int i, len = length(*a);
	for(i = 0; i < len - a->dec -1; i++) {
		if(p->num == 0) {
			a->head = p->next;
			p->next = NULL;
			a->head->prev = NULL;
			free(p);
			p = a->head;
		}else {
			break;
		}
	}
	p = a->tail;
	int decimal = a->dec;
	for(i = 0; i < decimal - 1; i++) {
		if(p->num == 0) {
			a->tail = p->prev;
			p->prev = NULL;
			a->tail->next = NULL;
			free(p);
			p = a->tail;
			a->dec--;

		}else {
			break;
		}
	}
	return;
}

//arithmetic operation.
void decimalEqual(Num a, Num b) {
	int i;
	if(a->dec > b->dec) {
		int diff = a->dec - b->dec;
		for(i = 0; i < diff; i++) {
			append(b, '0');
			b->dec++;
		}
	}
	else if(b->dec > a->dec) {
		int diff = b->dec - a->dec;
		for(i = 0; i < diff; i++) {
			append(a, '0');
			a->dec++;
		}
	}
}

//to make equal length by inserting 0 at front.
void lengthEqual(Num a, Num b) {
	int gap;
	gap = length(*a) - length(*b);
	if(gap > 0) {
		int i = 0;
		while(i < gap) {
			insert_f(b, 0);
			i++;
		}
	}
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		while(i < gap) {
			insert_f(a, 0);
			i++;
		}
	}
}
//copy number a in number b.
void copy(Num a, Num b) {
	int i, no, len;
	char ch;
	len = length(*a);
	node* t1 = a->head;
	for(i = 0; i < len; i++) {
		no = t1->num;
		ch = no + '0';
		append(b, ch);
		t1 = t1->next;
	}
	b->dec = a->dec;
	b->sign = a->sign;
	return;
}
//to see if number is 0 .
int zeroNumber(number a) {
	int i, flag = 0;
	node *p = a.head;
    for(i = 0; i < length(a); i++) {
		if(p->num != 0)
			flag = 1;
		 p = p->next;
	}
	return flag;
}



//Addition Operation
Num add(Num a, Num b) {
	Num ans;
	ans = (Num)malloc(sizeof(number));
	initNumber(ans);
	decimalEqual(a, b);
	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = sub(b, a);
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = sub(a, b);
		}
	}
	else if(a->sign == b->sign) {
		int i, n1, n2, carry = 0, sum;
		int len_a, len_b;
		node* t1 = a->tail;
		node* t2 = b->tail;
		len_a = length(*a);
		len_b = length(*b);
		if(a->sign == MINUS)
			ans->sign = MINUS;
		else
			ans->sign = PLUS;
		if(len_a >= len_b) {
			for(i = 1; i <= len_b; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_f(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_a - len_b; i++) {
				n1 = t1->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_f(ans, sum);
				t1 = t1->prev;
			}
		}else {
			for(i = 1; i <= len_a; i++) {
				n1 = t1->num;
				n2 = t2->num;
				sum = n1 + n2 +carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_f(ans, sum);
				t1 = t1->prev;
				t2 = t2->prev;
			}
			for(i = 1; i <= len_b - len_a; i++) {
				n1 = t2->num;
				sum = n1 + carry;
				carry = sum / 10;
				sum = sum % 10;
				insert_f(ans, sum);
				t2 = t2->prev;
			}
		}
		ans->dec = a->dec;
		if(carry != 0)
			insert_f(ans, carry);
	}
	return ans;
}

/*Function for finding bigger number among equal length numbers.*/
int compareEqual(number a, number b) {
	lengthEqual(&a, &b);
	decimalEqual(&a, &b);
	node *p, *q;
	int len;
	int i;
	len = length(a);
	p = a.head;
	q = b.head;
	for(i = 1; i <= len; i++) {
		if(p->num > q->num)
			return 1;
		else if(p->num < q->num)
			return -1;
		p = p->next;
		q = q->next;
	}
	return 0;
}
//Substraction operation.
number *sub(number *a, number *b) {
	number *ans;
	ans = (number *)malloc(sizeof(number));
	initNumber(ans);
	decimalEqual(a, b);
	lengthEqual(a, b);

	if(a->sign != b->sign) {
		if(a->sign == MINUS) {
			a->sign = PLUS;
			ans = add(a, b);
			ans->sign = MINUS;
		}
		else if(b->sign == MINUS) {
			b->sign = PLUS;
			ans = add(a, b);
			ans->sign = PLUS;
		}
	}
	else if(a->sign == b->sign) {
		if(a->sign == MINUS) {
			a->sign = b->sign = PLUS;
			ans = sub(b, a);
		}
		else if(a->sign == PLUS) {
			int n1, n2, diff, borrow = 0, i, len;
			node *t1 = a->tail;
			node *t2 = b->tail;
			len = length(*b);
			if(compareEqual(*a, *b) == 1) {
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n1 = n1 - borrow;
					if(n1 >= n2) {
						diff = n1 - n2;
						borrow = 0;
						insert_f(ans, diff);
					}
					else {
						n1 = n1 + 10;
						diff = n1 - n2;
						borrow = 1;
						insert_f(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else if(compareEqual(*a, *b) == -1) {
				ans->sign = MINUS;
				for(i = 1; i <= len; i++) {
					n1 = t1->num;
					n2 = t2->num;
					n2 = n2 - borrow;
					if(n2 >= n1) {
						diff = n2 - n1;
						borrow = 0;
						insert_f(ans, diff);
					}
					else {
						n2 = n2 + 10;
						diff = n2 - n1;
						borrow = 1;
						insert_f(ans, diff);
					}
					t1 = t1->prev;
					t2 = t2->prev;
				}
			}
			else {
				if(compareEqual(*a, *b) == 0) {
					insert_f(ans, 0);
				}
			}
		}
	}
	ans->dec = a->dec;
	return ans;
}
//Multiplication Operation.
Num mult(Num a, Num b) {
	Num ans = (Num)malloc(sizeof(number));
	initNumber(ans);
	if((zeroNumber(*a) == 0) || (zeroNumber(*b) == 0)) {
		append(ans, '0');
		return ans;
	}
	int lengthdiff;
	if(a->sign == b->sign) {
		ans->sign = PLUS;
		a->sign = b->sign = PLUS;
	}
	else {
		ans->sign = MINUS;
		a->sign = b->sign = PLUS;
	}
	lengthdiff = length(*a) - length(*b);
	if(lengthdiff < 0) {
		ans = mult(b, a);
		return ans;
	}
	else {
		node *t1, *t2;
		int len_a = length(*a);
		int len_b = length(*b);
		int i, j, n1 = 0, n2 = 0;
		int tempresult[2 * len_a];
		for(i = 0; i < 2 *len_a; i++)
			tempresult[i] = 0;
		int k = 2 * len_a - 1;
		t2 = b->tail;
		for(i = 0; i < len_b; i++) {
			t1 = a->tail;
			int carry1 = 0, carry2 = 0;
			for(j = k - i; j > len_a - 2; j--) {
				if(t1 != NULL && t2 != NULL) {
					n1 = t1->num * t2->num + carry1;
					t1 = t1->prev;
					carry1 = n1 / 10;
					n1 = n1 % 10;
					n2 = tempresult[j] + n1 + carry2;
					carry2 = n2 / 10;
					n2 = n2 % 10;
					tempresult[j] = n2;
				}
				else {
					break;
				}
			}
			tempresult[j] = carry1 + carry2 + tempresult[j];
			len_a--;
			t2 = t2->prev;
		}
		for(i= k; i >= len_a - 1 && i >= 0; i--) {
			insert_f(ans, tempresult[i]);
		}
		ans->dec = a->dec + b->dec;
		return ans;
	}
}
//Division Operation.
Num division(number *m, number *n){
	if(zeroNumber(*n) == 0) {
		printf("Dividing by Zero is not allowed.\n");
		return NULL;
	}
	zeroRemov(m);
	zeroRemov(n);

	int k = m->dec > n->dec ? m->dec : n->dec;
	int i = 0;

	while(i < k) {
		if(m->dec > 0)
			m->dec--;
		else
			append(m, '0');
		if(n->dec > 0)
			n->dec--;
		else
			append(n, '0');
		i++;
	}
	i = 9;
	Num c, d, ans, q, pro;
	c = (Num)malloc(sizeof(number));
	d = (Num)malloc(sizeof(number));
	ans = (Num)malloc(sizeof(number));
	pro = (Num)malloc(sizeof(number));
	q = (Num)malloc(sizeof(number));

	initNumber(ans);
	initNumber(c);
	initNumber(q);
	initNumber(d);
	if(m->sign == n->sign) {
		q->sign = PLUS;
		m->sign = n->sign = PLUS;
	}
	else {
		q->sign = MINUS;
		m->sign = n->sign = PLUS;
	}
	node *p = m->head;
	char ch = p->num + '0';
	append(d, ch);
	while(q->dec < SCALE){
		while(i >= 0){
			insert_f(c, i);
			pro = mult(n, c);
			ans = sub(d, pro);
			if(ans->sign != MINUS) {
				append(q, i + '0');
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				break;
			}
			else{
				node *tmp = c->head;
				free(tmp);
				c->head = c->tail = NULL;
				i--;
			}
		}
		d = ans;
		if(p->next != NULL) {
			p = p->next;
			ch = p->num + '0';
			append(d, ch);
		}
		else{
			q->dec++;
			append(d, '0');
		}
		i = 9;
		node *tmp = c->head;
		free(tmp);
		c->head = c->tail = NULL;
	}
	q->dec--;
	return q;
}


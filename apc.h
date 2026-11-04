#ifndef APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APC_H
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

/* Include the prototypes here */
// Inserting protoypes
int dl_insert_last(Dlist **head, Dlist **tail, int data);
int dl_insert_first(Dlist **head, Dlist **tail, int data);

// Printing prototypes
void print_list(Dlist *head); 
void print_result(Dlist *head);

// Operations prototype
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **Rhead,Dlist **Rtail);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **Rhead, Dlist **Rtail);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

#endif

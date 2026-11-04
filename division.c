#include "apc.h"

// Frees a whole list from the head
static void free_list(Dlist **head, Dlist **tail)
{
	Dlist *del;
	while(*head != NULL)
	{
		del = *head;
		*head = del->next;
		free(del);
	}
	*tail = NULL;
}

// Returns 1 if number1 >= number2 (both have no leading zeros)
static int is_greater_or_equal(Dlist *head1, Dlist *head2)
{
	int len1 = 0, len2 = 0;
	Dlist *t1 = head1, *t2 = head2;

	while(t1) { len1++; t1 = t1->next; }
	while(t2) { len2++; t2 = t2->next; }

	if(len1 != len2)
		return len1 > len2;

	t1 = head1;
	t2 = head2;
	while(t1 && t2)
	{
		if(t1->data != t2->data)
			return t1->data > t2->data;
		t1 = t1->next;
		t2 = t2->next;
	}
	return 1;   // equal
}

// Removes the starting zeros (keeps at least one digit)
static void remove_zeros(Dlist **head, Dlist **tail)
{
	while(*head != *tail && (*head)->data == 0)
	{
		Dlist *del = *head;
		*head = del->next;
		(*head)->prev = NULL;
		free(del);
	}
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	/* Definition goes here */

	// remainder list and quotient (result) list
	Dlist *rem_h = NULL, *rem_t = NULL;
	Dlist *res_h = NULL, *res_t = NULL;
	Dlist *Rhead = NULL, *Rtail = NULL;   // subtraction output

	int count = 0;

	// Divisor is 0 -> cannot divide
	Dlist *check = *head2;
	while(check != NULL && check->data == 0)
		check = check->next;
	if(check == NULL)
	{
		printf("ERROR : Division by zero is not possible\n");
		*headR = NULL;
		return FAILURE;
	}

	// check h1 != NULL
	Dlist *temp1 = *head1;
	while(temp1 != NULL)
	{
		// 'rem' -> take 1 value from the front of the h1
		dl_insert_last(&rem_h, &rem_t, temp1->data);
		remove_zeros(&rem_h, &rem_t);

		count = 0;

		// rem >= h2 ?  (Yes -> subtract again and again, No -> count stays 0)
		while(is_greater_or_equal(rem_h, *head2))
		{
			// Call subtraction(rem, h2)
			Rhead = NULL;
			Rtail = NULL;
			subtraction(&rem_h, &rem_t, head2, tail2, &Rhead, &Rtail);

			// rem = rem - h2
			free_list(&rem_h, &rem_t);
			rem_h = Rhead;
			rem_t = Rtail;

			// increment count
			count++;
		}

		// Insert the count value to the 'res' list (0 if rem < h2)
		dl_insert_last(&res_h, &res_t, count);

		temp1 = temp1->next;
	}

	// Remove the starting zeros and give the result to the caller
	remove_zeros(&res_h, &res_t);
	*headR = res_h;

	free_list(&rem_h, &rem_t);
	return SUCCESS;
}
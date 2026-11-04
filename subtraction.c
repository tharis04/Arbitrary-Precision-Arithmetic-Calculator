#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **Rhead, Dlist **Rtail)
{
	/* Definition goes here */
	int borrow = 0, result = 0, negative = 0;
	int len1 = 0, len2 = 0;

	// Count the digits of both numbers
	Dlist *t1 = *head1;
	Dlist *t2 = *head2;
	while(t1 != NULL)
	{
		len1++;
		t1 = t1->next;
	}
	while(t2 != NULL)
	{
		len2++;
		t2 = t2->next;
	}

	// Find out if num1 < num2
	if(len1 < len2)
	{
		negative = 1;
	}
	else if(len1 == len2)
	{
		t1 = *head1;
		t2 = *head2;
		while(t1 != NULL && t2 != NULL)
		{
			if(t1->data != t2->data)
			{
				if(t1->data < t2->data)
					negative = 1;
				break;
			}
			t1 = t1->next;
			t2 = t2->next;
		}
	}

	// If num1 < num2, swap the lists so that num1 > num2
	if(negative)
	{
		Dlist *swap;

		swap = *head1;
		*head1 = *head2;
		*head2 = swap;

		swap = *tail1;
		*tail1 = *tail2;
		*tail2 = swap;
	}

	// Temp variable initialization
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	//Traversal from tail
	while(temp1 != NULL || temp2 != NULL)
	{
		// If the numbers have equal number of digits
		if(temp1 != NULL && temp2 != NULL)
		{
			result = temp1->data - temp2->data - borrow;
		}

		// If the 1st number has more number of digits than 2nd number
		else if(temp1 != NULL && temp2 == NULL)
		{
			result = temp1->data - 0 - borrow;
		}

		// (2nd number can never be longer after the swap, kept to match addition)
		else if(temp1 == NULL && temp2 != NULL)
		{
			result = 0 - temp2->data - borrow;
		}

		// Borrow identification
		if(result < 0)
		{
			result = result + 10;
			borrow = 1;
		}
		else
		{
			borrow = 0;
		}

		// Insert the results
		dl_insert_first(Rhead, Rtail, result);

		// Move the temp pointer
		if(temp1)
			temp1 = temp1->prev;
		if(temp2)
			temp2 = temp2->prev;
	}

	// Remove leading zeros (keep at least one digit)
	while(*Rhead != *Rtail && (*Rhead)->data == 0)
	{
		Dlist *del = *Rhead;
		*Rhead = del->next;
		(*Rhead)->prev = NULL;
		free(del);
	}

	// add ( - ) 
	if(negative)
	{
		(*Rhead)->data = -(*Rhead)->data;
	}
	return result;
}

#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	/* Definition goes here */
	Dlist *R1head = NULL, *R1tail = NULL;
	Dlist *R2head = NULL, *R2tail = NULL;
	Dlist *Rhead = NULL, *Rtail = NULL;
	Dlist *del;

	// Initializing temp variable
	Dlist *temp1 = NULL;
	Dlist *temp2 = *tail2;

	int count = 0, res = 0, carry = 0;

	while(temp2)
	{
		temp1 = *tail1;
		carry = 0;

		// Insert 'count' zeros first (shift)
		for(int i = 0; i < count; i++)
		{
			dl_insert_first(&R2head, &R2tail, 0);
		}

		while(temp1)
		{
			res = (temp2->data * temp1->data) + carry;
			carry = res / 10;
			res = res % 10;

			if(count == 0)
				dl_insert_first(&R1head, &R1tail, res);
			else
				dl_insert_first(&R2head, &R2tail, res);

			temp1 = temp1->prev;
		}

		// Left over carry
		if(carry)
		{
			if(count == 0)
				dl_insert_first(&R1head, &R1tail, carry);
			else
				dl_insert_first(&R2head, &R2tail, carry);
		}

		// From the 2nd row onwards: R = R1 + R2
		if(count != 0)
		{
			addition(&R1head, &R1tail, &R2head, &R2tail, &Rhead, &Rtail);

			// Free old R1 and R2
			while(R1head)
			{
				del = R1head;
				R1head = R1head->next;
				free(del);
			}
			while(R2head)
			{
				del = R2head;
				R2head = R2head->next;
				free(del);
			}
			R1tail = NULL;
			R2tail = NULL;

			// R becomes the new R1 (running total)
			R1head = Rhead;
			R1tail = Rtail;
			Rhead = Rtail = NULL;
		}

		temp2 = temp2->prev;
		count++;
	}

	// Remove leading zeros (keep at least one digit)
	while(R1head != R1tail && R1head->data == 0)
	{
		del = R1head;
		R1head = R1head->next;
		R1head->prev = NULL;
		free(del);
	}

	*headR = R1head;
	return 0;
}
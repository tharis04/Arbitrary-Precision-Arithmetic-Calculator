#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **Rhead,Dlist **Rtail)
{
	/* Definition goes here */
	int carry =0, result =0;
	
	// Temp variable initialization
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	//Traversal from tail
	while( temp1 != NULL || temp2 != NULL)
	{
		// If the numbers have equal number of digits
		if(temp1 != NULL && temp2 != NULL)
		{
			result = temp1->data + temp2->data + carry;
		}
		
		// If the 1st number has more number of digits than 2nd number
		else if(temp1 != NULL && temp2 == NULL)
		{
			result = temp1->data + 0 + carry; 
		}

		// If the 2st number has more number of digits than 1nd number
		else if(temp1 == NULL && temp2 != NULL)
		{
			result = 0 + temp2->data + carry; 
		}

		// Carry value identification
		if(result > 9)
		{
			carry = result / 10; // takes the first number and store it in carry
			result = result % 10; // takes the last number and then store it in result
		}
		else
		{
			carry = 0; // reset, otherwise the old carry is added again to the next digit
		}
		

		// Insert the results
		dl_insert_first(Rhead,Rtail, result);

		// Move the temp pointer
		if(temp1)
			temp1 = temp1->prev;
		if(temp2)
			temp2 = temp2->prev;
	}
	if(carry == 1)
	{
		dl_insert_first(Rhead, Rtail, carry);
	}
	return result;
}
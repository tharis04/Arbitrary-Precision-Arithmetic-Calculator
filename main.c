#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apc.h"
#include <unistd.h> // for sleep()

// Frees a whole list from the head
void free_list(Dlist **head, Dlist **tail)
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

int main(int argc, char *argv[])
{

    printf("\n=====================================================\n");
    printf("             \033[33mArbitrary Precision Calculator\033[0m\n");
    printf("                 \033[33m-THARIS SELVARAJ-\033[0m\n");
    printf("=====================================================\n");

    char choice;
    char num1[1000], num2[1000], op[10];
    int first = 1;

    do
    {
        // LIST CREATION (fresh lists for every calculation)

        Dlist *head1 = NULL, *tail1 = NULL;
        Dlist *head2 = NULL, *tail2 = NULL;
        Dlist *Rhead = NULL, *Rtail = NULL;
        Dlist *headR = NULL, *tailR = NULL;

        // INPUT : 1st round from command line (if given), next rounds from the user
        if(choice == 'Y' || choice == 'y')
        {
            printf("=====================================================\n");
            printf("\n*** Rebooting APC! Manually! ***\n");
            for (int i = 0; i <= 100; i += 2)
                {
                    printf("\r");
                    for (int j = 0; j < 50; j++)
                        printf(j < i / 2 ? "█" : " ");
                    printf(" %d%%", i);
                    fflush(stdout);
                    usleep(100000);
                }
                printf("\n");
                printf("\033[32m*** Rebooted Successfully ***\033[0m\n");
                printf("=====================================================\n");
            
        }
        if(first && argc == 4)
        {
            strcpy(num1, argv[1]);
            strcpy(op,   argv[2]);
            strcpy(num2, argv[3]);
        }
        else
        {
            printf("\nEnter the 1st number : ");
            scanf("%999s", num1);
            printf("Enter the operator (+ - x /) : ");
            scanf("%9s", op);
            printf("Enter the 2nd number : ");
            scanf("%999s", num2);
        }
        first = 0;

        char operator = op[0];

        int i=0,num;

        while(num1[i] != '\0')
        {
            num = atoi((char[]){num1[i], '\0'});
            dl_insert_last(&head1,&tail1,num);
            i++;
        }
        //print_list(head1);

        i=0;
        while(num2[i] != '\0')
        {
            num = atoi((char[]){num2[i], '\0'});
            dl_insert_last(&head2,&tail2,num);
            i++;
        }
        //print_list(head2);

        switch (operator)
        {
            case '+':
                /* call the function to perform the addition operation */
                printf("\033[32mSelected Addition...\033[0m\n");
                printf("=====================================================\n");
                addition(&head1,&tail1,&head2,&tail2,&Rhead,&Rtail);
                print_result(Rhead);
                printf("=====================================================\n");
                break;
            case '-':
                /* call the function to perform the subtraction operation */
                printf("\033[32mSelected Subtraction...\033[0m\n");
                printf("=====================================================\n");
                subtraction(&head1, &tail1, &head2, &tail2, &Rhead, &Rtail);
                print_result(Rhead);
                printf("=====================================================\n");
                break;
            case 'x':
                /* call the function to perform the multiplication operation */
                printf("\033[32mSelected Multiplication...\033[0m\n");
                printf("=====================================================\n");
                multiplication(&head1, &tail1, &head2, &tail2, &headR);
                print_result(headR);
                printf("=====================================================\n");
                break;
            case '/':
                /* call the function to perform the division operation */
                printf("\033[32mSelected Division...\033[0m\n");
                printf("=====================================================\n");
                if(division(&head1, &tail1, &head2, &tail2, &headR) == SUCCESS)
                    print_result(headR);
                printf("=====================================================\n");
                break;
            default:
                printf("Invalid Input:-( Try again...\n");
        }

        // Free the lists before the next round
        free_list(&head1, &tail1);
        free_list(&head2, &tail2);
        free_list(&Rhead, &Rtail);
        free_list(&headR, &tailR);

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &choice);   // the space before %c skips the leftover newline

    } while(choice == 'y' || choice == 'Y');

    if(choice == 'N' || choice == 'n')
        {
            printf("\n*** Exiting APC ***\n");
        }
        printf("\n");
    return 0;
}
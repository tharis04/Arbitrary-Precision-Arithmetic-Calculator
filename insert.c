#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apc.h"

int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    // NEWNODE CREATION
    Dlist *newnode = malloc(sizeof(Dlist));
    
    // VALIDATION
    if(newnode == NULL)
    {
        printf("Memory Allocation failed\n");
        return FAILURE;
    }
    
    // NODE MEMBERS
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    
    // only single node available
    if((*head) == NULL)
    {
        *head = newnode;
        *tail = newnode;
        return SUCCESS;
    }
    
    newnode->prev = *tail;
    (*tail)->next = newnode;
    (*tail) = newnode;
    
    return SUCCESS;
}


int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *newnode = malloc(sizeof(Dlist));
    
    if(newnode == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }
    
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    
    // LIST EMPTY
    if((*head) == NULL)
    {
        *head = newnode;
        *tail = newnode;
        return SUCCESS;
    }
    
    (*head)->prev = newnode;
    newnode->next = *head;
    *head = newnode;
    
    return SUCCESS;
}
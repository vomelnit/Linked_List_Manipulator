#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "error_handling.h"

enum list_sort_by {SORT_BY_ID, SORT_BY_YEARS, SORT_BY_NAME};

typedef struct node
{
    int         id;
    int         years;
    char        *name;
    struct node *next;
} node;

//Print list items into stdout
void    print_list                (node *head);
//Insert item at begin
void    insert_first_to_list      (node **head,
                                   int id,
                                   int years,
                                   char *name);
//Delete first item
node*   delete_and_get_first_in_list      (node **head);
//Check of list emptiness
bool    is_list_empty             (node *head);
//Get length of list
int     get_list_length           (node *head);
//Find a link with given id
node*   get_node_by_id            (node *head,
                                   int id);
//Delete a link with given id
node*   delete_and_get_node_by_id (node **head,
                                   int id);
//Sort sist
void    sort_list                 (node *head,
                                   int sort_by);
//Reverse the list
void    reverse_list              (node** head_ref);
//Get linked list elemnts as char**
char**  get_list_as_string_array  (node *head);

int     delete_entire_list        (node *head);

#endif

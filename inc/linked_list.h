#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "error_handling.h"

/****************************************************************************
*   DECLARATIONS
****************************************************************************/

/**
 * @brief Enum that helps to identify sorting param for linked list.
 *
 * When func sort_list() is used we need to specify, by which element of
 * node structure we will sort our linked list.
 */
enum list_sort_by {
    SORT_BY_ID,     /**< Sorting by id. */
    SORT_BY_YEARS,  /**< Sorting by years. */
    SORT_BY_NAME    /**< Sorting by name. */
};

/**
 * @brief Element of linked list.
 *
 * Structure defines element of linked list.
 * Describe persons' characteristics
 */
typedef struct node
{
    int         id;     /**< Id of element. */
    int         years;  /**< Age of person. */
    char        *name;  /**< First ame of person. */
    struct node *next;  /**< ptr on next linked list's element. */
} node;

//Print list items into stdout
void    print_list                      (node *head);
//Insert item at begin
void    insert_first_to_list            (node **head,
                                         int id,
                                         int years,
                                         char *name);
//Delete first item
node*   delete_and_get_first_in_list    (node **head);
//Check of list emptiness
bool    is_list_empty                   (node *head);
//Get length of list
int     get_list_length                 (node *head);
//Find a link with given id
node*   get_node_by_id                  (node *head,
                                         int id);
//Delete a link with given id
node*   delete_and_get_node_by_id       (node **head,
                                         int id);
//Sort sist
void    sort_list                       (node *head,
                                         int sort_by);
//Reverse the list
void    reverse_list                    (node** head_ref);
//Get linked list elemnts as char**
char**  get_list_as_string_array        (node *head);

int     delete_entire_list              (node *head);

#endif  /* LINKED_LIST_H */

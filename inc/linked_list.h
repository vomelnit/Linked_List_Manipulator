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

/** @brief Print list items into stdout
 *
 *  @param head pointer to top of linked list.
 *  @return NO_ERROR (0) if func was executed.
 */
int     print_list                      (node *head);

/** @brief Insert person's data at top of linked list
 *
 *  @param head pointer to top of linked list.
 *  @param id person identificator.
 *  @param years age of person.
 *  @param name pointer to char array with person's name.
 *  @return NO_ERROR (0) if func was executed.
 */
int     insert_first_to_list            (node **head,
                                         int id,
                                         int years,
                                         char *name);

/** @brief Delete person's data at the top of linked list
 *
 *  Pay attention that memory (of returned struct)
 *  must be deallocated manually. If list is empty - func will return NULL.
 *  Hint: before this func is_list_empty() should be called.
 *
 *  @param head pointer to pointer to top of linked list.
 *  @return node struct that was deleted from list.
 *  If list is empty - return NULL
 */
node*   delete_and_get_first_in_list    (node **head);

/** @brief Check of linked list emptiness
 *
 *  @param head pointer to top of linked list.
 *  @return TRUE (1) if list is empty. Else - FALSE (0)
 */
bool    is_list_empty                   (node *head);

/** @brief Get length of linked list
 *
 *  @param head pointer to top of linked list.
 *  @return Amount of list's elements
 */
int     get_list_length                 (node *head);

/** @brief Get element of list by id
 *
 *  Pay attention that: if list is empty - func will return NULL.
 *  If there is no element with entered id - func will return NULL.
 *
 *  @param head pointer to top of linked list.
 *  @param id identificator of element (person).
 *  @return node struct that was has entered id. If not found - return NULL
 */
node*   get_node_by_id                  (node *head,
                                         int id);
/** @brief Delete a link with given id
 *
 *  Pay attention that: if list is empty - func will return NULL.
 *  If there is no element with entered id - func will return NULL.
 *  Memory (of returned struct) must be deallocated manually.
 *
 *  @param head pointer to pointer to top of linked list.
 *  @param id identificator of element (person).
 *  @return node struct that was deleted by entered id.
 *  Or NULL - if didn't found
 */
node*   delete_and_get_node_by_id       (node **head,
                                         int id);

/** @brief Sort linked list by entered field of struct
 *
 *  @param head pointer to top of linked list.
 *  @param sort_by list_sort_by value that will point by which field list
 *  must be sorted.
 *  @return NO_ERROR(0) - if func was executed correctly. Else - more than zero.
 */
int     sort_list                       (node *head,
                                         int sort_by);

/** @brief Reverse order in the linked list
 *
 *  @param head pointer to pointer to top of linked list.
 *  @return NO_ERROR(0) - if func was executed correctly. Else - more than zero.
 */
int     reverse_list                    (node** head_ref);

/** @brief Get linked list elements as char**
 *
 *  Format of each element "(%d,%d,%s)\r\n"
 *
 *  @param head pointer to top of linked list.
 *  @return char array of arrays for each element of list.
 */
char**  get_list_as_string_array        (node *head);

/** @brief Delete linked list and free memory of list
 *
 *  @param head pointer to top of linked list.
 *  @return NO_ERROR(0) - if func was executed correctly.
 */
int     delete_entire_list              (node *head);

#endif  /* LINKED_LIST_H */

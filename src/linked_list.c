#include "linked_list.h"

inline void
print_list (node *head) {
    node *current_node = head;
    printf ("\n====LIST====\n");
    //start from the beginning
    while(NULL != current_node) {
        printf ("(%d,%d,%s)\n",current_node->id, current_node->years,
                               current_node->name);
        current_node = current_node->next;
    }
    printf ("============\n");
}

int
delete_entire_list (node *head) {
    node *current_node = head;
    node *node_to_deallocate;
    while(NULL != current_node) {
        node_to_deallocate = current_node;
        current_node = current_node->next;
        free (node_to_deallocate);
    }
    return 0;
}

void
insert_first_to_list (node **head, int id, int years, char *name) {
    //create a link
    node *link = (node*) malloc (sizeof(struct node));
    if (NULL == link)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    link->id = id;
    link->years = years;
    link->name = malloc (strlen(name));
    if (link->name == NULL)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    strcpy (link->name, name);
    //point it to old first node
    link->next = *head;
    //point first to new first node
    *head = link;
}

//delete first item
inline node*
delete_and_get_first_in_list (node **head) {
    //save reference to first link
    if (NULL == *head)
        error_handler (LINKED_LIST_IS_EMPTY, NON_CRITICAL);
    node *tempLink = *head;
    //mark next to first link as first
    *head = tempLink->next;
    //return the deleted link
    return tempLink;
}

//is list empty
inline bool
is_list_empty (node *head) {
    return head == NULL;
}

int
get_list_length (node *head) {
    int  length = 0;
    node *current;

    for (current = head; current != NULL; current = current->next) length++;

    return length;
}

//find a link with given id
node*
get_node_by_id (node *head, int id) {
    //start from the first link
    node* current = head;
    //if list is empty
    if(NULL == head) {
        error_handler (LINKED_LIST_IS_EMPTY, NON_CRITICAL);
        return NULL;
    }
    //navigate through list
    while (current->id != id) {
        //if it is last node
        if (current->next == NULL) {
            return NULL;
        } else {
            //go to next link
            current = current->next;
        }
    }
    //if data found, return the current Link
    return current;
}

//delete a link with given id
node*
delete_and_get_node_by_id (node **head, int id) {
    //start from the first link
    node* current = *head;
    node* previous = NULL;
    //if list is empty
    if (NULL == *head) {
        error_handler (LINKED_LIST_IS_EMPTY, NON_CRITICAL);
        return NULL;
    }
    //navigate through list
    while(current->id != id) {
        //if it is last node
        if (NULL == current->next) {
            return NULL;
        } else {
            //store reference to current link
            previous = current;
            //move to next link
            current = current->next;
        }
    }
    //found a match, update the link
    if (current == *head) *head = current->next;
    else previous->next = current->next;

    return current;
}

void
sort_list (node *head, int sort_by) {
    int  i;
    int  j;
    int  k;
    int  tempyears;
    int  tempId;
    char * tempName;
    node *current;
    node *next;
    bool compare_result = 0;

    if (NULL == head) error_handler (LINKED_LIST_IS_EMPTY, NON_CRITICAL);

    int size = get_list_length (head);
    k = size ;


    for ( i = 0 ; i < size - 1 ; i++, k-- ) {
        current = head;
        next = head->next;

        for ( j = 1 ; j < k ; j++ ) {
            if (sort_by == SORT_BY_ID)
                compare_result = current->id > next->id;
            else if (sort_by == SORT_BY_YEARS)
                compare_result = current->years > next->years;
            else if (sort_by == SORT_BY_NAME)
                compare_result = strcmp(current->name, next->name) > 0;
            else
                error_handler (UNKNOWN_SORT_BY_VALUE, NON_CRITICAL);

            if (compare_result) {
                tempId = current->id;
                current->id = next->id;
                next->id = tempId;

                tempyears = current->years;
                current->years = next->years;
                next->years = tempyears;

                tempName = current->name;
                current->name = next->name;
                next->name = tempName;
            }

            current = current->next;
            next    = next->next;
        }
    }
}

void
reverse_list (node** head_ref) {
    node* prev    = NULL;
    node* current = *head_ref;
    node* next;

    if (NULL == head_ref)
        error_handler (LINKED_LIST_IS_EMPTY, NON_CRITICAL);

    while (NULL != current) {
        next          = current->next;
        current->next = prev;
        prev          = current;
        current       = next;
    }

    *head_ref = prev;
}

char**
get_list_as_string_array (node *head){
    int  size      = get_list_length (head);
    node *ptr      = head;
    int  i         = 0;
    char row[200];
    char **row_arr = malloc (sizeof (char*) * size);

    if (NULL == row_arr)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    //start from the beginning
    while (NULL != ptr) {
        sprintf (row, "(%d,%d,%s)\r\n",ptr->id,ptr->years,ptr->name);
        row_arr[i] = malloc (strlen (row) + 1);
        if (NULL == row_arr[i])
            error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
        strcpy (row_arr[i], row);
        ptr = ptr->next;
        i++;
    }

    return row_arr;
}

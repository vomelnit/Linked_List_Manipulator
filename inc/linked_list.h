#ifndef LINKED_LIST_H
  #define LINKED_LIST_H

  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>

  #include "error_handling.h"

  enum sort_by{SORT_BY_ID, SORT_BY_YEARS, SORT_BY_NAME};

  typedef struct node
  {
    int         id;
    int         years;
    char        *name;
    struct node *next;
  } node;

  //Print list items into stdout
  void    printList                 (node *head);
  //Insert item at begin
  void    insertFirst               (node **head, int id,
                                     int years,
                                     char *name);
  //Delete first item
  node*   deleteFirst               (node **head);
  //Check of list emptiness
  bool    isEmpty                   (node *head);
  //Get length of list
  int     length                    (node *head);
  //Find a link with given id
  node*   find_by_id                (node *head,
                                     int id);
  //Delete a link with given id
  node*   delete_by_id              (node **head,
                                     int id);
  //Sort sist
  void    sort                      (node *head,
                                     int sort_by);
  //Reverse the list
  void    reverse                   (node** head_ref);
  //Get linked list elemnts as char**
  char**  get_list_as_string_array  (node *head);

#endif

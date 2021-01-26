#ifndef INTERFACE_H
#define INTERFACE_H

/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "file_processing.h"
/****************************************************************************
*   DECLARATIONS
****************************************************************************/
enum Menu_commands{
    PRINT_LIST                = (int)'1',
    INSERT_ELEMENT_ON_TOP     = (int)'2',
    DELETE_ELEMENT_FROM_TOP   = (int)'3',
    FIND_ELEMENT_BY_ID        = (int)'4',
    SORT_LIST_BY_ID           = (int)'5',
    SORT_LIST_BY_YEARS        = (int)'6',
    SORT_LIST_BY_NAME         = (int)'7',
    PRINT_LIST_LENGTH         = (int)'8',
    REVERSE_LIST              = (int)'9'
};

int   print_intial_info                 (node  *head);

int   main_menu_cmd_processing          (char  *cmd,
                                         node **head,
                                         char  *filename);

int   main_app_loop                     (node **head,
                                         char  *filename_for_list_data);

void  custom_fflush_stdin               ();

void  print_help_info                   ();

void  exit_routine                      (char *filename,
                                         node *head);

int  insert_entered_row_to_linked_list  (node **head,
                                         char  *row);

int  insert_element_into_list_routine   (node **head);

int  get_id_and_find_element_by_id      (node **head);

int  execute_main_menu_entered_cmd      (char  *entered_str,
                                         node **head,
                                         char  *filename);

#endif /* INTERFACE_H */

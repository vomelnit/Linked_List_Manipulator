#ifndef INTERFACE_H
#define INTERFACE_H

/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "file_processing.h"
/****************************************************************************
*   DECLARATIONS
****************************************************************************/

/**
 * @brief Enum that helps to identify entered commands in main menu.
 *
 * This enum was implemented in order to handle entered commands in main menu.
 */
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

/** @brief Print welcome info and output linked list elements
 *
 *  @param head pointer to the top of linked list.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int   print_intial_info                 (node  *head);

/** @brief Processing of entered command in menu
 *
 *  @param cmd pointer to command string.
 *  @param head pointer to pointer to the top of linked list.
 *  @param filename pointer to filename string.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int   main_menu_cmd_processing          (char  *cmd,
                                         node **head,
                                         char  *filename);

/** @brief Loop that get entered characters from stdin and process entered text
 *
 *  @param head pointer to pointer to the top of linked list.
 *  @param filename_for_list_data pointer to filename string.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int   main_app_loop                     (node **head,
                                         char  *filename_for_list_data);

/** @brief fflush stdin till '\n' character
 *
 *  @return Void
 */
void  custom_fflush_stdin               ();

/** @brief Pring info in order to help to interact with main menu
 *
 *  @return Void
 */
void  print_help_info                   ();

/** @brief Save linked list to file, free memory of list and exit(0)
 *
 *  @param head pointer to the top of linked list.
 *  @param filename pointer to filename string.
 *  @return Void
 */
void  exit_routine                      (char  *filename,
                                         node  *head);

/** @brief Check entered row (entered by user) and add it to list
 *
 *  @param head pointer to the top of linked list.
 *  @param row pointer to row string.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int  insert_entered_row_to_linked_list  (node **head,
                                         char  *row);

/** @brief Get row from stdin and add it to list
 *
 *  @param head pointer to pointer the top of linked list.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int  insert_element_into_list_routine   (node **head);

/** @brief Get id from stdin and print full element data
 *
 *  @param head pointer to pointer the top of linked list.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int  get_id_and_find_element_by_id      (node **head);

/** @brief Check entered command and react on it
 *
 *  @param entered_str pointer entered command string.
 *  @param head pointer to pointer the top of linked list.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
int  execute_main_menu_entered_cmd      (char  *entered_str,
                                         node **head,
                                         char  *filename);

#endif /* INTERFACE_H */

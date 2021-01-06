#ifndef INTERFACE_H
  #define INTERFACE_H

  #include "file_processing.h"

  void  custom_fflush_stdin               ();

  void  print_help_info                   ();

  void  exit_routine                      (char *filename,
                                           node *head);

  int  insert_entered_row_to_linked_list  (node **head,
                                           char *row);

  int  insert_element_into_list_routine   (node **head);

  int  get_id_and_find_element_by_id      (node **head);

  int  execute_main_menu_entered_cmd      (char *entered_str,
                                           node **head);

#endif

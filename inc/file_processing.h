#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <sys/stat.h>
#include <unistd.h>

#include "linked_list.h"
/****************************************************************************
 *  DEFINES
 ****************************************************************************/
#define NODE_VALUE_NUMBER 3 /**< Quantity of elements to read while insertion. */
#define DEFAULT_FILENAME "list.txt"
#define FILENAME_MAX_LENGTH 100
/****************************************************************************
 *  DECLARATIONS
 ****************************************************************************/
typedef enum {FALSE = 0, TRUE} boolean;

 int      create_file_for_linked_list           (char  *filename);

 int      init_linked_list_from_file            (char  *filename,
                                                 node **head);

char*     get_filename_for_list_data            (int    argc,
                                                 char **argv);

bool      is_file_exist                         (char  *filename);

long int  get_size_of_file                      (char  *filename);

int       put_list_arr_into_file                (char  *filename_for_list_data,
                                                 char **row_arr,
                                                 int    row_arr_size);

int       save_list_to_file                     (char  *filename_for_list_data,
                                                 node  *head);

char**    get_array_of_rows_from_file           (FILE  *file);

char**    get_values_from_file_row              (char  *row,
                                                 is_critical_t is_error_critical);

bool      check_if_str_consist_of_digits        (char  *string);

bool      check_if_str_consist_of_alphabets     (char  *str);

bool      check_if_row_values_match             (char **values);

// void      insert_row_values_into_linked_list    (node **head,
//                                                  char **values);

int       convert_rows_to_linked_list           (node **head,
                                                 char **rows);

#endif  /* FILE_PROCESSING_H */

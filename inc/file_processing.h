#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "linked_list.h"
#include <sys/stat.h>

/****************************************************************************
 *  DEFINES
 ****************************************************************************/
#define NODE_VALUE_NUMBER 3 /**< Quantity of elements to read while insertion. */

typedef enum {FALSE = 0, TRUE} boolean;

/****************************************************************************
 *  DECLARATIONS
 ****************************************************************************/
bool      is_file_exist                         (char *filename);

long int  get_size_of_file                      (char *filename);

void      put_list_arr_into_file                (char *filename_for_list_data,
                                                 char **row_arr,
                                                 int row_arr_size);

void      save_list_to_file                     (char *filename_for_list_data,
                                                 node *head);

char**    get_array_of_rows_from_file           (FILE *file);

char**    get_values_from_file_row              (char *row,
                                                 is_critical_t is_error_critical);

bool      check_if_str_consist_of_digits        (char *string);

bool      check_if_str_consist_of_alphabets     (char *str);

bool      check_if_row_values_match             (char **values);

void      insert_row_values_into_linked_list    (node **head,
                                                 char **values);

void      convert_rows_to_linked_list           (node **head,
                                                 char **rows);


#endif  /* FILE_PROCESSING_H */

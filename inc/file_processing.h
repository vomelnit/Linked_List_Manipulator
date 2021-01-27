#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H


#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <sys/stat.h>
#include <unistd.h>

#include "linked_list.h"
#include "error_handling.h"
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

/** @brief Open file <filename> and close it
 *
 *  @param filename name of file to open.
 *  @return NO_ERROR (0) if func was executed correctly. Else - more than zero.
 */
error_handle_t       create_file_for_linked_list           (char  *filename);

/** @brief Open file <filename> and create linked list according to it's data.
 *
 *  @param filename name of file to open.
 *  @param head pointer to pointer to linked list top.
 *  @return NO_ERROR (0) if func was executed correctly. Else - more than zero.
 */
error_handle_t       init_linked_list_from_file            (char  *filename,
                                                 node **head);

/** @brief Get filename of linked list data.
 *
 *  If filename was specified as console argument - return it.
 *  If not specified - then return default filename DEFAULT_FILENAME
 *
 *  @param argc number of entered arguments in console.
 *  @param argv pointer to pointer arguments values.
 *  @return pointer to filename.
 */
char*     get_filename_for_list_data            (int    argc,
                                                 char **argv);

/** @brief Check if file exists.
 *
 *  @param filename name of file to open.
 *  @return TRUE(1) if file exists in directory of prog execution.
 *  Else - FALSE(0)
 */
bool      is_file_exist                         (char  *filename);

// /** @brief Get size of file <filename>.
//  *
//  *  @param filename name of file to open.
//  *  @return size of file in bytes
//  */
// long int  get_size_of_file                      (char  *filename);

/** @brief Write to file <filename_for_list_data> rows <row_arr> and close it.
 *
 *  @param filename_for_list_data name of file for data.
 *  @param row_arr pointer to pointer to data that must be writted to file.
 *  @param row_arr_size number of rows in row_arr.
 *  @return NO_ERROR (0) if func was executed correctly. Else - more than zero.
 */
error_handle_t       put_list_arr_into_file                (char  *filename_for_list_data,
                                                 char **row_arr,
                                                 int    row_arr_size);

/** @brief Convert linked list strings and write to file.
 *
 *  This func convert list to char** in order to call func
 *  put_list_arr_into_file() and write list to file
 *
 *  @param filename_for_list_data name of file for data.
 *  @param head pointer to the top of linked list.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
error_handle_t       save_list_to_file                     (char  *filename_for_list_data,
                                                 node  *head);

/** @brief Get strings of data for list from file.
 *
 *  @param file pointer to file of data.
 *  @return rows of data in char* format.
 */
char**    get_array_of_rows_from_file           (FILE  *file);

/** @brief Get fields of linked list element from string.
 *
 * Pay attention that it can return NULL - if data in file was incorrect.
 *
 *  @param row pointer to string of data for one element.
 *  @param is_error_critical is wrong number of fields in row can stop the prog.
 *  @return pointer on array of fields in string format.
 *  Or NULL if data is incorrect
 */
char**    get_values_from_file_row              (char  *row,
                                                 is_critical_t is_error_critical);

/** @brief Check if string's characters are '0'-'9'.
 *
 *  @param string pointer to string for checking.
 *  @return TRUE(1) if string consists of digits. Else - FALSE(0)
 */
bool      check_if_str_consist_of_digits        (char  *string);

/** @brief Check if string's characters are letters 'a'-'z' or 'A'-'Z'.
 *
 *  @param str pointer to string for checking.
 *  @return TRUE(1) if string consists of letters. Else - FALSE(0)
 */
bool      check_if_str_consist_of_alphabets     (char  *str);

/** @brief Check if strings match linked list data.
 *
 *  Func check if values[0] and values[1] consist of digits,
 *  and values[2] consist of letters.
 *
 *  @param values pointer to strings for checking.
 *  @return TRUE(1) if strings match pattern. Else - FALSE(0)
 */
bool      check_if_row_values_match             (char **values);

/** @brief Convert strings of data into linked list.
 *
 *  @param head pointer to pointer to strings for checking.
 *  @param rows pointer to array of strings from file.
 *  @return NO_ERROR (0) if func was executed correctly.
 */
error_handle_t       convert_rows_to_linked_list           (node **head,
                                                 char **rows);

#ifdef __cplusplus
}
#endif

#endif  /* FILE_PROCESSING_H */

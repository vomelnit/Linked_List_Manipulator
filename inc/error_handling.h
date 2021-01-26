#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/****************************************************************************
*   DECLARATIONS
****************************************************************************/

/**
 * @brief Enum that helps to identify error/warning.
 *
 * This enum was implemented in order to inform user about error/warnings.
 * And in order to handle them properly.
 */
typedef enum {
    NO_ERROR,                       /**< Everything is OK. */
    TOO_MANY_ARG_IN_MAIN,           /**< Too many arguments in console. */
    FILE_PERMISSIONS_ERR,           /**< File has some permissions problem. */
    FILE_OPEN_ERROR,                /**< File opening error. */
    FILE_CREATION_ERR,              /**< File creation error. */
    NO_SPECIFIED_FILE,              /**< File wasn't specified. */
    CMD_TOO_LONG,                   /**< Entered command was too long. */
    WRONG_CMD_ENTERED,              /**< Entered command was incorrect. */
    CMD_EXEC_WRONG,                 /**< Error while command execution. */
    ROW_TOO_LONG,                   /**< Entered row for insertion was too long. */
    ROW_DISMATCH_PATTERN,           /**< Entered row has wrong format. */
    ROW_ELEMENTS_DISMATCH,          /**< Entered row has wrong element. */
    TOO_MANY_ARG_IN_ROW,            /**< Entered row has too many elements. */
    MEMORY_ALLOCATION_ERR,          /**< Error while memory allocation. */
    LINKED_LIST_IS_EMPTY,           /**< Linked list has no elements. */
    FILE_STAT_ERR,                  /**< Cannot get info about file. */
    WRITE_TO_FILE_ERR,              /**< Cannot write into file. */
    VALUE_IS_NOT_NUMBER,            /**< Sorting by id. */
    UNKNOWN_SORT_BY_VALUE,          /**< Wrong 'list_sort_by' value. */
    FILENAME_TOO_LONG,              /**< Entered filename is too long. */
    LIST_DEALLOCATION_ERR,          /**< Error while linked list memory freeing. */
    STDIN_EOF_ERR,                  /**< Error while getchar from stdin. */
    MAIN_LOOP_ERROR,                /**< Error: main loop exit . */
    UNKNOWN_ERROR                   /**< For errors with unknown reasons. */
} error_handle_t;

/**
 * @brief Enum that specify if error is critical.
 *
 * If CRITICAL then program will be shutdown,
 * else - only warning must be printed.
 */
typedef enum {
    NON_CRITICAL = 0,   /**< For warnings. */
    CRITICAL = 1        /**< For errors. */
} is_critical_t;

/** @brief Handle errors and warnings during prog execution
 *
 *  Enter number of error from error_handle_t enum.
 *  Set if this error is critical. Func will print msg
 *  that will point out what was wrong acording to error number.
 *  If error is crirtical - then func will stop the program via exit().
 *  If error is not not critical - func will print out warning only.
 *
 *  @param error error_handle_t error that was executed.
 *  @param is_error_critical Specify if program must be shutdowned.
 *  @return Void.
 */
void  error_handler  (error_handle_t error,
                      bool is_error_critical);

#endif /* ERROR_HANDLING_H */

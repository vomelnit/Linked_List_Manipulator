#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NO_ERROR,
    FILENAME_NOT_SPECIFIED,
    FILE_PERMISSIONS_ERR,
    FILE_OPEN_ERROR,
    FILE_CREATION_ERR,
    NO_SPECIFIED_FILE,
    CMD_TOO_LONG,
    WRONG_CMD_ENTERED,
    CMD_EXEC_WRONG,
    ROW_TOO_LONG,
    ROW_DISMATCH_PATTERN,
    ROW_ELEMENTS_DISMATCH,
    TOO_MANY_ARG_IN_ROW,
    MEMORY_ALLOCATION_ERR,
    LINKED_LIST_IS_EMPTY,
    FILE_STAT_ERR,
    WRITE_TO_FILE_ERR,
    VALUE_IS_NOT_NUMBER,
    UNKNOWN_SORT_BY_VALUE
} error_handle_t;

typedef enum {NON_CRITICAL = 0, CRITICAL = 1} is_critical_t;

void  error_handler  (error_handle_t error,
                      bool is_error_critical);

#endif

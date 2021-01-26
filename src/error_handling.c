
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "error_handling.h"

inline void
error_handler (error_handle_t error, bool is_error_critical) {

    if (is_error_critical) printf("\033[31;1m"); /*Red color*/
    else printf("\033[33;1m"); /*Yellow color*/
    printf ("ERROR HANDLER::");

    switch (error) {

    case NO_ERROR:
        printf ("No error.\n");
        break;

    case TOO_MANY_ARG_IN_MAIN:
        printf ("Too many arguments. Specify only filename.\n");
        printf ("Example: $[program name] [filename]\n");
        break;

    case FILE_PERMISSIONS_ERR:
        printf ("Program does not have write or/and read permissions for file.\n");
        break;

    case FILE_OPEN_ERROR:
        printf ("Unable to open file.\n");
        break;

    case FILE_CREATION_ERR:
        printf ("Unable to create file.\n");
        break;

    case NO_SPECIFIED_FILE:
        printf ("There is no specified file.\n");
        break;

    case CMD_TOO_LONG:
        printf ("Command is too long.\n");
        break;

    case WRONG_CMD_ENTERED:
        printf ("Wrong command was entered.\n");
        printf ("Enter 'h' or 'help' to see command interface.\n");
        break;

    case CMD_EXEC_WRONG:
        printf ("Command was executed wrong.\n");
        break;

    case ROW_TOO_LONG:
        printf ("Row is too long.\n");
        break;

    case ROW_DISMATCH_PATTERN:
        printf ("Row doesn't match pattern of data.\n");
        printf ("Must be '(id,years,name)'\n");
        printf ("For ins. (1,22,Yulia)\n");
        printf ("Hint: Last row in file must be filled (no empty line)\n");
        break;

    case ROW_ELEMENTS_DISMATCH:
        printf ("Row elements doesn't match pattern of data.\n");
        printf ("Must be (id,years,name)\n");
        printf ("'id' is number\n'years' is number\n");
        printf ("'name' is string of alphabetical symbols'\n");
        printf ("For ins. (3,52,Oleg)\n");
        break;

    case TOO_MANY_ARG_IN_ROW:
        printf ("There is too much arguments in row\n");
        break;

    case MEMORY_ALLOCATION_ERR:
        printf ("Memory wasn't allocated\n");
        break;

    case LINKED_LIST_IS_EMPTY:
        printf ("Linked list is empty\n");
        break;

    case FILE_STAT_ERR:
        printf ("Cannot get file stats.\n");
        break;

    case WRITE_TO_FILE_ERR:
        printf ("Cannot write to file.\n");
        break;

    case VALUE_IS_NOT_NUMBER:
        printf ("Entered value is not a number.\n");
        break;

    case UNKNOWN_SORT_BY_VALUE:
        printf ("Sorting value is unknown.\n");
        break;

    case FILENAME_TOO_LONG:
        printf ("Entered filename is too long.\n");
        break;

    case LIST_DEALLOCATION_ERR:
        printf ("Error while linked list deallocation.\n");
        break;

    case STDIN_EOF_ERR:
        printf ("Error while getchar from stdin in main loop.\n");
        break;

    case MAIN_LOOP_ERROR:
        printf ("Error: exit from main loop.\n");
        break;

    case UNKNOWN_ERROR:
        printf ("Unknown error.\n");
        break;

    default:
        printf ("Unknown error.\n");
        return;
    }

    printf("\033[0m");
    if (is_error_critical) exit (EXIT_FAILURE);
}

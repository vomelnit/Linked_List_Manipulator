
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "interface.h"

int
print_intial_info(node * head){
    int return_result = 0;
    printf ("Current List:");
    return_result = print_list (head);
    printf ("\nEnter 'h' or 'help' to see command interface.\n");
    printf ("---------------------------------------------\n");
    printf ("Enter command: ");
    return return_result;
}

int main_menu_cmd_processing(char *cmd, node **head, char *filename){
    int   cmd_result = 0;

    cmd_result = execute_main_menu_entered_cmd (cmd, head, filename);
    if      (cmd_result == WRONG_CMD_ENTERED) return WRONG_CMD_ENTERED;
    else if (cmd_result == CMD_EXEC_WRONG) return CMD_EXEC_WRONG;
    else     return NO_ERROR;
}

int main_app_loop (node **head, char *filename_for_list_data){
    int   entered_str_size      = 5;
    char *entered_str           = calloc (entered_str_size, sizeof (char));
    int   character_from_stdin;
    int   symbol_number         = 0;
    int   return_result         = 0;

    while (EOF != (character_from_stdin = getchar ())) {
        if ('\n' != character_from_stdin ){
            entered_str[symbol_number] = character_from_stdin;
            symbol_number++;
            if (symbol_number >= entered_str_size) {
                error_handler (CMD_TOO_LONG, NON_CRITICAL);
                custom_fflush_stdin ();
                entered_str[0] = '\0';
                symbol_number = 0;
                printf ("Enter command: ");
            }
        } else {
            entered_str[symbol_number] = '\0';
            symbol_number = 0;
            return_result = main_menu_cmd_processing(entered_str,
                                                     head,
                                                     filename_for_list_data);
            if (return_result) error_handler (return_result, NON_CRITICAL);
            printf ("Enter command: ");
        }
    } /* while EOF != getchar ()*/
    return MAIN_LOOP_ERROR;
}

void
custom_fflush_stdin (){
	int c;
	while ('\n' != (c = getchar ()) &&
			EOF != c) { }
}

void
print_help_info () {
    const char *help_str = "  ------HELP------\n\
    1 - Show current list elements\n\
    2 - Insert element on the top of list\n\
    3 - Delete element from the top of list\n\
    4 - Find element by 'id'\n\
    5 - Sort list by id\n\
    6 - Sort list by years\n\
    7 - Sort list by name\n\
    8 - Show length of list\n\
    9 - Reverse the list\n\
    exit - Save list to file and exit\n\
    ----------------";
    printf ("%s\n", help_str);
    }

void
exit_routine (char *filename, node *head){
    int result = 0;
    result = save_list_to_file (filename, head);
    if (result) error_handler(UNKNOWN_ERROR, CRITICAL);
    printf ("List was saved into file '%s'.\n", filename);
    printf ("Program is closing...\n");
    if (delete_entire_list(head))
        error_handler(LIST_DEALLOCATION_ERR, NON_CRITICAL);
    free (head);
    exit (EXIT_SUCCESS);
}

int
insert_entered_row_to_linked_list(node **head, char *row){
    int result = 0;
    if (row == NULL) return CMD_EXEC_WRONG;
    if ( (row[0] != '(') ||
       ((strstr(row, ")\r\n") - row) != strlen(row)-3)) {
        error_handler(ROW_DISMATCH_PATTERN, NON_CRITICAL);
        return ROW_DISMATCH_PATTERN;
    }

    char **row_values = get_values_from_file_row(row, NON_CRITICAL);
    if (row_values == NULL) return TOO_MANY_ARG_IN_ROW;
    if (!check_if_row_values_match (row_values)) {
        error_handler (ROW_ELEMENTS_DISMATCH, NON_CRITICAL);
        return ROW_ELEMENTS_DISMATCH;
    }

    result = insert_first_to_list (head, atoi(row_values[0]),
                                   atoi(row_values[1]), row_values[2]);
    if (result) return UNKNOWN_ERROR;
    return NO_ERROR;
}

int
insert_element_into_list_routine(node **head){
    int   character;
    int   entered_row_size = 200;
    int   symbol_number    = 0;
    char *entered_row      = calloc(entered_row_size, sizeof(char));

    printf ("Enter row using format (id,years,name):\n");

    if (entered_row == NULL)
        error_handler(MEMORY_ALLOCATION_ERR, CRITICAL);

    while ( (EOF != (character = getchar ()) ) &&
          ('\n' != character )) {
        entered_row[symbol_number] = character;
        symbol_number++;
        if ((symbol_number + 3) >= entered_row_size) {
            error_handler(ROW_TOO_LONG,NON_CRITICAL);
            custom_fflush_stdin();
            free(entered_row);
            return ROW_TOO_LONG;
        }
    }

    entered_row[symbol_number] = '\r';
    entered_row[symbol_number+1] = '\n';
    int result = insert_entered_row_to_linked_list (head, entered_row);
    free (entered_row);
    return result;
}

int
get_id_and_find_element_by_id (node **head) {
    int   character;
    int   entered_row_size = 10;
    int   symbol_number    = 0;
    char *entered_row      = calloc(entered_row_size, sizeof(char));

    if (NULL == entered_row) error_handler(MEMORY_ALLOCATION_ERR, CRITICAL);

    printf("Enter id: ");
    while ( (EOF != (character = getchar())) &&
          ('\n' != character )) {
        entered_row[symbol_number] = character;
        symbol_number++;
        if ((symbol_number + 3) >= entered_row_size) {
            error_handler(ROW_TOO_LONG, NON_CRITICAL);
            custom_fflush_stdin();
            free(entered_row);
            return ROW_TOO_LONG;
        }
    }

    if (check_if_str_consist_of_digits (entered_row)){
        node *foundLink = get_node_by_id (*head,atoi(entered_row));
        if (NULL == foundLink) {
            printf ("Element wasn't found.\n");
        } else {
            printf ("Element found: ");
            printf ("(%d,%d,%s)\n",foundLink->id,foundLink->years, foundLink->name);
        }
    } else {
        error_handler (VALUE_IS_NOT_NUMBER, NON_CRITICAL);
        return VALUE_IS_NOT_NUMBER;
    }
    return NO_ERROR;
}

int
execute_main_menu_entered_cmd(char *entered_str, node **head, char *filename){
    int result = 0;

    if( (0 == strcmp(entered_str,"help")) ||
        (0 == strcmp(entered_str,"h"))) {
            print_help_info ();
            return NO_ERROR;
    }
    if ((strcmp(entered_str,"exit") == 0)) exit_routine (filename, *head);
    if ((strlen(entered_str) != 1) ||
        ((entered_str[0] < 48 || entered_str[0] > 57))){
            return WRONG_CMD_ENTERED;
    }

        switch ((int)entered_str[0]) {

        case PRINT_LIST:
            print_list (*head);
            break;

        case INSERT_ELEMENT_ON_TOP:
            if (insert_element_into_list_routine(head) != 0)
                return CMD_EXEC_WRONG;
            break;

        case DELETE_ELEMENT_FROM_TOP: {
            node *deleted_node = delete_and_get_first_in_list (head);
            printf ("Deleted value:");
            printf ("(%d,%d,%s)\n",
                deleted_node->id,
                deleted_node->years,
                deleted_node->name);
            free (deleted_node);
            break;
        }

        case FIND_ELEMENT_BY_ID:
            if (get_id_and_find_element_by_id (head) != 0)
            return CMD_EXEC_WRONG;
            break;

        case SORT_LIST_BY_ID:
            result = sort_list (*head, SORT_BY_ID);
            if (result) error_handler(result, NON_CRITICAL);
            else printf ("Sorting by id was done.\n");
            break;

        case SORT_LIST_BY_YEARS:
            result = sort_list (*head, SORT_BY_YEARS);
            if (result) error_handler(result, NON_CRITICAL);
            else printf ("Sorting by years was done.\n");
            break;

        case SORT_LIST_BY_NAME:
            result = sort_list (*head, SORT_BY_NAME);
            if (result) error_handler(result, NON_CRITICAL);
            else printf ("Sorting by name was done.\n");
            break;

        case PRINT_LIST_LENGTH:
            printf ("List length: %d\n",get_list_length (*head));
            break;

        case REVERSE_LIST:
            result = reverse_list (head);
            if (result) error_handler(result, NON_CRITICAL);
            else printf ("List reversed\n");
            break;

        default:
            return WRONG_CMD_ENTERED;
        }
    return NO_ERROR;
}

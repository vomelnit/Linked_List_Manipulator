#include "interface.h"

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
    save_list_to_file (filename, head);
    printf ("List was saved into file '%s'.\n", filename);
    printf ("Program is closing...\n");
    if (delete_entire_list(head))
        error_handler(LIST_DEALLOCATION_ERR, NON_CRITICAL);

    exit (EXIT_SUCCESS);
}

int
insert_entered_row_to_linked_list(node **head, char *row){
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

    insert_first_to_list (head, atoi(row_values[0]),
                          atoi(row_values[1]), row_values[2]);
    return 0;
}

int
insert_element_into_list_routine(node **head){
    int  character;
    int  entered_row_size = 200;
    int  symbol_number = 0;
    char *entered_row = calloc(entered_row_size, sizeof(char));

    printf ("Enter row using format '(<id>,<years>,<name>)':\n");

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
    int  character;
    int  entered_row_size = 10;
    int  symbol_number = 0;
    char *entered_row = calloc(entered_row_size, sizeof(char));

    if (NULL == entered_row) error_handler(MEMORY_ALLOCATION_ERR, CRITICAL);

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
    return 0;
}

int
execute_main_menu_entered_cmd(char *entered_str, node **head){
    if( (0 == strcmp(entered_str,"help")) ||
        (0 == strcmp(entered_str,"h"))) {
            print_help_info ();
            return 0;
    }
    if ((strcmp(entered_str,"exit") == 0)) return 1; /* TODO: rewrite return 1*/
    if ((strlen(entered_str) != 1) ||
        ((entered_str[0] < 48 || entered_str[0] > 57))){
            return WRONG_CMD_ENTERED;
    }

        switch (entered_str[0]) {

        case '1':
            print_list (*head);
            break;

        case '2':
            if (insert_element_into_list_routine(head) != 0)
                return CMD_EXEC_WRONG;
            break;

        case '3': {
            node *deleted_node = delete_and_get_first_in_list (head);
            printf ("Deleted value:");
            printf ("(%d,%d,%s)\n",
                deleted_node->id,
                deleted_node->years,
                deleted_node->name);
            free (deleted_node);
            break;
        }

        case '4':
        if (get_id_and_find_element_by_id (head) != 0)
            return CMD_EXEC_WRONG;
        break;

        case '5':
            sort_list (*head, SORT_BY_ID);
            printf ("Sorting by id was done.\n");
            break;

        case '6':
            sort_list (*head, SORT_BY_YEARS);
            printf ("Sorting by years was done.\n");
            break;

        case '7':
            sort_list (*head, SORT_BY_NAME);
            printf ("Sorting by name was done.\n");
            break;

        case '8':
            printf ("List length: %d\n",get_list_length (*head));
            break;

        case '9':
            reverse_list (head);
            printf ("List reversed\n");
            break;

        default:
            return WRONG_CMD_ENTERED;
        }
    return 0;
}

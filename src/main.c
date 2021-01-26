
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <unistd.h>
#include "interface.h"


/****************************************************************************
*   DEFINES
****************************************************************************/
#define DEFAULT_FILENAME "list.txt"
#define FILENAME_MAX_LENGTH 100

char*
get_filename_for_list_data(int argc, char **argv){
    char *filename_for_list_data =  calloc (FILENAME_MAX_LENGTH, sizeof(char));

    if (argc > 2){
        error_handler (TOO_MANY_ARG_IN_MAIN, CRITICAL);
    } else if (argc == 1){
        filename_for_list_data = DEFAULT_FILENAME;
        printf("Dafault filename '%s' was choosen.\n", DEFAULT_FILENAME);
    } else if (argc == 2){
        if ( strlen(argv[1]) > FILENAME_MAX_LENGTH )
            error_handler (FILENAME_TOO_LONG, CRITICAL);
        filename_for_list_data = argv[1];
    } else {
        printf("Something wrong with argc\n");
        error_handler (UNKNOWN_ERROR, CRITICAL);
    }
    return filename_for_list_data;
}

int
init_linked_list_from_file (char *filename, node **head){
    FILE *list_data_file;
    int   result = 0;

    if ( (access (filename, R_OK) != 0) ||
         (access (filename, R_OK) != 0)){
         return FILE_PERMISSIONS_ERR;
    }

    list_data_file = fopen (filename, "r");
    if (list_data_file == NULL) return FILE_OPEN_ERROR;

    printf ("File '%s' was opened.\n", filename);

    char ** file_rows = get_array_of_rows_from_file (list_data_file);
    result = convert_rows_to_linked_list (head, file_rows);
    if (result) error_handler(UNKNOWN_ERROR, CRITICAL);
    free (file_rows);
    fclose (list_data_file);

    return NO_ERROR;
}

int
create_file_for_linked_list (char *filename){
    FILE *list_data_file;

    list_data_file = fopen (filename, "w");
    if (list_data_file == NULL) return FILE_CREATION_ERR;
    else printf ("File '%s' was created.\n", filename);

    fclose (list_data_file);
    return NO_ERROR;
}

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
    //if (cmd_result == 1) exit_routine (filename, *head);
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

int
main (int argc, char *argv[]) {

    node  *head = NULL;
    int    return_result = 0;
    char * filename_for_list_data = get_filename_for_list_data(argc, argv);


    if (is_file_exist (filename_for_list_data)) {
        return_result = init_linked_list_from_file (filename_for_list_data,&head);
        if (return_result) error_handler(return_result, CRITICAL);
    } else {
        return_result = create_file_for_linked_list(filename_for_list_data);
        if (return_result) error_handler(return_result, CRITICAL);
    }

    if (print_intial_info (head)) error_handler(UNKNOWN_ERROR, NON_CRITICAL);

    return_result = main_app_loop(&head, filename_for_list_data);
    if (return_result) error_handler(return_result, CRITICAL);

  exit(EXIT_FAILURE);
}

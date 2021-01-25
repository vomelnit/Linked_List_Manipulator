#include <unistd.h>
#include "interface.h"

int
main (int argc, char *argv[]) {

    FILE *list_data_file;
    node *head = NULL;

    if (argc != 2){
        error_handler (FILENAME_NOT_SPECIFIED, CRITICAL);
    }

    char *filename_for_list_data = argv[1];

    if (is_file_exist (filename_for_list_data)) {
        if ( (access (filename_for_list_data, R_OK) != 0) ||
             (access (filename_for_list_data, R_OK) != 0)){
             error_handler (FILE_PERMISSIONS_ERR, CRITICAL);
        }

        list_data_file = fopen (filename_for_list_data, "r");
        if (list_data_file == NULL) error_handler (FILE_OPEN_ERROR, CRITICAL);

        printf ("File '%s' was opened.\n", filename_for_list_data);

        char ** file_rows = get_array_of_rows_from_file (list_data_file);
        convert_rows_to_linked_list (&head, file_rows);
        free (file_rows);
    } else {
        error_handler (NO_SPECIFIED_FILE, NON_CRITICAL);
        list_data_file = fopen (filename_for_list_data, "w");
        if (list_data_file == NULL) error_handler (FILE_CREATION_ERR, CRITICAL);
        else printf ("File '%s' was created.\n", filename_for_list_data);
    }
    fclose (list_data_file);

    printf ("Current List:");
    print_list (head);
    printf ("\nEnter 'h' or 'help' to see command interface.\n");
    printf ("---------------------------------------------\n");
    printf ("Enter command: ");

    int   entered_str_size = 5;
    char  *entered_str = calloc (entered_str_size, sizeof (char));
    int   ch;
    int   symbol_number = 0;
    int   cmd_result = 0;

    while (EOF != (ch = getchar ())) {
        if ('\n' != ch ){
            entered_str[symbol_number] = ch;
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
            cmd_result = execute_main_menu_entered_cmd (entered_str, &head);
            if (cmd_result == 1) exit_routine (filename_for_list_data, head);
            else if (cmd_result == WRONG_CMD_ENTERED) error_handler (WRONG_CMD_ENTERED, NON_CRITICAL);
            else if (cmd_result == CMD_EXEC_WRONG) error_handler (CMD_EXEC_WRONG, NON_CRITICAL);

            printf ("Enter command: ");
        }
  }
  return 0;
}

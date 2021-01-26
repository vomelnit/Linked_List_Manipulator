
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "interface.h"


/****************************************************************************
*   DEFINES
****************************************************************************/

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

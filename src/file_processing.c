
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "file_processing.h"

char*
get_filename_for_list_data(int argc, char *argv[]){
    char *filename_for_list_data =  (char*) calloc (FILENAME_MAX_LENGTH,
                                                    sizeof(char));

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

error_handle_t
init_linked_list_from_file (char *filename, node **head){
    FILE            *list_data_file;
    error_handle_t   result;

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

error_handle_t
create_file_for_linked_list (char *filename){
    FILE *list_data_file;

    list_data_file = fopen (filename, "w");
    if (list_data_file == NULL) return FILE_CREATION_ERR;
    else printf ("File '%s' was created.\n", filename);

    fclose (list_data_file);
    return NO_ERROR;
}

inline bool
is_file_exist (char *filename) {
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}

inline long int
get_size_of_file (char *filename) {
    struct stat buffer;
    if (stat (filename, &buffer) != 0)
        error_handler (FILE_STAT_ERR, CRITICAL);

    return buffer.st_size;
}

error_handle_t
put_list_arr_into_file (char *filename_for_list_data,
                        char **row_arr,
                        int row_arr_size) {
    FILE *file = fopen (filename_for_list_data, "w");
    if (NULL == file)
        return FILE_OPEN_ERROR;
    for (int i = 0; i < row_arr_size; i++) {
        if (!fputs(row_arr[i], file))
            return WRITE_TO_FILE_ERR;
    }
    fclose (file);
    return NO_ERROR;
}

error_handle_t
save_list_to_file (char *filename_for_list_data, node *head) {
    error_handle_t result;
    char **entire_list_array_as_strings = get_list_as_string_array (head);
    result = put_list_arr_into_file (filename_for_list_data,
                                     entire_list_array_as_strings,
                                     get_list_length (head));
    if (result) error_handler (result, CRITICAL);
    free (entire_list_array_as_strings);

    return NO_ERROR;
}

char**
get_array_of_rows_from_file (FILE *file){
    if (file == NULL)
        error_handler (FILE_OPEN_ERROR, CRITICAL);

    int    row_arr_size = 30;
    char   *line = NULL;
    size_t len = 0;
    int    i = 0;
    char   **row_arr = (char**) calloc (row_arr_size, sizeof(char *));

    if (row_arr == NULL)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);

    while (-1 != getline(&line, &len, file) ) {
        if ((i+2) >= row_arr_size) {
            row_arr_size += 10;
            row_arr = (char**) realloc(row_arr, row_arr_size * sizeof (char *));
            if (row_arr == NULL)
                error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
        }
        row_arr[i] = (char*) calloc ((strlen (line) + 1) , sizeof (char));
        if (row_arr[i] == NULL)
            error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
        strcpy (row_arr[i], line);
        i++;
    }
    free (line);

    return row_arr;
}

char**
get_values_from_file_row (char *row, is_critical_t is_error_critical){
    char **values = (char**) calloc (NODE_VALUE_NUMBER, sizeof (char*));
    if (NULL == values)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    int  value_str_size = 100;

    for (int k = 0; k < NODE_VALUE_NUMBER; k++){
        values[k] = (char*) calloc (value_str_size, sizeof(char));
        if (NULL == values[k])
            error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    }
    unsigned int j = 1;
    int value_index = 0;
    int value_symbol_index = 0;

    while(j <= (strlen (row) - 4)){
        if (row[j] != ',') {
            values[value_index][value_symbol_index] = row[j];
            value_symbol_index++;

            if ( (value_str_size + 2) >= value_symbol_index) {
                value_str_size += 20;
                values[value_index] = (char*) realloc (values[value_index],
                                        sizeof (char) * value_str_size);
                if (NULL == values[value_index])
                    error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
            }
        } else {
            values[value_index][value_symbol_index] = '\0';
            value_index++;
            value_str_size = 100;
            value_symbol_index = 0;

            if (value_index >= NODE_VALUE_NUMBER) {
                printf("Row '%s': ", row);
                error_handler(TOO_MANY_ARG_IN_ROW, is_error_critical);
                return NULL;
            }
        }
        j++;
    }
    return values;
}

inline bool
check_if_str_consist_of_digits (char *string) {
    unsigned int i;
    for (i = 0; i < strlen( string ); i++) {
    if (string[i] < 48 || string[i] > 57) return FALSE;
    }
    return TRUE;
}

inline bool
check_if_str_consist_of_alphabets(char *str){
    unsigned int i;
    for(i = 0; i < strlen(str); i ++){
        if ((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] == ' '))
            continue;
        else
            return FALSE;
     }
     return TRUE;
}

bool
check_if_row_values_match (char **values) {
    bool result = TRUE;
    result &= check_if_str_consist_of_digits (values[0]);
    result &= check_if_str_consist_of_digits (values[1]);
    result &= check_if_str_consist_of_alphabets (values[2]);

    return result;
}

error_handle_t
convert_rows_to_linked_list (node **head, char **rows){
    int i              = 0;
    error_handle_t result ;
    while (NULL != rows[i]) {
        if ( ('(' != rows[i][0]) ||
             ((strstr(rows[i], ")\r\n") - rows[i]) != (int)strlen(rows[i])-3)) {
            printf("Row %d:", i+1);
            error_handler (ROW_DISMATCH_PATTERN, CRITICAL);
        }

        char **row_values = get_values_from_file_row (rows[i], CRITICAL);
        if (NULL == row_values)
            error_handler (TOO_MANY_ARG_IN_ROW, CRITICAL);
        if (!check_if_row_values_match (row_values)) {
            printf ("Row %d: ", i+1);
            error_handler (ROW_ELEMENTS_DISMATCH, CRITICAL);
        }

        result = insert_first_to_list (head, atoi(row_values[0]),
                                       atoi(row_values[1]), row_values[2]);
        if (result) error_handler(UNKNOWN_ERROR, CRITICAL);
        i++;
    }

    result = reverse_list (head);
    if (result) error_handler (result, NON_CRITICAL);

    return NO_ERROR;
}

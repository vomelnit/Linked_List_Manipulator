
/****************************************************************************
*   INCLUDES
****************************************************************************/
#include "file_processing.h"

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

void
put_list_arr_into_file (char *filename_for_list_data,
                        char **row_arr,
                        int row_arr_size) {
    FILE *file = fopen (filename_for_list_data, "w");
    if (NULL == file)
        error_handler (FILE_OPEN_ERROR, CRITICAL);
    for (int i = 0; i < row_arr_size; i++) {
        if (!fputs(row_arr[i], file))
            error_handler (WRITE_TO_FILE_ERR, CRITICAL);
    }
    fclose (file);
}

void
save_list_to_file (char *filename_for_list_data, node *head) {
    char **entire_list_array_as_strings = get_list_as_string_array (head);
    put_list_arr_into_file (filename_for_list_data,
                            entire_list_array_as_strings,
                            get_list_length (head));
    free (entire_list_array_as_strings);
}

char**
get_array_of_rows_from_file (FILE *file){
    if (file == NULL)
        error_handler (FILE_OPEN_ERROR, CRITICAL);

    int    row_arr_size = 30;
    char   *line = NULL;
    size_t len = 0;
    int    i = 0;
    char   **row_arr = calloc (row_arr_size, sizeof(char *));

    if (row_arr == NULL)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);

    while (-1 != getline(&line, &len, file) ) {
        if ((i+2) >= row_arr_size) {
            row_arr_size += 10;
            row_arr = realloc(row_arr, row_arr_size * sizeof (char *));
            if (row_arr == NULL)
                error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
        }
        row_arr[i] = calloc ((strlen (line) + 1) , sizeof (char));
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
    char **values = calloc (NODE_VALUE_NUMBER, sizeof (char*));
    if (NULL == values)
        error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    int  value_str_size = 100;

    for (int k = 0; k < NODE_VALUE_NUMBER; k++){
        values[k] = calloc (value_str_size, sizeof(char));
        if (NULL == values[k])
            error_handler (MEMORY_ALLOCATION_ERR, CRITICAL);
    }
    int j = 1;
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
    for (int i = 0; i < strlen( string ); i++) {
    if (string[i] < 48 || string[i] > 57) return FALSE;
    }
    return TRUE;
}

inline bool
check_if_str_consist_of_alphabets(char *str){
    for(int i = 0; i < strlen(str); i ++){
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
    int result = 1;
    result &= check_if_str_consist_of_digits (values[0]);
    result &= check_if_str_consist_of_digits (values[1]);
    result &= check_if_str_consist_of_alphabets (values[2]);

    return result;
}

void
insert_row_values_into_linked_list (node **head, char **values) {
    insert_first_to_list (head, atoi(values[0]), atoi(values[1]), values[2]);
}

void
convert_rows_to_linked_list (node **head, char **rows){
    int i = 0;
    while (NULL != rows[i]) {
        if ( ('(' != rows[i][0]) ||
             ((strstr(rows[i], ")\r\n") - rows[i]) != strlen(rows[i])-3)) {
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

        insert_first_to_list (head, atoi(row_values[0]),
                              atoi(row_values[1]), row_values[2]);
        i++;
    }
    reverse_list (head);
}

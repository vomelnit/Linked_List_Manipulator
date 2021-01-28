#include <gtest/gtest.h>

#include "interface.h"

#define BUFF_SIZE 1024

class LinkedListInitializationTest : public ::testing::Test
{
   protected:

       char *filename_for_list_data;
       FILE *file;
       uint8_t max_name_length = 20;
       uint16_t row_number = 100;
       node *head = NULL;
       node *head_to_compare = NULL;

       virtual void SetUp()
       {
           int years;
           char *person_name      = (char *) calloc (max_name_length, sizeof(char ));
           filename_for_list_data = (char *) calloc (20, sizeof(char ));
           strcpy(filename_for_list_data, "testfile.txt");

           file = fopen(filename_for_list_data, "w"); // write only
           if (file == NULL) printf("File wasn't opened.\n");

           for (uint8_t row_ctr = 0; row_ctr < row_number; row_ctr++){
               years = rand() % 50 + 1960;
               person_name = getRandomName(person_name, max_name_length);
               insert_first_to_list(&head_to_compare, row_ctr + 1, years, person_name);
               fprintf(file, "(%d,%d,%s)\r\n", row_ctr + 1, years, person_name);
           }
           reverse_list (&head_to_compare);
           free(person_name);
           fclose (file);
       }

       virtual void TearDown()
       {
           if (remove(filename_for_list_data)){
               printf("File '%s' wasn't deleted\n", filename_for_list_data);
           }
           free(filename_for_list_data);
           delete_entire_list(head_to_compare);
           delete_entire_list(head);
       }

       char *getRandomName(char *person_name, uint8_t max_name_length){
           uint8_t str_ctr;
           char *filename_for_list_data;
           person_name[0] = rand() % ('Z'-'A') + 'A';
           uint8_t name_length = rand() % (max_name_length-5) + 5;
           for (str_ctr = 1; str_ctr + 1 < name_length; str_ctr++){
               person_name[str_ctr] = rand() % ('z'-'a') + 'a';
           }
           person_name[str_ctr + 1] = '\0';
           return  person_name;
       }
};

TEST_F (LinkedListInitializationTest, NormalFile){
    error_handle_t result;
    result = init_linked_list_from_file (filename_for_list_data, &head);
    ASSERT_TRUE(result == NO_ERROR);
}


TEST_F (LinkedListInitializationTest, WrongRowsInFile_BeginFormat){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"[112,2000,Andrey)\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);
    
    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_MiddleFormat1){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(112.2000,Andrey)\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_MiddleFormat2){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(112,2000 Andrey)\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_EndFormat){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(112,2000,Andrey\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_firstValue){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(1e1,1988,Hello)\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}
TEST_F (LinkedListInitializationTest, WrongRowsInFile_secondValue){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(111,123f,Hello)\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_thirdValue){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(111,1999,Hel1lo)\r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_NoNewLine){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(111,1999,Hello)");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, WrongRowsInFile_ExcessSpace){
    file = fopen(filename_for_list_data, "a"); // write only
    if (file == NULL) printf("File wasn't opened.\n");

    fprintf(file,"(111,1999,Hello) \r\n");
    fprintf(file,"(121,1997,Egor)\r\n");
    fprintf(file,"(122,1977,Valentin)\r\n");
    fclose (file);

    EXPECT_EXIT(init_linked_list_from_file (filename_for_list_data, &head),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

TEST_F (LinkedListInitializationTest, CheckDataToListConvertation){
    error_handle_t result;
    node *permanent_element;
    node *element_from_file;

    result = init_linked_list_from_file (filename_for_list_data, &head);
    ASSERT_TRUE(result == NO_ERROR);
    ASSERT_EQ(get_list_length(head), get_list_length(head_to_compare));
    ASSERT_EQ(get_list_length(head), row_number);

    for (uint16_t link_ctr = 0; link_ctr < row_number; link_ctr++){
        permanent_element = delete_and_get_first_in_list(&head_to_compare);
        element_from_file = delete_and_get_first_in_list(&head);
        ASSERT_EQ(permanent_element->id, element_from_file->id);
        ASSERT_EQ(permanent_element->years, element_from_file->years);
        ASSERT_STREQ(permanent_element->name, element_from_file->name);
    }

    ASSERT_TRUE(is_list_empty(head_to_compare));
    ASSERT_TRUE(is_list_empty(head));
    free (permanent_element);
    free(element_from_file);
}

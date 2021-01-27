/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <gtest/gtest.h>

#include "interface.h"

TEST (TestConsoleArguments, WithoutArguments){
    int argc    = 1;
    char **argv = (char **) calloc (1, sizeof(char*)     );
    argv[0]     = (char * ) calloc (1, sizeof(char ) * 20);
    strcpy(argv[0],"program_name");

    char *filename_for_list_data = get_filename_for_list_data(argc, argv);

    ASSERT_STREQ(filename_for_list_data, DEFAULT_FILENAME);
}

TEST (TestConsoleArguments, SpecifiedFilename){
    int   argc = 2;
    char *filename_for_list_data;
    char **argv = (char **) calloc (2, sizeof(char*));//(char **) calloc(1, sizeof(char*));
    argv[0] = (char *) calloc (1, sizeof(char)*20);
    argv[1] = (char *) calloc (1, sizeof(char)*20);

    strcpy(argv[0],"program_name");
    strcpy(argv[1],"file.txt");

    filename_for_list_data = get_filename_for_list_data(argc, argv);
    ASSERT_STREQ(filename_for_list_data, "file.txt");

    strcpy(argv[1],"lalala.txt");
    filename_for_list_data = get_filename_for_list_data(argc, argv);
    ASSERT_STREQ(filename_for_list_data, "lalala.txt");
}

TEST (TestConsoleArguments, TooManyArguments){
    int argc = 3;
    char *error_msg = "ERROR HANDLER::Too many arguments. Specify only filename.";
    char **argv = (char **) calloc (3, sizeof(char*));
    argv[0] = (char *) calloc (1, sizeof(char)*20);
    argv[1] = (char *) calloc (1, sizeof(char)*20);
    argv[2] = (char *) calloc (1, sizeof(char)*20);

    strcpy(argv[0],"program_name");
    strcpy(argv[1],"file.txt");
    strcpy(argv[2],"excess_agrument");

    char *filename_for_list_data;

    EXPECT_EXIT(get_filename_for_list_data(argc, argv),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

int
main (int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

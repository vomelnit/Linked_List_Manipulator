#include <gtest/gtest.h>

#include "file_processing.h"

class ConsoleArgumentsTest : public ::testing::Test
{
  protected:

      int    argc;
      char **argv;
      char  *filename_for_list_data;

      virtual void SetUp()
      {
          argv    = (char **) calloc (3,  sizeof(char*));
          argv[0] = (char * ) calloc (20, sizeof(char ));
          argv[1] = (char * ) calloc (20, sizeof(char ));
          argv[2] = (char * ) calloc (20, sizeof(char ));
          strcpy(argv[0], "program_name");
      }

      virtual void TearDown()
      {
          free(argv);
      }
};


TEST_F (ConsoleArgumentsTest, WithoutArguments){
    argc    = 1;
    filename_for_list_data = get_filename_for_list_data(argc, argv);
    ASSERT_STREQ(filename_for_list_data, DEFAULT_FILENAME);
}

TEST_F (ConsoleArgumentsTest, SpecifiedFilename){
    argc = 2;
    strcpy(argv[1],"file.txt");

    filename_for_list_data = get_filename_for_list_data(argc, argv);
    ASSERT_STREQ(filename_for_list_data, "file.txt");

    strcpy(argv[1],"lalala.txt");
    filename_for_list_data = get_filename_for_list_data(argc, argv);
    ASSERT_STREQ(filename_for_list_data, "lalala.txt");
}

TEST_F (ConsoleArgumentsTest, TooManyArguments){
    argc = 3;
    strcpy(argv[1],"file.txt");
    strcpy(argv[2],"excess_agrument");

    EXPECT_EXIT(get_filename_for_list_data(argc, argv),
                ::testing::ExitedWithCode(EXIT_FAILURE),
                "");
}

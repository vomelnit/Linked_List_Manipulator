/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <gtest/gtest.h>

#include "console_arguments_test.h"
#include "linked_list_initialization_test.h"
#include "interface.h"
using namespace std;

#define BUFF_SIZE 1024

int
main (int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    return result;
}

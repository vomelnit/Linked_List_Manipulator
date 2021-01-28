/****************************************************************************
*   INCLUDES
****************************************************************************/
#include <gtest/gtest.h>

#include "console_arguments_test.h"
#include "linked_list_initialization_test.h"
#include "interface.h"

int
main (int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

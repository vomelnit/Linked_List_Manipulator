TARGET_DIR    =./bin
OBJ_DIR       =./obj
SRC_DIR       =./src
INCLUDES      =./inc
TEST_DIR	  =./test
TEST_INCLUDES =./test
TARGET        = $(TARGET_DIR)/program
TEST_TARGET   = $(TARGET_DIR)/tests
CC            = gcc -std=c11
CPP		      = g++ -std=c++11
CFLAGS     	  = -Wall -Wextra #-Werror
TEST_FLAGS    = -lgtest -lgtest_main  -pthread

MAIN_SRC      = $(SRC_DIR)/main.c
MAIN_TEST_SRC = $(TEST_DIR)/test_main.cpp

SRC           = $(SRC_DIR)/interface.c \
	        	$(SRC_DIR)/error_handling.c \
	        	$(SRC_DIR)/file_processing.c \
 			 	$(SRC_DIR)/linked_list.c

OBJ 	      = $(SRC:.c=.o)
MAIN_OBJ      = $(MAIN_SRC:.c=.o)
MAIN_TEST_OBJ = $(MAIN_TEST_SRC:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJ_DIR) $(OBJ) $(MAIN_OBJ) $(TARGET_DIR)
	 $(CC) -o $(TARGET) $(CFLAGS) $(MAIN_OBJ) $(OBJ) -I $(INCLUDES) ; mv $(SRC_DIR)/*.o $(OBJ_DIR)/

test: $(TEST_TARGET)

$(TEST_TARGET): $(OBJ_DIR) $(OBJ) $(MAIN_TEST_OBJ) $(TARGET_DIR)
	$(CPP) -o $(TEST_TARGET) $(CFLAGS) $(MAIN_TEST_OBJ) $(OBJ) -I $(INCLUDES) -I $(TEST_INCLUDES) $(TEST_FLAGS);\
	mv $(SRC_DIR)/*.o $(OBJ_DIR)/;
	mv $(TEST_DIR)/*.o $(OBJ_DIR)/

$(TARGET_DIR):
	test ! -d $(TARGET_DIR) && mkdir $(TARGET_DIR)

$(OBJ_DIR):
	test ! -d $(OBJ_DIR) && mkdir $(OBJ_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

$(MAIN_OBJ):
	$(CC) $(CFLAGS) -o $@ -c $(MAIN_SRC) -I $(INCLUDES)

$(MAIN_TEST_OBJ):
	$(CPP) $(CFLAGS) -o $@ -c $(MAIN_TEST_SRC) -I $(INCLUDES) -I $(TEST_INCLUDES)

clean:
	rm -rf $(OBJ_DIR)/*

fclean: clean
	rm -rf $(TARGET)

re: fclean all

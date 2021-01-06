TARGET_DIR =./bin
OBJ_DIR    =./obj
SRC_DIR    =./src
TARGET     = $(TARGET_DIR)/program
CC         = gcc -std=c11
CFLAGS     = -Wall -Wextra #-Werror
SRC        = $(SRC_DIR)/main.c \
             $(SRC_DIR)/interface.c \
	     $(SRC_DIR)/error_handling.c \
	     $(SRC_DIR)/file_processing.c \
	     $(SRC_DIR)/linked_list.c\

#OBJ        = main.o \
#             interface.o \
#             error_handling.o \
#             file_processing.o \
#             linked_list.o\


OBJ = $(SRC:.c=.o)

INCLUDES  = ./inc

all: $(TARGET)

$(TARGET): $(OBJ_DIR) $(OBJ) $(TARGET_DIR)
	 $(CC) -o $(TARGET) $(CFLAGS) $(SRC) -I $(INCLUDES); mv $(SRC_DIR)/*.o $(OBJ_DIR)/ 

$(TARGET_DIR):
	test ! -d $(TARGET_DIR) && mkdir $(TARGET_DIR)

$(OBJ_DIR):
	test ! -d $(OBJ_DIR) && mkdir $(OBJ_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES) 

$(MV_OBJ):
	mv $(SRC_DIR)/*.o $(OBJ_DIR)/  

clean:
	rm -rf $(OBJ_DIR)/*

fclean: clean
	rm -rf $(TARGET)

re: fclean all

# ------------------------------ compiler ----------------------------------------
CC = gcc

# ------------------------------ directories -----------------------------------
SRC_DIR = src
INC_DIR = include
TST_DIR = test

# -------- placement to save bin (exe ?) and obj file -------------------------
OBJ_DIR = obj
BIN_DIR = bin

# ------------------------------ files ----------------------------------------
# -------- foo (makefile worksheet) -------------------------------------------
SRC_FOO = $(SRC_DIR)/foo.c
INC_FOO = $(INC_DIR)/foo.h
TEST_FOO = $(TST_DIR)/main.c
OBJ_FOO = $(OBJ_DIR)/foo.o

# -------- bit array (bit array worksheet) ------------------------------------
SRC_BIT_ARRAY = $(SRC_DIR)/bit_array.c
INC_BIT_ARRAY = $(INC_DIR)/bit_array.h
TEST_BIT_ARRAY = $(TST_DIR)/bit_array_test.c
OBJ_BIT_ARRAY = $(OBJ_DIR)/bit_array.o

# -------- stack (stack worksheet) --------------------------------------------
SRC_STACK = $(SRC_DIR)/stack.c
INC_STACK = $(INC_DIR)/stack.h
TEST_STACK = $(TST_DIR)/stack_test.c
OBJ_STACK = $(OBJ_DIR)/stack.o

# -------- vector (dynamic vector worksheet) ----------------------------------
SRC_VECTOR = $(SRC_DIR)/vector.c
INC_VECTOR = $(INC_DIR)/vector.h
TEST_VECTOR = $(TST_DIR)/vector_test.c
OBJ_VECTOR = $(OBJ_DIR)/vector.o

# -------- slist (singly linked list worksheet) -------------------------------
SRC_SLIST = $(SRC_DIR)/slsit.c
INC_SLIST = $(INC_DIR)/slist.h
TEST_SLIST = $(TST_DIR)/slist_test.c
OBJ_SLIST = $(OBJ_DIR)/slist.o

# -------- slist_ex (slist exercise worksheet) --------------------------------
SRC_SLIST_EX = $(SRC_DIR)/slsit_ex.c
INC_SLIST_EX = $(INC_DIR)/slist_ex.h
TEST_SLIST_EX = $(TST_DIR)/slist_ex_test.c
OBJ_SLIST_EX = $(OBJ_DIR)/slist_ex.o

# -------- queue (queue worksheet) --------------------------------------------
SRC_QUEUE = $(SRC_DIR)/queue.c
INC_QUEUE = $(INC_DIR)/queue.h
TEST_QUEUE = $(TST_DIR)/queuetest.c
OBJ_QUEUE = $(OBJ_DIR)/queue.o

# -------- ------------ all sources --------------------------------------------
SRC_ALL = $(SRC_FOO) $(SRC_STACK) $(SRC_BIT_ARRAY) \
          $(SRC_VECTOR) $(SRC_SLIST) $(SRC_QUEUE) \
          $(TEST_FOO)
          
# ------------------------------ objects ---------------------------------------
OBJS_ALL = $(SRC_ALL:%.c=$(OBJ_DIR)/%.o)

# ------------------------------ target ---------------------------------------
TARGET = $(BIN_DIR)/prog

# ------------------------------ flags ---------------------------------------
CFLAGS_COMMON = -Wall -Wextra -pedantic-errors -I $(INC_DIR)

CFLAGS_C89_DEBUG   = -ansi $(CFLAGS_COMMON) -g
CFLAGS_C89_RELEASE = -ansi $(CFLAGS_COMMON) -DNDEBUG -O3

CFLAGS_C99_DEBUG   = -std=c99 $(CFLAGS_COMMON) -g
CFLAGS_C99_RELEASE = -std=c99 $(CFLAGS_COMMON) -DNDEBUG -O3

LDFLAGS = -lm

# ------------------------------ default ---------------------------------------
all: c89-release

# ------------------------------ build modes -----------------------------------

c89-debug:   CFLAGS = $(CFLAGS_C89_DEBUG)
c89-debug:   $(TARGET)

c89-release: CFLAGS = $(CFLAGS_C89_RELEASE)
c89-release: $(TARGET)

c99-debug:   CFLAGS = $(CFLAGS_C99_DEBUG)
c99-debug:   $(TARGET)

c99-release: CFLAGS = $(CFLAGS_C99_RELEASE)
c99-release: $(TARGET)

# ------------------------------ linking ---------------------------------------

$(TARGET): $(OBJS_ALL) | $(BIN_DIR)
	$(CC) $(OBJS_ALL) $(LDFLAGS) -o $@

# ------------------------------ compilation -----------------------------------

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# -------- directories --------

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# -------- utilities --------

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean c89-debug c89-release c99-debug c99-release


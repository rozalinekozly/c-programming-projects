# Compiler and Flags
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG_FLAGS = -g
RELEASE_FLAGS = -DNDEBUG -O3
INC = -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
TEST_DIR = test
OBJ_DIR = bin/obj
BIN_DIR = bin

# Valgrind command
VLG = valgrind --leak-check=yes --track-origins=yes

# Modules list
MODULES = bit_array buffer slist slist_ex dlist stack uid vector queue sorted_list pqueue task scheduler

# Targets
.PHONY: all debug release clean test_all

all: debug

# --- Compilation Logic ---

# Prevent Make from deleting object files automatically
.PRECIOUS: $(OBJ_DIR)/%.o

# Debug Build for all
debug: $(foreach mod,$(MODULES),$(BIN_DIR)/$(mod)_debug)

# Release Build for all
release: $(foreach mod,$(MODULES),$(BIN_DIR)/$(mod)_release)

# Pattern rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INC) -c $< -o $@

# --- Dependencies Handling ---
# -> if you want to add a make file, use same you must add all 
# the dependencies (this is not effective must be corrected! and 
# doesn't make the actual job of "make"

# queue depends on slist
$(BIN_DIR)/queue_debug: $(OBJ_DIR)/slist.o
$(BIN_DIR)/queue_release: $(OBJ_DIR)/slist.o

# sorted_list depends on dlist
$(BIN_DIR)/sorted_list_debug: $(OBJ_DIR)/dlist.o
$(BIN_DIR)/sorted_list_release: $(OBJ_DIR)/dlist.o

# pqueue depends on sorted_list AND dlist
$(BIN_DIR)/pqueue_debug: $(OBJ_DIR)/sorted_list.o $(OBJ_DIR)/dlist.o
$(BIN_DIR)/pqueue_release: $(OBJ_DIR)/sorted_list.o $(OBJ_DIR)/dlist.o

# task depends on uid
$(BIN_DIR)/task_debug: $(OBJ_DIR)/uid.o
$(BIN_DIR)/task_release: $(OBJ_DIR)/uid.o

# scheduler depends on EVERYTHING below it
# Added: sorted_list.o and dlist.o
$(BIN_DIR)/scheduler_debug: $(OBJ_DIR)/uid.o $(OBJ_DIR)/task.o $(OBJ_DIR)/pqueue.o $(OBJ_DIR)/sorted_list.o $(OBJ_DIR)/dlist.o
$(BIN_DIR)/scheduler_release: $(OBJ_DIR)/uid.o $(OBJ_DIR)/task.o $(OBJ_DIR)/pqueue.o $(OBJ_DIR)/sorted_list.o $(OBJ_DIR)/dlist.o
# --- Linker Rules ---

# Generic rule to build a debug executable
$(BIN_DIR)/%_debug: $(TEST_DIR)/%_test.c $(OBJ_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INC) $^ -o $@ $(LDFLAGS)

# Generic rule to build a release executable
$(BIN_DIR)/%_release: $(TEST_DIR)/%_test.c $(OBJ_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(RELEASE_FLAGS) $(INC) $^ -o $@ $(LDFLAGS)

# --- Utility Tasks ---

# Run valgrind on everything
test_all: debug
	@for mod in $(MODULES); do \
		echo "\n--- Testing $$mod ---"; \
		$(VLG) ./$(BIN_DIR)/$${mod}_debug; \
	done
	
# Shortcuts for running
deb_%: $(BIN_DIR)/%_debug
	./$<

rel_%: $(BIN_DIR)/%_release
	./$<

vlg_%: $(BIN_DIR)/%_debug
	$(VLG) ./$<

clean:
	rm -rf bin

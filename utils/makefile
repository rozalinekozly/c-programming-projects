# utils/Makefile

# Configuration
SRC_DIR     := src
INCLUDE_DIR := include
BIN_DIR     := bin

CC       := gcc
CFLAGS   := -ansi -Wall -Wextra -pedantic-errors
CPPFLAGS := -I$(INCLUDE_DIR)
LDLIBS   := -lm

# Build mode
ifeq ($(filter release, $(MAKECMDGOALS)), release)
  OBJDIR := $(BIN_DIR)/release
  CFLAGS += -O3
  CPPFLAGS += -DNDEBUG
else
  OBJDIR := $(BIN_DIR)/debug
  CFLAGS += -g
endif

LIB := $(OBJDIR)/libutils.so

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)
DEPS      := $(OBJS:.o=.d)

vpath %.c $(SRC_DIR)

.PHONY: all debug release clean

all:
	@$(MAKE) debug
	@$(MAKE) release

debug: $(LIB)
release: $(LIB)

$(LIB): $(OBJS) | $(OBJDIR)
	$(CC) -shared -fPIC -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -MMD -MT $@ -MF $(@:.o=.d) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(BIN_DIR)/debug/*.o $(BIN_DIR)/debug/*.d $(BIN_DIR)/debug/*.so
	rm -f $(BIN_DIR)/release/*.o $(BIN_DIR)/release/*.d $(BIN_DIR)/release/*.so

-include $(DEPS)

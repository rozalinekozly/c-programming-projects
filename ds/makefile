CC = gcc

# ---------------- flags ----------------
CFLAGS_COMMON = -Wall -Wextra -pedantic-errors -I include
CFLAGS_C89_DEBUG   = -ansi $(CFLAGS_COMMON) -g
CFLAGS_C89_RELEASE = -ansi $(CFLAGS_COMMON) -DNDEBUG -O3

LDFLAGS  = -lm
VALGRIND = valgrind --leak-check=yes --track-origins=yes

# ---------------- top level ----------------
all: debug release

debug:   stack-debug bit_array-debug slist-debug slist_ex-debug vector-debug queue-debug
release: stack-release bit_array-release slist-release slist_ex-release vector-release queue-release

# =========================================================
# stack
# =========================================================
stack:
	$(CC) $(CFLAGS) src/stack.c test/stack_test.c -o $(OUT) $(LDFLAGS)

stack-debug: CFLAGS = $(CFLAGS_C89_DEBUG)
stack-debug: OUT = stack_debug
stack-debug: stack

stack-release: CFLAGS = $(CFLAGS_C89_RELEASE)
stack-release: OUT = stack_release
stack-release: stack

stack-val: stack-debug
	$(VALGRIND) ./stack_debug

# =========================================================
# bit array
# =========================================================
bit_array:
	$(CC) $(CFLAGS) src/bit_array.c test/bit_array_test.c -o $(OUT) $(LDFLAGS)

bit_array-debug: CFLAGS = $(CFLAGS_C89_DEBUG)
bit_array-debug: OUT = bit_array_debug
bit_array-debug: bit_array

bit_array-release: CFLAGS = $(CFLAGS_C89_RELEASE)
bit_array-release: OUT = bit_array_release
bit_array-release: bit_array

bit_array-val: bit_array-debug
	$(VALGRIND) ./bit_array_debug

# =========================================================
# slist
# =========================================================
slist:
	$(CC) $(CFLAGS) src/slist.c test/slist_test.c -o $(OUT) $(LDFLAGS)

slist-debug: CFLAGS = $(CFLAGS_C89_DEBUG)
slist-debug: OUT = slist_debug
slist-debug: slist

slist-release: CFLAGS = $(CFLAGS_C89_RELEASE)
slist-release: OUT = slist_release
slist-release: slist

slist-val: slist-debug
	$(VALGRIND) ./slist_debug

# =========================================================
# slist_ex
# =========================================================
slist_ex:
	$(CC) $(CFLAGS) src/slist_ex.c test/slist_ex_test.c -o $(OUT) $(LDFLAGS)

slist_ex-debug: CFLAGS = $(CFLAGS_C89_DEBUG)
slist_ex-debug: OUT = slist_ex_debug
slist_ex-debug: slist_ex

slist_ex-release: CFLAGS = $(CFLAGS_C89_RELEASE)
slist_ex-release: OUT = slist_ex_release
slist_ex-release: slist_ex

slist_ex-val: slist_ex-debug
	$(VALGRIND) ./slist_ex_debug

# =========================================================
# vector
# =========================================================
vector:
	$(CC) $(CFLAGS) src/vector.c test/vector_test.c -o $(OUT) $(LDFLAGS)

vector-debug: CFLAGS = $(CFLAGS_C89_DEBUG)
vector-debug: OUT = vector_debug
vector-debug: vector

vector-release: CFLAGS = $(CFLAGS_C89_RELEASE)
vector-release: OUT = vector_release
vector-release: vector

vector-val: vector-debug
	$(VALGRIND) ./vector_debug

# =========================================================
# queue (depends on slist)
# =========================================================
queue:
	$(CC) $(CFLAGS) src/queue.c src/slist.c test/queue_test.c -o $(OUT) $(LDFLAGS)

queue-debug: CFLAGS = $(CFLAGS_C89_DEBUG)
queue-debug: OUT = queue_debug
queue-debug: queue

queue-release: CFLAGS = $(CFLAGS_C89_RELEASE)
queue-release: OUT = queue_release
queue-release: queue

queue-val: queue-debug
	$(VALGRIND) ./queue_debug

# ---------------- utils ----------------
clean:
	rm -f *_debug *_release

.PHONY: all debug release clean


CC = gcc
FLAGS = -Wall -Wextra -pedantic -g
INCLUDES = -I ../utils/include

YELLOW = \033[1;33m
RESET = \033[0m

.DEFAULT_GOAL := help

help:
	@echo "$(YELLOW)available commands:$(RESET)"
	@echo "$(YELLOW)  make sem_manip  - last modified: $(shell date -r src/sem_manipulation.c '+%Y-%m-%d %H:%M:%S')$(RESET)"
	@echo "$(YELLOW)  make clear      - last modified: $(shell date -r Makefile '+%Y-%m-%d %H:%M:%S')$(RESET)"

sem_manip:
	$(CC) $(FLAGS) src/sem_manipulation.c $(INCLUDES) -lm -o sem_manip
	@echo "$(YELLOW)---------- file name: sem_manip --------------$(RESET)"
	@echo "$(YELLOW)type: r to run, x to do nothing$(RESET)"
	@read input && [ "$$input" = "r" ] && ./sem_manip || true

clear:
	@rm -f sem_manip
	@echo "$(YELLOW)------- all release & debug files via make has been removed! -------$(RESET)"

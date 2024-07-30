CFLAGS = -Wall -Werror -Wextra -std=c11

all : s21_grep

s21_grep : grep.o
	gcc $(CFLAGS) -o s21_grep grep.o

grep.o : grep.c
	gcc $(CFLAGS) -o grep.o -c grep.c

test: s21_grep_test.sh
	sh s21_grep_test.sh

clean :
	-rm *.o
	-rm s21_grep

rebuild: clean all
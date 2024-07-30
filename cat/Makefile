CFLAGS = -Wall -Werror -Wextra -std=c11

all : s21_cat

s21_cat : cat.o
	gcc $(CFLAGS) -o s21_cat cat.o

cat.o : cat.c
	gcc $(CFLAGS) -o cat.o -c cat.c

test: s21_cat_test.sh
	sh s21_cat_test.sh

clean :
	-rm *.o
	-rm s21_cat

rebuild : clean all

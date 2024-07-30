#include "s21_cat.c"

int main(int argc, char *argv[]) {
  struct flags f = {0};
  parsing_flags(argc, argv, &f);
  read_file(argc, argv, f);
  return 0;
}

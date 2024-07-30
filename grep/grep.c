#include "s21_grep.c"

int main(int argc, char *argv[]) {
  struct flags f = {0};
  if (argc > 1) {
    char str_for_e_and_f[STR_LEN] = {0};
    parsing_flags(argc, argv, &f, str_for_e_and_f);
    if (!f.e && !f.f) {
      if (!*argv[optind]) {
        argv[optind] = ".";
      }
      strcat(str_for_e_and_f, argv[optind]);
      optind += 1;
    }
    read_file(argc, argv, str_for_e_and_f, f);
  }
  return 0;
}

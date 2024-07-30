#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parsing_flags(int argc, char *argv[], struct flags *f) {
  int opt;
  int index;
  char options[] = "+benstvET?";
  struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };
  while ((opt = getopt_long(argc, argv, options, long_options, &index)) != -1) {
    add_flags(opt, f);
  }
}

void add_flags(int opt, struct flags *f) {
  switch (opt) {
    case 'b':
      f->b = 1;
      break;
    case 'e':
      f->e = 1;
      f->v = 1;
      break;
    case 'n':
      f->n = 1;
      break;
    case 's':
      f->s = 1;
      break;
    case 't':
      f->t = 1;
      f->v = 1;
      break;
    case 'v':
      f->v = 1;
      break;
    case 'E':
      f->e = 1;
      break;
    case 'T':
      f->t = 1;
      break;
    default:
      fprintf(stderr, "1llegal option -- %c", opt);
      fprintf(stderr, "usage: cat [-belnstuv] [file ...]");
  }
}

void read_file(int argc, char *argv[], struct flags f) {
  int y_file = optind;
  int ch;
  int str_count = 0;
  int count = 0;
  int con_t = 0;
  int chek = '\n';
  while (y_file != argc) {
    FILE *fp;
    fp = fopen(argv[y_file], "rb");
    if (fp != NULL) {
      while ((ch = getc(fp)) != EOF) {
        if (chek == '\n') {
          if (ch == '\n' && f.s) {
            if (con_t) continue;
            con_t = 1;
          } else {
            con_t = 0;
          }
        }
        if (f.n && !f.b) {
          if (chek == '\n') {
            printf("%6d\t", ++str_count);
          }
        }
        chek = ch;
        if (f.b) {
          if (ch != '\n') {
            if (!count) {
              printf("%6d\t", ++str_count);
              count = 1;
            }
          }
          if (ch == '\n') count = 0;
        }
        if (f.v) {
          if ((ch >= 0 && ch <= 31) || ch == 127) {
            if ((ch != 9 && ch != 10) && ch != 127) {
              printf("^%c", ch + 64);
              continue;
            }
            if (ch == 127) {
              printf("^?");
              continue;
            }
          }
        }
        if (ch == '\n') {
          if (f.e) {
            putchar('$');
          }
        }
        if (ch == '\t') {
          if (f.t) {
            ch = 'I';
            printf("^%c", ch);
            continue;
          }
        }
        printf("%c", ch);
      }
      str_count = 0;
      fclose(fp);
      y_file++;
    } else {
      break;
    }
  }
}

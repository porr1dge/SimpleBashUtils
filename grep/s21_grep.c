#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void add_flags(int opt, struct flags *f, char *str_for_e_and_f, int *e_c) {
  switch (opt) {
    case 'e':
      f->e = 1;
      processing_e_flag(optarg, e_c, str_for_e_and_f, f);
      break;
    case 'i':
      f->i = 1;
      break;
    case 'v':
      f->v = 1;
      break;
    case 'c':
      f->c = 1;
      break;
    case 'l':
      f->l = 1;
      break;
    case 'n':
      f->n = 1;
      break;
    case 'h':
      f->h = 1;
      break;
    case 's':
      f->s = 1;
      break;
    case 'f':
      f->f = 1;
      processing_f_flag(optarg, e_c, str_for_e_and_f, f);
      break;
    case 'o':
      f->o = 1;
      break;
    case '?':
      exit(1);
    default:
      break;
  }
  if (f->vo_i_d) f->o = 0;
}

void processing_e_flag(char *optarg, int *e_c, char *str_for_e_and_f,
                       struct flags *f) {
  if (*e_c) {
    char ch[] = "|";
    strcat(str_for_e_and_f, ch);
  }
  if (!*optarg) {
    optarg = ".";
    f->vo_i_d += 1;
  }
  strcat(str_for_e_and_f, optarg);
  *e_c += 1;
}

void processing_f_flag(char *optarg, int *e_c, char *str_for_e_and_f,
                       struct flags *f) {
  FILE *fp;
  int c = f->vo_i_d;
  fp = fopen(optarg, "r");
  if (fp == NULL) {
    printf("grep: %s: No such file or directory\n", optarg);
    exit(2);
  }
  while (!feof(fp)) {
    if (*e_c) {
      char *ch = "|";
      strcat(str_for_e_and_f, ch);
    }
    size_t len = strlen(str_for_e_and_f);
    size_t n_len;
    fgets(str_for_e_and_f + len, BUFF, fp);
    char *ten_char = strrchr(str_for_e_and_f, '\n');
    if (ten_char) *ten_char = '\0';
    n_len = strlen(str_for_e_and_f);
    if (n_len == len) {
      f->vo_i_d++;
      char *ch = ".";
      strcat(str_for_e_and_f, ch);
    }
    *e_c += 1;
  }
  fclose(fp);
  if (str_for_e_and_f[strlen(str_for_e_and_f) - 1] == '.') {
    if ((f->vo_i_d - c) == 1) f->vo_i_d = c;
    str_for_e_and_f[strlen(str_for_e_and_f) - 1] = '\0';
    str_for_e_and_f[strlen(str_for_e_and_f) - 1] = '\0';
  }
}

void parsing_flags(int argc, char *argv[], struct flags *f, char *str_for_e) {
  int opt = 0;
  int e_c = 0;
  char option[] = "e:ivclnhsf:o";
  while ((opt = getopt_long(argc, argv, option, NULL, NULL)) != -1) {
    add_flags(opt, f, str_for_e, &e_c);
  }
}

void read_file(int argc, char *argv[], char *str_for_e_and_f, struct flags f) {
  FILE *fp = NULL;
  int new_l;
  int error = 0;
  int count = argc - optind;
  regex_t re;
  regmatch_t pmatch[1] = {0};
  size_t nmatch = 1;
  int status = 0;
  char buf[BUFF];
  int number_string = 1;
  int c_count = 0;
  int cflags = 0;
  if (f.i) cflags = REG_ICASE;
  status = regcomp(&re, str_for_e_and_f, REG_EXTENDED | cflags);
  if (status != 0) exit(3);
  for (; optind < argc; optind++) {
    fp = fopen(argv[optind], "r");
    if (fp == NULL && !f.s) {
      printf("grep: %s: No such file or directory\n", argv[optind]);
      error++;
    }
    if (fp != NULL) {
      while (fgets(buf, BUFF, fp)) {
        new_l = 1;
        status = regexec(&re, buf, nmatch, pmatch, 0);
        if (f.v) status = status ? 0 : 1;
        if (!status) {
          if (!f.c && !f.l) {
            if ((count > 1) && !f.h) {
              printf("%s:", argv[optind]);
            }
            if (f.n) {
              printf("%d:", number_string);
            }
            if (f.o && !f.v) {
              new_l = 0;
              char *p = buf;
              while (!status) {
                if (pmatch[0].rm_eo == pmatch[0].rm_so) break;
                printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                       p + pmatch[0].rm_so);
                p += pmatch[0].rm_eo;
                status = regexec(&re, p, nmatch, pmatch, REG_NOTBOL);
              }
            }
            if (!f.o || f.v) printf("%s", buf);
            if (buf[strlen(buf) - 1] != '\n' && new_l) {
              printf("\n");
            }
          }
          c_count++;
        }
        number_string++;
      }
      if (f.c) {
        if (count > 1 && !f.h) {
          printf("%s:", argv[optind]);
        }
        if (f.l && c_count) {
          printf("1\n");
        } else {
          printf("%d\n", c_count);
        }
      }
      if (f.l && c_count) {
        printf("%s\n", argv[optind]);
      }
      fclose(fp);
    }
    c_count = 0;
    number_string = 1;
  }
  regfree(&re);
  if (error) exit(2);
}

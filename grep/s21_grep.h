#ifndef _S21_GREP
#define _S21_GREP

#define STR_LEN 2048
#define BUFF 256

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int vo_i_d;
};

void parsing_flags(int argc, char *argv[], struct flags *f,
                   char *str_for_e_and_f);
void add_flags(int opt, struct flags *f, char *str_for_e_and_f, int *e_c);
void processing_e_flag(char *optarg, int *e_c, char *str_for_e_and_f,
                       struct flags *f);
void processing_f_flag(char *optarg, int *e_c, char *str_for_e_and_f,
                       struct flags *f);
void read_file(int argc, char *argv[], char *str_for_e_and_f, struct flags f);

#endif
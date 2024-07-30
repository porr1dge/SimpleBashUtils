#ifndef _S21_CAT
#define _S21_CAT

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
};

void parsing_flags(int argc, char *argv[], struct flags *f);
void add_flags(int opt, struct flags *f);
void read_file(int argc, char *argv[], struct flags f);

#endif
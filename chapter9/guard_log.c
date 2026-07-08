#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char *now() {
  time_t t;
  time(&t);
  return asctime(localtime(&t));
}

int main(int argc, char *argv[]) {
  time_t waktu;
  time(&waktu);
  printf("Waktu time: %ld\n", waktu);
  // struct tm *t = &waktu;

  // printf("Tahun: %d\n", t->tm_year + 1900); // Harus ditambah 1900
  // printf("Bulan: %d\n", t->tm_mon + 1);    // Harus ditambah 1
  // printf("Tanggal: %d\n", t->tm_mday);
  char comment[80];
  char cmd[120];
  //
  // fgets(comment, 80, stdin);
  // sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());
  // printf("%s \n",cmd);
  // system(cmd);
  return 0;
}

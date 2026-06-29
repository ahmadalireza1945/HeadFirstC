#include <stdio.h>
void got_sout_east(int *lat, int *lon) {
  *lat = *lat - 1;
  *lon = *lon + 1;
}

int main(int argc, char *argv[]) {
  int latitide = 2;
  int longlatitude = 3;

  got_sout_east(&latitide, &longlatitude);
  printf("avast: now at: [%i, %i]\n", latitide, longlatitude);
}

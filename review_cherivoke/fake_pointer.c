#include <stdio.h>

int main() {
  int x = 3;
  int *p = &x;
  long long q = (long long)p;
  q = q + 8;
  printf("%d\n", *((int *)q));
  return 0;
}

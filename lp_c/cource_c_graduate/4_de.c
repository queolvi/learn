#include <stdlib.h>
#include <stdio.h>

long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

long long de_pr(long long a, long long b, long long c) {
  int d = extended_gcd(a, b);
  
  if (c % d != 0) { printf("NONE"); }
  else {
    int k = c / d;
    printf(*x * k, *y * k, "\n");
  }
  return 0;
}

int main () {

  long long a, b, c;
  scanf("%d%d%d", a, b, c);
  long long res = de_pr(a, b, c);
  printf(res);
}

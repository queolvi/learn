#include <stdio.h>
#include <stdlib.h>
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

int main() {
    long long x, y;
    scanf("%lld %lld", &x, &y);
    
    long long a, b, d;
    
    d = extended_gcd(llabs(x), llabs(y), &a, &b);
    
    if (x < 0) a = -a;
    if (y < 0) b = -b;
    
    printf("%lld %lld %lld\n", a, b, d);
    return 0;
}

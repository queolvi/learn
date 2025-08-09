#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
unsigned long long euclid (unsigned long long a, unsigned long long b) 
{
while (true) {
if (a >= b) 
    {
	  if (a % b == 0){	return b;	}
		else { a = a - b; } 
	  } 
		else { if (b % a == 0) { return a;} 
            else {	b = b - a;	} 
        }
  }
}

int main() {
  	int a = 0, b = 0;
	scanf("%d%d",&a, &b);
	printf("%lld", euclid(fabs(a), fabs(b)));
  


	return 0;


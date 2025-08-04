#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#ifdef my_code
struct rational_struct {
  int x, y;
};

struct rational_struct rational_foo(unsigned long long a, unsigned long long b) {
  if (a < 0) { abort(); }
  unsigned long long q = a % b;
  int stop = 0;
  while (q != 0) {
    q = a / b;
    q = (int)q;
    a = 1;
    b = q;
  }
 struct rational_struct rational_res;
  rational_res.x = a;
  rational_res.y = b;
  return rational_res;
}


int main() {
  	int a = 0, b = 0;
	  scanf("%d%d",&a, &b);

    struct rational_struct res_from_foo = rational_foo(fabs(a), fabs(b));
	printf("%d%d", res_from_foo);
  


	return 0;
}
#endif
struct rational_struct {
    int x, y;
};

// Функция для вычисления цепной дроби
void print_continued_fraction(int a, int b) {
    printf("[%d", a / b); // Первый элемент
    
    int remainder = a % b;
    while (remainder != 0) {
        printf(";%d", b / remainder);
        int temp = b;
        b = remainder;
        remainder = temp % remainder;
    }
    
    printf("]");
}

int main() {
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);
    
    // Проверка на отрицательные значения
    a = abs(a);
    b = abs(b);
    
    // Проверка на ноль в знаменателе
    if (b == 0) {
        printf("Error: denominator cannot be zero\n");
        return 1;
    }
    
    print_continued_fraction(a, b);
    
    return 0;
}


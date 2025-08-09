#include <stdio.h>
#include <stdlib.h>

void print_continued_fraction(int a, int b) {
    // Обработка нулевого числителя
    if (a == 0) {
        printf("0");
        return;
    }
    
    // Определяем знак
    int sign = 1;
    if ((a < 0) ^ (b < 0)) {
        sign = -1;
    }
    a = abs(a);
    b = abs(b);
    
    // Первый элемент (целая часть)
    printf("%d", sign * (a / b));
    
    int remainder = a % b;
    while (remainder != 0) {
        printf(" %d", b / remainder);
        int temp = b;
        b = remainder;
        remainder = temp % remainder;
    }
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    // Проверка деления на ноль
    if (b == 0) {
        printf("Error: division by zero");
        return 1;
    }
    
    print_continued_fraction(a, b);
    
    return 0;
}

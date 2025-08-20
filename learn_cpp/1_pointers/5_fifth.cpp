#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void increment(int *arr, int size) {
    for(int i = 0; i < size; i++) {
        (*(arr + i))++;
    }
}

int main() {
    int x = 5, y = 10;
    swap(&x, &y);
    cout << x << " " << y << endl; // 10, 5
    
    int nums[] = {1, 2, 3, 4, 5};
    increment(nums, 5);
    for(int i = 0; i < 5; i++) {
        cout << nums[i] << " ";  //2 3 4 5 6
    }
    
    return 0;
}

#include "vector.h"

int main () {

vector<int> v1;
for(int i = 0; i < 6; ++i) { v1.pushBack(i); }

for(int i = 0; i < 6; ++i) { std::cout << "|" << v1[i] << "|" << "\n"; }
  return 0;
}

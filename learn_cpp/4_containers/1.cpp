#include <iostream>
#include <vector>
int main () {

  std::vector vec{1,2,3,4,5,6,7,8,9,10};
  vec.push_back(11);
  vec.erase(vec.begin() + 1);
  int sum = 0;
  for (int i = 0; i < vec.size(); ++i) {
    sum += vec[i];
  }
 for (auto i = vec.rbegin(); i != vec.rend(); ++i) {
   std::cout << *i << " ";
 } 


  return 0;
}

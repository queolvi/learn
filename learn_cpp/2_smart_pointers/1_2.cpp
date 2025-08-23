#include <iostream>
#include <memory>
int ret_unique(std::unique_ptr<int> rhs); 

int main () {

auto ptr = std::make_unique<int>(53);
int res = ret_unique(std::move(ptr));
std::cout << "value = " << res << "\n";
// if user will write some like : std::cout << *ptr; // so, ptr may be nullptr. fail

  return 0;
}
int ret_unique(std::unique_ptr<int> rhs) {
  int value = *rhs;
  return value;

  // in another var, foo has get value with ref, and i may return just *rhs. in this way foo cannot own a resource
}

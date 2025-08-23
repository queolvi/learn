#include <iostream>
#include <memory>

class node_ {
public:
  std::string name;
  std::shared_ptr<node_> partner; // cyclical ref
  node_(const std::string& n) : name(n) 
  {
    std::cout << "node " << name << " created\n";
  }  
  ~node_()
  {
    std::cout << "Node  " << name << "  destroyed\n";
  }
  void set_partner(std::shared_ptr<node_> p) {  partner = p; }
};
void create_circular_ref() {
  std::cout << "creating circular ref \n";
  
  auto node_f = std::make_shared<node_>("Alice");
  auto node_s = std::make_shared<node_>("Bob");
  
  node_f->set_partner(node_s);
  node_f->set_partner(node_f);
  
  std::cout << "Alice use count: " << node_f.use_count() << std::endl; 
  std::cout << "Bob use count: " << node_s.use_count() << std::endl;
// when foo exists, memory isn't clean, bec its cyclical ref
}
int main () {
create_circular_ref();
  std::cout << "Func ended, but mem leak occured\n";
  return 0;
}

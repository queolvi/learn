#include <iostream>
#include <stdexcept>
class point_ {
  protected:
  auto x = 0.0, y = 0.0;
};

class base_ {
  protected:
  point_ a_, b_;
  public:

};

class tools : protected base_, protected point_ {
  public:
  size_t size_f_base;
  
  tools(size_t size_p) : size_f_base(size_p) {
    if(size_f_base < 6) { std::invalid_argument("You banned! Size must be greater or equal of 6!!! I abort your programm muhahahaha >:} ");
      abort();
    }
  };

  void calc_dist(point_& a_, point_& b);
  void dump(std::ostream& os);

  
};  
  
void tools::calc_dist(point_& a_, point_& b) {

}
void tools::dump(std::ostream& os) {
  for(auto x : point_ ) {
    os << point_
  }
}


int main () {


const size_t size_f_base = 3; 
point_ arr_points* = new point_[size_f_base];
auto choice_{false};

if(choice == true) {

}


  return 0;
}

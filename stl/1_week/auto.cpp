#include <iostream>
#include <stdexcept>
#include <cmath>
class point_ {
  protected:
  double x = 0.0, y = 0.0;
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

  double calc_dist(point_& a_, point_& b);
  void dump(std::ostream& os);

  
};  
  
double tools::calc_dist(point_& a_, point_& b) {
  using::point_;

  double res = std::sqrt( std::pow((b_.x - a_.x), 2) + std::pow((b_.y - a_.y), 2));
  return res;

}
void tools::dump(std::ostream& os) {
  point_* p_ = new point_[size_f_base];

  for(auto x : p_ ) {
    os << p_;
    ++p_;
  }
delete [] p_;
}


int main () {


const size_t size_f_base = 3; 
point_ arr_points* = new point_[size_f_base];

auto choice_{false};

if(choice_ == true) {


}

  
  return 0;
}

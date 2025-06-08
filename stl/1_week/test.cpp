#include <iostream>
#include <stdexcept>

class point_ {
protected:
    double x = 0.0, y = 0.0;  // Fixed: explicitly declare type as double
};

class base_ {
protected:
    point_ a_, b_;
public:
    // You might want to add some public methods here
};

class tools : protected base_, protected point_ {
public:
    size_t size_f_base;
    
    tools(size_t size_p) : size_f_base(size_p) {
        if(size_f_base < 6) { 
            throw std::invalid_argument("Size must be greater or equal to 6!"); 
            // Better to throw than abort - gives caller chance to handle error
        }
    }

    void calc_dist(point_& a_, point_& b_);  // Fixed: parameter name conflict
    void dump(std::ostream& os);
};  
  
void tools::calc_dist(point_& a_, point_& b_) {
    // Implementation needed
}

void tools::dump(std::ostream& os) {
    point_* p_ = new point_[size_f_base];

    for(size_t i = 0; i < size_f_base; i++) {  // Fixed: can't use range-for with pointer
        os << &p_[i];  // This will print address - you probably want to print coordinates
    }
    delete [] p_;
}

int main() {
    const size_t size_f_base = 6; 
    point_* arr_points = new point_[size_f_base];  // Fixed: syntax error in declaration
    
    try {
        tools t(size_f_base);  // This will throw exception
    } catch(const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    bool choice_ = false;  // Fixed: declare type
    
    if(choice_ == true) {
        // Do something
    }

    delete[] arr_points;  // Don't forget to free memory
    return 0;
}

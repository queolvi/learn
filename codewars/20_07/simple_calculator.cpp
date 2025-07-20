#include <stdexcept>

double calculator(double a, double b, char op) {
  double res = 0;
  if (op == '+') { res = a + b; return res; }
  else if (op == '-') { res = a - b; return res; }
  else if (op == '*') { res = a * b; return res; }
  else if (op == '/') { res = a / b; return res; }
  else { throw std::invalid_argument(""); }
}
/*
 #include <fmt/core.h>
#include <string>
#include <stdexcept>

void doTest(double a, double b, char op, double expected) {
  std::string message = fmt::format("a: {}, b: {}, op: '{}'", a, b, op);
  Assert::That(calculator(a, b, op), Equals(expected), ExtraMessage(message));
}

void testException(double a, double b, char op) {
  AssertThrows(std::invalid_argument, calculator(a, b, op));
}

Describe(Sample_tests) {
  It(Valid_operators_should_return_correct_result) {
    doTest(1, 2, '+', 3);
    doTest(1, 2, '-', -1);
    doTest(3, 5, '*', 15);
    doTest(6, 2, '/', 3);
  }
  
  It(Invalid_operators_should_throw) {
    testException(6, 2, '.');
    testException(3, 5, '\\');
    testException(5, 5, '=');
    testException(6, 3, '\t');
  }
};
 
 */

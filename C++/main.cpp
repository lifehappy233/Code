#include <iostream>

class Fraction {
private:
  double a, b;

public:
  Fraction(double _a = 0, double _b = 0) : a(_a), b(_b) {}

  // operator double() const {
  //   return (double)a / b;
  // }

  int valn() const {
    return a;
  }

  int valm() const {
    return b;
  }

  Fraction operator + (const Fraction &t) {
    return Fraction(a + t.a, b + t.b);
  }
};

inline std::ostream &operator << (std::ostream &os, const Fraction &t) {
  return os << t.valn() << " / " << t.valm();
}

int main() {
  Fraction a(1, 2);
  std::cout << a + 3 << std::endl;
  // Fraction ans = a + 3;
  // std::cout << ans << std::endl;
  return 0;
}
#include <iostream>

class complex {
public:
  complex(double r = 0, double i = 0) : re(i), im(i) {}

  double real() const {
    return re;
  }

  double image() const {
    return im;
  }

private:
  double re, im;
};

std::ostream& operator << (std::ostream& os, const complex &x) {
  return os << "(" << x.real() << ", " << x.image() << ")";
}

int main() {
  complex a(1.0, 1.0);
  
  const complex b(2.0, 2.0);

  std::cout << a << std::endl;

  std::cout << b << std::endl;

  return 0;
}
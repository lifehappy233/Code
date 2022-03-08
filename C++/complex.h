#ifndef __COMPLEX__
#define __COMPLEX__

class complex {
private:
  double re, im;

  friend complex &__doapl(complex *ths, const complex &x);

public:
  complex(double r = 0, double i = 0) :re(r), im(i) {}

  complex &operator += (const complex &x);

  double real() const {
    return re;
  }

  double image() const {
    return im;
  }

};

#endif
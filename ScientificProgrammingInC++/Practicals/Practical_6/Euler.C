#include "MyFunc.H"

double eulerStep(double x, double dt)
{
  return x + f(x) * dt;
}

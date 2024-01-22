#ifndef EULERPTR_H
#define EULERPTR_H
#include <functional>
double eulerStep(const std::function<double(double)>& f, double x, double dt);
#endif

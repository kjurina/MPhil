#include <iostream>
#include <fstream>
#include "Euler.H"

int main()
{
  double finalT, dt, y0;

  std::cout << "Enter final time: ";
  std::cin >> finalT;
  std::cout << "Enter initial value of y: ";
  std::cin >> y0;
  std::cout << "Enter time-step: ";
  std::cin >> dt;

  std::ofstream out("Practical_3.out");

  double t = 0, y = y0;
  while( t < finalT )
  {
    if( t + dt > finalT )
    {
      dt = finalT - t;
    }
    
    y = eulerStep(y, t);
    t += dt;
    out << t << " " << y << std::endl;
  }
  
  out.close();
  std::cout << "y(" << finalT << ") = " << y << std::endl;

  return 0;
}

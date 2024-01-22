#include <iostream>
#include <cmath>

int main(void)
{
  double a, b, c;
  std::cout << "Enter a, b, and c for the quadratic ax^2+bx+c=0" << std::endl;
  std::cin >> a >> b >> c;

  if( fabs(a) < 1e-8 )
  {
    if( fabs(b) < 1e-8 )
    {
      if( c != 0 )
      {
	std::cout << "No solutions" << std::endl;
      }
      else
      {
	std::cout << "Trivially, all values of x solve this quadratic." << std::endl;
      }
    }
    else
    {
      std::cout << "Equation has a single solution: " << -c / b << std::endl;
    }
    
  }
  else
  {
    const double det = b*b - 4*a*c;
    if( det < 0 )
    {
      std::cout << "No real solutions" << std::endl;
    }
    else if( det > 0 )
    {
      std::cout << "Two real solutions: " << (-b + sqrt(det)) / (2*a)
		<< "and " << (-b - sqrt(det)) / (2*a) << std::endl;
    }
    else
    {
      std::cout << "One solution only: " << -b / (2*a) << std::endl;
    }
  }
  
}

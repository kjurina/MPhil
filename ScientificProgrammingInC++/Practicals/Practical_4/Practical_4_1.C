#include <iostream>
#include <cmath>
#include <limits>

int sum(int a, int b)
{
  return a + b;
}

void decrease(int& a, int b)
{
  a -= b;
}

int q(double a, double b, double c, double& x1, double& x2)
{
  if( fabs(a) < 1e-8 )
  {
    if( fabs(b) < 1e-8 )
    {
      if( c != 0 )
      {
	return 0;
      }
      else
      {
	return std::numeric_limits<int>::max();
      }
    }
    else
    {
      x1 = -c / b;
      return 1;
    }
    
  }
  else
  {
    const double det = b*b - 4*a*c;
    if( det < 0 )
    {
      return 0;
    }
    else if( det > 0 )
    {
      x1 = (-b + sqrt(det)) / (2*a);
      x2 = (-b - sqrt(det)) / (2*a);
      return 2;
    }
    else
    {
      x1 = -b / (2*a);
      return 1;
    }
  }

}


int main(void)
{
  int a = 5;
  int b = 3;
  int c = -125;

  std::cout << "Sum of " << a << " and " << b << " = " << sum(a,b) << std::endl;
  decrease(b, 3);
  std::cout << "Now b = " << b << std::endl;

  double x1;
  double x2;
  int solns = q(a,b,c, x1, x2);

  std::cout << "Quadratic has " << solns << " solutions" << std::endl;
  if(solns >= 1 && solns < std::numeric_limits<int>::max())
  {
    std::cout << "First solution = " << x1 << std::endl;
  }
  if(solns == 2)
  {
    std::cout << "Second solution = " << x2 << std::endl;
  }
  return 0;
}

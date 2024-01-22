#include <iostream>
#include <array>


double det(const std::array<std::array<double,3>,3>& m)
{
  double d = 0;

  d += m[0][0] * (m[1][1] * m[2][2] - m[1][2]*m[2][1]);
  d -= m[0][1] * (m[1][0] * m[2][2] - m[1][2]*m[2][0]);
  d += m[0][2] * (m[1][0] * m[2][1] - m[1][1]*m[2][0]);

  return d;
}

double trace(const std::array<std::array<double,3>,3>& m)
{
  return m[0][0] + m[1][1] + m[2][2];
}

int main()
{
  std::array<std::array<double,3>,3> m;

  for(int i=0 ; i < 3 ; i++)
  {
    for(int j=0 ; j < 3 ; j++)
    {
      std::cout << "Enter m(" << i << "," << j << "): ";
      std::cin >> m[i][j];
    }
  }
  
  std::cout << "Trace = " << trace(m) << std::endl;
  std::cout << "Determinant = " << det(m) << std::endl;

  return 0;
}

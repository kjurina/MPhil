#include <iostream>
#include <array>

void partialSum(const std::array<int,20> a, std::array<int,20>& sums)
{
  int sum = 0;
  for(int i=0 ; i < 20 ; i++)
  {
    sum += a[i];
    sums[i] = sum;
  }
  
}


int main(void)
{
  std::array<int,20> c;
  std::array<int,20> d;
  for(int i=0 ; i < 20 ; i++)
  {
    c[i] = i;
  }
  partialSum(c, d);
  std::cout << "Triangular numbers:" << std::endl;
  for(int i=0 ; i < 20 ; i++)
  {
    std::cout << "d[" << i << "] = " << d[i] << std::endl;
  }
  return 0;
}

#include <iostream>

int main(void)
{
  int n;
  std::cout << "Please enter the maximum square: ";
  std::cin >> n;
  for(int i=0 ; i <= n ; i++ )
  {
    std::cout << i << " * " << i << " = " << i*i << std::endl;
  }
  
}

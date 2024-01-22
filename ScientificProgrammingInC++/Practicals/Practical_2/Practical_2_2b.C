#include <iostream>
#include <fstream>

int main(void)
{
  int n;
  do
  {
    std::cout << "Please enter the maximum square: ";
    std::cin >> n;

    if( n < 0 )
    {
      std::cout << "Please enter a +ve number" << std::endl;
    }
  }
  while(n < 0);

  std::ofstream data("squares.dat");

  for(int i=0 ; i <= n ; i++ )
  {
    data << i << " " << i*i << std::endl;
  }
  
  data.close();
}

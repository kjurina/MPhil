#include <list>
#include <algorithm>
#include <iostream>

int main(void)
{
  std::cout << "Enter a list of positive numbers, ending with a negative one" << std::endl;
  std::list<double> numbers;
  while(std::cin.good())
  {
    double x;
    std::cin >> x;
    if(x < 0)
    {
      break;
    }
    numbers.push_back(x);
  }
  
  numbers.sort();
  std::list<double>::const_iterator numIter = numbers.begin();
  const std::list<double>::const_iterator numEnd = numbers.end();

  std::cout << "Sorted list, every other element:" << std::endl;
  for( ; numIter != numEnd ; )
  {
    std::cout << *numIter << std::endl;
    ++numIter;
    // Incrementing the end iterator gives undefined behaviour
    if( numIter != numEnd )
    {
      ++numIter;
    }
  }
  
  return 0;
}

#include <vector>
#include <algorithm>
#include <iostream>

int main(void)
{
    std::cout << "Enter a list of positive numbers, ending with a negative one" << std::endl;
    std::vector<double> numbers;
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

    std::sort(numbers.begin(), numbers.end());

    std::vector<double>::const_iterator numIter = numbers.begin();
    const std::vector<double>::const_iterator numEnd = numbers.end();

    std::cout << "Sorted vector, every other element:" << std::endl;

    for( ; numIter!=numEnd; )
    {
        std::cout << *numIter << std::endl;
        ++numIter;
        if(numIter != numEnd)
        {
            ++numIter;
        }
    }
    return 0;
}



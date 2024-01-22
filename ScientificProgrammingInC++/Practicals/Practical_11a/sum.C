#include <vector>
#include <iostream>
#include <iomanip>

template<typename T>
T sum(const std::vector<T>& numbers)
{
    T ans = 0;
    for (unsigned int i = 0; i < numbers.size(); i++)
    {
        ans += numbers[i];
    }
    return ans;
}

// template<>
// float sum<float>(const std::vector<float>& numbers)
// {
//     float ans;
//     float c = 0;
//     for (size_t i = 0; i < numbers.size(); i++)
//     {
//         float y = numbers[i] - c;
//         float t = ans + y;
//         c = (t - ans) - y;
//         ans = t;
//     }
//     return ans;
// }


int main(void)
{
  std::vector<int> ints;
  ints.resize(4);
  ints[0] = 50;
  ints[1] = 9;
  ints[2] = 987;
  ints[3] = 345;

  std::cout << "Sum ints = " << sum(ints) << std::endl;

  std::vector<float> reals;
  reals.resize(4);

  reals[0] = 1000000.0;
  reals[1] = 3.14159;
  reals[2] = 2.71828;
  reals[3] = 0;

  std::cout << "Sum reals = " << std::setprecision(16) << sum(reals) << std::endl;

  return 0;
}

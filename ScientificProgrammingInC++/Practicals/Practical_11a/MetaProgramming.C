#include <iostream>

template<int A, int B>
struct GCD
{
  static const int value = GCD<B, A % B>::value;
};

template<int A>
struct GCD<A,0>
{
  static const int value = A;
};

int main(void)
{
  std::cout << GCD<10,9>::value << std::endl;
  std::cout << GCD<10,4>::value << std::endl;
  std::cout << GCD<55,22>::value << std::endl;
}

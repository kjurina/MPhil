// Now using a partially specialised class with IsReal<T> as
// a template parameter.

#include <vector>
#include <iostream>
#include <iomanip>

// Generic form of IsReal - default is false
template<typename T>
struct IsReal
{
  static const bool value = false;
};

// Specialise for float and double types
template<>
struct IsReal<float>
{
  static const bool value = true;
};
template<>
struct IsReal<double>
{
  static const bool value = true;
};
  
// General form of sum function class
// We don't need to specify a general form here, only for the two partial specialisations.
template<typename T, bool UseKahan = IsReal<T>::value> struct SumVector;

// Partially specialised form for integers
// Used when IsReal<T>::value = false
template<typename T>
struct SumVector<T, false> 
{
  // Static so that we can call the function without reference to an object.
  static T sum(const std::vector<T>& numbers);
};

template<typename T>
T SumVector<T,false>::sum(const std::vector<T>& numbers)
{
  T ans = 0;
  // Use simple summation
  for(size_t i=0 ; i < numbers.size() ; i++)
  {
    ans += numbers[i];
  }
  
  return ans;
}

// Partially specialised form for floats and doubles
// Used when IsReal<T>::value = true
template<typename T>
struct SumVector<T, true> 
{
  // Static so that we can call the function without reference to an object.
  static T sum(const std::vector<T>& numbers);
};

template<typename T>
T SumVector<T,true>::sum(const std::vector<T>& numbers)
{
  // Use Kahan summation
  T ans = 0;
  T c = 0;
  for(size_t i=0 ; i < numbers.size() ; i++)
  {
    T y = numbers[i] - c;
    T t = ans + y;
    c = (t - ans) - y;
    ans = t;
  }
  return ans;
}


int main(void)
{
  std::vector<int> ints;
  ints.resize(4);
  ints[0] = 50;
  ints[1] = 9;
  ints[2] = 987;
  ints[3] = 345;

  // Because the template is associated with the class rather
  // than the function, the compiler can no longer deduce the
  // template parameters from the function parameter alone.
  // We have to tell it the answer.

  std::cout << "Sum ints = " << SumVector<int>::sum(ints) << std::endl;

  std::vector<float> reals;
  reals.resize(4);

  reals[0] = 1000000.0;
  reals[1] = 3.14159;
  reals[2] = 2.71828;
  reals[3] = 0;

  // This probably now appears to be a lot of work for very little gain,
  // particularly compared to overloaded functions.
  // However, we have the advantage that Kahan summation can be applied to
  // both float and double without copy-pasted code.
  // You can also easily compare the result using Kahan or non-Kahan summation
  // for floats by changing only line 19 above to give value = false.
  std::cout << "Sum reals = " << std::setprecision(10) << SumVector<float>::sum(reals) << std::endl;

  return 0;
}

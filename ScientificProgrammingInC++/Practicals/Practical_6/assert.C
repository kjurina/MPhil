#include <iostream>

#define ASSERT(x) if( !(x) ) \
{			     \
  std::cout << "Test " << #x << " failed at line " \
  << __LINE__					   \
  << " in " << __FILE__ << std::endl;\
}				     
  
#define POW2(i) (1 << i)

int main(void)
{
    int a = 5;
    //ASSERT(a == 5);
    //ASSERT(a == 6);

    int i = POW2(3);

    std::cout<<POW2(8);

    return 0;
}

/* Example of a Matrix class.
   Only a simple addition operator has been defined
   as well as the trace function.

   Other operators should follow this pattern.
   (The det() function is tricky to implement in general for arbitrary SIZE.
   You could define specialized forms for SIZE=1,2,3 and only go higher
   if you ever explicitly need it.
 */

#include <iostream>

template<int SIZE, typename T = double> class Matrix
{
private:

    T data[SIZE][SIZE];
  
public:

    T operator()(unsigned int i, unsigned int j)const
    {
        return data[i][j];
    }

    T& operator()(unsigned int i, unsigned int j)
    {
        return data[i][j];
    }

    Matrix& operator+=(const Matrix& b)
    {
        for (unsigned int i = 0; i < SIZE; i++)
        {
            for (unsigned int j = 0; j < SIZE; j++)
            {
                data[i][j] += b(i,j);
            }
        }
        return *this;
    }
};

template<int SIZE, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<SIZE, T>& a)
{
    os << "[";
    for(unsigned int i = 0;i<SIZE;i++)
    {
        os << "[";
        for (unsigned int j = 0; j < SIZE; j++)
        {
            os << a(i,j) << " ";
        }
        os << "]" << std::endl;
    }
    os << "]";
    return os;
}

template<int SIZE, typename T>
T trace(const Matrix<SIZE, T>& a)
{
    T t = 0;
    for (unsigned int i = 0; i < SIZE; i++)
    {
        t += a(i,i);
    }
    return t;
}

int main(void)
{
    Matrix<2> a;
    a(0,0) = 1;
    a(0,1) = 2;
    a(1,0) = -1;
    a(1,1) = 3;

    std::cout << "a = " << a << std::endl;
    std::cout << "Trace of a = " << trace(a) << std::endl;

    Matrix<2> c;
    c(0,0) = 2.3;
    c(0,1) = 1.0;
    c(1,0) = -1.4;
    c(1,1) = 5.4;

    std::cout << "c = " << c << std::endl;
    std::cout << "Trace of a = " << trace(c) << std::endl;

    a += c;

    std::cout << "a = " << a << std::endl;
    std::cout << "Trace of a = " << trace(a) << std::endl;
  
   return 0;
}

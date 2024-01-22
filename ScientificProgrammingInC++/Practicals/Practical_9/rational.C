#include <iostream>

class Rational
{
private:
    int num_;
    int denom_;
    //int value_;

    void reduce();

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);


public:
    Rational();
    Rational(int);
    Rational(int, int);

    int denom()const;
    int num()const;

    double value()const;
    operator double()const;

    const Rational& operator/=(const Rational& b);
    const Rational& operator*=(const Rational& b);
    const Rational& operator+=(const Rational& b);
    const Rational& operator-=(const Rational& b); 




};

Rational::Rational(){}

//Rational::Rational(int num)
Rational::Rational(int n)
{
  num_ = n;
  denom_ = 1;
}

Rational::Rational(int num, int denom)
:
num_(num),
denom_(denom)
{
    if(denom == 0)
    {
        std::cerr << "Attempt to define a Rational with zero denominator" << std::endl;
    }
}


int Rational::num() const
{
    return num_;
}

int Rational::denom() const
{
    return denom_;
}

double Rational::value()const
{
    return (double)num_ / (double)denom_;
}

Rational::operator double()const
{
  return value();
}

const Rational& Rational::operator/=(const Rational& b)
{
    Rational c;
    c.num_ = num_*b.denom_;
    c.denom_ = denom_ * b.num_;
    c.reduce();

    num_ = c.num_;
    denom_ = c.denom_;
    return *this;
}

const Rational& Rational::operator*=(const Rational& b)
{
    Rational c;
    c.num_ = num_*b.num_;
    c.denom_ = denom_ * b.denom_;
    c.reduce();

    num_ = c.num_;
    denom_ = c.denom_;
    return *this;
}

const Rational& Rational::operator+=(const Rational& b)
{
    Rational c;
    c.num_ = num_*b.denom_+b.num_*denom_;
    c.denom_ = denom_ * b.denom_;
    c.reduce();

    num_ = c.num_;
    denom_ = c.denom_;
    return *this;
}

const Rational& Rational::operator-=(const Rational& b)
{
    Rational c;
    c.num_ = num_ * b.denom_ - b.num_ * denom_;
    c.denom_ = denom_ * b.denom_;
    c.reduce();

    num_ = c.num_;
    denom_ = c.denom_;

    return *this;
}

void Rational::reduce()
{
    // Find the Greatest Common Divisor of two integers:
    int r1, r2;
    if(std::abs(num_) > std::abs(denom_))
    {
        r1 = num_;
        r2 = denom_;
    }
    else
    {
        r1 = denom_;
        r2 = num_;
    }
    
    while(r2 != 0)
    {
        int t = r2;
        r2 = r1 % r2;
        r1 = t;
    }
    
    num_ /= r1;
    denom_ /= r1;
}

/* Binary operators on Rationals.
   These are implemented in terms of the operate-and-assign operators.
   This reduces the likelihood that we make mistakes in copy-pasting.

   They return an object which is not done by reference, since the local variable c
   is destroyed as soon as the function exits.

   Note that binary operator-overloadings should be defined as global functions,
   i.e. outside of the class itself.
 */





Rational operator*(const Rational& a, const Rational& b)
{
  Rational c = a;
  c *= b;
  return c;
}



/* Since it is possible for a Rational to be cast to a double,
   we also need operators for the case such as b * 3.

   Here, it is ambiguous whether we expect b to be cast to a double,
   and the operation (double) * (int) be carried out,
   or whether we expect the integer 3 to be cast to a Rational and
   the operation (Rational) * (Rational) to be carried out.

   This is ambiguous according to the C++ standard unless
   we define explicit operators for the case
   whether the RHS of the operator is an integer.
   We should also do this for the case where the LHS is
   an integer - left as a (trivial) exercise for the reader.

   Note that within the functions, (Rational) += (int) (etc.) is well-defined.
 */





Rational operator*(const Rational& a, const int& b)
{
    Rational c = a;
    c *= b;
    return c;
}







std::ostream& operator<<(std::ostream& os, const Rational& r)
{
    os << r.num() << "/" << r.denom();
    return os;
}

std::istream& operator>>(std::istream& is, Rational& r)
{
    is >> r.num_;
    char c;
    is >> c;
    if( c != '/')
    {
        std::cerr << "Ill-defined rational input" << std::endl;
    }
    
    is >> r.denom_;
    r.reduce();
    return is;
}


int main()
{
    Rational a(10,3);
    //a.reduce();
    std::cout << "a = " << a.num() << "/" << a.denom() << " ~ " <<
    a.value() << std::endl;

    a /= 5;
    //std::cout << 19%8 << std::endl; 
    Rational b(3,4);
    std::cout << "a = " << a.num() << "/" << a.denom() << " ~ " << a.value() << std::endl;
    //std::cout << b * 3 << std::endl;
    a += b * 3;
    std::cout << "a = " << a.num() << "/" << a.denom() << " ~ " << a.value() << std::endl;

    Rational c;
    std::cout << "Please enter a rational number in the form a/b: ";
    std::cin >> c;
    std::cout << "c = " << c << " ~ " << (double)c << std::endl;
    c -= 5;
    std::cout << "c = " << c << " ~ " << (double)c << std::endl;

    c -= b*a;
    std::cout << "c = " << c << " ~ " << (double)c << std::endl;
}
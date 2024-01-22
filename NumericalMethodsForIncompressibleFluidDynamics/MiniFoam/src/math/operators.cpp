//#include    "operators.hpp"
#include    <vector>
#include    <cmath>

#include    "operators.hpp"


std::vector<float> crossProduct(std::vector<float>& v1, std::vector<float>& v2)
{
    std::vector<float> cross {0,0,0};
    cross[0] = v1[1] * v2[2] - v2[1] * v1[2];
    cross[1] = v2[0] * v1[2] - v1[0] * v2[2];
    cross[2] = v1[0] * v2[1] - v2[0] * v1[1];//
    return cross;
}

float dotProduct(std::vector<float>& v1, std::vector<float>& v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float mag(std::vector<float>& v1)
{//
    return sqrt(v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2]);
    
}

float mag(float num)
{
    return sqrt(num * num);
}

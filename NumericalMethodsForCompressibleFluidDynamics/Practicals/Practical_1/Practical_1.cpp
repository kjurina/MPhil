#include    <iostream>
#include    <cmath>
#include    <vector>
#include    <fstream>
using namespace std;


int main()
{
    int nPoints = 100;
    double x0 = 0.0; 
    double x1 = 6.0;
    double tStart = 0.0;
    double tStop = 1.0;
    double a = 1.0;  

    double dx = (x1 - x0) / (nPoints - 1); 

    double dt = dx;

    std::vector<double> u;

    u.resize(nPoints);

    for(int i = 0; i < u.size(); i++)
    {
        double x = x0 + i * dx;
        u[i] = sin(x);
    }
/*
    for(int i = 0; i < u.size(); i++)
    {
        u[i] = 0;

        double x = x0 + (i - 1) * dx;

        if (x >= 0.25 && x <= 0.75)
        {
            u[i] = 1;
        }
    }
*/

    //std::vector<double> u0 = u;

    std::vector<double> uPlus1;

    uPlus1.resize(nPoints + 2);  

    double t = tStart;

    //do{
        t = t + dt;

        //u[0] = u[nPoints];

        //u[nPoints+1] = u[1];

        for(int i = 1; i < nPoints +1; i++)
        {
            uPlus1[i] = u[i] - a * dt / dx * (u[i] - u[i - 1]);
        }

        //u = uPlus1;

    //} while (t < tStop);

    std::ofstream output;

    output.open("advectionResults.dat",ios::out);

    for(int i = 0; i < nPoints; i++) 
    {
        double x = x0 + i * dx;
        output << x /*<< " " << u[i]*/ << " " << u[i] << std::endl;
    }
    return 0;
}
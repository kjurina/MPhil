#include    <iostream>
#include    <cmath>
#include    <vector>
#include    <fstream>
using namespace std;

std::vector<double> solveAdvection
(   
    int nPoints, 
    double x0,
    double x1,
    double a, 
    double tStop,
    string numericalMethod, 
    std::vector<double> u0
);

std::vector<double> setInitial
(
    int nPoints, 
    double x0,
    double x1
);

int main()
{
    int nPoints = 100;

    double x0 = -1;

    double x1 = 1;

    double a = 1;

    double tStop = 10;

    string numericalMethod ("Lax–Wendroff");

    std::vector<double> u0 = setInitial(nPoints, x0, x1);

    std::vector<double> u = solveAdvection(nPoints, x0, x1, a, tStop, numericalMethod, u0);

    cout << u0.size() << endl;


    return 0;

}

std::vector<double> solveAdvection
(   
    int nPoints, 
    double x0,
    double x1,
    double a, 
    double tStop,
    string numericalMethod, 
    std::vector<double> u0
)
{
    double CFL = 0.8;

    double dx = (x1 - x0) / (nPoints); 

    double dt = CFL * dx / a;

    std::vector<double> u = u0;

    double tStart = 0;

    double t = tStart;

    do{
        t = t + dt;

        u0[0] = u0[nPoints];

        u0[nPoints + 1] = u0[1];

        if (numericalMethod == "Lax-Friedrichs")
        {
            for(int i = 1; i < nPoints + 1; i++)
            {
                u[i] = (1 + CFL) / 2 * u0[i - 1] + (1 - CFL) / 2 * u0[i + 1];
            }

            u0 = u;
        }
        else if (numericalMethod == "Lax–Wendroff")
        {
            for(int i = 1; i < nPoints + 1; i++)
            {
                u[i] = (1 + CFL) * CFL / 2 * u0[i - 1] + (1 - pow(CFL,2)) * u0[i] 
                 - (1 - CFL) * CFL / 2 * u0[i + 1];
            }

            u0 = u;
        }
        else if (numericalMethod == "Warming-Beam")
        {
            for(int i = 1; i < nPoints + 1; i++)
            {
                u[i] = -(1 - CFL) * CFL / 2 * u0[i - 2] + CFL * (2 - CFL) * u0[i - 1] 
                 + (CFL - 1) * (CFL - 2) * CFL / 2 * u0[i];
            }

            u0 = u;
        }
    } while (t < tStop);

    std::ofstream output;

    output.open("advectionResults.dat", ios::out);

    for(int i = 1; i < nPoints+1; i++) 
    {
        double x = x0 + (i - 1) * dx;

        output << x << " " << u0[i] << std::endl;
    }

    return u0;
}


std::vector<double> setInitial
(
    int nPoints, 
    double x0,
    double x1
)
{
    double dx = (x1 - x0) / (nPoints - 1); 

    std::vector<double> u0;

    u0.resize(nPoints + 2);

    for(int i = 1; i < nPoints + 2; i++)
    {
        double x = x0 + (i - 1) * dx;

        u0[i] = exp(-8 * pow(x,2));
    }
/*
    std::ofstream output;

    output.open("advectionResults.dat", ios::out);

    for(int i = 0; i < nPoints+2; i++) 
    {
        double x = x0 + (i - 1) * dx;

        output << x << " " << u0[i] << std::endl;
    }
*/
    return u0;
}




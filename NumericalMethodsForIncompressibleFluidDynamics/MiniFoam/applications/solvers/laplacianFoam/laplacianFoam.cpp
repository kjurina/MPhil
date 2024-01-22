#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <sstream>
#include <map>
#include <variant>
#include <any>
#include <numeric>
#include <algorithm>
#include <cmath>

#include    "../../../src/finiteVolume/fvMesh/fvMesh.hpp"
//#include    "src/mesh/operators.hpp"


using namespace std;

//namespace fs = std::filesystem;


int main()
{

        //std::cout << "Current path is " << fs::current_path() << '\n'; // (1)
        //fs::current_path(fs::temp_directory_path()); // (3)
        //std::cout << "Current path is " << fs::current_path() << '\n';

    fvMesh mesh;

    
    //std::vector<vector<int>> boundaryMesh = mesh.boundaryMesh();//

    // Prints Faces on the boundary(on per-patch basis)
    /*for (int i = 0; i < boundaryMesh.size(); i++)
    {
        std::vector<int> patch = boundaryMesh[i];

        for (int j = 0; j < patch.size(); j++)
        {
            std::cout << patch[j] << " ";
        }
        cout << "\n";
    }
    */
    return 0;
}

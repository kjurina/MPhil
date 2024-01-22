/*---------------------------------------------------------------------------*\
Application
    icoFoam

Description
    Transient solver for incompressible, laminar flow of Newtonian fluids.

Author
    Karlo Jurina
\*---------------------------------------------------------------------------*/

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
//#include <cctype>
//#include <sstream>
#include <map>
#include <variant>
#include <any>
#include <numeric>
#include <algorithm>
#include <cmath>//

using namespace std;//

class fvMesh
{
    private:

        //private members

        filesystem::path fvMeshPath_ = "constant/fvMesh";//////

        //fvMesh folder files
        int nCells_;

        vector<vector<float>> pointList_;

        vector<int> ownerList_;

        vector<int> neighbourList_;

        vector<vector<int>> faceList_;

        map<string,map<string, any>> boundaryList_;

        //fvMesh geometry data

        vector<vector<float>> faceCentres_;

        vector<vector<float>> faceAreaVectors_;

        vector<float> faceAreaMagnitudes_;

        vector<vector<float>> faceNormals_;

        vector<vector<float>> cellCentres_;

        vector<float> cellVolumes_;

        //private Reading member functions

        int readNumberOfCellsFromOwnerFile();

        vector<vector<float>> readPointsFromfvMesh();

        vector<int> readOwnerFromfvMesh();

        vector<int> readNeighbourFromfvMesh();

        vector<vector<int>> readFacesFromfvMesh();

        map<string,map<string, any>> readBoundaryFromfvMesh();

        //private Geometry member functions

        vector<vector<float>> calculateFaceCentres(vector<vector<float>> pointList, vector<vector<int>> faceList);

        vector<vector<float>> calculateFaceAreaVectors (vector<vector<float>> pointList, vector<vector<int>> faceList, vector<vector<float>> faceCentres);

        vector<float> calculateMagSf (vector<vector<float>> Sf);

        vector<vector<float>> calculateFaceNormals(vector<vector<float>> Sf, vector<float> magSf);

        vector<vector<float>> calculateCellCentres (vector<int> owner, vector<int>neighbour, vector<vector<float>> Sf);

        vector<float> calculateCellVolumes( vector<int>& owner, vector<int>& neighbour, vector<vector<float>>& faceCentres, vector<vector<float>>& Sf, vector<vector<float>>& cellCenters);

    public:

        //constructor
        fvMesh();
        ~fvMesh(){};//

        vector<string> readInFoamFileAsVectorOfStrings(filesystem::path path);

        void cleanFoamVectorOfStrings(vector<string>& spoints);

        vector<vector<float>> convertVectorOfStringsIntoPoints(vector<string> spoints);

        vector<int> convertVectorOfStringsIntoOwner(vector<string> sOwner);

        vector<int> convertVectorOfStringsIntoNeighbour(vector<string> sNeighbour);

        vector<vector<int>> convertVectorOfStringsIntoFaces(vector<string> sFaces);

        map<string,map<string, any>> convertVectorOfStringsIntoBoundary(vector<string> sBoundary);

        //Return functions
        int nPoints();
        int nFaces();
        int nCells();
        int nBoundaryPatches();
        std::vector<float> V();
        std::vector<vector<float>> Sf();
        std::vector<vector<float>> C();
        std::vector<vector<float>> fC();

        //Additional functions

        std::vector<string> boundaryNames();
        
        std::vector<string> boundaryTypes(vector<string> sBoundary);
        
        std::vector<int> boundaryNFaces();

        std::vector<int> boundaryStartFace();

        std::vector<vector<int>> boundaryMesh();


        //map<string,vector<int>> boundariesWithFaces();
};
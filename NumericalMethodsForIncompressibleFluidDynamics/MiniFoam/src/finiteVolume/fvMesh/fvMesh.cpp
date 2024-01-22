
#include    "fvMesh.hpp"
#include    "../../math/operators.hpp"

//
//Default contructor
fvMesh::fvMesh()
:
    fvMeshPath_("constant/polyMesh"),
    nCells_(readNumberOfCellsFromOwnerFile()),
    pointList_(readPointsFromfvMesh()),
    ownerList_(readOwnerFromfvMesh()),
    neighbourList_(readNeighbourFromfvMesh()),
    faceList_(readFacesFromfvMesh()),
    boundaryList_(readBoundaryFromfvMesh()),
    //
    faceCentres_(calculateFaceCentres(pointList_, faceList_)),
    faceAreaVectors_(calculateFaceAreaVectors(pointList_,faceList_, faceCentres_)),
    faceAreaMagnitudes_(calculateMagSf(faceAreaVectors_)),
    faceNormals_(calculateFaceNormals(faceAreaVectors_, faceAreaMagnitudes_)),
    cellCentres_(calculateCellCentres(ownerList_,neighbourList_,faceCentres_)),
    cellVolumes_(calculateCellVolumes(ownerList_,neighbourList_,faceCentres_,faceAreaVectors_,cellCentres_))
    //
{
    cout << "Creating Mesh." << endl;
}

int fvMesh::readNumberOfCellsFromOwnerFile()
{
    filesystem::path path = fvMeshPath_/"owner";//


    ifstream file;
    file.open(path);
    int nCells;
    //haha
    if (!file) 
    {   
        cout << "Owner file is missing from the constant folder" << endl;
    }
    string line;
    while(getline(file, line))
    {
        if (line.find("note") != string::npos)
        {
            break;
        }
    }
    stringstream ss(line);
    string word;
    vector<string> notes;
    while (ss >> word)
    {
        notes.push_back(word);
    }
    for (int i = 0; i < notes.size(); i++)
    {
        if(notes[i] == "nCells:")
        {
            nCells = stoi(notes[i+1]);
            break;
        }
    }
    
    return nCells;
}

vector<vector<float>>fvMesh::readPointsFromfvMesh()
{
    vector<string> spoints = readInFoamFileAsVectorOfStrings(fvMeshPath_/"points");
    vector<vector<float>> points = convertVectorOfStringsIntoPoints(spoints);
    return points;
}

vector<int>fvMesh::readOwnerFromfvMesh()
{
    vector<string> sOwner = readInFoamFileAsVectorOfStrings(fvMeshPath_/"owner");
    vector<int> owner = convertVectorOfStringsIntoOwner(sOwner);
    return owner;
}

vector<int>fvMesh::readNeighbourFromfvMesh()
{
    vector<string> sNeighbour = readInFoamFileAsVectorOfStrings(fvMeshPath_/"neighbour");
    vector<int> neighbour = convertVectorOfStringsIntoNeighbour(sNeighbour);
    return neighbour;
}

vector<vector<int>> fvMesh::readFacesFromfvMesh()
{
    vector<string> sFaces = readInFoamFileAsVectorOfStrings(fvMeshPath_/"faces");
    vector<vector<int>> faces = convertVectorOfStringsIntoFaces(sFaces);
    return faces;
}

map<string,map<string, any>> fvMesh::readBoundaryFromfvMesh()
{
    vector<string> sBoundary = readInFoamFileAsVectorOfStrings(fvMeshPath_/"boundary");
    map<string,map<string, any>> boundary = convertVectorOfStringsIntoBoundary(sBoundary);
    return boundary;
}

vector<string> fvMesh::readInFoamFileAsVectorOfStrings(filesystem::path path)
{
    ifstream file;
    file.open(path);
    if (!file) 
    {   
        cout << "File missing from the fvMesh folder" << endl;
    }
    vector<string> spoints;
    string line;
    while(getline(file, line))
    {
        if( empty(line) || line.find("//") != string::npos )
        {
            continue;  
        }
        else
        {
            spoints.push_back(line);
        }
    }
    cleanFoamVectorOfStrings(spoints);
    return spoints;
}

void fvMesh::cleanFoamVectorOfStrings(vector<string>& spoints)
{
    if( spoints[0].find("/*") != string::npos)
    {
        spoints.erase( spoints.begin(), spoints.begin()+ 6 );
        if (spoints[0].find("FoamFile") != string::npos)
        {
            while(spoints[0].find("}") == string::npos)
            {
                spoints.erase( spoints.begin());
            }
            spoints.erase( spoints.begin());
        }
    }
    int nPoints = stoi(spoints[0]);
    spoints.erase(spoints.begin(),spoints.begin()+2);
    spoints.erase(spoints.end());
}

vector<vector<float>> fvMesh::convertVectorOfStringsIntoPoints(vector<string>spoints)
{
    vector<vector<float>> points;

    for (int i = 0; i < spoints.size(); i++)
    {
        spoints[i].erase(0,1);
        spoints[i].pop_back();
        stringstream ss(spoints[i]);
        string word;
        vector<float> point;
        while (ss >> word) 
        {   
            point.push_back(stof(word));
        }
        points.push_back(point); 
    }
    return points;
}

vector<int> fvMesh::convertVectorOfStringsIntoOwner(vector<string> sOwner)
{
    vector<int> owner;

    for (int i = 0; i < sOwner.size(); i++)
    {
        owner.push_back(stoi(sOwner[i]));
    }
    return owner;
}

vector<int> fvMesh::convertVectorOfStringsIntoNeighbour(vector<string> sNeighbour)
{
    vector<int> neighbour;

    for (int i = 0; i < sNeighbour.size(); i++)
    {
        neighbour.push_back(stoi(sNeighbour[i]));
    }
    return neighbour;
}

vector<vector<int>> fvMesh::convertVectorOfStringsIntoFaces(vector<string> sFaces)
{
    vector<vector<int>> faces;

    for (int i = 0; i < sFaces.size(); i++)
    {
        sFaces[i].erase(0,2);
        sFaces[i].pop_back();
        stringstream ss(sFaces[i]);
        string word;
        vector<int> points;
        while (ss >> word) 
        {   
            points.push_back(stoi(word));
        }
        faces.push_back(points);
    }
    return faces;
}

map<string, map<string, any>> fvMesh::convertVectorOfStringsIntoBoundary(vector<string> sBoundary)
{
    map<string, map<string,any>> boundary;

    std::vector<string> boundaryNames;
    vector<string> boundaryTypes;
    vector<int> boundaryNFaces;
    vector<int> boundaryStartFace;

    for (int i = 0; i<sBoundary.size(); i++)
    {
        if( i == sBoundary.size()-1)
        {
            break;
        }
        if( sBoundary[i+1].find("{") != string::npos )
        {
            stringstream ss(sBoundary[i]);
            string word;
            while(ss >> word)
            {
                boundaryNames.push_back(word);
            }
        }
        else if (sBoundary[i].find("type") != string::npos)
        {
            stringstream ss(sBoundary[i]);
            string word;
            while(ss >> word)
            {
                if(word != "type")
                {
                    word.pop_back();
                    boundaryTypes.push_back(word);                    
                }
            }
        }
        else if (sBoundary[i].find("nFaces") != string::npos)
        {
            stringstream ss(sBoundary[i]);
            string word;
            while(ss >> word)
            {
                if(word != "nFaces")
                {
                    word.pop_back();
                    boundaryNFaces.push_back(stoi(word));
                }
            }
        }
        else if (sBoundary[i].find("startFace") != string::npos)
        {
            stringstream ss(sBoundary[i]);
            string word;
            while(ss >> word)
            {
                if(word != "startFace")
                {
                    
                    word.pop_back();
                    boundaryStartFace.push_back(stoi(word));
                }
            }
        }
    }

    for (int i=0; i<boundaryNames.size();++i)
    {
        map<string,any> data;

        data["type"] = boundaryTypes[i];
        data["nFaces"] = boundaryNFaces[i];
        data["startFace"] = boundaryStartFace[i];
        boundary[boundaryNames[i]] = data;
    }

    for ( auto item : boundary )
    {
        //print out the name
        /*cout << item.first << " : "  << endl;

        //now print out all of the data about the person
        for ( auto data : item.second )
        {
            cout << data.first << " ";
            if(data.second.type() == typeid(int))
            {
                cout << any_cast<int>(data.second) << endl;
            }
            else
            {
                cout << any_cast<string>(data.second) << endl;
            }
        }
        */
    }
    return boundary;
}

vector<vector<float>> fvMesh::calculateFaceCentres(vector<vector<float>> pointList, vector<vector<int>> faceList)
{
    vector<vector<float>> faceCentres;
    for (auto&& faceI : faceList_)
    {
        int nPointsInFace = faceI.size();
        vector<float> faceCentre {0.0, 0.0, 0.0};
        for (auto&& pointI : faceI)
        {
            vector<float> coords = pointList_[pointI];
            transform(faceCentre.begin(), faceCentre.end(), coords.begin(), faceCentre.begin(), plus<float>());
        }
        //vector<float> faceCentre {0.0, 0.0, 0.0};
        transform(faceCentre.begin(), faceCentre.end(), faceCentre.begin(), [nPointsInFace]( float &element )
        {return element / nPointsInFace; });
        faceCentres.push_back(faceCentre);
    }
  /*  for (auto&& centre : faceCentres)
    {
        for (auto&& coord : centre)
        {
            cout << coord << "\t";
        }
        cout << endl; 
    }
    */
    return faceCentres;
}

vector<vector<float>> fvMesh::calculateFaceAreaVectors(vector<vector<float>> pointList, vector<vector<int>> faceList, vector<vector<float>> faceCentres)
{
    vector<vector<float>> Sf;
    for (int i = 0; i < faceList.size(); i++)
    {
        vector<float> SfI {0,0,0};
        for (int j = 0; j < faceList[i].size(); j++)
        {
            vector<float> p2;
            if( j == faceList[i].size()-1)
            {
                p2 = pointList[faceList[i][0]];
            }
            else
            {
                p2 = pointList[faceList[i][j+1]];
            }
            vector<float> p1 = pointList[faceList[i][j]];
            vector<float> v1 {0, 0, 0};
            vector<float> v2 {0, 0, 0};
            vector<float> c = faceCentres[i];

            transform(p2.begin(),p2.end(),p1.begin(),
            v1.begin(),(std::minus<float>()));
            transform(c.begin(),c.end(),p1.begin(),
            v2.begin(),(std::minus<float>()));
            auto StI = crossProduct(v1,v2);
            transform(StI.begin(),StI.end(),StI.begin(),[]( float &element )
            {return element * 0.5; });
            transform(SfI.begin(),SfI.end(),StI.begin(),
            SfI.begin(),(std::plus<float>()));
        }
        Sf.push_back(SfI);
    /*    for (auto i : SfI)
            cout << i << " ";
        cout << endl;*/
    }
    return Sf;
}

vector<float> fvMesh::calculateMagSf(vector<vector<float>> Sf)
{
    vector<float> magSf;
    for (auto&& SfI : Sf)
    {
        auto magSfI = mag(SfI);
        magSf.push_back(magSfI);
    }
    return magSf;
}

vector<vector<float>> fvMesh::calculateFaceNormals(vector<vector<float>> Sf, vector<float> magSf)
{
    vector<vector<float>> faceNormals;
    for( int i = 0; i < Sf.size(); i++ )
    {
        auto magSfI = magSf[i];
        vector<float> faceNormalI {0, 0, 0};
        transform(Sf[i].begin(), Sf[i].end(), faceNormalI.begin(),
        [&magSfI](float element){return element / magSfI;});
        faceNormals.push_back(faceNormalI);
       // cout << i << endl;
    }
    return faceNormals;
}

vector<vector<float>> fvMesh::calculateCellCentres (vector<int> owner, vector<int>neighbour, vector<vector<float>> fC)
{
    vector<vector<float>> cellCentres;
    for (int i = 0; i < nCells_; i++ )
    {
        vector<float> cellCentre {0,0,0};
        int nFacesInCell {0};
        for (int j = 0; j < owner.size(); j++ ) 
        {
            if(owner[j] == i)
            {
                ++nFacesInCell;
                vector<float> cC = fC[j];  
                transform(cellCentre.begin(),cellCentre.end(),
                cC.begin(), cellCentre.begin(), std::plus<float>());
            }
        }
        for (int j = 0; j < neighbour.size(); j++)
        {
            if(neighbour[j] == i)
            {
                ++nFacesInCell;
                vector<float> cC = fC[j];  
                transform(cellCentre.begin(),cellCentre.end(),
                cC.begin(), cellCentre.begin(), std::plus<float>());
            }
        }
        transform(cellCentre.begin(), cellCentre.end(),
        cellCentre.begin(), [&nFacesInCell](float &element)
        {return element / nFacesInCell;});
        cellCentres.push_back(cellCentre);
       // cout << nFacesInCell << endl;
   /*     for (auto cc : cellCentre)
        {
            cout << cc << " ";
        }
        cout << endl;
        //cout << i << " " << endl;*/
    }   
    return cellCentres;
}

vector<float> fvMesh::calculateCellVolumes(vector<int>& owner, vector<int>& neighbour, vector<vector<float>>& faceCentres,
vector<vector<float>>& Sf, vector<vector<float>>& cellCentres)
{
    vector<float> cellVolumes;
    for (int i = 0; i < nCells_; i++ )
    {
        float cellVolumeI {0};
        int nFacesInCell {0};
        for (int j = 0; j < owner.size(); j++ ) 
        {
            if(owner[j] == i)
            {
                ++nFacesInCell;
                vector<float> fC = faceCentres[j];
                vector<float> cC = cellCentres[i];
                vector<float> SfI = Sf[j];
                vector<float> centerDiff {0, 0, 0};  
                transform(fC.begin(),fC.end(),
                cC.begin(), centerDiff.begin(), std::minus<float>());
                //auto dot = dotProduct(centerDiff, SfI);
                cellVolumeI += dotProduct(centerDiff, SfI);
            }
        }
        for (int j = 0; j < neighbour.size(); j++)
        {
            if(neighbour[j] == i)
            {
                ++nFacesInCell;
                vector<float> fC = faceCentres[j];
                vector<float> cC = cellCentres[i];
                vector<float> SfI = Sf[j];
                vector<float> centerDiff {0, 0, 0};  
                transform(fC.begin(),fC.end(),
                cC.begin(), centerDiff.begin(), std::minus<float>());
                cellVolumeI += mag(dotProduct(centerDiff, SfI));
            }
        }
        //cout << nFacesInCell << endl;
        cellVolumes.push_back(cellVolumeI/3);
       // cout << cellVolumes[i] << endl;
    }   
    return cellVolumes;   
}

int fvMesh::nPoints()
{
    return pointList_.size();
}
int fvMesh::nFaces()
{
    return faceList_.size();
}
int fvMesh::nCells()
{
    return nCells_;
}
int fvMesh::nBoundaryPatches()
{
    return boundaryList_.size();
}
std::vector<float> fvMesh::V()
{
    return cellVolumes_;
};
std::vector<std::vector<float>> fvMesh::Sf()
{
    return faceAreaVectors_;
};
std::vector<std::vector<float>> fvMesh::fC()
{
    return faceCentres_;
};
std::vector<std::vector<float>> fvMesh::C()
{
    return cellCentres_;
};

std::vector<string> fvMesh::boundaryNames()
{
    map<string,map<string, any>> boundaryDict = boundaryList_;

    vector<string> boundaryNames;

    for (auto item : boundaryDict)
    {
        boundaryNames.push_back(item.first);
    }

    return boundaryNames;
}
std::vector<string> fvMesh::boundaryTypes(vector<string> sBoundary)
{
    std::vector<string> boundaryTypes;

    return boundaryTypes;
}
std::vector<int> fvMesh::boundaryNFaces()
{
    map<string,map<string, any>> boundaryDict = boundaryList_;

    std::vector<int> boundaryNFaces;

    for (auto item : boundaryDict)
    {
        //cout << item.first << endl;
        for ( auto data : item.second )
        {
            if(data.first == "nFaces")
            {
                boundaryNFaces.push_back(any_cast<int>(data.second));
            }
        }
    }

    return boundaryNFaces;
}
std::vector<int> fvMesh::boundaryStartFace()
{
    map<string,map<string, any>> boundaryDict = boundaryList_;

    //cout << "size " << boundaryDict.size();

    std::vector<int> boundaryStartFace;

    //int it = 0;

    for (auto item : boundaryDict)
    {
        for ( auto data : item.second )
        {
            if(data.first == "startFace")
            {
                //cout << any_cast<int>(data.second) << endl;
                boundaryStartFace.push_back(any_cast<int>(data.second));
                //it += 1;
                //cout << it << endl;
            }
        }
    }

    //for(int i = 0 ; i < boundaryStartFace.size(); i++)
    //{
    //    cout << boundaryStartFace[i] << endl;
    //}

    //cout << "size " << boundaryStartFace.size();

    return boundaryStartFace;
}
std::vector<vector<int>> fvMesh::boundaryMesh()
{
    std::vector<std::vector<int>> boundaryMesh;

    std::vector<int> boundaryNFaces = this->boundaryNFaces();

    std::vector<int> boundaryStartFace = this->boundaryStartFace();

    for (int i = 0; i < boundaryNFaces.size(); i++)
    { 
        boundaryMesh.emplace_back(std::vector<int>(boundaryNFaces[i]));

        //cout << patch.size();

        for (int j = 0; j < boundaryNFaces[i]; j++)
        {
            boundaryMesh[i][j] = boundaryStartFace[i] + j;
            //cout << boundaryStartFace[i] + j << endl;
           // cout << patch[j] << " ";
        }
        //cout << endl;
    }

    return boundaryMesh;
}
